/*
 * Arc-themed digital watch face with incremental second trail
 */

#include "digital_face.h"
#include "watch_face_geometry.h"
#include "watch_face_common.h"
#include "../shared/watch_state.h"
#include "../shared/ui_layout.h"
#include "../shared/watch_ui_widgets.h"
#include "../watchCore/timekeeper.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// ============================================================================
// LAYOUT
// ============================================================================

#define SCREEN_W                96U

#define DIGITAL_TIME_Y          24U
#define DIGITAL_TIME_SCALE_X    3U
#define DIGITAL_TIME_SCALE_Y    3U

#define DIGITAL_SECONDS_Y       53U
#define DIGITAL_SECONDS_SCALE   2U

#define DIGITAL_DATE_X          33U
#define DIGITAL_DATE_Y          4U

#define DIGITAL_AMPM_X          6U
#define DIGITAL_AMPM_Y          4U

#define DIGITAL_BASE_LINE_W     2U
#define DIGITAL_TOTAL_STEPS      60U
#define DIGITAL_ARC_START_IDX    15U
#define DIGITAL_ARC_Y_OFFSET     5U

// ============================================================================
// STATE
// ============================================================================

static Time_t s_last_time_drawn;
static Date_t s_last_date_drawn;
static bool s_last_alarm_drawn;
static TimeFormat_t s_last_format_drawn;
static bool s_last_is_pm;

static uint8_t s_last_progress_count;

// ============================================================================
// PRIVATE HELPERS
// ============================================================================

static void clear_ampm_area(void) {
    oledC_DrawRectangle((uint8_t)(DIGITAL_AMPM_X - 1U), (uint8_t)(DIGITAL_AMPM_Y - 1U),
                        (uint8_t)(DIGITAL_AMPM_X + 14U), (uint8_t)(DIGITAL_AMPM_Y + 9U),
                        COLOR_BG);
}

static void draw_ampm(bool is_pm) {
    clear_ampm_area();
    oledC_DrawStringSolid(DIGITAL_AMPM_X, DIGITAL_AMPM_Y, 1U, 1U,
                          (uint8_t*)(is_pm ? "PM" : "AM"),
                          COLOR_SECONDARY, COLOR_BG);
}

static void draw_top_meta(const WatchState_t* state, bool is_pm) {
    WatchFace_DrawDate(DIGITAL_DATE_X, DIGITAL_DATE_Y,
                       &state->current_date, &s_last_date_drawn,
                       COLOR_DIM, COLOR_BG);

    if (state->time_format == FORMAT_12H) {
        draw_ampm(is_pm);
    } else {
        clear_ampm_area();
    }

    WatchFace_DrawAlarmIcon(ALARM_X, ALARM_Y, ALARM_W, ALARM_H, state->alarm.enabled);
    s_last_alarm_drawn = state->alarm.enabled;
}

static void get_big_time_layout(WatchUi_DualTimeLayout_t* layout) {
    WatchUi_ComputeDualTimeLayout(SCREEN_W, 2U, 2U,
                                  DIGITAL_TIME_SCALE_X, DIGITAL_TIME_SCALE_X, DIGITAL_TIME_SCALE_X,
                                  5U, 1U, 1U, layout);
}

static void draw_big_time(uint8_t hour, uint8_t minute) {
    WatchUi_DualTimeLayout_t layout;
    get_big_time_layout(&layout);

    WatchUi_DrawNN(hour, layout.left_x, DIGITAL_TIME_Y,
                   DIGITAL_TIME_SCALE_X, DIGITAL_TIME_SCALE_Y,
                   COLOR_PRIMARY, COLOR_BG);

    WatchUi_DrawColon(layout.colon_x, DIGITAL_TIME_Y,
                      DIGITAL_TIME_SCALE_X, DIGITAL_TIME_SCALE_Y,
                      COLOR_PRIMARY, COLOR_BG);

    WatchUi_DrawNN(minute, layout.right_x, DIGITAL_TIME_Y,
                   DIGITAL_TIME_SCALE_X, DIGITAL_TIME_SCALE_Y,
                   COLOR_PRIMARY, COLOR_BG);
}

