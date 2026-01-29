/**
 * ADXL345 Accelerometer Demo with OLED Display
 * 
 * This example demonstrates reading acceleration data from the ADXL345
 * and displaying it on the OLED screen.
 * 
 * Features auto-detection of I2C address (0x53 or 0x1D)
 */

#include "clock_app.h"

int main(void) {
    APP_Init();
    
    while(1) {
        APP_Loop();
    }

    return 0;
}