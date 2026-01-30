/*
 * watch_main.c
 * Main application for PIC24 Watch Project
 */
#include <xc.h>
#include <stdlib.h>

#include "watch_main.h"

#include "shared/watch_state.h"
#include "watchInput/buttons.h"
#include "watchInput/accel_input.h"
#include "../System/delay.h"
#include "app_init.h"
#include "watchManagers/app_input_handler.h"
#include "watchManagers/app_display_manager.h"
#include "watchManagers/app_time_manager.h"

int watch_main(void) {
    APP_InitializeHardware();

    uint32_t last_uptime_s = 0;

    while (1) {
        APP_UpdateTimeAndAlarms(&last_uptime_s);

        // --- Handle Inputs ---
        ButtonEvent_t btn = Buttons_Update();
        AccelEvent_t accel = AccelInput_Check();

        // --- Handle Display Modes ---
        APP_HandleInputEvents(btn, accel);
        
        APP_UpdateDisplay();

        DELAY_milliseconds(10);
    }

    return 0;
}