static void draw_seconds_value(uint8_t second) {
    uint8_t sec_w = WatchUi_TextWidth(2U, 5U, DIGITAL_SECONDS_SCALE, 1U);
    uint8_t sec_x = WatchUi_CenterX96(sec_w);
    WatchUi_DrawNN(second, sec_x, DIGITAL_SECONDS_Y,
                   DIGITAL_SECONDS_SCALE, DIGITAL_SECONDS_SCALE,
                   COLOR_ACCENT, COLOR_BG);
}

static void progress_step_xy(uint8_t step, uint8_t* x, uint8_t* y) {
    uint8_t clamped = (step >= DIGITAL_TOTAL_STEPS) ? (DIGITAL_TOTAL_STEPS - 1U) : step;
    uint8_t k = (uint8_t)(clamped >> 1); // 0..29, no division
    uint8_t i0 = (uint8_t)(DIGITAL_ARC_START_IDX + k);      // 15..44
    uint8_t i1 = (uint8_t)(i0 + 1U);                        // 16..45
    uint8_t x0 = (uint8_t)SEC_POINTS[i0][0];
    uint8_t y0 = (uint8_t)SEC_POINTS[i0][1];

    if ((clamped & 1U) == 0U) {
        *x = x0;
        *y = (uint8_t)(y0 + DIGITAL_ARC_Y_OFFSET);
        return;
    }

    uint8_t x1 = (uint8_t)SEC_POINTS[i1][0];
    uint8_t y1 = (uint8_t)SEC_POINTS[i1][1];
    *x = (uint8_t)((x0 + x1) >> 1);
    *y = (uint8_t)(((uint8_t)((y0 + y1) >> 1)) + DIGITAL_ARC_Y_OFFSET);
}

static void draw_step_point(uint8_t step, uint16_t color) {
    uint8_t x;
    uint8_t y;
    progress_step_xy(step, &x, &y);
    oledC_DrawCircle(x, y, 1U, color);
}

static void draw_step_segment(uint8_t from_step, uint8_t to_step, uint16_t color) {
    uint8_t x0;
    uint8_t y0;
    uint8_t x1;
    uint8_t y1;
    progress_step_xy(from_step, &x0, &y0);
    progress_step_xy(to_step, &x1, &y1);
    oledC_DrawLine(x0, y0, x1, y1, DIGITAL_BASE_LINE_W, color);
}

static void draw_frame(void) {
    draw_step_point(0U, COLOR_DIM);
    for (uint8_t i = 1U; i < DIGITAL_TOTAL_STEPS; i++) {
        draw_step_segment((uint8_t)(i - 1U), i, COLOR_DIM);
    }
}

static void draw_progress_to_count(uint8_t count) {
    if (count > DIGITAL_TOTAL_STEPS) {
        count = DIGITAL_TOTAL_STEPS;
    }

    if (count == 0U) {
        s_last_progress_count = 0U;
        return;
    }

    draw_step_point(0U, COLOR_PRIMARY);
    for (uint8_t i = 1U; i < count; i++) {
        draw_step_segment((uint8_t)(i - 1U), i, COLOR_PRIMARY);
    }

    if (count == 1U) {
        draw_step_point(0U, COLOR_ACCENT);
    } else {
        uint8_t hx;
        uint8_t hy;
        progress_step_xy((uint8_t)(count - 1U), &hx, &hy);
        oledC_DrawCircle(hx, hy, 2U, COLOR_ACCENT);
    }

    s_last_progress_count = count;
}

