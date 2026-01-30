/*
 * watch_main.c
 * Main application for PIC24 Watch Project
 */

#include <xc.h>
#include "shared/watch_state.h"
#include "watchCore/watch_timer.h"
#include "watchCore/timekeeper.h"
#include "watchCore/alarm.h"
#include "watchFaces/digital_face.h"
#include "watchFaces/analog_face.h"
#include "watchFaces/binary_face.h"
#include "watchMenu/menu.h"
#include "watchInput/buttons.h"
#include "watchInput/potentiometer.h"
#include "watchInput/accel_input.h"
#include "pomodoroTimer/pomodoro.h"
#include "../ledDriver/LED.h"
#include "../System/system.h"
#include "../System/delay.h"

// ============================================================================
// PRIVATE FUNCTIONS
// ============================================================================

static void InitializeHardware(void) {
    // Initialize system
    SYSTEM_Initialize();
    
    // Initialize LEDs for button feedback
    LED1_Init();
    LED2_Init();
    LED1_Off();
    LED2_Off();
    
    // Initialize RGB LED (optional, for visual feedback)
    RGB_Init();
    RGB_SetRaw(0, 0, 0);
    
    // Initialize watch state
    Watch_InitState();
    
    // Initialize timer system (1Hz ISR)
    WatchTimer_Init();
    
    // Initialize input systems
    Buttons_Init();
    Pot_Init();
    Accel_Init();
    
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

static void HandleWatchMode(void) {
    WatchState_t* state = Watch_GetState();
    
    // Check for menu entry (S1 long press)
    ButtonEvent_t btn = Buttons_GetEvent();
    if (btn == BTN_S1_LONG) {
        Menu_Enter();
        LED1_On();
        DELAY_milliseconds(100);
        LED1_Off();
        return;
    }
    
    // Check for alarm dismissal (any button press)
    if (Alarm_IsRinging() && (btn == BTN_S1_SHORT || btn == BTN_S2_SHORT)) {
        Alarm_Dismiss();
        state->needs_redraw = true;
        return;
    }
    
    // Check for face switching (S2 short press in watch mode)
    if (btn == BTN_S2_SHORT) {
        state->watch_face = (state->watch_face + 1) % FACE_COUNT;
        state->needs_redraw = true;
        LED2_On();
        DELAY_milliseconds(100);
        LED2_Off();
        return;
    }
    
    // Check for accelerometer events
    AccelEvent_t accel = Accel_GetEvent();
    if (accel == ACCEL_FLIPPED || accel == ACCEL_SHAKEN) {
        // Could implement screen blanking or other features
    }
    
    // Update watch display
    if (state->second_tick) {
        state->second_tick = false;
        Timekeeper_Tick();
        Alarm_Check();
        Alarm_Update();
        state->needs_redraw = true;
    }
    
    // Redraw if needed
    if (state->needs_redraw) {
        state->needs_redraw = false;
        
        // Handle alarm flashing
        static bool flash_state = false;
        if (Alarm_IsRinging()) {
            flash_state = !flash_state;
            // Implement screen inversion or color change
            oledC_setBackground(flash_state ? COLOR_WARNING : COLOR_BG);
        } else {
            oledC_setBackground(COLOR_BG);
        }
        
        // Draw appropriate watch face
        switch (state->watch_face) {
            case FACE_DIGITAL:
                DigitalFace_Draw();
                break;
            case FACE_ANALOG:
                AnalogFace_Draw();
                break;
            case FACE_BINARY:
                BinaryFace_Draw();
                break;
        }
    }
}

static void HandleMenuMode(void) {
    WatchState_t* state = Watch_GetState();
    
    // Check for accelerometer exit
    AccelEvent_t accel = Accel_GetEvent();
    if (accel == ACCEL_FLIPPED || accel == ACCEL_SHAKEN) {
        Menu_Exit();
        LED1_On();
        LED2_On();
        DELAY_milliseconds(100);
        LED1_Off();
        LED2_Off();
        return;
    }
    
    // Get button events
    ButtonEvent_t btn = Buttons_GetEvent();
    
    // Provide LED feedback
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
    
    // Get potentiometer value
    uint16_t pot_val = Pot_Read();
    
    // Handle menu input
    Menu_HandleInput(btn, pot_val);
    
    // Update time display in corner (every second)
    if (state->second_tick) {
        state->second_tick = false;
        Timekeeper_Tick();
        Menu_Update();  // Update small time display
    }
    
    // Redraw menu if needed
    if (state->needs_redraw) {
        state->needs_redraw = false;
        Menu_Draw();
    }
}

static void HandlePomodoroMode(void) {
    WatchState_t* state = Watch_GetState();
    
    // Check for exit to menu (S1 long press)
    ButtonEvent_t btn = Buttons_GetEvent();
    if (btn == BTN_S1_LONG) {
        Menu_Enter();
        LED1_On();
        DELAY_milliseconds(100);
        LED1_Off();
        return;
    }
    
    // Check for accelerometer exit
    AccelEvent_t accel = Accel_GetEvent();
    if (accel == ACCEL_FLIPPED || accel == ACCEL_SHAKEN) {
        Menu_Exit();  // Return to watch mode
        return;
    }
    
    // Provide button feedback
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
    
    // Handle Pomodoro input
    Pomodoro_HandleInput(btn);
    
    // Update Pomodoro timer (every second)
    if (state->second_tick) {
        state->second_tick = false;
        Pomodoro_Update();
        state->needs_redraw = true;
    }
    
    // Redraw if needed
    if (state->needs_redraw) {
        state->needs_redraw = false;
        Pomodoro_Draw();
    }
}

// ============================================================================
// MAIN APPLICATION
// ============================================================================

int main(void) {
    // Initialize all hardware and modules
    InitializeHardware();
    
    WatchState_t* state = Watch_GetState();
    state->needs_redraw = true;
    
    // Main application loop
    while (1) {
        switch (state->display_mode) {
            case MODE_WATCH:
                HandleWatchMode();
                break;
                
            case MODE_MENU:
                HandleMenuMode();
                break;
                
            case MODE_POMODORO:
                HandlePomodoroMode();
                break;
        }
        
        // Small delay to prevent CPU spinning
        DELAY_milliseconds(10);
    }
    
    return 0;
}
