/*
 * accel_input.c
 * Fixed robust accelerometer detection
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "accel_input.h"
#include "../../accel3Driver/ACCEL3.h"
#include "../watchCore/timekeeper.h"

// ============================================================================
// CONFIGURATION
// ============================================================================

#define FLIP_THRESHOLD_Z        200      // Z-axis threshold for flip (negative Z)
#define SHAKE_THRESHOLD_DELTA   200      // Minimum delta squared magnitude for shake
#define SHAKE_COUNT_REQUIRED    3
#define SHAKE_TIMEOUT_MS        1000
#define SHAKE_DEADZONE          50       // Ignore very small movements (noise)

// ============================================================================
// PRIVATE DATA
// ============================================================================

static int16_t last_x = 0, last_y = 0, last_z = 0;
static bool first_read = true;
static uint8_t shake_count = 0;
static uint32_t last_shake_time = 0;

// ============================================================================
// PRIVATE FUNCTIONS
// ============================================================================

static inline bool IsFlipped(int16_t z) {
    return z < -FLIP_THRESHOLD_Z;
}

static bool IsShaking(int16_t x, int16_t y, int16_t z) {
    int32_t dx = x - last_x;
    int32_t dy = y - last_y;
    int32_t dz = z - last_z;

    // Ignore very small movements
    if (dx*dx + dy*dy + dz*dz < SHAKE_DEADZONE*SHAKE_DEADZONE)
        return false;

    // Check if total delta exceeds threshold
    return (dx*dx + dy*dy + dz*dz >= (int32_t)SHAKE_THRESHOLD_DELTA*SHAKE_THRESHOLD_DELTA);
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
    int16_t x, y, z;
    ACCEL3_ReadXYZ(&x, &y, &z);

    if (first_read) {
        last_x = x;
        last_y = y;
        last_z = z;
        first_read = false;
        return ACCEL_NONE;
    }

    // --- Flip detection ---
    if (IsFlipped(z)) {
        last_x = x;
        last_y = y;
        last_z = z;
        return ACCEL_FLIP;
    }

    // --- Shake detection ---
    if (IsShaking(x, y, z)) {
        uint32_t now = Timekeeper_GetMillis();

        if (now - last_shake_time > SHAKE_TIMEOUT_MS)
            shake_count = 0;

        shake_count++;
        last_shake_time = now;

        if (shake_count >= SHAKE_COUNT_REQUIRED) {
            shake_count = 0;
            last_x = x;
            last_y = y;
            last_z = z;
            return ACCEL_SHAKE;
        }
    } else {
        // Update last values only if not shaking (filter out noise)
        last_x = x;
        last_y = y;
        last_z = z;
    }

    return ACCEL_NONE;
}
