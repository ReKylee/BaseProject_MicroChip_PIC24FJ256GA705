/*
 * Implementation of alarm functionality
 */

#include <stdlib.h>

#include "alarm.h"
#include "../shared/watch_state.h"
#include "../../oledDriver/oledC.h"



// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void Alarm_Init(void) {
}

void Alarm_Check(void) {
    WatchState_t* state = Watch_GetState();
    
    if (!state->alarm.enabled || state->alarm.triggered) {
        return;
    }
    
    if (state->current_time.hour == state->alarm.hour &&
        state->current_time.minute == state->alarm.minute &&
        state->current_time.second == 0) {
        
        state->alarm.triggered = true;
        state->alarm.trigger_count = 0;
        state->prev_display_mode = state->display_mode;
        state->prev_watch_face = state->watch_face;
        state->display_mode = MODE_WATCH;
        state->watch_face = FACE_ALARM;
        state->needs_full_redraw = true;
    }
}

void Alarm_SetTime(uint8_t hour, uint8_t minute) {
    WatchState_t* state = Watch_GetState();
    
    if (hour < 24 && minute < 60) {
        state->alarm.hour = hour;
        state->alarm.minute = minute;
        state->needs_redraw = true;
    }
}

void Alarm_Enable(void) {
    WatchState_t* state = Watch_GetState();
    state->alarm.enabled = true;
    state->needs_redraw = true;
}

void Alarm_Disable(void) {
    WatchState_t* state = Watch_GetState();
    state->alarm.enabled = false;
    state->alarm.triggered = false;
    state->needs_redraw = true;
}

void Alarm_Toggle(void) {
    WatchState_t* state = Watch_GetState();
    
    if (state->alarm.enabled) {
        Alarm_Disable();
    } else {
        Alarm_Enable();
    }
}

void Alarm_Dismiss(void) {
    WatchState_t* state = Watch_GetState();
    state->alarm.triggered = false;
    state->alarm.trigger_count = 0;
    if (!state->alarm.recurring) {
        state->alarm.enabled = false;
    }
    state->display_mode = state->prev_display_mode;
    state->watch_face = state->prev_watch_face;
    oledC_sendCommand(OLEDC_CMD_SET_DISPLAY_MODE_ON, NULL, 0);
    oledC_setBackground(COLOR_BG);
    state->needs_full_redraw = true;
}

bool Alarm_IsRinging(void) {
    WatchState_t* state = Watch_GetState();
    return state->alarm.triggered;
}

void Alarm_Update(void) {
    WatchState_t* state = Watch_GetState();
    
    if (state->alarm.triggered) {
        state->alarm.trigger_count++;
        
        if (state->alarm.trigger_count >= ALARM_AUTO_OFF_SECONDS) {
            Alarm_Dismiss();
        }
    }
}
