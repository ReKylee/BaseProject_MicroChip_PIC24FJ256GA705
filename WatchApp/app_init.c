#include "app_init.h"
#include "../System/delay.h"
#include "watchFaces/alarm_face.h"
#include <xc.h> // For SYSTEM_Initialize and other XC specific stuff
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
    // Initialize system
    SYSTEM_Initialize();
    oledC_setup();
    
    // Initialize timekeeper and hardware timers
    Timekeeper_Init();
    
    // Initialize input systems
    Buttons_Init();
    Pot_Init();
    AccelInput_Init();
    
    // Initialize LEDs for button feedback
    LED1_Init();
    LED2_Init();
    LED1_Off();
    LED2_Off();

    // Initialize watch state
    Watch_InitState();

    // Initialize all watch faces
    DigitalFace_Init();
    AnalogFace_Init();
    BinaryFace_Init();
    AlarmFace_Init();

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