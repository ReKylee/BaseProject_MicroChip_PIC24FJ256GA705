/*
 * Debug menu screen (compiled only with DEBUG_MODE)
 */

#include "debug_menu.h"

#ifdef DEBUG_MODE

#include "../shared/watch_state.h"
#include "../watchInput/potentiometer.h"
#include "../../accel3Driver/ACCEL3.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include "../watchCore/alarm.h"
#include "../watchCore/timekeeper.h"
#include <stdio.h>

// Layout
#define DEBUG_HEADER_Y 1
#define DEBUG_HEADER_H 10
#define DEBUG_TIME_X 48
#define DEBUG_TIME_Y 1
#define DEBUG_TITLE_X 2
#define DEBUG_TITLE_Y 1

static DisplayMode_t s_prev_mode = MODE_WATCH;
static bool s_debug_drawn = false;
static uint16_t s_dbg_last_pot_raw = 0xFFFF;
static uint8_t s_dbg_last_pot_pct = 0xFF;
static int16_t s_dbg_last_ax = 0x7FFF;
static int16_t s_dbg_last_ay = 0x7FFF;
static int16_t s_dbg_last_az = 0x7FFF;
static uint8_t s_dbg_last_alarm_hour = 0xFF;
static uint8_t s_dbg_last_alarm_min = 0xFF;
static uint8_t s_dbg_last_alarm_en = 0xFF;
static Time_t s_last_time = {0xFF, 0xFF, 0xFF};
static TimeFormat_t s_last_time_format = FORMAT_24H;

static void draw_header(const char* title) {
    oledC_DrawRectangle(0, DEBUG_HEADER_Y, 95, DEBUG_HEADER_Y + DEBUG_HEADER_H, COLOR_BG);
    oledC_DrawString(DEBUG_TITLE_X, DEBUG_TITLE_Y, 1, 1, (uint8_t*)title, COLOR_ACCENT);
}

static void draw_time_full(void) {
    WatchState_t* state = Watch_GetState();
    char buf[12];
    uint8_t hour = state->current_time.hour;
    bool is_pm = false;
    draw_header("DEBUG");
    if (state->time_format == FORMAT_12H) {
        hour = Timekeeper_Convert24to12(hour, &is_pm);
        snprintf(buf, sizeof(buf), "%02d:%02d:%02d %s",
                 hour, state->current_time.minute, state->current_time.second,
                 is_pm ? "PM" : "AM");
        oledC_DrawString((uint8_t)(96 - (11 * 6)), DEBUG_TIME_Y, 1, 1, (uint8_t*)buf, COLOR_DIM);
    } else {
        snprintf(buf, sizeof(buf), "%02d:%02d:%02d",
                 hour, state->current_time.minute, state->current_time.second);
        oledC_DrawString((uint8_t)(96 - (8 * 6)), DEBUG_TIME_Y, 1, 1, (uint8_t*)buf, COLOR_DIM);
    }
    s_last_time = state->current_time;
    s_last_time_format = state->time_format;
}

static void draw_time_update(void) {
    WatchState_t* state = Watch_GetState();
    if (state->current_time.second != s_last_time.second ||
        state->time_format != s_last_time_format) {
        draw_time_full();
    }
}

static void draw_line(uint8_t y, const char* text) {
    oledC_DrawRectangle(0, y, 95, (uint8_t)(y + 8), COLOR_BG);
    oledC_DrawString(2, y, 1, 1, (uint8_t*)text, COLOR_PRIMARY);
}

void DebugMenu_Enter(void) {
    WatchState_t* state = Watch_GetState();
    s_prev_mode = state->display_mode;
    state->display_mode = MODE_DEBUG;
    state->needs_full_redraw = true;
    s_debug_drawn = false;
}

void DebugMenu_Exit(void) {
    WatchState_t* state = Watch_GetState();
    state->display_mode = s_prev_mode;
    state->needs_full_redraw = true;
    s_debug_drawn = false;
}

void DebugMenu_Toggle(void) {
    WatchState_t* state = Watch_GetState();
    if (state->display_mode == MODE_DEBUG) {
        DebugMenu_Exit();
    } else {
        DebugMenu_Enter();
    }
}

