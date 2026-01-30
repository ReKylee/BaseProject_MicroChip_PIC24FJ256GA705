/*
 * watch_state.c
 * Implementation of central state management
 */

#include "watch_state.h"
#include <string.h>

// ============================================================================
// PRIVATE DATA
// ============================================================================

static WatchState_t g_watch_state;

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

WatchState_t* Watch_GetState(void) {
    return &g_watch_state;
}

void Watch_InitState(void) {
    // Clear everything
    memset(&g_watch_state, 0, sizeof(WatchState_t));
    
    // Set default time (12:00:00)
    g_watch_state.current_time.hour = 12;
    g_watch_state.current_time.minute = 0;
    g_watch_state.current_time.second = 0;
    
    // Set default date (01/01)
    g_watch_state.current_date.day = 1;
    g_watch_state.current_date.month = 1;
    
    // Set default format
    g_watch_state.time_format = FORMAT_24H;
    
    // Set default watch face
    g_watch_state.watch_face = FACE_DIGITAL;
    
    // Set display mode
    g_watch_state.display_mode = MODE_WATCH;
    
    // Initialize alarm (disabled)
    g_watch_state.alarm.enabled = false;
    g_watch_state.alarm.triggered = false;
    
    // Pomodoro defaults (25/5 minute intervals)
    g_watch_state.pomodoro.state = POMODORO_IDLE;
    g_watch_state.pomodoro.remaining_seconds = 25 * 60;
    g_watch_state.pomodoro.work_sessions = 0;
    g_watch_state.pomodoro.paused = false;
    
    // Force initial full redraw
    g_watch_state.needs_redraw = false;
    g_watch_state.needs_full_redraw = true;
}
