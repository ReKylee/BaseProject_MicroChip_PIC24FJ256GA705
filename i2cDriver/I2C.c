#include "I2C.h"
#include "../System/delay.h" 

static i2c_config_t config;

/* * Safety Wait Macro
 * Mimics the 'while(bit)' of the working driver but adds a bailout counter.
 */
#define WAIT_FOR_BIT(bit) do { \
    uint32_t timeout = config.timeout_ms * 1000; \
    while (bit) { \
        if (--timeout == 0) return I2C_TIMEOUT; \
        if (I2C1STATbits.BCL) return I2C_COLLISION; \
        DELAY_milliseconds(1); \
    } \
} while(0)

void i2c_init(const i2c_config_t *cfg) {
    if (cfg) config = *cfg;
    else {
        config.bus_hz = 100000;
        config.timeout_ms = 50;
    }

    I2C1CONLbits.I2CEN = 0; // Disable
    I2C1STAT = 0x0000;
    I2C1CONL = 0x8000;

    // Calculate I2C Baud Rate Generator value
    // I2CxBRG = (FCY / Fscl - FCY / 10000000) - 1
    // FCY / 10000000 is for clock slew(disabled above 400kHZ)
    uint32_t target_bus_hz = config.bus_hz;
    if (target_bus_hz > 400000) {

        I2C1CONLbits.DISSLW = 1; // disable slew rate
        I2C1BRG = ((FCY / target_bus_hz) - 1);
    } else {
        I2C1CONLbits.DISSLW = 0; // normal
        I2C1BRG = ((FCY / target_bus_hz - FCY / 10000000) - 1);
    }



    I2C1CONLbits.I2CEN = 1; // Enable
}

static i2c_status_t start(void) {
    I2C1STATbits.BCL = 0; // Clear collision flag proactively
    I2C1CONLbits.SEN = 1; // Initiate Start
    while (I2C1CONLbits.SEN);
    if (I2C1STATbits.BCL) return I2C_COLLISION; // Check BCL after operation
    return I2C_OK;
}

static i2c_status_t restart(void) {
    I2C1CONLbits.RSEN = 1; // Initiate Restart
    WAIT_FOR_BIT(I2C1CONLbits.RSEN);
    if (I2C1STATbits.IWCOL) return I2C_COLLISION;
    if (I2C1STATbits.BCL) return I2C_COLLISION;

    return I2C_OK;
}

static i2c_status_t stop(void) {
    I2C1CONLbits.PEN = 1; // Initiate Stop
    WAIT_FOR_BIT(I2C1CONLbits.PEN);
    if (I2C1STATbits.IWCOL) return I2C_COLLISION;
    if (I2C1STATbits.BCL) return I2C_COLLISION;

    return I2C_OK;
}

static i2c_status_t tx(uint8_t data) {
    // Clear collision flags before transmitting
    I2C1STATbits.IWCOL = 0;
    I2C1STATbits.BCL = 0;

    while (I2C1STATbits.TRSTAT);
    I2C1TRN = data; // Load data
    WAIT_FOR_BIT(I2C1STATbits.TRSTAT); // Wait for transmission to complete

    if (I2C1STATbits.IWCOL) return I2C_COLLISION; // Check for write collision
    if (I2C1STATbits.BCL) return I2C_COLLISION; // Check for bus collision
    return I2C1STATbits.ACKSTAT ? I2C_NACK : I2C_OK; // Check ACK after transmission
}

static uint8_t rx(bool ack) {
    I2C1CONLbits.RCEN = 1; // Enable Receive

    // We cannot use the macro easily here because we return data, not status
    // But we can implement a simple blocking wait based on the working driver
    while (I2C1CONLbits.RCEN);

    uint8_t data = I2C1RCV;

    // Send ACK/NACK
    I2C1CONLbits.ACKDT = ack ? 0 : 1;
    I2C1CONLbits.ACKEN = 1;

    if (ack) while (I2C1CONLbits.ACKEN);

    return data;
}

/* --- High Level Operations --- */

i2c_status_t i2c_writeReg(uint8_t addr, uint8_t reg, uint8_t val) {
    if (start() != I2C_OK) return I2C_TIMEOUT;

    if (tx(addr << 1) != I2C_OK) {
        stop();
        return I2C_NACK;
    } // Addr + Write
    if (tx(reg) != I2C_OK) {
        stop();
        return I2C_NACK;
    } // Register
    if (tx(val) != I2C_OK) {
        stop();
        return I2C_NACK;
    } // Value

    stop();
    return I2C_OK;
}

i2c_status_t i2c_readRegs(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len) {
    if (start() != I2C_OK) return I2C_TIMEOUT;

    if (tx(addr << 1) != I2C_OK) {
        stop();
        return I2C_NACK;
    } // Addr + Write
    if (tx(reg) != I2C_OK) {
        stop();
        return I2C_NACK;
    } // Register

    if (restart() != I2C_OK) {
        stop();
        return I2C_TIMEOUT;
    }

    if (tx((addr << 1) | 1) != I2C_OK) {
        stop();
        return I2C_NACK;
    } // Addr + Read

    for (uint8_t i = 0; i < len; i++) {
        // Send ACK for all bytes except the last one
        data[i] = rx(i < (len - 1));
    }

    stop();
    return I2C_OK;
}

i2c_status_t i2c_readReg(uint8_t addr, uint8_t reg, uint8_t *val) {
    return i2c_readRegs(addr, reg, val, 1);
}