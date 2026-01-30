/*
 * digital_face.c
 * Implementation of digital watch face with partial updates.
 */

#include "digital_face.h"
#include "../shared/watch_state.h"
#include "../shared/watch_types.h"
#include "../watchCore/timekeeper.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include <stdio.h>
#include <string.h>

// ============================================================================
// CONFIGURATION
// ============================================================================

#define DIGIT_WIDTH     18      // 3 (scale) * 5 (font) + 3
#define DIGIT_HEIGHT    32      // 4 (scale) * 8 (font)
#define TIME_Y          30      // Vertical position of time
#define DATE_Y          5
#define AMPM_Y          70
#define ALARM_ICON_X    88
#define ALARM_ICON_Y    5

// ============================================================================
// MODULE STATE
// ============================================================================

static Time_t last_time_drawn;
static Date_t last_date_drawn;
static bool last_alarm_drawn = false;
static TimeFormat_t last_format_drawn;

// ============================================================================
// PRIVATE FUNCTIONS
// ============================================================================

// --- Drawing Helpers ---

static void draw_time_component(uint8_t value, uint8_t x, uint16_t color) {
    char str[3];
    sprintf(str, "%02d", value);
    oledC_DrawString(x, TIME_Y, 3, 4, (uint8_t*)str, color);
}

static void draw_seconds(uint8_t value, uint16_t color) {
    char str[3];
    sprintf(str, "%02d", value);
    oledC_DrawString(75, TIME_Y + 20, 1, 1, (uint8_t*)str, color);
}

static void draw_colon(uint16_t color) {
    oledC_DrawString(44, TIME_Y, 3, 4, (uint8_t*)":", color);
}

static void draw_date(const Date_t* date, uint16_t color) {
    char date_str[6];
    sprintf(date_str, "%02d/%02d", date->day, date->month);
    oledC_DrawString(2, DATE_Y, 1, 1, (uint8_t*)date_str, color);
}

static void draw_ampm(bool is_pm, uint16_t color) {
    const char* str = is_pm ? "PM" : "AM";
    oledC_DrawString(70, AMPM_Y, 1, 1, (uint8_t*)str, color);
}

static void draw_alarm_icon(uint16_t color) {
    oledC_DrawRectangle(ALARM_ICON_X, ALARM_ICON_Y, ALARM_ICON_X + 5, ALARM_ICON_Y + 5, color);
}

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void DigitalFace_Init(void) {
    // Clear last drawn state
    memset(&last_time_drawn, 0, sizeof(Time_t));
    memset(&last_date_drawn, 0, sizeof(Date_t));
    last_time_drawn.second = 99; // Force initial draw
    last_format_drawn = FORMAT_24H;
}

void DigitalFace_Draw(void) {
    WatchState_t* state = Watch_GetState();
    
    // --- Draw Time ---
    uint8_t hour = state->current_time.hour;
    bool is_pm = false;
    if (state->time_format == FORMAT_12H) {
        hour = Timekeeper_Convert24to12(hour, &is_pm);
    }
    draw_time_component(hour, 8, COLOR_PRIMARY);
    draw_colon(COLOR_PRIMARY);
    draw_time_component(state->current_time.minute, 56, COLOR_PRIMARY);
    draw_seconds(state->current_time.second, COLOR_DIM);

    // --- Draw Static Info ---
    draw_date(&state->current_date, COLOR_DIM);
    if (state->alarm.enabled) {
        draw_alarm_icon(COLOR_ACCENT);
    }
    if (state->time_format == FORMAT_12H) {
        draw_ampm(is_pm, COLOR_SECONDARY);
    }

    // --- Update Last Drawn State ---
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
    uint8_t current_hour_12 = 0;
    
    if (state->time_format == FORMAT_12H) {
        current_hour_12 = Timekeeper_Convert24to12(now.hour, &is_pm);
    }

    // Check for format change (12H/24H)
    if (state->time_format != last_format_drawn) {
        DigitalFace_Draw(); // Do a full redraw on format change
        return;
    }

    // Check seconds
    if (now.second != last_time_drawn.second) {
        draw_seconds(last_time_drawn.second, COLOR_BG);
        draw_seconds(now.second, COLOR_DIM);
    }

    // Check minutes
    if (now.minute != last_time_drawn.minute) {
        draw_time_component(last_time_drawn.minute, 56, COLOR_BG);
        draw_time_component(now.minute, 56, COLOR_PRIMARY);
        needs_hour_update = true; // Hour might need update in 12h mode (e.g. 12:59 -> 1:00)
    }

    // Check hours
    uint8_t last_hour_12 = 0;
    if (state->time_format == FORMAT_12H) {
        bool last_is_pm;
        last_hour_12 = Timekeeper_Convert24to12(last_time_drawn.hour, &last_is_pm);
        if (current_hour_12 != last_hour_12) {
             needs_hour_update = true;
        }
        if (is_pm != last_is_pm) {
            draw_ampm(!is_pm, COLOR_BG);
            draw_ampm(is_pm, COLOR_SECONDARY);
        }
    } else { // 24H format
        if (now.hour != last_time_drawn.hour) {
            needs_hour_update = true;
        }
    }
    
    if (needs_hour_update) {
        uint8_t last_hour_to_draw = (state->time_format == FORMAT_12H) ? last_hour_12 : last_time_drawn.hour;
        uint8_t current_hour_to_draw = (state->time_format == FORMAT_12H) ? current_hour_12 : now.hour;
        draw_time_component(last_hour_to_draw, 8, COLOR_BG);
        draw_time_component(current_hour_to_draw, 8, COLOR_PRIMARY);
    }

    // Check date
    if (today.day != last_date_drawn.day || today.month != last_date_drawn.month) {
        draw_date(&last_date_drawn, COLOR_BG);
        draw_date(&today, COLOR_DIM);
        last_date_drawn = today;
    }

    // Check alarm status
    if (state->alarm.enabled != last_alarm_drawn) {
        draw_alarm_icon(last_alarm_drawn ? COLOR_BG : COLOR_ACCENT);
        last_alarm_drawn = state->alarm.enabled;
    }
    
    last_time_drawn = now;
    last_format_drawn = state->time_format;
}