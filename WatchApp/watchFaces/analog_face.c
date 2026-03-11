/*
 * Optimized analog watch face with fully precomputed geometry
 * Immediate-mode drawing, minimal runtime math
 */

#include "analog_face.h"
#include "watch_face_geometry.h"
#include "watch_face_common.h"
#include "../shared/fast_math.h"
#include "../shared/watch_state.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include <string.h>

// ============================================================================
// CONFIGURATION
// ============================================================================

#define MARKER_MAJOR_WIDTH  3
#define MARKER_MINOR_WIDTH  1
/* Delay (in second indices) before restoring thick elements crossed by second hand. */
#define SECOND_RESTORE_DELAY_STEPS 2U
#define HOUR_HAND_W 3U
#define MIN_HAND_W 2U
#define SEC_HAND_W 1U

#define ANALOG_DATE_X  33
#define ANALOG_DATE_Y  88


#define CENTER_DOT_RADIUS  2

// ============================================================================
// STATE
// ============================================================================

static uint8_t s_last_hour = CACHE_INVALID_U8;
static uint8_t s_last_min = CACHE_INVALID_U8;
static uint8_t s_last_sec = CACHE_INVALID_U8;
static Date_t s_last_date_drawn;
static bool s_last_alarm_drawn;

static void draw_markers(void) {
    for (uint8_t i = 0; i < 12; i++) {
        uint8_t idx = FastMath_Mul5U8(i);
        uint8_t width = (i == 0 || i == 3 || i == 6 || i == 9) ? MARKER_MAJOR_WIDTH : MARKER_MINOR_WIDTH;
        oledC_DrawLine(HOUR_POINTS[idx][0], HOUR_POINTS[idx][1],
                MIN_POINTS[idx][0], MIN_POINTS[idx][1],
                width,
                COLOR_DIM);
    }
    oledC_DrawRing(CENTER_X, CENTER_Y, RADIUS, 1, COLOR_DIM);
}

static void draw_hand(const int8_t points[][2], uint8_t idx, uint8_t width, uint16_t color) {
    oledC_DrawLine(CENTER_X, CENTER_Y, points[idx][0], points[idx][1], width, color);
}

static void erase_hand(const int8_t points[][2], uint8_t idx, uint8_t width) {
    draw_hand(points, idx, width, COLOR_BG);
}

static int8_t step_toward_zero_i8(int8_t v) {
    if (v > 0) return (int8_t)(v - 1);
    if (v < 0) return (int8_t)(v + 1);
    return 0;
}

/* Draw second hand slightly inset so it does not cut through the outer ring. */
static void draw_second_hand(uint8_t idx, uint16_t color) {
    int8_t dx = (int8_t)(SEC_POINTS[idx][0] - CENTER_X);
    int8_t dy = (int8_t)(SEC_POINTS[idx][1] - CENTER_Y);
    dx = step_toward_zero_i8(dx);
    dy = step_toward_zero_i8(dy);
    oledC_DrawLine(CENTER_X, CENTER_Y,
                   (uint8_t)(CENTER_X + dx),
                   (uint8_t)(CENTER_Y + dy),
                   SEC_HAND_W,
                   color);
}

static void erase_second_hand(uint8_t idx) {
    draw_second_hand(idx, COLOR_BG);
}

static void draw_center_dot(void) {
    oledC_DrawCircle(CENTER_X, CENTER_Y, CENTER_DOT_RADIUS, COLOR_ACCENT);
}

static void draw_all_hands(uint8_t hour, uint8_t min, uint8_t sec) {
    draw_hand(HOUR_POINTS, hour, HOUR_HAND_W, COLOR_SECONDARY);
    draw_hand(MIN_POINTS, min, MIN_HAND_W, COLOR_PRIMARY);
    draw_second_hand(sec, COLOR_ACCENT);
    draw_center_dot();
}

static void draw_hands_full(uint8_t hour, uint8_t min, uint8_t sec) {
    draw_all_hands(hour, min, sec);

    s_last_hour = hour;
    s_last_min = min;
    s_last_sec = sec;
}

static void draw_marker_at(uint8_t sec_idx) {
    if (FastMath_Mod5U8(sec_idx) != 0U) return;
    uint8_t marker_idx = sec_idx;
    uint8_t width = (marker_idx == 0 || marker_idx == 15 || marker_idx == 30 || marker_idx == 45)
        ? MARKER_MAJOR_WIDTH
        : MARKER_MINOR_WIDTH;
    oledC_DrawLine(HOUR_POINTS[marker_idx][0], HOUR_POINTS[marker_idx][1],
                   MIN_POINTS[marker_idx][0], MIN_POINTS[marker_idx][1],
                   width,
                   COLOR_DIM);
}

static inline bool is_cardinal_idx(uint8_t idx) {
    return (idx == 0U || idx == 15U || idx == 30U || idx == 45U);
}

static inline uint8_t sec_idx_sub_delay(uint8_t sec_idx) {
    return FastMath_SubMod60U8(sec_idx, SECOND_RESTORE_DELAY_STEPS);
}

