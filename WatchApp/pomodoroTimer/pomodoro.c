/*
 * Implementation of Pomodoro timer
 */

#include <stdlib.h>

#include "pomodoro.h"
#include "../shared/watch_state.h"
#include "../shared/watch_types.h"
#include "../shared/fast_math.h"
#include "../shared/ui_layout.h"
#include "../shared/watch_ui_widgets.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"

// ============================================================================
// PRIVATE FUNCTIONS
// ============================================================================

#define POMO_TOMATO_Y 8
#define POMO_TOMATO_R 5
#define POMO_LABEL_Y 22
#define POMO_TIME_Y 38
#define POMO_MIN_SCALE 3
#define POMO_SEC_SCALE 2
#define POMO_SECONDS_Y_OFFSET 6
#define POMO_BAR_X 8
#define POMO_BAR_Y 80
#define POMO_BAR_W 80
#define POMO_BAR_H 8
#define POMO_PAUSE_Y 66
#define POMO_SCREEN_W 96
#define POMO_SCREEN_MAX_X (POMO_SCREEN_W - 1)
#define POMO_SESSION_SPACING 18
#define POMO_TIME_BOX_PAD 1
#define POMO_LABEL_CLEAR_HEIGHT 17
#define POMO_PAUSE_TEXT "PAUSED"
#define POMO_PAUSE_TEXT_CHARS 6U
#define POMO_PAUSE_TEXT_H 7
#define FONT_COLS 5
#define FONT_ROWS 8
#define FONT_GAP 1

static PomodoroState_t s_last_state = POMODORO_IDLE;
static uint16_t s_last_remaining = CACHE_INVALID_U16;
static uint8_t s_last_sessions = CACHE_INVALID_U8;
static bool s_last_paused = false;
static uint8_t s_last_fill_width = CACHE_INVALID_U8;
static uint16_t s_last_total = CACHE_INVALID_U16;
static uint8_t s_last_min = CACHE_INVALID_U8;
static uint8_t s_last_sec = CACHE_INVALID_U8;

static uint16_t minutes_to_seconds_u8(uint8_t minutes) {
    return (uint16_t)FastMath_Mul60U32FromU8(minutes);
}

static uint8_t mul11_u8(uint8_t v) {
    return (uint8_t)((v << 3) + (v << 1) + v);
}

static uint8_t compute_fill_width(uint16_t elapsed, uint16_t total) {
    if (total == 0U) {
        return 0U;
    }
    uint32_t scaled = (uint32_t)elapsed * (uint32_t)POMO_BAR_W;
    uint8_t q = (uint8_t)(scaled / (uint32_t)total);
    return (q > POMO_BAR_W) ? POMO_BAR_W : q;
}

static void split_minutes_seconds(uint16_t total_seconds, uint8_t* minutes, uint8_t* seconds) {
    uint8_t mins = FastMath_Div60U16(total_seconds);
    *minutes = mins;
    *seconds = (uint8_t)(total_seconds - (uint16_t)FastMath_Mul60U32FromU8(mins));
}

static void get_time_layout(WatchUi_DualTimeLayout_t* layout) {
    WatchUi_ComputeDualTimeLayout(POMO_SCREEN_W, 2U, 2U, POMO_MIN_SCALE, POMO_SEC_SCALE, POMO_SEC_SCALE,
                                  FONT_COLS, FONT_GAP, 1U, layout);
}

static void clear_time_area_full(void) {
    WatchUi_DualTimeLayout_t layout;

    get_time_layout(&layout);
    oledC_DrawRectangle((uint8_t)(layout.left_x - POMO_TIME_BOX_PAD), (uint8_t)(POMO_TIME_Y - POMO_TIME_BOX_PAD),
                        (uint8_t)(layout.left_x + layout.total_w + POMO_TIME_BOX_PAD),
                        (uint8_t)(POMO_TIME_Y + ((FONT_ROWS + 1) * POMO_MIN_SCALE) + POMO_TIME_BOX_PAD),
                        COLOR_BG);
}

static void clear_label_area(void) {
    oledC_DrawRectangle(0, (uint8_t)(POMO_LABEL_Y - POMO_TIME_BOX_PAD),
                        POMO_SCREEN_MAX_X, (uint8_t)(POMO_LABEL_Y + POMO_LABEL_CLEAR_HEIGHT),
                        COLOR_BG);
}

