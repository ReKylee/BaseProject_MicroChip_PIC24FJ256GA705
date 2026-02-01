#include "app_input_handler.h"
#include "../shared/watch_state.h"
#include "../watchInput/buttons.h"
#include "../watchInput/accel_input.h"
#include "../watchMenu/menu.h"
#include "../watchCore/alarm.h"
#include "../watchFaces/digital_face.h"
#include "../watchFaces/analog_face.h"
#include "../watchFaces/binary_face.h"
#include "../../ledDriver/LED.h"
#include "../../System/delay.h"
#include "../watchInput/potentiometer.h"
#include "../pomodoroTimer/pomodoro.h"
#include "../watchCore/timekeeper.h"

// Private functions for handling inputs in different modes

// Helper function for LED feedback
static void app_button_led_feedback(ButtonEvent_t btn) {
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
}

static uint32_t s_menu_enter_ms = 0;

static void handle_watch_mode(ButtonEvent_t btn, AccelEvent_t accel) {
    WatchState_t* state = Watch_GetState();

    if (btn == BTN_S1_LONG) {
        Menu_Enter();
        s_menu_enter_ms = Timekeeper_GetMillis();
        state->needs_full_redraw = true;
        return;
    }

    if (btn == BTN_S2_LONG) {
        state->display_mode = MODE_POMODORO;
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
        app_button_led_feedback(BTN_S2_SHORT); // Use helper for feedback
        return;
    }
}

static void handle_menu_mode(ButtonEvent_t btn, AccelEvent_t accel) {
    WatchState_t* state = Watch_GetState();

    if (s_menu_enter_ms != 0 && (Timekeeper_GetMillis() - s_menu_enter_ms) < 300) {
        accel = ACCEL_NONE;
    }

    if (accel == ACCEL_FLIP || accel == ACCEL_SHAKE) {
        Menu_Exit();
        s_menu_enter_ms = 0;
        state->needs_full_redraw = true;
        return;
    }

    app_button_led_feedback(btn); // Use helper for feedback

    uint16_t pot_val = Pot_GetRaw();
    Menu_HandleInput(btn, pot_val);
}

static void handle_pomodoro_mode(ButtonEvent_t btn, AccelEvent_t accel) {
    WatchState_t* state = Watch_GetState();

    if (btn == BTN_S1_LONG) {
        Menu_Enter();
        state->needs_full_redraw = true;
        return;
    }

    if (btn == BTN_S2_LONG) {
        Menu_Exit();
        state->needs_full_redraw = true;
        return;
    }

    (void)accel;

    app_button_led_feedback(btn); // Use helper for feedback

    Pomodoro_HandleInput(btn == BTN_S2_SHORT, btn == BTN_S1_SHORT);
}

void APP_HandleInputEvents(ButtonEvent_t btn, AccelEvent_t accel) {
    WatchState_t* state = Watch_GetState();

    switch (state->display_mode) {
        case MODE_WATCH:
            handle_watch_mode(btn, accel);
            break;
        case MODE_MENU:
            handle_menu_mode(btn, accel);
            break;
        case MODE_POMODORO:
            handle_pomodoro_mode(btn, accel);
            break;
        default: break;
    }
}
