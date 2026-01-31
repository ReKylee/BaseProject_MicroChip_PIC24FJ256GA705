#include "app_input_handler.h"

// Private functions for handling inputs in different modes

static void HandleWatchMode(ButtonEvent_t btn, AccelEvent_t accel) {
    WatchState_t* state = Watch_GetState();

    if (btn == BTN_S1_LONG) {
        Menu_Enter();
        state->needs_full_redraw = true;
        return;
    }

    if (Alarm_IsRinging() && (btn == BTN_S1_SHORT || btn == BTN_S2_SHORT)) {
        Alarm_Dismiss();
        state->needs_full_redraw = true; // Force redraw to clear alarm state
        return;
    }

    if (btn == BTN_S2_SHORT) {
        state->watch_face = (state->watch_face + 1) % FACE_COUNT_SELECTABLE;
        // Re-initialize the face to build its specific shape list
        switch (state->watch_face) {
            case FACE_DIGITAL: DigitalFace_Init();
                break;
            case FACE_ANALOG: AnalogFace_Init();
                break;
            case FACE_BINARY: BinaryFace_Init();
                break;
            default: break;
        }
        state->needs_full_redraw = true;
        LED2_On();
        DELAY_milliseconds(100);
        LED2_Off();
        return;
    }
}

static void HandleMenuMode(ButtonEvent_t btn, AccelEvent_t accel) {
    WatchState_t* state = Watch_GetState();

    if (accel == ACCEL_FLIP || accel == ACCEL_SHAKE) {
        Menu_Exit();
        state->needs_full_redraw = true;
        return;
    }
    
    if (btn == BTN_S1_SHORT || btn == BTN_S1_LONG) {
        LED1_On();
        DELAY_milliseconds(50);
        LED1_Off();
    }
    if (btn == BTN_S2_SHORT) {
        LED2_On();
        DELAY_milliseconds(50);
        LED2_Off();
    }

    uint16_t pot_val = Pot_GetRaw();
    Menu_HandleInput(btn, pot_val);
}

static void HandlePomodoroMode(ButtonEvent_t btn, AccelEvent_t accel) {
    WatchState_t* state = Watch_GetState();

    if (btn == BTN_S1_LONG) {
        Menu_Enter();
        state->needs_full_redraw = true;
        return;
    }

    if (accel == ACCEL_FLIP || accel == ACCEL_SHAKE) {
        Menu_Exit();
        state->needs_full_redraw = true;
        return;
    }

    if (btn != BTN_NONE) {
        if (btn == BTN_S1_SHORT) {
            LED1_On();
            DELAY_milliseconds(50);
            LED1_Off();
        } else if (btn == BTN_S2_SHORT) {
            LED2_On();
            DELAY_milliseconds(50);
            LED2_Off();
        }
    }

    Pomodoro_HandleInput(btn == BTN_S2_SHORT, btn == BTN_S1_SHORT);
}

void APP_HandleInputEvents(ButtonEvent_t btn, AccelEvent_t accel) {
    WatchState_t* state = Watch_GetState();

    switch (state->display_mode) {
        case MODE_WATCH:
            HandleWatchMode(btn, accel);
            break;
        case MODE_MENU:
            HandleMenuMode(btn, accel);
            break;
        case MODE_POMODORO:
            HandlePomodoroMode(btn, accel);
            break;
    }
}