typedef struct {
    const char* label;
    uint8_t label_len;
    uint16_t color;
} PomodoroStateInfo_t;

static const PomodoroStateInfo_t s_state_info[] = {
    [POMODORO_IDLE]        = {"READY", 5, COLOR_DIM},
    [POMODORO_WORK]        = {"WORK",  4, COLOR_WARNING},
    [POMODORO_SHORT_BREAK] = {"BREAK", 5, COLOR_SUCCESS},
    [POMODORO_LONG_BREAK]  = {"LONG",  4, COLOR_SUCCESS},
};

static const PomodoroStateInfo_t* get_state_info(PomodoroState_t state) {
    if (state > POMODORO_LONG_BREAK) state = POMODORO_IDLE;
    return &s_state_info[state];
}

static uint16_t get_total_seconds(WatchState_t* state) {
    switch (state->pomodoro.state) {
        case POMODORO_WORK: return minutes_to_seconds_u8(state->pomodoro.work_minutes);
        case POMODORO_SHORT_BREAK: return minutes_to_seconds_u8(state->pomodoro.short_break_minutes);
        case POMODORO_LONG_BREAK: return minutes_to_seconds_u8(state->pomodoro.long_break_minutes);
        default: return minutes_to_seconds_u8(state->pomodoro.work_minutes);
    }
}

static uint16_t get_bar_color(PomodoroState_t state) {
    switch (state) {
        case POMODORO_WORK: return COLOR_WARNING;
        case POMODORO_SHORT_BREAK:
        case POMODORO_LONG_BREAK: return COLOR_SUCCESS;
        default: return COLOR_DIM;
    }
}

static void start_work_session(WatchState_t* state) {
    state->pomodoro.state = POMODORO_WORK;
    state->pomodoro.remaining_seconds = minutes_to_seconds_u8(state->pomodoro.work_minutes);
    state->pomodoro.paused = false;
}

static void start_break(WatchState_t* state) {
    if (state->pomodoro.work_sessions >= state->pomodoro.long_break_after_sessions) {
        state->pomodoro.state = POMODORO_LONG_BREAK;
        state->pomodoro.remaining_seconds = minutes_to_seconds_u8(state->pomodoro.long_break_minutes);
        state->pomodoro.work_sessions = 0;
    } else {
        state->pomodoro.state = POMODORO_SHORT_BREAK;
        state->pomodoro.remaining_seconds = minutes_to_seconds_u8(state->pomodoro.short_break_minutes);
    }
    state->pomodoro.paused = false;
}

static void finish_cycle_to_idle(WatchState_t* state) {
    state->pomodoro.state = POMODORO_IDLE;
    state->pomodoro.remaining_seconds = minutes_to_seconds_u8(state->pomodoro.work_minutes);
    state->pomodoro.paused = false;
}

static void draw_time_full(uint16_t remaining_seconds) {
    uint8_t minutes;
    uint8_t seconds;
    split_minutes_seconds(remaining_seconds, &minutes, &seconds);
    WatchUi_DualTimeLayout_t layout;

    get_time_layout(&layout);
    clear_time_area_full();

    WatchUi_DrawNN(minutes, layout.left_x, POMO_TIME_Y, POMO_MIN_SCALE, POMO_MIN_SCALE, COLOR_PRIMARY, COLOR_BG);
    WatchUi_DrawColon(layout.colon_x, (uint8_t)(POMO_TIME_Y + POMO_SECONDS_Y_OFFSET), POMO_SEC_SCALE, POMO_SEC_SCALE, COLOR_DIM, COLOR_BG);
    WatchUi_DrawNN(seconds, layout.right_x, (uint8_t)(POMO_TIME_Y + POMO_SECONDS_Y_OFFSET), POMO_SEC_SCALE, POMO_SEC_SCALE, COLOR_PRIMARY, COLOR_BG);
}

