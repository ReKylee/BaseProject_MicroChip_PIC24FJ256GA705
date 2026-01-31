/*
 * pomodoro.c
 * Implementation of Pomodoro timer
 */

#include "pomodoro.h"
#include "../shared/watch_state.h"
#include "../shared/watch_types.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include <stdio.h>

// ============================================================================
// PRIVATE FUNCTIONS
// ============================================================================

static void StartWorkSession(WatchState_t* state) {
    state->pomodoro.state = POMODORO_WORK;
    state->pomodoro.remaining_seconds = state->pomodoro.work_minutes * 60;
    state->pomodoro.paused = false;
}

static void StartBreak(WatchState_t* state) {
    // Determine break type
    if (state->pomodoro.work_sessions >= state->pomodoro.long_break_after_sessions) {
        state->pomodoro.state = POMODORO_LONG_BREAK;
        state->pomodoro.remaining_seconds = state->pomodoro.long_break_minutes * 60;
        state->pomodoro.work_sessions = 0;  // Reset counter
    } else {
        state->pomodoro.state = POMODORO_SHORT_BREAK;
        state->pomodoro.remaining_seconds = state->pomodoro.short_break_minutes * 60;
    }
    state->pomodoro.paused = false;
}

static void DrawProgressBar(WatchState_t* state, uint16_t remaining, uint16_t total) {
    // Draw progress bar at bottom of screen
    uint8_t bar_width = 80;
    uint8_t bar_height = 8;
    uint8_t bar_x = 8;
    uint8_t bar_y = 80;
    
    // Draw outline
    oledC_DrawRectangle(bar_x - 1, bar_y - 1, 
                       bar_x + bar_width + 1, bar_y + bar_height + 1, 
                       COLOR_DIM);
    
    // Draw filled portion
    uint8_t fill_width = (remaining * bar_width) / total;
    if (fill_width > 0) {
        oledC_DrawRectangle(bar_x, bar_y, 
                           bar_x + fill_width, bar_y + bar_height, 
                           COLOR_SUCCESS);
    }
}

static void DrawSessionCounter(WatchState_t* state, uint8_t sessions) {
    // Draw completed work session indicators (tomatoes!)
    for (uint8_t i = 0; i < state->pomodoro.long_break_after_sessions; i++) {
        uint8_t x = 10 + (i * 20);
        uint8_t y = 10;
        
        if (i < sessions) {
            // Filled tomato
            oledC_DrawCircle(x, y, 5, COLOR_WARNING);
        } else {
            // Empty tomato
            oledC_DrawRing(x, y, 5, 1, COLOR_DIM);
        }
    }
}

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void Pomodoro_Init(void) {
    WatchState_t* state = Watch_GetState();
    state->pomodoro.state = POMODORO_IDLE;
    state->pomodoro.remaining_seconds = state->pomodoro.work_minutes * 60;
    state->pomodoro.work_sessions = 0;
    state->pomodoro.paused = false;
}

void Pomodoro_Start(void) {
    WatchState_t* state = Watch_GetState();
    
    if (state->pomodoro.state == POMODORO_IDLE) {
        StartWorkSession(state);
    } else {
        state->pomodoro.paused = false;
    }
}

void Pomodoro_Pause(void) {
    WatchState_t* state = Watch_GetState();
    state->pomodoro.paused = true;
}

void Pomodoro_Reset(void) {
    Pomodoro_Init();
}

void Pomodoro_Update(void) {
    WatchState_t* state = Watch_GetState();
    
    // Don't update if paused or idle
    if (state->pomodoro.paused || state->pomodoro.state == POMODORO_IDLE) {
        return;
    }
    
    // Decrement timer
    if (state->pomodoro.remaining_seconds > 0) {
        state->pomodoro.remaining_seconds--;
    }
    
    // Check if timer completed
    if (state->pomodoro.remaining_seconds == 0) {
        if (state->pomodoro.state == POMODORO_WORK) {
            // Work session completed
            state->pomodoro.work_sessions++;
            StartBreak(state);
        } else {
            // Break completed
            StartWorkSession(state);
        }
    }
    
    state->needs_redraw = true;
}

void Pomodoro_Draw(void) {
    WatchState_t* state = Watch_GetState();
    
    // Clear screen
    oledC_setBackground(COLOR_BG);
    
    // Draw session counter
    DrawSessionCounter(state, state->pomodoro.work_sessions);
    
    // Draw state label
    const char* state_label;
    uint16_t label_color;
    uint16_t total_seconds;
    
    switch (state->pomodoro.state) {
        case POMODORO_WORK:
            state_label = "WORK";
            label_color = COLOR_WARNING;
            total_seconds = state->pomodoro.work_minutes * 60;
            break;
        case POMODORO_SHORT_BREAK:
            state_label = "BREAK";
            label_color = COLOR_SUCCESS;
            total_seconds = state->pomodoro.short_break_minutes * 60;
            break;
        case POMODORO_LONG_BREAK:
            state_label = "LONG BREAK";
            label_color = COLOR_SUCCESS;
            total_seconds = state->pomodoro.long_break_minutes * 60;
            break;
        default:
            state_label = "READY";
            label_color = COLOR_DIM;
            total_seconds = state->pomodoro.work_minutes * 60;
            break;
    }
    
    oledC_DrawString(30, 25, 2, 1, (uint8_t*)state_label, label_color);
    
    // Draw remaining time (MM:SS)
    uint16_t minutes = state->pomodoro.remaining_seconds / 60;
    uint16_t seconds = state->pomodoro.remaining_seconds % 60;
    
    char time_str[6];
    sprintf(time_str, "%02d:%02d", minutes, seconds);
    oledC_DrawString(20, 45, 3, 3, (uint8_t*)time_str, COLOR_PRIMARY);
    
    // Draw progress bar
    DrawProgressBar(state, state->pomodoro.remaining_seconds, total_seconds);
    
    // Draw pause indicator if paused
    if (state->pomodoro.paused) {
        oledC_DrawString(35, 70, 1, 1, (uint8_t*)"PAUSED", COLOR_ACCENT);
    }
}

void Pomodoro_HandleInput(bool start_pause, bool reset) {
    WatchState_t* state = Watch_GetState();
    
    if (reset) {
        Pomodoro_Reset();
    } else if (start_pause) {
        if (state->pomodoro.paused || state->pomodoro.state == POMODORO_IDLE) {
            Pomodoro_Start();
        } else {
            Pomodoro_Pause();
        }
    }
}
