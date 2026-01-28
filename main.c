/**
 * ADXL345 Accelerometer Demo with OLED Display
 * 
 * This example demonstrates reading acceleration data from the ADXL345
 * and displaying it on the OLED screen.
 * 
 * Features auto-detection of I2C address (0x53 or 0x1D)
 */

#include <stdio.h>
#include "System/system.h"
#include "accel3Driver/ACCEL3.h"
#include "oledDriver/oledC.h"
#include "oledDriver/oledC_colors.h"
#include "oledDriver/oledC_shapes.h"
#include "System/delay.h"
#include "i2cDriver/I2C.h"

static inline void error(const char *msg, int code) {
    char buf[32]; // buffer to hold combined message
    snprintf(buf, sizeof (buf), "%s: %d", msg, code);

    oledC_clearScreen();
    oledC_DrawString(2, 45, 1, 1, (uint8_t*) buf, OLEDC_COLOR_RED);

    while (1); // halt execution
}

int main(void) {
    char text[20];
    // Initialize system
    SYSTEM_Initialize();

    // Initialize OLED display
    oledC_setup();
    oledC_setBackground(OLEDC_COLOR_ALICEBLUE);

    i2c_config_t cfg = {
        .bus_hz = 100000,
        .timeout_ms = 10000,
    };
    i2c_init(&cfg);
    // Initialize with detected address
    ACCEL3_Config_t accel_cfg = {
        .i2c_address = ADXL345_ADDR_SDO_HIGH,

    };
    ACCEL3_Status_t acc_ret = ACCEL3_Init(&accel_cfg);
    if (acc_ret != ACCEL3_OK) {
        error("ACCEL3", acc_ret);
    }

    // Clear screen and draw UI
    oledC_setBackground(OLEDC_COLOR_ALICEBLUE);
    oledC_DrawString(2, 5, 2, 2, (uint8_t*) "ADXL345", OLEDC_COLOR_DARKBLUE);
    oledC_DrawString(2, 30, 2, 2, (uint8_t*) "X:", OLEDC_COLOR_BLACK);
    oledC_DrawString(2, 50, 2, 2, (uint8_t*) "Y:", OLEDC_COLOR_BLACK);
    oledC_DrawString(2, 70, 2, 2, (uint8_t*) "Z:", OLEDC_COLOR_BLACK);

    // Main loop - continuously read and display acceleration data
    while (1) {
        // Clear previous values only (X=30 to X=95)
        oledC_DrawRectangle(30, 30, 95, 45, OLEDC_COLOR_ALICEBLUE);
        oledC_DrawRectangle(30, 50, 95, 65, OLEDC_COLOR_ALICEBLUE);
        oledC_DrawRectangle(30, 70, 95, 85, OLEDC_COLOR_ALICEBLUE);

        // Read and display X-axis
        int16_t x, y, z;
        ACCEL3_ReadXYZ(&x, &y, &z);
        sprintf(text, "%+d", x);
        oledC_DrawString(30, 30, 2, 2, (uint8_t*) text, OLEDC_COLOR_BLACK);

        // Read and display Y-axis
        sprintf(text, "%+d", y);
        oledC_DrawString(30, 50, 2, 2, (uint8_t*) text, OLEDC_COLOR_BLACK);

        // Read and display Z-axis
        sprintf(text, "%+d", z);
        oledC_DrawString(30, 70, 2, 2, (uint8_t*) text, OLEDC_COLOR_BLACK);

        // Update at ~10Hz
        DELAY_milliseconds(100);
    }

    return 0;
}