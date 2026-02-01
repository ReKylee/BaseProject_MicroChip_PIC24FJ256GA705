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

#define POMO_TOMATO_Y 8
#define POMO_TOMATO_R 5
#define POMO_LABEL_Y 22
#define POMO_TIME_Y 38
#define POMO_TIME_SCALE 3
#define POMO_BAR_X 8
#define POMO_BAR_Y 80
#define POMO_BAR_W 80
#define POMO_BAR_H 8
#define POMO_PAUSE_Y 66

static PomodoroState_t s_last_state = POMODORO_IDLE;
static uint16_t s_last_remaining = 0xFFFF;
static uint8_t s_last_sessions = 0xFF;
static bool s_last_paused = false;
static uint8_t s_last_fill_width = 0xFF;
static uint16_t s_last_total = 0xFFFF;
static uint8_t s_last_min = 0xFF;
static uint8_t s_last_sec = 0xFF;

static const char* get_state_label(PomodoroState_t state) {
    switch (state) {
        case POMODORO_WORK: return "WORK";
        case POMODORO_SHORT_BREAK: return "BREAK";
        case POMODORO_LONG_BREAK: return "LONG";
        default: return "READY";
    }
}

static uint8_t get_state_label_len(PomodoroState_t state) {
    switch (state) {
        case POMODORO_WORK: return 4;
        case POMODORO_SHORT_BREAK: return 5;
        case POMODORO_LONG_BREAK: return 4;
        default: return 5;
    }
}
static uint16_t get_state_color(PomodoroState_t state) {
    switch (state) {
        case POMODORO_WORK: return COLOR_WARNING;
        case POMODORO_SHORT_BREAK: return COLOR_SUCCESS;
        case POMODORO_LONG_BREAK: return COLOR_SUCCESS;
        default: return COLOR_DIM;
    }
}

static uint16_t get_total_seconds(WatchState_t* state) {
    switch (state->pomodoro.state) {
        case POMODORO_WORK: return (uint16_t)(state->pomodoro.work_minutes * 60);
        case POMODORO_SHORT_BREAK: return (uint16_t)(state->pomodoro.short_break_minutes * 60);
        case POMODORO_LONG_BREAK: return (uint16_t)(state->pomodoro.long_break_minutes * 60);
        default: return (uint16_t)(state->pomodoro.work_minutes * 60);
    }
}

static void start_work_session(WatchState_t* state) {
    state->pomodoro.state = POMODORO_WORK;
    state->pomodoro.remaining_seconds = state->pomodoro.work_minutes * 60;
    state->pomodoro.paused = false;
}

