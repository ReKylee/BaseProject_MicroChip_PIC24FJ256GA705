/*
 * analog_face.c
 * Optimized analog watch face with fully precomputed geometry
 * Immediate-mode drawing, minimal runtime math
 */

#include "analog_face.h"
#include "watch_face_geometry.h"
#include "watch_face_common.h"
#include "../shared/watch_state.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include <stdio.h>
#include <string.h>

// ============================================================================
// CONFIGURATION
// ============================================================================

// Marker widths for main (3,6,9,12) vs minor markers
#define MARKER_MAJOR_WIDTH  3
#define MARKER_MINOR_WIDTH  1

// Date position
#define ANALOG_DATE_X  33
#define ANALOG_DATE_Y  88

// Alarm icon position
// #define ALARM_X  88
// #define ALARM_Y  5
// #define ALARM_W  5
// #define ALARM_H  5

// Center dot
#define CENTER_DOT_RADIUS  2

// ============================================================================
// STATE
// ============================================================================

static uint8_t s_last_hour = 255;
static uint8_t s_last_min = 255;
static uint8_t s_last_sec = 255;
static Date_t s_last_date_drawn;

static void draw_markers(void) {
    for (uint8_t i = 0; i < 12; i++) {
        uint8_t idx = i * 5;
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

static void draw_marker_at(uint8_t sec_idx) {
    if ((sec_idx % 5) != 0) return;
    uint8_t marker_idx = sec_idx;
    uint8_t width = (marker_idx == 0 || marker_idx == 15 || marker_idx == 30 || marker_idx == 45)
        ? MARKER_MAJOR_WIDTH
        : MARKER_MINOR_WIDTH;
    oledC_DrawLine(HOUR_POINTS[marker_idx][0], HOUR_POINTS[marker_idx][1],
                   MIN_POINTS[marker_idx][0], MIN_POINTS[marker_idx][1],
                   width,
                   COLOR_DIM);
}

static void restore_after_second(uint8_t old_sec, uint8_t hour_idx, uint8_t min_idx) {
    if (old_sec == 255) return;
    erase_hand(SEC_POINTS, old_sec, 1);
    draw_marker_at(old_sec);
    oledC_DrawRing(CENTER_X, CENTER_Y, RADIUS, 1, COLOR_DIM);
    if (old_sec == s_last_hour) {
        draw_hand(HOUR_POINTS, hour_idx, 3, COLOR_SECONDARY);
    }
    if (old_sec == s_last_min) {
        draw_hand(MIN_POINTS, min_idx, 2, COLOR_PRIMARY);
    }
}

static uint8_t compute_hour_idx(uint8_t hour, uint8_t min) {
    return (uint8_t)((hour % 12) * 5 + min / 12);
}

static void draw_hands(uint8_t hour, uint8_t min, uint8_t sec) {
    bool hour_changed = (s_last_hour != hour);
    bool min_changed = (s_last_min != min);
    bool sec_changed = (s_last_sec != sec);

    if (s_last_hour == 255 || s_last_min == 255 || s_last_sec == 255) {
        hour_changed = min_changed = sec_changed = true;
    }

    if (sec_changed && !hour_changed && !min_changed) {
        restore_after_second(s_last_sec, hour, min);
        draw_hand(SEC_POINTS, sec, 1, COLOR_ACCENT);
    } else {
        // Erase only the hands that changed so we don't wipe other hands.
        if (hour_changed && s_last_hour != 255) erase_hand(HOUR_POINTS, s_last_hour, 3);
        if (min_changed && s_last_min != 255) erase_hand(MIN_POINTS, s_last_min, 2);
        if (sec_changed && s_last_sec != 255) erase_hand(SEC_POINTS, s_last_sec, 1);

        // Restore markers and ring after erasing.
        if (hour_changed || min_changed || sec_changed) {
            draw_markers();
        }

        // Redraw all current hands to restore any erased overlap.
        draw_hand(HOUR_POINTS, hour, 3, COLOR_SECONDARY);
        draw_hand(MIN_POINTS, min, 2, COLOR_PRIMARY);
        draw_hand(SEC_POINTS, sec, 1, COLOR_ACCENT);
    }

    // Redraw center dot to hide joins.
    oledC_DrawCircle(CENTER_X, CENTER_Y, CENTER_DOT_RADIUS, COLOR_ACCENT);

    s_last_hour = hour;
    s_last_min = min;
    s_last_sec = sec;
}

// ============================================================================
// PUBLIC API
// ============================================================================

void AnalogFace_Init(void) {
    oledC_setBackground(COLOR_BG);
    memset(&s_last_date_drawn, 0, sizeof(Date_t)); // Initialize last_date_drawn

    draw_markers();

    // Date - Initial draw
    WatchState_t* state = Watch_GetState();
    WatchFace_DrawDate(ANALOG_DATE_X, ANALOG_DATE_Y, &state->current_date, &s_last_date_drawn, COLOR_DIM, COLOR_BG);

    // Reset hand state
    s_last_hour = s_last_min = s_last_sec = 255;
}

void AnalogFace_DrawUpdate(void) {
    WatchState_t* s = Watch_GetState();

    uint8_t sec = s->current_time.second;
    uint8_t min = s->current_time.minute;
    uint8_t hour = compute_hour_idx(s->current_time.hour, min);

    draw_hands(hour, min, sec);
    WatchFace_DrawAlarmIcon(ALARM_X, ALARM_Y, ALARM_W, ALARM_H, s->alarm.enabled);
    WatchFace_DrawDate(ANALOG_DATE_X, ANALOG_DATE_Y, &s->current_date, &s_last_date_drawn, COLOR_DIM, COLOR_BG);
}

void AnalogFace_Draw(void) {
    AnalogFace_DrawUpdate();
}
