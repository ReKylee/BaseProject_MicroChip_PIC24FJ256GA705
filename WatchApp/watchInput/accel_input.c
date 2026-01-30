/*
 * accel_input.c
 * Implementation of accelerometer event detection
 */

#include "accel_input.h"
#include "../../accel3Driver/ACCEL3.h"
#include <stdbool.h>
#include <stdlib.h>

// ============================================================================
// CONFIGURATION
// ============================================================================

#define FLIP_THRESHOLD          8000    // Z-axis threshold for flip detection
#define SHAKE_THRESHOLD         10000   // Total acceleration for shake
#define SHAKE_COUNT_REQUIRED    3       // Number of shake events needed
#define SHAKE_TIMEOUT_MS        1000    // Time window for shake detection

// ============================================================================
// PRIVATE DATA
// ============================================================================

static uint8_t shake_count = 0;
static uint32_t last_shake_time = 0;
static int16_t last_z = 0;
static bool first_read = true;

// ============================================================================
// PRIVATE FUNCTIONS
// ============================================================================

static bool IsFlipped(int16_t z) {
    // Check if device is flipped (OLED facing down)
    // Negative Z indicates flip
    return (z < -FLIP_THRESHOLD);
}

static bool IsShaking(int16_t x, int16_t y, int16_t z) {
    // Calculate total acceleration magnitude change
    if (first_read) {
        first_read = false;
        return false;
    }
    
    // Simple shake detection: large change in any axis
    int32_t total = (int32_t)x * x + (int32_t)y * y + (int32_t)z * z;
    
    if (total > (int32_t)SHAKE_THRESHOLD * SHAKE_THRESHOLD) {
        return true;
    }
    
    return false;
}

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void AccelInput_Init(void) {
    ACCEL3_Init(NULL);

    first_read = true;
    shake_count = 0;
    last_shake_time = 0;
}

AccelEvent_t AccelInput_Check(void) {
    // Read accelerometer
    int16_t x, y, z;
    ACCEL3_ReadXYZ(&x, &y, &z);
    
    // Check for flip
    if (IsFlipped(z)) {
        return ACCEL_FLIP;
    }
    
    // Check for shake
    if (IsShaking(x, y, z)) {
        uint32_t current_time = 0; // Would use WatchTimer_GetMillis()
        
        // Reset shake count if timeout occurred
        if (current_time - last_shake_time > SHAKE_TIMEOUT_MS) {
            shake_count = 0;
        }
        
        shake_count++;
        last_shake_time = current_time;
        
        // Detect shake if enough shakes detected
        if (shake_count >= SHAKE_COUNT_REQUIRED) {
            shake_count = 0;
            return ACCEL_SHAKE;
        }
    }
    
    last_z = z;
    first_read = false;
    
    return ACCEL_NONE;
}
