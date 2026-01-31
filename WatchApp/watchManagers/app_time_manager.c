#include <stdbool.h>
#include <stdint.h> // For uint32_t

#include "app_time_manager.h"
#include "../shared/watch_state.h"
#include "../watchCore/timekeeper.h"
#include "../watchCore/alarm.h"
#include "../pomodoroTimer/pomodoro.h"
#include "../../Timers/Timers.h"

void APP_UpdateTimeAndAlarms(uint32_t* last_uptime_s) {
    WatchState_t* state = Watch_GetState();

    // --- Handle Time Updates ---
    uint32_t current_uptime_s = Timer_GetTicks(1);
    if (current_uptime_s != *last_uptime_s) {
        *last_uptime_s = current_uptime_s;
        
        Timekeeper_GetTime(&state->current_time);
        
        Alarm_Check();
        Alarm_Update();
        
        if (state->display_mode == MODE_POMODORO) Pomodoro_Update();
        
        state->needs_redraw = true;
    }
}