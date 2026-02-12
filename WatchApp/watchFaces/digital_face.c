/*
 * Optimized digital watch face with partial updates
 */

#include "digital_face.h"
#include "../shared/watch_state.h"
#include "../shared/watch_types.h"
#include "../watchCore/timekeeper.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "watch_face_common.h" // Include common drawing functions

// ============================================================================
// CONFIG
// ============================================================================

#define TIME_SCALE_X    3
#define TIME_SCALE_Y    4
#define TIME_Y          18
#define SCREEN_W        96
#define FONT_W          5
#define FONT_SPACING    1

#define SECONDS_Y       56
#define AMPM_Y          6
#define DATE_Y_BOTTOM   76

// ============================================================================
// STATE
// ============================================================================

static Time_t s_last_time_drawn;
static Date_t s_last_date_drawn;
static bool s_last_alarm_drawn;
static TimeFormat_t s_last_format_drawn;

// ============================================================================
// PRIVATE HELPERS
// ============================================================================

static void format_2d(uint8_t value, char out[3]) {
    out[0] = (char)('0' + (value / 10));
    out[1] = (char)('0' + (value % 10));
    out[2] = '\0';
}

static void draw_time_digits(uint8_t value, uint8_t x, uint8_t y, uint16_t color, uint8_t scale_x, uint8_t scale_y) {
    char buf[3];
    format_2d(value, buf);
    oledC_DrawString(x, y, scale_x, scale_y, (uint8_t*)buf, color);
}

static void draw_seconds(uint8_t value, uint16_t color) {
    char buf[3];
    format_2d(value, buf);
    uint8_t text_w = (uint8_t)(2 * (FONT_W + FONT_SPACING));
    uint8_t x = (uint8_t)((SCREEN_W - text_w) / 2);
    oledC_DrawString(x, SECONDS_Y, 1, 1, (uint8_t*)buf, color);
}

static void draw_ampm(bool is_pm, uint16_t color) {
    uint8_t text_w = (uint8_t)(2 * (FONT_W + FONT_SPACING));
    uint8_t x = (uint8_t)((SCREEN_W - text_w) / 2);
    oledC_DrawString(x, AMPM_Y, 1, 1, (uint8_t*)(is_pm ? "PM" : "AM"), color);
}

static uint8_t time_text_width(void) {
    // "HH:MM" -> 5 chars
    return (uint8_t)(5 * (FONT_W * TIME_SCALE_X + FONT_SPACING));
}

// ============================================================================
// PUBLIC API
// ============================================================================

void DigitalFace_Init(void) {
    oledC_setBackground(COLOR_BG);
    memset(&s_last_time_drawn, 0, sizeof(Time_t));
    memset(&s_last_date_drawn, 0, sizeof(Date_t));
    s_last_time_drawn.second = 255; // force initial draw
    s_last_format_drawn = FORMAT_24H;
    s_last_alarm_drawn = false;
}

void DigitalFace_Draw(void) {
    oledC_setBackground(COLOR_BG);
    WatchState_t* state = Watch_GetState();
    uint8_t hour = state->current_time.hour;
    bool is_pm = false;

    if (state->time_format == FORMAT_12H) {
        hour = Timekeeper_Convert24to12(hour, &is_pm);
    }

    // Time
    uint8_t time_w = time_text_width();
    uint8_t time_x = (uint8_t)((SCREEN_W - time_w) / 2);
    uint8_t hour_x = time_x;
    uint8_t colon_x = (uint8_t)(hour_x + 2 * (FONT_W * TIME_SCALE_X + FONT_SPACING));
    uint8_t min_x = (uint8_t)(colon_x + (FONT_W * TIME_SCALE_X + FONT_SPACING));

    draw_time_digits(hour, hour_x, TIME_Y, COLOR_PRIMARY, TIME_SCALE_X, TIME_SCALE_Y);
    oledC_DrawString(colon_x, TIME_Y, TIME_SCALE_X, TIME_SCALE_Y, (uint8_t*)":", COLOR_PRIMARY);
    draw_time_digits(state->current_time.minute, min_x, TIME_Y, COLOR_PRIMARY, TIME_SCALE_X, TIME_SCALE_Y);
    draw_seconds(state->current_time.second, COLOR_DIM);

    // Date
    s_last_date_drawn.day = 0;
    uint8_t date_text_w = (uint8_t)(5 * (FONT_W + FONT_SPACING));
    uint8_t date_x = (uint8_t)((SCREEN_W - date_text_w) / 2);
    WatchFace_DrawDate(date_x, DATE_Y_BOTTOM, &state->current_date, &s_last_date_drawn, COLOR_DIM, COLOR_BG);

    // AM/PM
    if (state->time_format == FORMAT_12H) {
        draw_ampm(is_pm, COLOR_SECONDARY);
    }

    // Alarm
    WatchFace_DrawAlarmIcon(ALARM_X, ALARM_Y, ALARM_W, ALARM_H, state->alarm.enabled);

    // Save state
    s_last_time_drawn = state->current_time;
    s_last_date_drawn = state->current_date;
    s_last_alarm_drawn = state->alarm.enabled;
    s_last_format_drawn = state->time_format;
   
}

