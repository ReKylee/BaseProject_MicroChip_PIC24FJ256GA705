/*
 * Implementation of core timekeeping using hardware timers.
 * Merged from timekeeper.c and watch_timer.c.
 */

#include "timekeeper.h"
#include "../shared/watch_state.h"
#include "../shared/fast_math.h"
#include "../../Timers/Timers.h"
#include <xc.h>

// ============================================================================
// PRIVATE DATA
// ============================================================================

static const uint8_t s_days_in_month[12] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};
static const uint8_t TIMEKEEPER_MONTHS_PER_YEAR = 12U;
static const uint8_t TIMEKEEPER_MIN_MONTH = 1U;
static const uint32_t TIMEKEEPER_SECONDS_PER_MINUTE = 60UL;
static const uint32_t TIMEKEEPER_SECONDS_PER_HOUR = 3600UL;
static const uint8_t TIMEKEEPER_HOURS_PER_DAY = 24U;
static const uint16_t TIMEKEEPER_TIMER1_PERIOD = 1U;
static const uint8_t TIMEKEEPER_TIMER1_PRESCALER = 6U;
static const uint16_t TIMEKEEPER_TIMER2_PERIOD = 1042U;
static const uint8_t TIMEKEEPER_TIMER2_PRESCALER = 5U;

static Time_t s_base_time;
static Date_t s_base_date;
static uint32_t s_base_time_ticks;

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void Timekeeper_Init(void) {
    Timer1_Init(TIMEKEEPER_TIMER1_PERIOD, TIMEKEEPER_TIMER1_PRESCALER);
    Timer2_Init(TIMEKEEPER_TIMER2_PERIOD, TIMEKEEPER_TIMER2_PRESCALER);
    
    s_base_time = (Time_t){0, 0, 0};
    s_base_date = (Date_t){1, 1};
    s_base_time_ticks = 0;
}

bool Timekeeper_SetTime(const Time_t* time) {
    if (time->hour >= TIMEKEEPER_HOURS_PER_DAY ||
        time->minute >= TIMEKEEPER_SECONDS_PER_MINUTE ||
        time->second >= TIMEKEEPER_SECONDS_PER_MINUTE) {
        return false;
    }

    __builtin_disi(0x3FFF);
    s_base_time = *time;
    s_base_time_ticks = Timer_GetTicks(1);
    __builtin_disi(0x0000);
    return true;
}

void Timekeeper_SetDate(const Date_t* date) {
    if (date->month >= TIMEKEEPER_MIN_MONTH && date->month <= TIMEKEEPER_MONTHS_PER_YEAR) {
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

    uint32_t base_total_seconds =
        FastMath_Mul3600U32FromU8(s_base_time.hour) +
        FastMath_Mul60U32FromU8(s_base_time.minute) +
        (uint32_t)s_base_time.second;
    uint32_t current_total_seconds = base_total_seconds + elapsed_seconds;
    
    uint16_t days_passed = (uint16_t)FastMath_Div86400U32(current_total_seconds);
    uint16_t day = (uint16_t)s_base_date.day + days_passed;
    uint8_t month = s_base_date.month;

    while (day > Timekeeper_GetDaysInMonth(month)) {
        day -= Timekeeper_GetDaysInMonth(month);
        month++;
        if (month > TIMEKEEPER_MONTHS_PER_YEAR) {
            month = TIMEKEEPER_MIN_MONTH;
        }
    }
    
    WatchState_t* state = Watch_GetState();
    state->current_date.day = (uint8_t)day;
    state->current_date.month = month;

    uint32_t seconds_into_day = current_total_seconds - FastMath_Mul86400U32(days_passed);
    uint8_t hour = 0U;
    uint8_t minute = 0U;
    while (seconds_into_day >= TIMEKEEPER_SECONDS_PER_HOUR) {
        seconds_into_day -= TIMEKEEPER_SECONDS_PER_HOUR;
        hour++;
    }
    while (seconds_into_day >= TIMEKEEPER_SECONDS_PER_MINUTE) {
        seconds_into_day -= TIMEKEEPER_SECONDS_PER_MINUTE;
        minute++;
    }
    time->hour = hour;
    time->minute = minute;
    time->second = (uint8_t)seconds_into_day;
}

void Timekeeper_GetDate(Date_t* date) {
    *date = Watch_GetState()->current_date;
}

uint32_t Timekeeper_GetMillis(void) {
    return Timer_GetTicks(2);
}

uint8_t Timekeeper_Convert24to12(uint8_t hour24, bool* is_pm) {
    *is_pm = (hour24 >= (TIMEKEEPER_HOURS_PER_DAY >> 1));
    
    if (hour24 == 0U) {
        return (TIMEKEEPER_HOURS_PER_DAY >> 1);
    } else if (hour24 <= (TIMEKEEPER_HOURS_PER_DAY >> 1)) {
        return hour24;
    } else {
        return (uint8_t)(hour24 - (TIMEKEEPER_HOURS_PER_DAY >> 1));
    }
}

uint8_t Timekeeper_GetDaysInMonth(uint8_t month) {
    if (month < TIMEKEEPER_MIN_MONTH || month > TIMEKEEPER_MONTHS_PER_YEAR) {
        return 30;
    }
    return s_days_in_month[month - TIMEKEEPER_MIN_MONTH];
}
