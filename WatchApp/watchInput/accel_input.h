/*
 * accel_input.h
 * Accelerometer input for flip and shake detection
 */

#ifndef ACCEL_INPUT_H
#define ACCEL_INPUT_H

#include "../shared/watch_types.h"

// ============================================================================
// ACCELEROMETER FUNCTIONS
// ============================================================================

/**
 * @brief Initialize accelerometer module
 */
void AccelInput_Init(void);

/**
 * @brief Check for accelerometer events
 * @return Accelerometer event (flip or shake)
 */
AccelEvent_t AccelInput_Check(void);

#endif // ACCEL_INPUT_H
