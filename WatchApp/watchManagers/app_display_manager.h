#ifndef APP_DISPLAY_MANAGER_H
#define APP_DISPLAY_MANAGER_H

#include <stdbool.h> 
#include <stdint.h>  

#include "../shared/watch_state.h"
#include "../../oledDriver/oledC.h"
#include "../watchFaces/digital_face.h"
#include "../watchFaces/analog_face.h"
#include "../watchFaces/binary_face.h"
#include "../watchMenu/menu.h"
#include "../pomodoroTimer/pomodoro.h"
#include "../watchCore/alarm.h"
#include "../watchCore/timekeeper.h"

/**
 * @brief Manages and updates the watch display based on the current state.
 */
void APP_UpdateDisplay(void);

#endif // APP_DISPLAY_MANAGER_H