static void update_progress_from_second(uint8_t second) {
    uint8_t target = (uint8_t)(second + 1U);

    if (s_last_progress_count == CACHE_INVALID_U8) {
        draw_progress_to_count(target);
        return;
    }

    if (target < s_last_progress_count) {
        draw_frame();
        draw_progress_to_count(target);
        return;
    }

    if (target == s_last_progress_count) {
        return;
    }

    if (s_last_progress_count > 0U) {
        uint8_t px;
        uint8_t py;
        progress_step_xy((uint8_t)(s_last_progress_count - 1U), &px, &py);
        oledC_DrawCircle(px, py, 2U, COLOR_PRIMARY);

        if (s_last_progress_count == 1U) {
            draw_step_point(0U, COLOR_PRIMARY);
        } else {
            draw_step_segment((uint8_t)(s_last_progress_count - 2U),
                              (uint8_t)(s_last_progress_count - 1U),
                              COLOR_PRIMARY);
        }
    }

    if (s_last_progress_count == 0U && target > 0U) {
        draw_step_point(0U, COLOR_PRIMARY);
    }

    uint8_t i_start = (s_last_progress_count < 1U) ? 1U : s_last_progress_count;
    for (uint8_t i = i_start; i < target; i++) {
        draw_step_segment((uint8_t)(i - 1U), i, COLOR_PRIMARY);
    }

    if (target == 1U) {
        draw_step_point(0U, COLOR_ACCENT);
    } else {
        uint8_t hx;
        uint8_t hy;
        progress_step_xy((uint8_t)(target - 1U), &hx, &hy);
        oledC_DrawCircle(hx, hy, 2U, COLOR_ACCENT);
    }
    s_last_progress_count = target;
}

static uint8_t get_display_hour(const WatchState_t* state, bool* is_pm) {
    if (state->time_format == FORMAT_12H) {
        return Timekeeper_Convert24to12(state->current_time.hour, is_pm);
    }

    *is_pm = false;
    return state->current_time.hour;
}

// ============================================================================
// PUBLIC API
// ============================================================================

void DigitalFace_Init(void) {
    oledC_setBackground(COLOR_BG);

    memset(&s_last_time_drawn, 0, sizeof(Time_t));
    memset(&s_last_date_drawn, 0, sizeof(Date_t));

    s_last_time_drawn.second = CACHE_INVALID_U8;
    s_last_format_drawn = FORMAT_24H;
    s_last_alarm_drawn = false;
    s_last_is_pm = false;
    s_last_progress_count = CACHE_INVALID_U8;
}

void DigitalFace_Draw(void) {
    WatchState_t* state = Watch_GetState();
    bool is_pm = false;
    uint8_t hour = get_display_hour(state, &is_pm);

    oledC_setBackground(COLOR_BG);

    s_last_date_drawn.day = 0U;
    s_last_date_drawn.month = 0U;

    draw_frame();
    draw_big_time(hour, state->current_time.minute);
    draw_seconds_value(state->current_time.second);
    draw_top_meta(state, is_pm);
    draw_progress_to_count((uint8_t)(state->current_time.second + 1U));

    s_last_time_drawn = state->current_time;
    s_last_date_drawn = state->current_date;
    s_last_format_drawn = state->time_format;
    s_last_is_pm = is_pm;
}

void DigitalFace_DrawUpdate(void) {
    WatchState_t* state = Watch_GetState();
    bool is_pm = false;
    uint8_t hour = get_display_hour(state, &is_pm);

    if (state->time_format != s_last_format_drawn) {
        DigitalFace_Draw();
        return;
    }

    if (state->current_time.hour != s_last_time_drawn.hour) {
        draw_big_time(hour, state->current_time.minute);
    } else if (state->current_time.minute != s_last_time_drawn.minute) {
        draw_big_time(hour, state->current_time.minute);
    }

    if (state->current_time.second != s_last_time_drawn.second) {
        draw_seconds_value(state->current_time.second);
        update_progress_from_second(state->current_time.second);
    }

    if (state->time_format == FORMAT_12H && is_pm != s_last_is_pm) {
        draw_ampm(is_pm);
        s_last_is_pm = is_pm;
    }

    WatchFace_DrawDate(DIGITAL_DATE_X, DIGITAL_DATE_Y,
                       &state->current_date, &s_last_date_drawn,
                       COLOR_DIM, COLOR_BG);

    if (state->alarm.enabled != s_last_alarm_drawn) {
        WatchFace_DrawAlarmIcon(ALARM_X, ALARM_Y, ALARM_W, ALARM_H, state->alarm.enabled);
        s_last_alarm_drawn = state->alarm.enabled;
    }

    s_last_time_drawn = state->current_time;
    s_last_date_drawn = state->current_date;
}
