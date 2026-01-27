#ifndef APP_H
#define APP_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @file app.h
 * @brief Main application interface
 */

// ============================================================================
// Types
// ============================================================================

/**
 * @brief Display modes
 */
typedef enum {
    MODE_COMPOSITE = 0,  ///< Composite color mixing mode
    MODE_INDIVIDUAL = 1  ///< Individual color control mode
} DisplayMode_t;

// ============================================================================
// Function Prototypes
// ============================================================================

/**
 * @brief Initialize application and all drivers
 * @return true on success, false on error
 * 
 * @note Call once during startup before entering main loop
 * @note If this returns false, LED1 will be lit to indicate error
 */
bool app_setup(void);

/**
 * @brief Main application update function
 * 
 * @note Call repeatedly in main loop
 * @note Non-blocking - returns immediately
 */
void app_loop(void);

#endif // APP_H