void DigitalFace_DrawUpdate(void) {
    WatchState_t* state = Watch_GetState();
    Time_t now = state->current_time;
    Date_t today = state->current_date;

    bool needs_hour_update = false;
    bool is_pm = false;
    uint8_t current_hour_12 = now.hour;

    if (state->time_format == FORMAT_12H) {
        current_hour_12 = Timekeeper_Convert24to12(now.hour, &is_pm);
    }

    // Redraw everything if format changed
    if (state->time_format != s_last_format_drawn) {
        DigitalFace_Draw();
        return;
    }

    // Seconds
    if (now.second != s_last_time_drawn.second) {
        draw_seconds(s_last_time_drawn.second, COLOR_BG);
        draw_seconds(now.second, COLOR_DIM);
    }

    // Minutes
    uint8_t time_w = time_text_width();
    uint8_t time_x = (uint8_t)((SCREEN_W - time_w) / 2);
    uint8_t hour_x = time_x;
    uint8_t colon_x = (uint8_t)(hour_x + 2 * (FONT_W * TIME_SCALE_X + FONT_SPACING));
    uint8_t min_x = (uint8_t)(colon_x + (FONT_W * TIME_SCALE_X + FONT_SPACING));

    if (now.minute != s_last_time_drawn.minute) {
        draw_time_digits(s_last_time_drawn.minute, min_x, TIME_Y, COLOR_BG, TIME_SCALE_X, TIME_SCALE_Y);
        draw_time_digits(now.minute, min_x, TIME_Y, COLOR_PRIMARY, TIME_SCALE_X, TIME_SCALE_Y);
    }

    // Hours
    uint8_t last_hour_12 = s_last_time_drawn.hour;
    bool last_is_pm = false;
    if (state->time_format == FORMAT_12H) {
        last_hour_12 = Timekeeper_Convert24to12(s_last_time_drawn.hour, &last_is_pm);
        if (current_hour_12 != last_hour_12) needs_hour_update = true;
        if (is_pm != last_is_pm) {
            draw_ampm(!is_pm, COLOR_BG);
            draw_ampm(is_pm, COLOR_SECONDARY);
        }
    } else if (now.hour != s_last_time_drawn.hour) {
        needs_hour_update = true;
    }

    if (needs_hour_update) {
        uint8_t last_hour_to_draw = (state->time_format == FORMAT_12H) ? last_hour_12 : s_last_time_drawn.hour;
        uint8_t current_hour_to_draw = (state->time_format == FORMAT_12H) ? current_hour_12 : now.hour;
        draw_time_digits(last_hour_to_draw, hour_x, TIME_Y, COLOR_BG, TIME_SCALE_X, TIME_SCALE_Y);
        draw_time_digits(current_hour_to_draw, hour_x, TIME_Y, COLOR_PRIMARY, TIME_SCALE_X, TIME_SCALE_Y);
    }

    // Date
    uint8_t date_text_w = (uint8_t)(5 * (FONT_W + FONT_SPACING));
    uint8_t date_x = (uint8_t)((SCREEN_W - date_text_w) / 2);
    WatchFace_DrawDate(date_x, DATE_Y_BOTTOM, &today, &s_last_date_drawn, COLOR_DIM, COLOR_BG);

    // Alarm
    if (state->alarm.enabled != s_last_alarm_drawn) {
        WatchFace_DrawAlarmIcon(ALARM_X, ALARM_Y, ALARM_W, ALARM_H, state->alarm.enabled);
        s_last_alarm_drawn = state->alarm.enabled;
    }

    s_last_time_drawn = now;
    s_last_format_drawn = state->time_format;
}
