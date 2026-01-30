/*
 * timekeeper.h
 * Core timekeeping functionality
 */

#ifndef TIMEKEEPER_H
#define TIMEKEEPER_H

#include "../shared/watch_types.h"

// Enable Timers from Timers.c
#define USE_TIMER1
#define USE_TIMER2

// ============================================================================
// TIMEKEEPER FUNCTIONS
// ============================================================================

/**
 * @brief Initialize the timekeeper module and the underlying hardware timers.
 */
void Timekeeper_Init(void);

/**
 * @brief Set the current time. This will also reset the internal tick counter.
 * @param time Pointer to time structure
 */
void Timekeeper_SetTime(const Time_t* time);

/**
 * @brief Set the current date.
 * @param date Pointer to date structure
 */
void Timekeeper_SetDate(const Date_t* date);

/**
 * @brief Get the current time, calculated from the hardware timer.
 * @param time Pointer to store current time
 */
void Timekeeper_GetTime(Time_t* time);

/**
 * @brief Get the current date.
 * @param date Pointer to store current date
 */
void Timekeeper_GetDate(Date_t* date);

/**
 * @brief Convert 24h time to 12h format
 * @param hour24 Hour in 24h format (0-23)
 * @param is_pm Pointer to store PM flag
 * @return Hour in 12h format (1-12)
 */
uint8_t Timekeeper_Convert24to12(uint8_t hour24, bool* is_pm);

/**
 * @brief Get days in month.
 * @param month Month (1-12)
 * @return Number of days in month
 */
uint8_t Timekeeper_GetDaysInMonth(uint8_t month);

/**
 * @brief Get milliseconds since initialization. Note: resolution is ~1ms.
 * @return Milliseconds counter
 */
uint32_t Timekeeper_GetMillis(void);

#endif // TIMEKEEPER_H