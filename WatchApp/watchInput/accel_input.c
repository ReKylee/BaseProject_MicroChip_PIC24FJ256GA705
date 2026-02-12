/*
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

static int16_t s_last_x = 0, s_last_y = 0, s_last_z = 0;
static bool s_first_read = true;
static uint8_t s_shake_count = 0;
static uint32_t s_last_shake_time = 0;

// ============================================================================
// PRIVATE FUNCTIONS
// ============================================================================

static inline bool is_flipped(int16_t z) {
    return z < -FLIP_THRESHOLD_Z;
}

static bool is_shaking(int16_t x, int16_t y, int16_t z) {
    int32_t dx = x - s_last_x;
    int32_t dy = y - s_last_y;
    int32_t dz = z - s_last_z;
    int64_t delta_sq = (int64_t)dx * dx + (int64_t)dy * dy + (int64_t)dz * dz;
    int64_t deadzone_sq = (int64_t)SHAKE_DEADZONE * SHAKE_DEADZONE;
    int64_t threshold_sq = (int64_t)SHAKE_THRESHOLD_DELTA * SHAKE_THRESHOLD_DELTA;

    // Ignore very small movements
    if (delta_sq < deadzone_sq)
        return false;

    // Check if total delta exceeds threshold
    return delta_sq >= threshold_sq;
}

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void AccelInput_Init(void) {
    ACCEL3_Init(NULL);
    s_first_read = true;
    s_shake_count = 0;
    s_last_shake_time = 0;
}

AccelEvent_t AccelInput_Check(void) {
    int16_t x, y, z;
    ACCEL3_ReadXYZ(&x, &y, &z);

    if (s_first_read) {
        s_last_x = x;
        s_last_y = y;
        s_last_z = z;
        s_first_read = false;
        return ACCEL_NONE;
    }

    // --- Flip detection ---
    if (is_flipped(z)) {
        s_last_x = x;
        s_last_y = y;
        s_last_z = z;
        return ACCEL_FLIP;
    }

    // --- Shake detection ---
    if (is_shaking(x, y, z)) {
        uint32_t now = Timekeeper_GetMillis();

        if (now - s_last_shake_time > SHAKE_TIMEOUT_MS)
            s_shake_count = 0;

        s_shake_count++;
        s_last_shake_time = now;

        if (s_shake_count >= SHAKE_COUNT_REQUIRED) {
            s_shake_count = 0;
            s_last_x = x;
            s_last_y = y;
            s_last_z = z;
            return ACCEL_SHAKE;
        }
    } else {
        // Update last values only if not shaking (filter out noise)
        s_last_x = x;
        s_last_y = y;
        s_last_z = z;
    }

    return ACCEL_NONE;
}
