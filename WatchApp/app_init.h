#ifndef APP_INIT_H
#define APP_INIT_H

#include <xc.h>
#include "shared/watch_state.h"
#include "watchCore/timekeeper.h"
#include "watchFaces/digital_face.h"
#include "watchFaces/analog_face.h"
#include "watchFaces/binary_face.h"
#include "watchMenu/menu.h"
#include "watchInput/buttons.h"
#include "watchInput/potentiometer.h"
#include "watchInput/accel_input.h"
#include "pomodoroTimer/pomodoro.h"
#include "../ledDriver/LED.h"
#include "../System/system.h"
#include "../oledDriver/oledC.h"
#include "../accel3Driver/ACCEL3.h"
#include "../adcDriver/ADC.h"


/**
 * @brief Initializes all necessary hardware and application modules.
 */
void APP_InitializeHardware(void);

#endif // APP_INIT_H