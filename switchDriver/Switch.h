#ifndef SWITCH_H
#define SWITCH_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @file Switch.h
 * @brief Debounced switch input driver for PIC24FJ256GA705
 * 
 * Features:
 * - Hardware debouncing with configurable delay
 * - Edge detection (press/release)
 * - Non-blocking operation
 * - Minimal memory footprint
 */

// ============================================================================
// Configuration
// ============================================================================

#define DEBOUNCE_TIME_MS 25  // Adjust debounce time as needed

// Hardware pin definitions
#define S1_MASK (1 << 11)    // RA11
#define S2_MASK (1 << 12)    // RA12

// ============================================================================
// Macros - Inline for zero overhead
// ============================================================================

/** @brief Check if S1 is currently pressed (active low) */
#define S1_IsDown() (!(PORTA & S1_MASK))

/** @brief Check if S1 is currently released */
#define S1_IsUp() (!S1_IsDown())

/** @brief Check if S2 is currently pressed (active low) */
#define S2_IsDown() (!(PORTA & S2_MASK))

/** @brief Check if S2 is currently released */
#define S2_IsUp() (!S2_IsDown())

/** @brief Initialize S1 as input */
#define S1_Init() (TRISA |= S1_MASK)

/** @brief Initialize S2 as input */
#define S2_Init() (TRISA |= S2_MASK)

// ============================================================================
// Function Prototypes
// ============================================================================

/**
 * @brief Initialize both switches
 * @note Call once during system initialization
 */
void Switch_Init(void);

/**
 * @brief Check if S1 was just pressed (rising edge detection)
 * @return true if S1 was pressed since last call, false otherwise
 * @note Debounced - call regularly in main loop or timer
 */
bool S1_WasPressed(void);

/**
 * @brief Check if S1 was just released (falling edge detection)
 * @return true if S1 was released since last call, false otherwise
 * @note Debounced - call regularly in main loop or timer
 */
bool S1_WasReleased(void);

/**
 * @brief Check if S2 was just pressed (rising edge detection)
 * @return true if S2 was pressed since last call, false otherwise
 * @note Debounced - call regularly in main loop or timer
 */
bool S2_WasPressed(void);

/**
 * @brief Check if S2 was just released (falling edge detection)
 * @return true if S2 was released since last call, false otherwise
 * @note Debounced - call regularly in main loop or timer
 */
bool S2_WasReleased(void);

/**
 * @brief Reset switch state (clear any pending edges)
 * @note Useful after mode changes or to ignore switch events
 */
void Switch_ResetState(void);

#endif // SWITCH_H
