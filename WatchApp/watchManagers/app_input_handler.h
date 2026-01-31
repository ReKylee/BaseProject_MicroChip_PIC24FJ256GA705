#ifndef APP_INPUT_HANDLER_H
#define APP_INPUT_HANDLER_H

#include "../shared/watch_types.h"

/**
 * @brief Handles input events based on the current watch display mode.
 *
 * @param btn The button event that occurred.
 * @param accel The accelerometer event that occurred.
 */
void APP_HandleInputEvents(ButtonEvent_t btn, AccelEvent_t accel);

#endif // APP_INPUT_HANDLER_H