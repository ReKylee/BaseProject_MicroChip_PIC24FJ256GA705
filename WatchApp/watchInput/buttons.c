/*
 * buttons.c
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

static ButtonState_t s1_state = {false, 0, false};
static ButtonState_t s2_state = {false, 0, false};

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void Buttons_Init(void) {
    Switch_Init();
}

ButtonEvent_t Buttons_Update(void) {
    uint32_t current_time = Timekeeper_GetMillis();
    ButtonEvent_t event = BTN_NONE;
    
    // Check S1
    bool s1_down = S1_IsDown();
    
    if (s1_down && !s1_state.pressed) {
        // Button just pressed
        s1_state.pressed = true;
        s1_state.press_start_time = current_time;
        s1_state.long_press_fired = false;
        
    } else if (s1_down && s1_state.pressed && !s1_state.long_press_fired) {
        // Button held down - check for long press
        if ((current_time - s1_state.press_start_time) >= LONG_PRESS_MS) {
            s1_state.long_press_fired = true;
            event = BTN_S1_LONG;
        }
        
    } else if (!s1_down && s1_state.pressed) {
        // Button released
        if (!s1_state.long_press_fired) {
            // Was a short press
            event = BTN_S1_SHORT;
        }
        s1_state.pressed = false;
    }
    
    // Check S2 (only short press)
    if (event == BTN_NONE) {  // Only one event at a time
        bool s2_down = S2_IsDown();
        
        if (s2_down && !s2_state.pressed) {
            s2_state.pressed = true;
            
        } else if (!s2_down && s2_state.pressed) {
            s2_state.pressed = false;
            event = BTN_S2_SHORT;
        }
    }
    
    return event;
}

void Buttons_GetState(bool* s1_pressed, bool* s2_pressed) {
    *s1_pressed = S1_IsDown();
    *s2_pressed = S2_IsDown();
}