static void start_break(WatchState_t* state) {
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

static void draw_time_full(uint16_t remaining_seconds) {
    uint8_t minutes = (uint8_t)(remaining_seconds / 60);
    uint8_t seconds = (uint8_t)(remaining_seconds % 60);
    char min_str[3];
    char sec_str[3];
    sprintf(min_str, "%02d", minutes);
    sprintf(sec_str, "%02d", seconds);

    uint8_t min_scale = 3;
    uint8_t sec_scale = 2;
    uint8_t min_w = (uint8_t)(2 * (5 * min_scale + 1));
    uint8_t colon_w = (uint8_t)(1 * (5 * sec_scale + 1));
    uint8_t sec_w = (uint8_t)(2 * (5 * sec_scale + 1));
    uint8_t total_w = (uint8_t)(min_w + colon_w + sec_w + 2);
    uint8_t x0 = (uint8_t)((96 - total_w) / 2);

    oledC_DrawString(x0, POMO_TIME_Y, min_scale, min_scale, (uint8_t*)min_str, COLOR_PRIMARY);
    oledC_DrawString((uint8_t)(x0 + min_w + 1), (uint8_t)(POMO_TIME_Y + 6), sec_scale, sec_scale, (uint8_t*)":", COLOR_DIM);
    oledC_DrawString((uint8_t)(x0 + min_w + colon_w + 2), (uint8_t)(POMO_TIME_Y + 6), sec_scale, sec_scale, (uint8_t*)sec_str, COLOR_PRIMARY);
}

static void draw_time_partial(uint16_t remaining_seconds) {
    uint8_t minutes = (uint8_t)(remaining_seconds / 60);
    uint8_t seconds = (uint8_t)(remaining_seconds % 60);
    uint8_t min_scale = 3;
    uint8_t sec_scale = 2;
    uint8_t min_w = (uint8_t)(2 * (5 * min_scale + 1));
    uint8_t colon_w = (uint8_t)(1 * (5 * sec_scale + 1));
    uint8_t sec_w = (uint8_t)(2 * (5 * sec_scale + 1));
    uint8_t total_w = (uint8_t)(min_w + colon_w + sec_w + 2);
    uint8_t x0 = (uint8_t)((96 - total_w) / 2);

    if (minutes != s_last_min) {
        char min_str[3];
        sprintf(min_str, "%02d", minutes);
        oledC_DrawRectangle(x0 - 1, POMO_TIME_Y - 1,
                            (uint8_t)(x0 + min_w + 1), (uint8_t)(POMO_TIME_Y + min_scale * 8 + 1),
                            COLOR_BG);
        oledC_DrawString(x0, POMO_TIME_Y, min_scale, min_scale, (uint8_t*)min_str, COLOR_PRIMARY);
        s_last_min = minutes;
    }

    if (seconds != s_last_sec) {
        char sec_str[3];
        sprintf(sec_str, "%02d", seconds);
        uint8_t sec_x = (uint8_t)(x0 + min_w + colon_w + 2);
        uint8_t sec_y = (uint8_t)(POMO_TIME_Y + 6);
        oledC_DrawRectangle((uint8_t)(x0 + min_w), (uint8_t)(POMO_TIME_Y + 4),
                            (uint8_t)(sec_x + sec_w + 1), (uint8_t)(sec_y + sec_scale * 8 + 1),
                            COLOR_BG);
        oledC_DrawString((uint8_t)(x0 + min_w + 1), sec_y, sec_scale, sec_scale, (uint8_t*)":", COLOR_DIM);
        oledC_DrawString(sec_x, sec_y, sec_scale, sec_scale, (uint8_t*)sec_str, COLOR_PRIMARY);
        s_last_sec = seconds;
    }
}

static void draw_progress_bar_full(uint16_t remaining, uint16_t total) {
    oledC_DrawRectangle(POMO_BAR_X - 1, POMO_BAR_Y - 1,
                        POMO_BAR_X + POMO_BAR_W + 1, POMO_BAR_Y + POMO_BAR_H + 1,
                        COLOR_DIM);
    uint16_t elapsed = (remaining > total) ? 0 : (uint16_t)(total - remaining);
    uint8_t fill_width = (uint8_t)((elapsed * POMO_BAR_W) / total);
    oledC_DrawRectangle(POMO_BAR_X, POMO_BAR_Y,
                        (uint8_t)(POMO_BAR_X + POMO_BAR_W), (uint8_t)(POMO_BAR_Y + POMO_BAR_H),
                        COLOR_BG);
    if (fill_width > 0) {
        oledC_DrawRectangle(POMO_BAR_X, POMO_BAR_Y,
                            (uint8_t)(POMO_BAR_X + fill_width), (uint8_t)(POMO_BAR_Y + POMO_BAR_H),
                            COLOR_SUCCESS);
    }
    s_last_fill_width = fill_width;
    s_last_total = total;
}

static void draw_progress_bar_partial(uint16_t remaining, uint16_t total) {
    if (total == 0) return;
    if (s_last_total != total) {
        draw_progress_bar_full(remaining, total);
        return;
    }
    uint16_t elapsed = (remaining > total) ? 0 : (uint16_t)(total - remaining);
    uint8_t fill_width = (uint8_t)((elapsed * POMO_BAR_W) / total);
    if (s_last_fill_width == 0xFF) {
        draw_progress_bar_full(remaining, total);
        return;
    }
    if (fill_width > s_last_fill_width) {
        oledC_DrawRectangle((uint8_t)(POMO_BAR_X + s_last_fill_width), POMO_BAR_Y,
                            (uint8_t)(POMO_BAR_X + fill_width), (uint8_t)(POMO_BAR_Y + POMO_BAR_H),
                            COLOR_SUCCESS);
    } else if (fill_width < s_last_fill_width) {
        oledC_DrawRectangle((uint8_t)(POMO_BAR_X + fill_width), POMO_BAR_Y,
                            (uint8_t)(POMO_BAR_X + s_last_fill_width), (uint8_t)(POMO_BAR_Y + POMO_BAR_H),
                            COLOR_BG);
    }
    s_last_fill_width = fill_width;
}

static void draw_session_counter(WatchState_t* state, uint8_t sessions) {
    uint8_t count = state->pomodoro.long_break_after_sessions;
    uint8_t spacing = 18;
    uint8_t total_w = (uint8_t)((count - 1) * spacing);
    uint8_t x0 = (uint8_t)(48 - (total_w / 2));

    for (uint8_t i = 0; i < count; i++) {
        uint8_t x = (uint8_t)(x0 + i * spacing);
        uint8_t y = POMO_TOMATO_Y;
        if (i < sessions) {
            oledC_DrawCircle(x, y, POMO_TOMATO_R, COLOR_WARNING);
        } else {
            oledC_DrawRing(x, y, POMO_TOMATO_R, 1, COLOR_DIM);
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
        start_work_session(state);
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
            start_break(state);
        } else {
            // Break completed
            start_work_session(state);
        }
    }
    
    state->needs_redraw = true;
}

void Pomodoro_Draw(void) {
    WatchState_t* state = Watch_GetState();
    
    oledC_setBackground(COLOR_BG);
    
    draw_session_counter(state, state->pomodoro.work_sessions);
    
    const char* state_label = get_state_label(state->pomodoro.state);
    uint16_t label_color = get_state_color(state->pomodoro.state);
    uint16_t total_seconds = get_total_seconds(state);

    uint8_t label_len = get_state_label_len(state->pomodoro.state);
    uint8_t label_w = (uint8_t)(label_len * (5 * 2 + 1));
    uint8_t label_x = (uint8_t)((96 - label_w) / 2);
    oledC_DrawString(label_x, POMO_LABEL_Y, 2, 1, (uint8_t*)state_label, label_color);
    
    draw_time_full(state->pomodoro.remaining_seconds);
    
    draw_progress_bar_full(state->pomodoro.remaining_seconds, total_seconds);
    
    if (state->pomodoro.paused) {
        oledC_DrawString(34, POMO_PAUSE_Y, 1, 1, (uint8_t*)"PAUSED", COLOR_ACCENT);
    }

    s_last_state = state->pomodoro.state;
    s_last_remaining = state->pomodoro.remaining_seconds;
    s_last_sessions = state->pomodoro.work_sessions;
    s_last_paused = state->pomodoro.paused;
    s_last_min = (uint8_t)(state->pomodoro.remaining_seconds / 60);
    s_last_sec = (uint8_t)(state->pomodoro.remaining_seconds % 60);
}

void Pomodoro_DrawUpdate(void) {
    WatchState_t* state = Watch_GetState();

    if (state->pomodoro.state != s_last_state ||
        state->pomodoro.work_sessions != s_last_sessions) {
        Pomodoro_Draw();
        return;
    }

    if (state->pomodoro.remaining_seconds != s_last_remaining) {
        draw_time_partial(state->pomodoro.remaining_seconds);
        draw_progress_bar_partial(state->pomodoro.remaining_seconds, get_total_seconds(state));
        s_last_remaining = state->pomodoro.remaining_seconds;
    }

    if (state->pomodoro.paused != s_last_paused) {
        uint8_t text_w = (uint8_t)(6 * (5 + 1));
        uint8_t x0 = (uint8_t)((96 - text_w) / 2);
        oledC_DrawRectangle(x0 - 1, POMO_PAUSE_Y - 1,
                            (uint8_t)(x0 + text_w + 1), (uint8_t)(POMO_PAUSE_Y + 7),
                            COLOR_BG);
        if (state->pomodoro.paused) {
            oledC_DrawString(x0, POMO_PAUSE_Y, 1, 1, (uint8_t*)"PAUSED", COLOR_ACCENT);
        }
        s_last_paused = state->pomodoro.paused;
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
