/*
 * Implementation of button handling
 */

#include "buttons.h"
#include "../watchCore/timekeeper.h"
#include "../../switchDriver/Switch.h"
#include <stdbool.h>

// ============================================================================
// PRIVATE DATA
// ============================================================================

typedef struct {
    bool pressed;
    uint32_t press_start_time;
    bool long_press_fired;
} ButtonState_t;

static ButtonState_t s_s1_state = {false, 0, false};
static ButtonState_t s_s2_state = {false, 0, false};
static bool s_both_long_fired = false;

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void Buttons_Init(void) {
    Switch_Init();
}

ButtonEvent_t Buttons_Update(void) {
    uint32_t current_time = Timekeeper_GetMillis();
    ButtonEvent_t event = BTN_NONE;
    
    bool s1_down = S1_IsDown();
    bool s2_down = S2_IsDown();
    
    if (s1_down && !s_s1_state.pressed) {
        s_s1_state.pressed = true;
        s_s1_state.press_start_time = current_time;
        s_s1_state.long_press_fired = false;
        
    } else if (s1_down && s_s1_state.pressed && !s_s1_state.long_press_fired) {
        if (!s2_down && (current_time - s_s1_state.press_start_time) >= LONG_PRESS_MS) {
            s_s1_state.long_press_fired = true;
            event = BTN_S1_LONG;
        }
        
    } else if (!s1_down && s_s1_state.pressed) {
        if (!s_s1_state.long_press_fired) {
            event = BTN_S1_SHORT;
        }
        s_s1_state.pressed = false;
        s_both_long_fired = false;
    }
    
    if (event == BTN_NONE) {
        if (s2_down && !s_s2_state.pressed) {
            s_s2_state.pressed = true;
            s_s2_state.press_start_time = current_time;
            s_s2_state.long_press_fired = false;
        } else if (s2_down && s_s2_state.pressed && !s_s2_state.long_press_fired) {
            if (!s1_down && (current_time - s_s2_state.press_start_time) >= LONG_PRESS_MS) {
                s_s2_state.long_press_fired = true;
                event = BTN_S2_LONG;
            }
        } else if (!s2_down && s_s2_state.pressed) {
            if (!s_s2_state.long_press_fired) {
                event = BTN_S2_SHORT;
            }
            s_s2_state.pressed = false;
            s_both_long_fired = false;
        }
    }

    if (event == BTN_NONE && s1_down && s2_down) {
        uint32_t both_start = s_s1_state.press_start_time;
        if (s_s2_state.press_start_time > both_start) {
            both_start = s_s2_state.press_start_time;
        }
        if (!s_both_long_fired && (current_time - both_start) >= LONG_PRESS_MS) {
            s_both_long_fired = true;
            s_s1_state.long_press_fired = true;
            s_s2_state.long_press_fired = true;
            event = BTN_BOTH_LONG;
        }
    }
    
    return event;
}

void Buttons_GetState(bool* s1_pressed, bool* s2_pressed) {
    *s1_pressed = S1_IsDown();
    *s2_pressed = S2_IsDown();
}