static void restore_thick_elements_at(uint8_t sec_idx, uint8_t hour_idx, uint8_t min_idx) {
    if (is_cardinal_idx(sec_idx)) {
        draw_marker_at(sec_idx);
    }
    if (sec_idx == hour_idx) {
        draw_hand(HOUR_POINTS, hour_idx, HOUR_HAND_W, COLOR_SECONDARY);
    }
    if (sec_idx == min_idx) {
        draw_hand(MIN_POINTS, min_idx, MIN_HAND_W, COLOR_PRIMARY);
    }
}

static uint8_t compute_hour_idx(uint8_t hour, uint8_t min) {
    uint8_t hour12 = (hour >= 12U) ? (uint8_t)(hour - 12U) : hour;
    uint8_t minute_bucket = 0U;
    if (min >= 12U) minute_bucket = 1U;
    if (min >= 24U) minute_bucket = 2U;
    if (min >= 36U) minute_bucket = 3U;
    if (min >= 48U) minute_bucket = 4U;
    return (uint8_t)(FastMath_Mul5U8(hour12) + minute_bucket);
}

static void draw_hands(uint8_t hour, uint8_t min, uint8_t sec) {
    bool hour_changed = (s_last_hour != hour);
    bool min_changed = (s_last_min != min);
    bool sec_changed = (s_last_sec != sec);

    if (s_last_hour == CACHE_INVALID_U8 || s_last_min == CACHE_INVALID_U8 || s_last_sec == CACHE_INVALID_U8) {
        hour_changed = min_changed = sec_changed = true;
    }

    if (sec_changed && !hour_changed && !min_changed) {
        uint8_t old_sec = s_last_sec;
        erase_second_hand(s_last_sec);

        if (FastMath_Mod5U8(old_sec) == 0U && !is_cardinal_idx(old_sec)) {
            draw_marker_at(old_sec);
        }

        restore_thick_elements_at(sec_idx_sub_delay(sec), hour, min);
        draw_second_hand(sec, COLOR_ACCENT);
        draw_center_dot();
    } else {
        if (hour_changed && s_last_hour != CACHE_INVALID_U8) erase_hand(HOUR_POINTS, s_last_hour, HOUR_HAND_W);
        if (min_changed && s_last_min != CACHE_INVALID_U8) erase_hand(MIN_POINTS, s_last_min, MIN_HAND_W);
        if (sec_changed && s_last_sec != CACHE_INVALID_U8) erase_second_hand(s_last_sec);

        if (hour_changed || min_changed || sec_changed) {
            draw_markers();
        }

        draw_all_hands(hour, min, sec);
    }

    s_last_hour = hour;
    s_last_min = min;
    s_last_sec = sec;
}

// ============================================================================
// PUBLIC API
// ============================================================================

void AnalogFace_Init(void) {
    oledC_setBackground(COLOR_BG);
    memset(&s_last_date_drawn, 0, sizeof(Date_t));

    draw_markers();

    WatchState_t* state = Watch_GetState();
    WatchFace_DrawDate(ANALOG_DATE_X, ANALOG_DATE_Y, &state->current_date, &s_last_date_drawn, COLOR_DIM, COLOR_BG);
    s_last_alarm_drawn = state->alarm.enabled;
    WatchFace_DrawAlarmIcon(ALARM_X, ALARM_Y, ALARM_W, ALARM_H, s_last_alarm_drawn);

    s_last_hour = s_last_min = s_last_sec = CACHE_INVALID_U8;
}

void AnalogFace_DrawUpdate(void) {
    WatchState_t* s = Watch_GetState();

    uint8_t sec = s->current_time.second;
    uint8_t min = s->current_time.minute;
    uint8_t hour = compute_hour_idx(s->current_time.hour, min);

    draw_hands(hour, min, sec);
    if (s->alarm.enabled != s_last_alarm_drawn) {
        WatchFace_DrawAlarmIcon(ALARM_X, ALARM_Y, ALARM_W, ALARM_H, s->alarm.enabled);
        s_last_alarm_drawn = s->alarm.enabled;
    }
    WatchFace_DrawDate(ANALOG_DATE_X, ANALOG_DATE_Y, &s->current_date, &s_last_date_drawn, COLOR_DIM, COLOR_BG);
}

void AnalogFace_Draw(void) {
    WatchState_t* state = Watch_GetState();

    oledC_setBackground(COLOR_BG);
    draw_markers();

    uint8_t sec = state->current_time.second;
    uint8_t min = state->current_time.minute;
    uint8_t hour = compute_hour_idx(state->current_time.hour, min);
    draw_hands_full(hour, min, sec);

    s_last_date_drawn.day = 0;
    s_last_date_drawn.month = 0;
    WatchFace_DrawDate(ANALOG_DATE_X, ANALOG_DATE_Y, &state->current_date, &s_last_date_drawn, COLOR_DIM, COLOR_BG);
    WatchFace_DrawAlarmIcon(ALARM_X, ALARM_Y, ALARM_W, ALARM_H, state->alarm.enabled);
    s_last_alarm_drawn = state->alarm.enabled;
}
