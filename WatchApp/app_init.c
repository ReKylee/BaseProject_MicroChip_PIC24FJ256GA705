/*
 * Hardware and module startup sequence for the watch app.
 */

#include <xc.h>
#include <stdio.h>

#include "app_init.h"
#include "../System/delay.h"
#include "watchFaces/alarm_face.h"
#include "shared/watch_state.h"
#include "watchCore/timekeeper.h"
#include "watchFaces/digital_face.h"
#include "watchMenu/menu.h"
#include "watchInput/buttons.h"
#include "watchInput/potentiometer.h"
#include "watchInput/accel_input.h"
#include "pomodoroTimer/pomodoro.h"
#include "../ledDriver/LED.h"
#include "../System/system.h"
#include "../oledDriver/oledC.h"
#include "../oledDriver/oledC_shapes.h"
#include "../accel3Driver/ACCEL3.h"
#include "../adcDriver/ADC.h"

static void app_init_core(void) {
    SYSTEM_Initialize();
    oledC_setup();
    Timekeeper_Init();
}

static void app_init_leds(void) {
    LED1_Init();
    LED2_Init();
    LED1_Off();
    LED2_Off();
}

static void app_init_inputs(void) {
    Buttons_Init();
    Pot_Init();
    // Allow I2C lines/slaves to settle after reset/programming.
    DELAY_milliseconds(ACCEL_INIT_SETTLE_DELAY_MS);
    AccelInput_Init();
}

static void app_handle_accel_init_error(void) {
    if (ACCEL3_GetLastStatus() == ACCEL3_OK) {
        return;
    }

    char line1[24];
    char line2[24];
    const char* line3 = "UNPLUG/PLUG USB";
    const char* line4 = "THEN REPROGRAM";
    snprintf(line1, sizeof(line1), "ACCEL INIT ERR %d", (int)ACCEL3_GetLastStatus());
    snprintf(line2, sizeof(line2), "I2C ERR %d", (int)ACCEL3_GetLastI2CStatus());
    oledC_DrawRectangle(0, 0, 95, 95, COLOR_BG);
    oledC_DrawStringSolid(2, 34, 1, 1, (uint8_t*)line1, COLOR_WARNING, COLOR_BG);
    oledC_DrawStringSolid(2, 46, 1, 1, (uint8_t*)line2, COLOR_WARNING, COLOR_BG);
    oledC_DrawStringSolid(2, 58, 1, 1, (uint8_t*)line3, COLOR_DIM, COLOR_BG);
    oledC_DrawStringSolid(2, 70, 1, 1, (uint8_t*)line4, COLOR_DIM, COLOR_BG);
    DELAY_milliseconds(ACCEL_ERROR_SCREEN_MS);

#if ACCEL_INIT_HALT_ON_ERROR
    while (1) {
        LED1_Toggle();
        DELAY_milliseconds(ACCEL_ERROR_BLINK_MS);
    }
#endif
}

static void app_init_modules(void) {
    Watch_InitState();
    DigitalFace_Init();
    AlarmFace_Init();
    Menu_Init();
    Pomodoro_Init();
}

static void app_set_default_datetime(void) {
    Time_t default_time;
    Date_t default_date;
    default_time.hour = 12;
    default_time.minute = 0;
    default_time.second = 0;
    default_date.day = 1;
    default_date.month = 1;
    (void)Timekeeper_SetTime(&default_time);
    Timekeeper_SetDate(&default_date);
}

void APP_InitializeHardware(void) {
    app_init_core();
    app_init_leds();
    app_init_inputs();
    app_handle_accel_init_error();
    app_init_modules();
    app_set_default_datetime();
}
