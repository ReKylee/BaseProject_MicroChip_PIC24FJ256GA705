/*
 * pomodoro.h
 * Pomodoro timer module (25/5 minute intervals)
 */

#ifndef POMODORO_H
#define POMODORO_H

#include <stdint.h>
#include <stdbool.h>

// ============================================================================
// POMODORO CONFIGURATION
// ============================================================================

#define POMODORO_WORK_MINUTES       25
#define POMODORO_SHORT_BREAK_MIN    5
#define POMODORO_LONG_BREAK_MIN     15
#define POMODORO_LONG_BREAK_AFTER   4   // Long break after 4 work sessions

// ============================================================================
// POMODORO FUNCTIONS
// ============================================================================

/**
 * @brief Initialize Pomodoro timer
 */
void Pomodoro_Init(void);

/**
 * @brief Start/Resume Pomodoro timer
 */
void Pomodoro_Start(void);

/**
 * @brief Pause Pomodoro timer
 */
void Pomodoro_Pause(void);

/**
 * @brief Reset Pomodoro timer to beginning
 */
void Pomodoro_Reset(void);

/**
 * @brief Update Pomodoro timer (call every second)
 */
void Pomodoro_Update(void);

/**
 * @brief Draw Pomodoro display
 */
void Pomodoro_Draw(void);

/**
 * @brief Handle button input for Pomodoro
 * @param start_pause S2 button pressed (start/pause)
 * @param reset S1 button pressed (reset)
 */
void Pomodoro_HandleInput(bool start_pause, bool reset);

#endif // POMODORO_H
