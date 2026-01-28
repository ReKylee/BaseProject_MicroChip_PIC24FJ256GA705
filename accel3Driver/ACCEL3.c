#include "ACCEL3.h"
#include "../i2cDriver/I2C.h" 

static uint8_t slave_addr;

ACCEL3_Status_t ACCEL3_Init(const ACCEL3_Config_t *cfg) {
    // 1. Determine address (Default to 0x1D if config is NULL, matching LabC7)
    slave_addr = (cfg) ? cfg->i2c_address : ADXL345_ADDR_SDO_HIGH;

    // 2. Init I2C Bus
    i2c_config_t i2c_cfg = {.bus_hz = 100000, .timeout_ms = 50};
    i2c_init(&i2c_cfg);

    // 3. Verify Device ID (Should be 0xE5)
    uint8_t devid = 0;
    if (i2c_readReg(slave_addr, ADXL345_REG_DEVID, &devid) != I2C_OK) {
        return ACCEL3_ERR_I2C;
    }
    if (devid != 0xE5) {
        return ACCEL3_ERR_ID;
    }

    // 4. Configure Device (Sequence from LabC7)
    // Measure Mode (Power_CTL = 0x08)
    if (i2c_writeReg(slave_addr, ADXL345_REG_POWER_CTL, 0x08) != I2C_OK) return ACCEL3_ERR_I2C;

    return ACCEL3_OK;
}

ACCEL3_Status_t ACCEL3_ReadXYZ(int16_t *x, int16_t *y, int16_t *z) {
    uint8_t data[6];

    // Burst read 6 bytes starting from DATAX0
    if (i2c_readRegs(slave_addr, ADXL345_REG_DATAX0, data, 6) != I2C_OK) {
        return ACCEL3_ERR_I2C;
    }

    // Combine bytes (Little Endian)
    if (x) *x = (int16_t) ((data[1] << 8) | data[0]);
    if (y) *y = (int16_t) ((data[3] << 8) | data[2]);
    if (z) *z = (int16_t) ((data[5] << 8) | data[4]);

    return ACCEL3_OK;
}