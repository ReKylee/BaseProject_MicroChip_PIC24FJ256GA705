/*
 * Implementation of core timekeeping using hardware timers.
 * Merged from timekeeper.c and watch_timer.c.
 */

#include "timekeeper.h"
#include "../shared/watch_state.h"
#include "../../Timers/Timers.h"
#include <xc.h>

// ============================================================================
// PRIVATE DATA
// ============================================================================

static const uint8_t s_days_in_month[12] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static Time_t s_base_time;
static Date_t s_base_date;
static uint32_t s_base_time_ticks;

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void Timekeeper_Init(void) {
    Timer1_Init(1, 6);
    Timer2_Init(1042, 5);
    
    s_base_time = (Time_t){0, 0, 0};
    s_base_date = (Date_t){1, 1};
    s_base_time_ticks = 0;
}

bool Timekeeper_SetTime(const Time_t* time) {
    if (time->hour >= 24 || time->minute >= 60 || time->second >= 60) {
        return false;
    }

    __builtin_disi(0x3FFF);
    s_base_time = *time;
    s_base_time_ticks = Timer_GetTicks(1);
    __builtin_disi(0x0000);
    return true;
}

void Timekeeper_SetDate(const Date_t* date) {
    if (date->month >= 1 && date->month <= 12) {
        uint8_t max_days = Timekeeper_GetDaysInMonth(date->month);
        if (date->day >= 1 && date->day <= max_days) {
             __builtin_disi(0x3FFF);
            s_base_date = *date;
            s_base_time = Watch_GetState()->current_time;
            s_base_time_ticks = Timer_GetTicks(1);
             __builtin_disi(0x0000);
        }
    }
}

void Timekeeper_GetTime(Time_t* time) {
    uint32_t current_ticks = Timer_GetTicks(1);
    uint32_t elapsed_seconds = current_ticks - s_base_time_ticks;

    uint32_t base_total_seconds = s_base_time.hour * 3600 + s_base_time.minute * 60 + s_base_time.second;
    uint32_t current_total_seconds = base_total_seconds + elapsed_seconds;
    
    uint16_t days_passed = current_total_seconds / 86400;
    uint16_t day = (uint16_t)s_base_date.day + days_passed;
    uint8_t month = s_base_date.month;

    while (day > Timekeeper_GetDaysInMonth(month)) {
        day -= Timekeeper_GetDaysInMonth(month);
        month++;
        if (month > 12) {
            month = 1;
        }
    }
    
    WatchState_t* state = Watch_GetState();
    state->current_date.day = (uint8_t)day;
    state->current_date.month = month;

    uint32_t seconds_into_day = current_total_seconds % 86400;
    time->hour = seconds_into_day / 3600;
    time->minute = (seconds_into_day % 3600) / 60;
    time->second = seconds_into_day % 60;
}

void Timekeeper_GetDate(Date_t* date) {
    *date = Watch_GetState()->current_date;
}

uint32_t Timekeeper_GetMillis(void) {
    return Timer_GetTicks(2);
}

uint8_t Timekeeper_Convert24to12(uint8_t hour24, bool* is_pm) {
    *is_pm = (hour24 >= 12);
    
    if (hour24 == 0) {
        return 12;
    } else if (hour24 <= 12) {
        return hour24;
    } else {
        return hour24 - 12;
    }
}

uint8_t Timekeeper_GetDaysInMonth(uint8_t month) {
    if (month < 1 || month > 12) {
        return 30;
    }
    return s_days_in_month[month - 1];
}
