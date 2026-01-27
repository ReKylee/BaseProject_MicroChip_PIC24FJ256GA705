
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

void oledC_BitBangCommand(unsigned char cmd) {
    LATCbits.LATC9 = 0;
    LATCbits.LATC3 = 0;
    for (int i = 0; i < 8; i++) {
        DELAY_microseconds(1);
        LATBbits.LATB15 = 0;

        if (cmd & 0x80)
            LATBbits.LATB14 = 1;
        else
            LATBbits.LATB14 = 0;

        DELAY_microseconds(1);
        LATBbits.LATB15 = 1;

        cmd <<= 1;
    }
    LATCbits.LATC9 = 1;
}

int main(void) {
    // initialize the system
    SYSTEM_Initialize();
    oledC_setup();
    oledC_setBackground(OLEDC_COLOR_RED);
    //Remove Hardware SPI (see L9 slide #16)
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPOR7bits.RP14R = 0; //RB14->SPI MOSI
    RPOR7bits.RP15R = 0; //RB15->SPI Clock
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS
    //Set Direction (GPO) of software-SPI signals (CLK/MOSI)
    //<Add your code here>
    //Main loop
    while (1) {
        oledC_BitBangCommand(OLEDC_CMD_SET_DISPLAY_MODE_INVERSE);
        DELAY_milliseconds(1000);
        oledC_BitBangCommand(OLEDC_CMD_SET_DISPLAY_MODE_ON);
        DELAY_milliseconds(1000);
    }

    return 0;
}

/**
 * End of File
 */
