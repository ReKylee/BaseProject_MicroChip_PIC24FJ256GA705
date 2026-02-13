/*
 * App initialization entry point.
 */

#ifndef APP_INIT_H
#define APP_INIT_H

#ifndef ACCEL_INIT_HALT_ON_ERROR
#define ACCEL_INIT_HALT_ON_ERROR 1
#endif

#ifndef ACCEL_INIT_SETTLE_DELAY_MS
#define ACCEL_INIT_SETTLE_DELAY_MS 200
#endif

#ifndef ACCEL_ERROR_SCREEN_MS
#define ACCEL_ERROR_SCREEN_MS 1000
#endif

#ifndef ACCEL_ERROR_BLINK_MS
#define ACCEL_ERROR_BLINK_MS 200
#endif

/**
 * @brief Initializes all necessary hardware and application modules.
 */
void APP_InitializeHardware(void);

#endif // APP_INIT_H
