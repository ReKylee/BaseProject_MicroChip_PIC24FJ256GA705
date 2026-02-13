/*
 * Hardware and module startup sequence for the watch app.
 */

#include <xc.h>
#include "app_init.h"
#include "../System/delay.h"
#include "watchFaces/alarm_face.h"
#include "shared/watch_state.h"
#include "watchCore/timekeeper.h"
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
#include "../oledDriver/oledC.h"
#include "../accel3Driver/ACCEL3.h"
#include "../adcDriver/ADC.h"

void APP_InitializeHardware(void) {
    SYSTEM_Initialize();
    oledC_setup();
    
    Timekeeper_Init();
    
    Buttons_Init();
    Pot_Init();
    AccelInput_Init();
    
    LED1_Init();
    LED2_Init();
    LED1_Off();
    LED2_Off();

    Watch_InitState();

    DigitalFace_Init();
    AlarmFace_Init();

    Menu_Init();

    Pomodoro_Init();

    Time_t default_time = {12, 0, 0};
    Date_t default_date = {1, 1};
    (void)Timekeeper_SetTime(&default_time);
    Timekeeper_SetDate(&default_date);
}
