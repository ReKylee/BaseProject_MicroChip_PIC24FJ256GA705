/*
 * Pin Manager for PIC24FJ256GA705
 * Critical I2C Configuration:
 */

#include <xc.h>

void PIN_MANAGER_Initialize(void) {
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0000;
    LATB = 0x0000;
    LATC = 0x0000;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0xFFFF;
    TRISB = 0xFFFF;
    TRISC = 0xFFFF;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    IOCPDA = 0x0000;
    IOCPDB = 0x0000;
    IOCPDC = 0x0000;
    IOCPUA = 0x0000;
    IOCPUB = 0x0000;
    IOCPUC = 0x0000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;
    ODCC = 0x0000;

    // I2C1 (SDA1/SCL1) on RB9/RB8
    ODCBbits.ODCB8 = 1;   // Enable open-drain for SCL1 (RB8)
    ODCBbits.ODCB9 = 1;   // Enable open-drain for SDA1 (RB9)

    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS

    RPOR7bits.RP14R = 0x0007; //RB14->SPI1:SDO1
    RPOR7bits.RP15R = 0x0008; //RB15->SPI1:SCK1OUT
    RPINR20bits.SDI1R = 0x000D; //RB13->SPI1:SDI1

    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS
}