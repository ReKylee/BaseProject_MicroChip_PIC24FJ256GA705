/*
 * alarm.c
 * Implementation of alarm functionality
 */

#include "alarm.h"
#include "../shared/watch_state.h"
#include "../../oledDriver/oledC.h"

#define ALARM_AUTO_OFF_SECONDS  20

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void Alarm_Init(void) {
    // Alarm state is in global WatchState
}

void Alarm_Check(void) {
    WatchState_t* state = Watch_GetState();
    
    // Only check if alarm is enabled and not already triggered
    if (!state->alarm.enabled || state->alarm.triggered) {
        return;
    }
    
    // Check if current time matches alarm time
    if (state->current_time.hour == state->alarm.hour &&
        state->current_time.minute == state->alarm.minute &&
        state->current_time.second == 0) {  // Trigger at :00 seconds
        
        // Trigger alarm
        state->alarm.triggered = true;
        state->alarm.trigger_count = 0;
        state->prev_watch_face = state->watch_face; // Store current watch face
        state->watch_face = FACE_ALARM; // Switch to alarm face
        state->needs_redraw = true;
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
    state->watch_face = state->prev_watch_face; // Restore previous watch face
    oledC_setBackground(COLOR_BG); // Reset background
    state->needs_full_redraw = true; // Force full redraw to show restored face
}

bool Alarm_IsRinging(void) {
    WatchState_t* state = Watch_GetState();
    return state->alarm.triggered;
}

void Alarm_Update(void) {
    WatchState_t* state = Watch_GetState();
    
    // If alarm is triggered, increment counter
    if (state->alarm.triggered) {
        state->alarm.trigger_count++;
        
        // Auto-dismiss after 20 seconds
        if (state->alarm.trigger_count >= ALARM_AUTO_OFF_SECONDS) {
            Alarm_Dismiss();
        }
    }
}
