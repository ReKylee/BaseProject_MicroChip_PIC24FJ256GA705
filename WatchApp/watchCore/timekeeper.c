/*
 * timekeeper.c
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

static const uint8_t days_in_month[12] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

// Base time and date stored when time is set
static Time_t base_time;
static Date_t base_date;
static uint32_t base_time_ticks; // Uptime in seconds when time was set

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void Timekeeper_Init(void) {
    // Freq 1Hz, Priority 6 (high)
    Timer1_Init(1, 6);
    // Freq ~1kHz (1042Hz), Priority 5
    // PR = (4MHz / 256 / 1042Hz) - 1 = 14
    Timer2_Init(1042, 5);
    
    // Set initial base time to 00:00:00 at boot
    base_time = (Time_t){0, 0, 0};
    base_date = (Date_t){1, 1};
    base_time_ticks = 0;
}

void Timekeeper_SetTime(const Time_t* time) {
    // Validate and set time
    if (time->hour < 24 && time->minute < 60 && time->second < 60) {
        __builtin_disi(0x3FFF); // Disable interrupts for atomic update
        base_time = *time;
        base_time_ticks = Timer_GetTicks(1);
        __builtin_disi(0x0000); // Re-enable interrupts
    }
}

void Timekeeper_SetDate(const Date_t* date) {
    // Validate and set date
    if (date->month >= 1 && date->month <= 12) {
        uint8_t max_days = Timekeeper_GetDaysInMonth(date->month);
        if (date->day >= 1 && date->day <= max_days) {
             __builtin_disi(0x3FFF); // Disable interrupts for atomic update
            base_date = *date;
            // Also reset the base time to prevent date calculation inconsistencies
            base_time = Watch_GetState()->current_time;
            base_time_ticks = Timer_GetTicks(1);
             __builtin_disi(0x0000); // Re-enable interrupts
        }
    }
}

void Timekeeper_GetTime(Time_t* time) {
    uint32_t current_ticks = Timer_GetTicks(1);
    uint32_t elapsed_seconds = current_ticks - base_time_ticks;

    uint32_t base_total_seconds = base_time.hour * 3600 + base_time.minute * 60 + base_time.second;
    uint32_t current_total_seconds = base_total_seconds + elapsed_seconds;
    
    // Date calculation
    uint16_t days_passed = current_total_seconds / 86400; // 86400 seconds in a day
    uint8_t day = base_date.day + days_passed;
    uint8_t month = base_date.month;

    while (day > Timekeeper_GetDaysInMonth(month)) {
        day -= Timekeeper_GetDaysInMonth(month);
        month++;
        if (month > 12) {
            month = 1;
        }
    }
    
    WatchState_t* state = Watch_GetState();
    state->current_date.day = day;
    state->current_date.month = month;

    // Time calculation
    uint32_t seconds_into_day = current_total_seconds % 86400;
    time->hour = seconds_into_day / 3600;
    time->minute = (seconds_into_day % 3600) / 60;
    time->second = seconds_into_day % 60;
}

void Timekeeper_GetDate(Date_t* date) {
    *date = Watch_GetState()->current_date;
}

uint32_t Timekeeper_GetMillis(void) {
    // Timer2 is running at 1042Hz, so each tick is ~0.96ms.
    // This is close enough to 1ms for debounce/long-press timing.
    return Timer_GetTicks(2);
}

uint8_t Timekeeper_Convert24to12(uint8_t hour24, bool* is_pm) {
    *is_pm = (hour24 >= 12);
    
    if (hour24 == 0) {
        return 12;  // Midnight is 12 AM
    } else if (hour24 <= 12) {
        return hour24;
    } else {
        return hour24 - 12;
    }
}

uint8_t Timekeeper_GetDaysInMonth(uint8_t month) {
    if (month < 1 || month > 12) {
        return 30;  // Default fallback
    }
    return days_in_month[month - 1];
}