void DebugMenu_DrawFull(void) {
    WatchState_t* state = Watch_GetState();
    char line[22];
    int16_t ax = 0, ay = 0, az = 0;
    bool accel_ok = (ACCEL3_ReadXYZ(&ax, &ay, &az) == ACCEL3_OK);
    uint16_t pot_raw = Pot_GetRaw();
    uint8_t pot_pct = (uint8_t)((pot_raw * 100U) / 1023U);

    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    draw_header("DEBUG");
    draw_time_full();

    sprintf(line, "POT %4u %3u%%", pot_raw, pot_pct);
    draw_line(14, line);

    if (accel_ok) {
        sprintf(line, "AX%4d AY%4d", ax, ay);
        draw_line(24, line);
        sprintf(line, "AZ%4d", az);
        draw_line(34, line);
    } else {
        draw_line(24, "ACCEL ERR");
        draw_line(34, "");
    }

    sprintf(line, "AL %02d:%02d %s",
            state->alarm.hour, state->alarm.minute,
            state->alarm.enabled ? "ON" : "OFF");
    draw_line(44, line);
    draw_line(54, "S2=ALARM");

    s_dbg_last_pot_raw = pot_raw;
    s_dbg_last_pot_pct = pot_pct;
    s_dbg_last_ax = ax;
    s_dbg_last_ay = ay;
    s_dbg_last_az = az;
    s_dbg_last_alarm_hour = state->alarm.hour;
    s_dbg_last_alarm_min = state->alarm.minute;
    s_dbg_last_alarm_en = state->alarm.enabled ? 1 : 0;
    s_debug_drawn = true;
}

void DebugMenu_DrawUpdate(void) {
    WatchState_t* state = Watch_GetState();
    char line[22];
    int16_t ax = 0, ay = 0, az = 0;
    bool accel_ok = (ACCEL3_ReadXYZ(&ax, &ay, &az) == ACCEL3_OK);
    uint16_t pot_raw = Pot_GetRaw();
    uint8_t pot_pct = (uint8_t)((pot_raw * 100U) / 1023U);

    if (!s_debug_drawn) {
        DebugMenu_DrawFull();
        return;
    }

    if (pot_raw != s_dbg_last_pot_raw || pot_pct != s_dbg_last_pot_pct) {
        sprintf(line, "POT %4u %3u%%", pot_raw, pot_pct);
        draw_line(14, line);
        s_dbg_last_pot_raw = pot_raw;
        s_dbg_last_pot_pct = pot_pct;
    }

    if (accel_ok) {
        if (ax != s_dbg_last_ax || ay != s_dbg_last_ay) {
            sprintf(line, "AX%4d AY%4d", ax, ay);
            draw_line(24, line);
            s_dbg_last_ax = ax;
            s_dbg_last_ay = ay;
        }
        if (az != s_dbg_last_az) {
            sprintf(line, "AZ%4d", az);
            draw_line(34, line);
            s_dbg_last_az = az;
        }
    } else {
        if (s_dbg_last_ax != 0x7FFF || s_dbg_last_ay != 0x7FFF) {
            draw_line(24, "ACCEL ERR");
            draw_line(34, "");
            s_dbg_last_ax = 0x7FFF;
            s_dbg_last_ay = 0x7FFF;
            s_dbg_last_az = 0x7FFF;
        }
    }

    if (state->alarm.hour != s_dbg_last_alarm_hour ||
        state->alarm.minute != s_dbg_last_alarm_min ||
        (state->alarm.enabled ? 1 : 0) != s_dbg_last_alarm_en) {
        sprintf(line, "AL %02d:%02d %s",
                state->alarm.hour, state->alarm.minute,
                state->alarm.enabled ? "ON" : "OFF");
        draw_line(44, line);
        s_dbg_last_alarm_hour = state->alarm.hour;
        s_dbg_last_alarm_min = state->alarm.minute;
        s_dbg_last_alarm_en = state->alarm.enabled ? 1 : 0;
    }

    draw_time_update();
}

void DebugMenu_HandleInput(ButtonEvent_t btn) {
    if (btn == BTN_S2_SHORT) {
        WatchState_t* state = Watch_GetState();
        uint32_t now = (uint32_t)state->current_time.hour * 3600U +
                       (uint32_t)state->current_time.minute * 60U +
                       (uint32_t)state->current_time.second;
        uint32_t to_next_min = (state->current_time.second == 0) ? 0U : (60U - state->current_time.second);
        uint32_t target = now + to_next_min;
        uint8_t hour = (uint8_t)((target / 3600U) % 24U);
        uint8_t minute = (uint8_t)((target / 60U) % 60U);

        state->alarm.hour = hour;
        state->alarm.minute = minute;
        state->alarm.enabled = true;
        state->alarm.triggered = false;
        state->alarm.trigger_count = 0;
        state->needs_redraw = true;
        DebugMenu_Exit();
    }
}
#endif
