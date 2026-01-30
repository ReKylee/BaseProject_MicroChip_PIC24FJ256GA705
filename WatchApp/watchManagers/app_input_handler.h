#ifndef APP_INPUT_HANDLER_H
#define APP_INPUT_HANDLER_H

#include "../shared/watch_state.h"
#include "../watchInput/buttons.h"
#include "../watchInput/accel_input.h"
#include "../watchMenu/menu.h"
#include "../watchCore/alarm.h"
#include "../watchFaces/digital_face.h"
#include "../watchFaces/analog_face.h"
#include "../watchFaces/binary_face.h"
#include "../../ledDriver/LED.h"
#include "../../System/delay.h"
#include "../watchInput/potentiometer.h"
#include "../pomodoroTimer/pomodoro.h"

/**
 * @brief Handles input events based on the current watch display mode.
 *
 * @param btn The button event that occurred.
 * @param accel The accelerometer event that occurred.
 */
void APP_HandleInputEvents(ButtonEvent_t btn, AccelEvent_t accel);

#endif // APP_INPUT_HANDLER_H