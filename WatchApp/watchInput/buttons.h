/*
 * buttons.h
 * Button input handling with debounce and long press detection
 */

#ifndef BUTTONS_H
#define BUTTONS_H

#include "../shared/watch_types.h"

#define LONG_PRESS_MS   2000    // 2 seconds for long press

// ============================================================================
// BUTTON FUNCTIONS
// ============================================================================

/**
 * @brief Initialize button module
 */
void Buttons_Init(void);

/**
 * @brief Update button state (call from main loop)
 * @return Button event that occurred, or BTN_NONE
 */
ButtonEvent_t Buttons_Update(void);

/**
 * @brief Get button state for LED feedback
 * @param s1_pressed Pointer to store S1 state
 * @param s2_pressed Pointer to store S2 state
 */
void Buttons_GetState(bool* s1_pressed, bool* s2_pressed);

#endif // BUTTONS_H
