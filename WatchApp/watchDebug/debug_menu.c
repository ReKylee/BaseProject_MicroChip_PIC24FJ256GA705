/*
 * Debug menu screen (compiled only with DEBUG_MODE)
 */

#include "debug_menu.h"

#ifdef DEBUG_MODE

#include "../shared/watch_state.h"
#include "../shared/watch_settings_store.h"
#include "../shared/ui_layout.h"
#include "../shared/watch_format.h"
#include "../watchInput/potentiometer.h"
#include "../../accel3Driver/ACCEL3.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include "../watchCore/alarm.h"
#include "../watchCore/timekeeper.h"
#include <stdio.h>
#include <string.h>

#define DEBUG_HEADER_Y 1
#define DEBUG_HEADER_H 10
#define DEBUG_TIME_X 48
#define DEBUG_TIME_Y 1
#define DEBUG_TITLE_X 2
#define DEBUG_TITLE_Y 1

static DisplayMode_t s_prev_mode = MODE_WATCH;
static bool s_debug_drawn = false;
static uint16_t s_dbg_last_pot_raw = CACHE_INVALID_U16;
static uint8_t s_dbg_last_pot_pct = CACHE_INVALID_U8;
static int16_t s_dbg_last_ax = 0x7FFF;
static int16_t s_dbg_last_ay = 0x7FFF;
static int16_t s_dbg_last_az = 0x7FFF;
static uint8_t s_dbg_last_alarm_hour = CACHE_INVALID_U8;
static uint8_t s_dbg_last_alarm_min = CACHE_INVALID_U8;
static uint8_t s_dbg_last_alarm_en = CACHE_INVALID_U8;
static uint8_t s_dbg_last_date_day = CACHE_INVALID_U8;
static uint8_t s_dbg_last_date_month = CACHE_INVALID_U8;
static char s_date_step_msg[22] = "DT STEP READY";
static char s_last_date_step_msg[22] = "";
static Time_t s_last_time = {CACHE_INVALID_U8, CACHE_INVALID_U8, CACHE_INVALID_U8};
static TimeFormat_t s_last_time_format = FORMAT_24H;

static uint8_t pot_percent_0_to_100(uint16_t pot_raw) {
    uint32_t pct = (((uint32_t)pot_raw * 100U) + 512UL) >> 10;
    if (pct > 100U) {
        pct = 100U;
    }
    return (uint8_t)pct;
}

static void draw_header(const char* title) {
    oledC_DrawRectangle(0, DEBUG_HEADER_Y, 95, DEBUG_HEADER_Y + DEBUG_HEADER_H, COLOR_BG);
    oledC_DrawStringSolid(DEBUG_TITLE_X, DEBUG_TITLE_Y, 1, 1, (uint8_t*)title, COLOR_ACCENT, COLOR_BG);
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
        oledC_DrawStringSolid(WatchUi_RightX96(WatchUi_CharsToPx6(11U)), DEBUG_TIME_Y, 1, 1, (uint8_t*)buf, COLOR_DIM, COLOR_BG);
    } else {
        snprintf(buf, sizeof(buf), "%02d:%02d:%02d",
                 hour, state->current_time.minute, state->current_time.second);
        oledC_DrawStringSolid(WatchUi_RightX96(WatchUi_CharsToPx6(8U)), DEBUG_TIME_Y, 1, 1, (uint8_t*)buf, COLOR_DIM, COLOR_BG);
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
    oledC_DrawStringSolid(2, y, 1, 1, (uint8_t*)text, COLOR_PRIMARY, COLOR_BG);
}

static void debug_increment_date(void) {
    WatchState_t* state = Watch_GetState();
    Date_t prev = state->current_date;
    Date_t next = state->current_date;
    uint8_t max_days = Timekeeper_GetDaysInMonth(next.month);

    next.day++;
    if (next.day > max_days) {
        next.day = 1;
        next.month++;
        if (next.month > 12) {
            next.month = 1;
        }
    }

    Timekeeper_SetDate(&next);
    state->current_date = next;
    (void)WatchSettingsStore_SaveState(state);
    {
        char prev_buf[6];
        char next_buf[6];
        Watch_FormatDateDDMM(&prev, prev_buf);
        Watch_FormatDateDDMM(&next, next_buf);
        snprintf(s_date_step_msg, sizeof(s_date_step_msg), "DT %s>%s", prev_buf, next_buf);
    }
    state->needs_redraw = true;
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
    uint8_t pot_pct = pot_percent_0_to_100(pot_raw);

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
    {
        char date_buf[6];
        Watch_FormatDateDDMM(&state->current_date, date_buf);
        snprintf(line, sizeof(line), "DT %s", date_buf);
    }
    draw_line(54, line);
    draw_line(64, "S1=DATE+1");
    draw_line(74, "S2=ALARM");
    draw_line(84, s_date_step_msg);

    s_dbg_last_pot_raw = pot_raw;
    s_dbg_last_pot_pct = pot_pct;
    s_dbg_last_ax = ax;
    s_dbg_last_ay = ay;
    s_dbg_last_az = az;
    s_dbg_last_alarm_hour = state->alarm.hour;
    s_dbg_last_alarm_min = state->alarm.minute;
    s_dbg_last_alarm_en = state->alarm.enabled ? 1 : 0;
    s_dbg_last_date_day = state->current_date.day;
    s_dbg_last_date_month = state->current_date.month;
    strcpy(s_last_date_step_msg, s_date_step_msg);
    s_debug_drawn = true;
}

void DebugMenu_DrawUpdate(void) {
    WatchState_t* state = Watch_GetState();
    char line[22];
    int16_t ax = 0, ay = 0, az = 0;
    bool accel_ok = (ACCEL3_ReadXYZ(&ax, &ay, &az) == ACCEL3_OK);
    uint16_t pot_raw = Pot_GetRaw();
    uint8_t pot_pct = pot_percent_0_to_100(pot_raw);

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
    if (state->current_date.day != s_dbg_last_date_day ||
        state->current_date.month != s_dbg_last_date_month) {
        {
            char date_buf[6];
            Watch_FormatDateDDMM(&state->current_date, date_buf);
            snprintf(line, sizeof(line), "DT %s", date_buf);
        }
        draw_line(54, line);
        s_dbg_last_date_day = state->current_date.day;
        s_dbg_last_date_month = state->current_date.month;
    }
    if (strcmp(s_date_step_msg, s_last_date_step_msg) != 0) {
        draw_line(84, s_date_step_msg);
        strcpy(s_last_date_step_msg, s_date_step_msg);
    }

    draw_time_update();
}

void DebugMenu_HandleInput(ButtonEvent_t btn) {
    if (btn == BTN_S1_SHORT) {
        debug_increment_date();
        return;
    }

    if (btn == BTN_S2_SHORT) {
        WatchState_t* state = Watch_GetState();
        uint8_t hour = state->current_time.hour;
        uint8_t minute = state->current_time.minute;
        if (state->current_time.second != 0U) {
            minute++;
            if (minute >= 60U) {
                minute = 0U;
                hour++;
                if (hour >= 24U) {
                    hour = 0U;
                }
            }
        }

        state->alarm.hour = hour;
        state->alarm.minute = minute;
        state->alarm.enabled = true;
        state->alarm.triggered = false;
        state->alarm.trigger_count = 0;
        (void)WatchSettingsStore_SaveState(state);
        state->needs_redraw = true;
        DebugMenu_Exit();
    }
}
#endif
