#ifndef APP_TIME_MANAGER_H
#define APP_TIME_MANAGER_H

#include <stdint.h> 

#include "../shared/watch_state.h"
#include "../watchCore/timekeeper.h"
#include "../watchCore/alarm.h"
#include "../pomodoroTimer/pomodoro.h"
#include "../../Timers/Timers.h"

/**
 * @brief Handles time updates, alarm checks, and pomodoro timer updates.
 *
 * @param last_uptime_s Pointer to a variable holding the last known uptime in seconds.
 *                      This value will be updated by the function.
 */
void APP_UpdateTimeAndAlarms(uint32_t* last_uptime_s);

#endif // APP_TIME_MANAGER_H