static void draw_time_partial(uint16_t remaining_seconds) {
    uint8_t minutes;
    uint8_t seconds;
    split_minutes_seconds(remaining_seconds, &minutes, &seconds);
    WatchUi_DualTimeLayout_t layout;
    get_time_layout(&layout);

    if (minutes != s_last_min) {
        WatchUi_DrawNN(minutes, layout.left_x, POMO_TIME_Y, POMO_MIN_SCALE, POMO_MIN_SCALE, COLOR_PRIMARY, COLOR_BG);
        s_last_min = minutes;
    }

    if (seconds != s_last_sec) {
        uint8_t sec_y = (uint8_t)(POMO_TIME_Y + POMO_SECONDS_Y_OFFSET);
        WatchUi_DrawColon(layout.colon_x, sec_y, POMO_SEC_SCALE, POMO_SEC_SCALE, COLOR_DIM, COLOR_BG);
        WatchUi_DrawNN(seconds, layout.right_x, sec_y, POMO_SEC_SCALE, POMO_SEC_SCALE, COLOR_PRIMARY, COLOR_BG);
        s_last_sec = seconds;
    }
}

static void draw_progress_bar_full(uint16_t remaining, uint16_t total, uint16_t color) {
    oledC_DrawRectangle(POMO_BAR_X - 1, POMO_BAR_Y - 1,
                        POMO_BAR_X + POMO_BAR_W + 1, POMO_BAR_Y + POMO_BAR_H + 1,
                        COLOR_DIM);
    uint16_t elapsed = (remaining > total) ? 0 : (uint16_t)(total - remaining);
    uint8_t fill_width = compute_fill_width(elapsed, total);
    oledC_DrawRectangle(POMO_BAR_X, POMO_BAR_Y,
                        (uint8_t)(POMO_BAR_X + POMO_BAR_W), (uint8_t)(POMO_BAR_Y + POMO_BAR_H),
                        COLOR_BG);
    if (fill_width > 0) {
        oledC_DrawRectangle(POMO_BAR_X, POMO_BAR_Y,
                            (uint8_t)(POMO_BAR_X + fill_width), (uint8_t)(POMO_BAR_Y + POMO_BAR_H),
                            color);
    }
    s_last_fill_width = fill_width;
    s_last_total = total;
}

static void draw_progress_bar_partial(uint16_t remaining, uint16_t total, uint16_t color) {
    if (total == 0) return;
    if (s_last_total != total) {
        draw_progress_bar_full(remaining, total, color);
        return;
    }
    uint16_t elapsed = (remaining > total) ? 0 : (uint16_t)(total - remaining);
    uint8_t fill_width = compute_fill_width(elapsed, total);
    if (s_last_fill_width == CACHE_INVALID_U8) {
        draw_progress_bar_full(remaining, total, color);
        return;
    }
    if (fill_width > s_last_fill_width) {
        oledC_DrawRectangle((uint8_t)(POMO_BAR_X + s_last_fill_width), POMO_BAR_Y,
                            (uint8_t)(POMO_BAR_X + fill_width), (uint8_t)(POMO_BAR_Y + POMO_BAR_H),
                            color);
    } else if (fill_width < s_last_fill_width) {
        oledC_DrawRectangle((uint8_t)(POMO_BAR_X + fill_width), POMO_BAR_Y,
                            (uint8_t)(POMO_BAR_X + s_last_fill_width), (uint8_t)(POMO_BAR_Y + POMO_BAR_H),
                            COLOR_BG);
    }
    s_last_fill_width = fill_width;
}

static void draw_session_counter(WatchState_t* state, uint8_t sessions, uint8_t total) {
    uint8_t count = total;
    if (count == 0U) {
        count = state->pomodoro.long_break_after_sessions;
    }
    uint8_t total_w = (uint8_t)((count - 1U) * POMO_SESSION_SPACING);
    uint8_t x0 = WatchUi_CenterX96(total_w);

    for (uint8_t i = 0; i < count; i++) {
        uint8_t x = (uint8_t)(x0 + i * POMO_SESSION_SPACING);
        uint8_t y = POMO_TOMATO_Y;
        if (i < sessions) {
            oledC_DrawCircle(x, y, POMO_TOMATO_R, COLOR_WARNING);
        } else {
            oledC_DrawRing(x, y, POMO_TOMATO_R, 1, COLOR_DIM);
        }
    }
}

