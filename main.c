/*
 * watch_main.c
 * Main application for PIC24 Watch Project
 */

#include <xc.h>
#include <stdlib.h>
#include "WatchApp/shared/watch_state.h"
#include "WatchApp/watchCore/timekeeper.h"
#include "WatchApp/watchCore/alarm.h"
#include "WatchApp/watchFaces/digital_face.h"
#include "WatchApp/watchFaces/analog_face.h"
#include "WatchApp/watchFaces/binary_face.h"
#include "WatchApp/watchMenu/menu.h"
#include "WatchApp/watchInput/buttons.h"
#include "WatchApp/watchInput/potentiometer.h"
#include "WatchApp/watchInput/accel_input.h"
#include "WatchApp/pomodoroTimer/pomodoro.h"
#include "ledDriver/LED.h"
#include "System/system.h"
#include "System/delay.h"
#include "accel3Driver/ACCEL3.h"
#include "adcDriver/ADC.h"
#include "oledDriver/oledC.h"
#include "Timers/Timers.h"

// ============================================================================
// PRIVATE FUNCTIONS
// ============================================================================

static void InitializeHardware(void) {
    // Initialize system
    SYSTEM_Initialize();
    oledC_setup();
    
    // Initialize input systems
    Buttons_Init();
    Pot_Init();
    AccelInput_Init();
    
    // Initialize LEDs for button feedback
    LED1_Init();
    LED2_Init();
    LED1_Off();
    LED2_Off();

   
    // Initialize timekeeper and hardware timers
    Timekeeper_Init();

    // Initialize watch state
    Watch_InitState();


    // Initialize all watch faces
    DigitalFace_Init();
    AnalogFace_Init();
    BinaryFace_Init();

    // Initialize menu system
    Menu_Init();

    // Initialize Pomodoro timer
    Pomodoro_Init();

    // Set default time and date
    Time_t default_time = {12, 0, 0};
    Date_t default_date = {1, 1};
    Timekeeper_SetTime(&default_time);
    Timekeeper_SetDate(&default_date);
}

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
        state->watch_face = (state->watch_face + 1) % FACE_COUNT;
        // Re-initialize the face to build its specific shape list
        switch(state->watch_face) {
            case FACE_DIGITAL: DigitalFace_Init(); break;
            case FACE_ANALOG: AnalogFace_Init(); break;
            case FACE_BINARY: BinaryFace_Init(); break;
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

// ============================================================================
// MAIN APPLICATION
// ============================================================================

int main(void) {
    InitializeHardware();

    WatchState_t* state = Watch_GetState();
    uint32_t last_uptime_s = 0;

    while (1) {
        // --- Handle Time Updates ---
        uint32_t current_uptime_s = Timer_GetTicks(1);
        if (current_uptime_s != last_uptime_s) {
            last_uptime_s = current_uptime_s;
            
            Timekeeper_GetTime(&state->current_time);
            
            Alarm_Check();
            Alarm_Update();
            
            if (state->display_mode == MODE_POMODORO) Pomodoro_Update();
            
            state->needs_redraw = true;
        }

        // --- Handle Inputs ---
        ButtonEvent_t btn = Buttons_Update();
        AccelEvent_t accel = AccelInput_Check();

        // --- Handle Display Modes ---
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
        
        // --- DRAWING LOGIC ---
        if (state->needs_full_redraw) {
            state->needs_full_redraw = false;
            state->needs_redraw = false;
            
            oledC_setBackground(COLOR_BG);
            
            switch (state->display_mode) {
                case MODE_WATCH:
                    switch(state->watch_face) {
                        case FACE_DIGITAL: DigitalFace_Draw(); break;
                        case FACE_ANALOG: AnalogFace_Draw(); break;
                        case FACE_BINARY: BinaryFace_Draw(); break;
                        default: break;
                    }
                    break;
                case MODE_MENU: Menu_Draw(); break;
                case MODE_POMODORO: Pomodoro_Draw(); break;
            }
        } else if (state->needs_redraw) {
            state->needs_redraw = false;
            
            switch (state->display_mode) {
                case MODE_WATCH: {
                    static bool alarm_flashing = false;
                    if (Alarm_IsRinging()) {
                        alarm_flashing = !alarm_flashing;
                        oledC_setBackground(alarm_flashing ? COLOR_WARNING : COLOR_BG);
                        switch(state->watch_face) {
                            case FACE_DIGITAL: DigitalFace_Draw(); break;
                            case FACE_ANALOG: AnalogFace_Draw(); break;
                            case FACE_BINARY: BinaryFace_Draw(); break;
                            default: break;
                        }
                    } else {
                        if (alarm_flashing) { // Ensure screen is cleared after alarm stops
                            alarm_flashing = false;
                            state->needs_full_redraw = true;
                            break;
                        }
                        switch(state->watch_face) {
                            case FACE_DIGITAL: DigitalFace_DrawUpdate(); break;
                            case FACE_ANALOG: AnalogFace_DrawUpdate(); break;
                            case FACE_BINARY: BinaryFace_DrawUpdate(); break;
                            default: break;
                        }
                    }
                    break;
                }
                case MODE_MENU:
                    Menu_Draw();
                    break;
                case MODE_POMODORO:
                    // TODO: Implement Pomodoro_DrawUpdate for partial redraws
                    Pomodoro_Draw(); // For now, pomodoro still uses full redraw
                    break;
                default: break;
            }
        }

        DELAY_milliseconds(10);
    }

    return 0;
}
