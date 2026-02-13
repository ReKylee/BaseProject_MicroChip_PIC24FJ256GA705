#include "ACCEL3.h"
#include "../i2cDriver/I2C.h" 
#include "../System/delay.h"

static uint8_t slave_addr;

static ACCEL3_Status_t accel3_try_init_addr(uint8_t addr) {
    for (uint8_t attempt = 0; attempt < 3; attempt++) {
        uint8_t devid = 0;
        if (i2c_readReg(addr, ADXL345_REG_DEVID, &devid) != I2C_OK) {
            i2c_recover();
            DELAY_milliseconds(2);
            continue;
        }
        if (devid != 0xE5) {
            DELAY_milliseconds(2);
            continue;
        }

        if (i2c_writeReg(addr, ADXL345_REG_POWER_CTL, 0x00) != I2C_OK) {
            i2c_recover();
            DELAY_milliseconds(2);
            continue;
        }
        DELAY_milliseconds(2);
        if (i2c_writeReg(addr, ADXL345_REG_POWER_CTL, 0x08) != I2C_OK) {
            i2c_recover();
            DELAY_milliseconds(2);
            continue;
        }

        slave_addr = addr;
        return ACCEL3_OK;
    }

    return ACCEL3_ERR_I2C;
}

ACCEL3_Status_t ACCEL3_Init(const ACCEL3_Config_t *cfg) {
    // Init I2C Bus
    i2c_config_t i2c_cfg = {.bus_hz = 100000, .timeout_ms = 100};
    i2c_init(&i2c_cfg);

    if (cfg) {
        return accel3_try_init_addr(cfg->i2c_address);
    }

    ACCEL3_Status_t st = accel3_try_init_addr(ADXL345_ADDR_SDO_HIGH);
    if (st == ACCEL3_OK) {
        return ACCEL3_OK;
    }

    st = accel3_try_init_addr(ADXL345_ADDR_SDO_LOW);
    if (st == ACCEL3_OK) {
        return ACCEL3_OK;
    }

    return ACCEL3_ERR_ID;
}

ACCEL3_Status_t ACCEL3_ReadXYZ(int16_t *x, int16_t *y, int16_t *z) {
    uint8_t data[6];

    // Burst read 6 bytes starting from DATAX0
    if (i2c_readRegs(slave_addr, ADXL345_REG_DATAX0, data, 6) != I2C_OK) {
        if (x) *x = 0;
        if (y) *y = 0;
        if (z) *z = 0;
        return ACCEL3_ERR_I2C;
    }

    // Combine bytes (Little Endian)
    if (x) *x = (int16_t) ((data[1] << 8) | data[0]);
    if (y) *y = (int16_t) ((data[3] << 8) | data[2]);
    if (z) *z = (int16_t) ((data[5] << 8) | data[4]);

    return ACCEL3_OK;
}