static void draw_pause_indicator(bool paused) {
    uint8_t text_w = WatchUi_CharsToPx6(POMO_PAUSE_TEXT_CHARS);
    uint8_t x0 = WatchUi_CenterX96(text_w);
    oledC_DrawRectangle((uint8_t)(x0 - POMO_TIME_BOX_PAD), (uint8_t)(POMO_PAUSE_Y - POMO_TIME_BOX_PAD),
                        (uint8_t)(x0 + text_w + POMO_TIME_BOX_PAD), (uint8_t)(POMO_PAUSE_Y + POMO_PAUSE_TEXT_H),
                        COLOR_BG);
    if (paused) {
        oledC_DrawStringSolid(x0, POMO_PAUSE_Y, 1, 1, (uint8_t*)POMO_PAUSE_TEXT, COLOR_ACCENT, COLOR_BG);
    }
}

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void Pomodoro_Init(void) {
    WatchState_t* state = Watch_GetState();
    state->pomodoro.state = POMODORO_IDLE;
    state->pomodoro.remaining_seconds = minutes_to_seconds_u8(state->pomodoro.work_minutes);
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
    
    if (state->pomodoro.paused || state->pomodoro.state == POMODORO_IDLE) {
        return;
    }
    
    if (state->pomodoro.remaining_seconds > 0) {
        state->pomodoro.remaining_seconds--;
    }
    
    if (state->pomodoro.remaining_seconds == 0) {
        if (state->pomodoro.state == POMODORO_WORK) {
            state->pomodoro.work_sessions++;
            start_break(state);
        } else {
            if (state->pomodoro.work_sessions >= state->pomodoro.cycles_target) {
                finish_cycle_to_idle(state);
            } else {
                start_work_session(state);
            }
        }
    }
    
    state->needs_redraw = true;
}

void Pomodoro_Draw(void) {
    WatchState_t* state = Watch_GetState();
    
    oledC_setBackground(COLOR_BG);
    
    draw_session_counter(state, state->pomodoro.work_sessions, state->pomodoro.cycles_target);
    
    const PomodoroStateInfo_t* info = get_state_info(state->pomodoro.state);
    uint16_t total_seconds = get_total_seconds(state);

    uint8_t label_w = mul11_u8(info->label_len);
    uint8_t label_x = WatchUi_CenterX96(label_w);
    oledC_DrawStringSolid(label_x, POMO_LABEL_Y, 2, 1, (uint8_t*)info->label, info->color, COLOR_BG);

    draw_time_full(state->pomodoro.remaining_seconds);

    draw_progress_bar_full(state->pomodoro.remaining_seconds, total_seconds,
                           get_bar_color(state->pomodoro.state));

    draw_pause_indicator(state->pomodoro.paused);

    s_last_state = state->pomodoro.state;
    s_last_remaining = state->pomodoro.remaining_seconds;
    s_last_sessions = state->pomodoro.work_sessions;
    s_last_paused = state->pomodoro.paused;
    split_minutes_seconds(state->pomodoro.remaining_seconds, &s_last_min, &s_last_sec);
}

void Pomodoro_DrawUpdate(void) {
    WatchState_t* state = Watch_GetState();

    if (state->pomodoro.state != s_last_state ||
        state->pomodoro.work_sessions != s_last_sessions) {
        const PomodoroStateInfo_t* info = get_state_info(state->pomodoro.state);
        uint16_t total_seconds = get_total_seconds(state);
        uint8_t label_w = mul11_u8(info->label_len);
        uint8_t label_x = WatchUi_CenterX96(label_w);

        draw_session_counter(state, state->pomodoro.work_sessions, state->pomodoro.cycles_target);
        clear_label_area();
        oledC_DrawStringSolid(label_x, POMO_LABEL_Y, 2, 1, (uint8_t*)info->label, info->color, COLOR_BG);
        draw_time_full(state->pomodoro.remaining_seconds);
        draw_progress_bar_full(state->pomodoro.remaining_seconds, total_seconds,
                               get_bar_color(state->pomodoro.state));

        draw_pause_indicator(state->pomodoro.paused);

        s_last_state = state->pomodoro.state;
        s_last_remaining = state->pomodoro.remaining_seconds;
        s_last_sessions = state->pomodoro.work_sessions;
        s_last_paused = state->pomodoro.paused;
        split_minutes_seconds(state->pomodoro.remaining_seconds, &s_last_min, &s_last_sec);
        return;
    }

    if (state->pomodoro.remaining_seconds != s_last_remaining) {
        draw_time_partial(state->pomodoro.remaining_seconds);
        draw_progress_bar_partial(state->pomodoro.remaining_seconds, get_total_seconds(state),
                                  get_bar_color(state->pomodoro.state));
        s_last_remaining = state->pomodoro.remaining_seconds;
    }

    if (state->pomodoro.paused != s_last_paused) {
        draw_pause_indicator(state->pomodoro.paused);
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
