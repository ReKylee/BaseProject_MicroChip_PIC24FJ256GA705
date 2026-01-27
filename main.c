/**
 * @file main.c
 * @brief Main entry point for PIC24FJ256GA705 application
 * 
 * This is a minimal main() that demonstrates proper application structure
 * using the improved modular drivers.
 */

#include <stdlib.h>

#include "oledDriver/oledC_colors.h"
#include "oledDriver/oledC.h"
#include "System/delay.h"
#include "System/system.h"

/**
 * @brief Main entry point
 * @return Never returns (embedded system)
 */
int main(void) {
    SYSTEM_Initialize();
    oledC_setup();
    oledC_setBackground(OLEDC_COLOR_RED);
    //Main loop
    while (1) {
        oledC_sendCommand(OLEDC_CMD_SET_DISPLAY_MODE_INVERSE, NULL, 0);
        DELAY_milliseconds(1000);
        oledC_sendCommand(OLEDC_CMD_SET_DISPLAY_MODE_ON, NULL, 0);
        DELAY_milliseconds(1000);
    }

    return 0; // Never reached
}

/**
 * End of File
 */
