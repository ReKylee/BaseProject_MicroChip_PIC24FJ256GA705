/*
 * digital_face.c
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
#include <stdio.h>
#include "watch_face_common.h" // Include common drawing functions

// ============================================================================
// CONFIG
// ============================================================================

#define TIME_X_HOUR     8
#define TIME_X_MIN      56
#define TIME_Y          30
#define SECONDS_X       75
#define SECONDS_Y       (TIME_Y + 30)

#define AMPM_X          70
#define AMPM_Y          70

#define HOUR_DIGIT_WIDTH    18
#define MIN_DIGIT_WIDTH     18
#define SECONDS_WIDTH       14

// ============================================================================
// STATE
// ============================================================================

static Time_t last_time_drawn;
static Date_t last_date_drawn;
static bool last_alarm_drawn;
static TimeFormat_t last_format_drawn;

// ============================================================================
// PRIVATE HELPERS
// ============================================================================

static void draw_time_digits(uint8_t value, uint8_t x, uint8_t y, uint16_t color, uint8_t scale_x, uint8_t scale_y) {
    char buf[3];
    sprintf(buf, "%02d", value);
    oledC_DrawString(x, y, scale_x, scale_y, (uint8_t*)buf, color);
}

static void draw_seconds(uint8_t value, uint16_t color) {
    char buf[3];
    sprintf(buf, "%02d", value);
    oledC_DrawString(SECONDS_X, SECONDS_Y, 1, 1, (uint8_t*)buf, color);
}

static void draw_colon(uint16_t color) {
    oledC_DrawString(44, TIME_Y, 3, 4, (uint8_t*)":", color);
}

static void draw_ampm(bool is_pm, uint16_t color) {
    oledC_DrawString(AMPM_X, AMPM_Y, 1, 1, (uint8_t*)(is_pm ? "PM" : "AM"), color);
}

// ============================================================================
// PUBLIC API
// ============================================================================

void DigitalFace_Init(void) {
    oledC_setBackground(COLOR_BG);
    memset(&last_time_drawn, 0, sizeof(Time_t));
    memset(&last_date_drawn, 0, sizeof(Date_t));
    last_time_drawn.second = 255; // force initial draw
    last_format_drawn = FORMAT_24H;
    last_alarm_drawn = false;
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
    draw_time_digits(hour, TIME_X_HOUR, TIME_Y, COLOR_PRIMARY, 3, 4);
    draw_colon(COLOR_PRIMARY);
    draw_time_digits(state->current_time.minute, TIME_X_MIN, TIME_Y, COLOR_PRIMARY, 3, 4);
    draw_seconds(state->current_time.second, COLOR_DIM);

    // Date
    WatchFace_DrawDate(DATE_X, DATE_Y, &state->current_date, &last_date_drawn, COLOR_DIM, COLOR_BG);

    // AM/PM
    if (state->time_format == FORMAT_12H) {
        draw_ampm(is_pm, COLOR_SECONDARY);
    }

    // Alarm
    WatchFace_DrawAlarmIcon(ALARM_X, ALARM_Y, ALARM_W, ALARM_H, state->alarm.enabled);

    // Save state
    last_time_drawn = state->current_time;
    last_date_drawn = state->current_date;
    last_alarm_drawn = state->alarm.enabled;
    last_format_drawn = state->time_format;
   
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
    if (state->time_format != last_format_drawn) {
        DigitalFace_Draw();
        return;
    }

    // Seconds
    if (now.second != last_time_drawn.second) {
        draw_seconds(last_time_drawn.second, COLOR_BG);
        draw_seconds(now.second, COLOR_DIM);
    }

    // Minutes
    if (now.minute != last_time_drawn.minute) {
        draw_time_digits(last_time_drawn.minute, TIME_X_MIN, TIME_Y, COLOR_BG, 3, 4);
        draw_time_digits(now.minute, TIME_X_MIN, TIME_Y, COLOR_PRIMARY, 3, 4);
        needs_hour_update = true; // hour may change at 12/24 boundary
    }

    // Hours
    uint8_t last_hour_12 = last_time_drawn.hour;
    bool last_is_pm = false;
    if (state->time_format == FORMAT_12H) {
        last_hour_12 = Timekeeper_Convert24to12(last_time_drawn.hour, &last_is_pm);
        if (current_hour_12 != last_hour_12) needs_hour_update = true;
        if (is_pm != last_is_pm) {
            draw_ampm(!is_pm, COLOR_BG);
            draw_ampm(is_pm, COLOR_SECONDARY);
        }
    } else if (now.hour != last_time_drawn.hour) {
        needs_hour_update = true;
    }

    if (needs_hour_update) {
        uint8_t last_hour_to_draw = (state->time_format == FORMAT_12H) ? last_hour_12 : last_time_drawn.hour;
        uint8_t current_hour_to_draw = (state->time_format == FORMAT_12H) ? current_hour_12 : now.hour;
        draw_time_digits(last_hour_to_draw, TIME_X_HOUR, TIME_Y, COLOR_BG, 3, 4);
        draw_time_digits(current_hour_to_draw, TIME_X_HOUR, TIME_Y, COLOR_PRIMARY, 3, 4);
    }

    // Date
    WatchFace_DrawDate(DATE_X, DATE_Y, &today, &last_date_drawn, COLOR_DIM, COLOR_BG);

    // Alarm
    WatchFace_DrawAlarmIcon(ALARM_X, ALARM_Y, ALARM_W, ALARM_H, state->alarm.enabled);

    last_time_drawn = now;
    last_format_drawn = state->time_format;
}
