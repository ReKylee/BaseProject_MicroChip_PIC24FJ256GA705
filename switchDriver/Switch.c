#include "Switch.h"
#include "../systemExtensions/systemExtensions.h"

/**
 * @file Switch.c
 * @brief Implementation of debounced switch driver
 */

// ============================================================================
// Private State
// ============================================================================

typedef struct {
    bool stable_state;
    uint32_t last_change_time;
} switch_state_t;

static switch_state_t s1_state = {false, 0};
static switch_state_t s2_state = {false, 0};

// ============================================================================
// Private Helper Functions
// ============================================================================

/**
 * @brief Generic debounced press detection
 * @param state Pointer to switch state structure
 * @param raw_input Current raw switch reading (true = pressed)
 * @return true if press edge detected
 */
static bool detect_press(switch_state_t* state, bool raw_input) {
    uint32_t current_time = millis();
    
    if (raw_input != state->stable_state) {
        // State change detected
        if ((current_time - state->last_change_time) >= DEBOUNCE_TIME_MS) {
            // Debounce time has elapsed
            state->stable_state = raw_input;
            state->last_change_time = current_time;
            
            // Return true only on press (transition to pressed state)
            if (state->stable_state) {
                return true;
            }
        }
    } else {
        // No change, update last change time
        state->last_change_time = current_time;
    }
    
    return false;
}

/**
 * @brief Generic debounced release detection
 * @param state Pointer to switch state structure
 * @param raw_input Current raw switch reading (true = pressed)
 * @return true if release edge detected
 */
static bool detect_release(switch_state_t* state, bool raw_input) {
    uint32_t current_time = millis();
    
    if (raw_input != state->stable_state) {
        // State change detected
        if ((current_time - state->last_change_time) >= DEBOUNCE_TIME_MS) {
            // Debounce time has elapsed
            state->stable_state = raw_input;
            state->last_change_time = current_time;
            
            // Return true only on release (transition to released state)
            if (!state->stable_state) {
                return true;
            }
        }
    } else {
        // No change, update last change time
        state->last_change_time = current_time;
    }
    
    return false;
}

// ============================================================================
// Public Functions
// ============================================================================

void Switch_Init(void) {
    S1_Init();
    S2_Init();
    
    // Initialize state with current switch positions
    s1_state.stable_state = S1_IsDown();
    s1_state.last_change_time = millis();
    
    s2_state.stable_state = S2_IsDown();
    s2_state.last_change_time = millis();
}

bool S1_WasPressed(void) {
    return detect_press(&s1_state, S1_IsDown());
}

bool S1_WasReleased(void) {
    return detect_release(&s1_state, S1_IsDown());
}

bool S2_WasPressed(void) {
    return detect_press(&s2_state, S2_IsDown());
}

bool S2_WasReleased(void) {
    return detect_release(&s2_state, S2_IsDown());
}

void Switch_ResetState(void) {
    s1_state.stable_state = S1_IsDown();
    s1_state.last_change_time = millis();
    
    s2_state.stable_state = S2_IsDown();
    s2_state.last_change_time = millis();
}
