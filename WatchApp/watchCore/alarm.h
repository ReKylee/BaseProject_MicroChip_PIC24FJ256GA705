/*
 * alarm.h
 * Alarm functionality for the watch
 */

#ifndef ALARM_H
#define ALARM_H

#include "../shared/watch_types.h"

// ============================================================================
// ALARM FUNCTIONS
// ============================================================================

/**
 * @brief Initialize the alarm module
 */
void Alarm_Init(void);

/**
 * @brief Check if alarm should trigger
 * Called every second
 */
void Alarm_Check(void);

/**
 * @brief Set alarm time
 * @param hour Alarm hour (0-23)
 * @param minute Alarm minute (0-59)
 */
void Alarm_SetTime(uint8_t hour, uint8_t minute);

/**
 * @brief Enable the alarm
 */
void Alarm_Enable(void);

/**
 * @brief Disable the alarm
 */
void Alarm_Disable(void);

/**
 * @brief Toggle alarm enabled state
 */
void Alarm_Toggle(void);

/**
 * @brief Dismiss the alarm (stop ringing)
 */
void Alarm_Dismiss(void);

/**
 * @brief Check if alarm is currently ringing
 * @return true if alarm is ringing
 */
bool Alarm_IsRinging(void);

/**
 * @brief Update alarm state (handle auto-off after 20 seconds)
 * Called every second
 */
void Alarm_Update(void);

#endif // ALARM_H
