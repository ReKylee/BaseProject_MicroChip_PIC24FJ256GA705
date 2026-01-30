/*
 * watch_state.h
 * Central state management for the watch application
 * Single source of truth - no data duplication
 */

#ifndef WATCH_STATE_H
#define WATCH_STATE_H

#include "watch_types.h"

// ============================================================================
// GLOBAL WATCH STATE
// ============================================================================

typedef struct {
    // Time and Date
    Time_t current_time;
    Date_t current_date;
    TimeFormat_t time_format;
    
    // Display
    WatchFace_t watch_face;
    DisplayMode_t display_mode;
    
    // Alarm
    Alarm_t alarm;
    
    // Menu
    MenuState_t menu_state;
    uint8_t menu_selection;
    uint8_t menu_edit_field;    // Which field is being edited
    
    // Pomodoro
    Pomodoro_t pomodoro;
    
    // Flags
    bool needs_redraw;          // Set when display needs partial update
    bool needs_full_redraw;     // Set when a full screen refresh is needed
    bool second_tick;           // Set by 1Hz ISR
    bool last_alarm_ringing; // Tracks if alarm was ringing in the previous second
    uint8_t last_alarm_second_flash_check; // To control flashing rate
    
    // Previous state for alarm exit
    WatchFace_t prev_watch_face;
} WatchState_t;

// ============================================================================
// GLOBAL STATE ACCESS
// ============================================================================

// Get pointer to global watch state
WatchState_t* Watch_GetState(void);

// Initialize watch state
void Watch_InitState(void);

#endif // WATCH_STATE_H
