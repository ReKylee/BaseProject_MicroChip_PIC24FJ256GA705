/*
 * Per-second update coordinator for time, alarms, and pomodoro.
 */

#include <stdbool.h>
#include <stdint.h>

#include "app_time_manager.h"
#include "../shared/watch_state.h"
#include "../shared/watch_settings_store.h"
#include "../watchCore/timekeeper.h"
#include "../watchCore/alarm.h"
#include "../pomodoroTimer/pomodoro.h"
#include "../../Timers/Timers.h"

#define SETTINGS_AUTOSAVE_PERIOD_S 900UL

static uint32_t s_last_settings_save_uptime_s = 0;

void APP_UpdateTimeAndAlarms(uint32_t* last_uptime_s) {
    WatchState_t* state = Watch_GetState();
    uint32_t current_uptime_s = Timer_GetTicks(1);
    if (current_uptime_s != *last_uptime_s) {
        *last_uptime_s = current_uptime_s;
        
        Timekeeper_GetTime(&state->current_time);
        
        Alarm_Check();
        Alarm_Update();
        
        if (state->display_mode == MODE_POMODORO) Pomodoro_Update();

        if ((current_uptime_s - s_last_settings_save_uptime_s) >= SETTINGS_AUTOSAVE_PERIOD_S) {
            (void)WatchSettingsStore_SaveState(state);
            s_last_settings_save_uptime_s = current_uptime_s;
        }
        
        state->needs_redraw = true;
    }
}
