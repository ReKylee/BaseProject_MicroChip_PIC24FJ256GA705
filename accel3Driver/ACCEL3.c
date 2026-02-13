#include "ACCEL3.h"
#include "../i2cDriver/I2C.h" 
#include "../System/delay.h"

static uint8_t slave_addr;
static ACCEL3_Status_t s_last_status = ACCEL3_OK;
static i2c_status_t s_last_i2c_status = I2C_OK;

static ACCEL3_Status_t accel3_try_init_addr(uint8_t addr,
                                            bool* saw_collision,
                                            bool* saw_i2c_error,
                                            bool* saw_id_mismatch) {
    bool recovered_collision_once = false;
    for (uint8_t attempt = 0; attempt < 3; attempt++) {
        uint8_t devid = 0;
        i2c_status_t st = i2c_readReg(addr, ADXL345_REG_DEVID, &devid);
        if (st != I2C_OK) {
            s_last_i2c_status = st;
            *saw_i2c_error = true;
            if (st == I2C_COLLISION) {
                *saw_collision = true;
                if (!recovered_collision_once) {
                    i2c_recover();
                    recovered_collision_once = true;
                }
            }
            DELAY_milliseconds(2);
            continue;
        }
        if (devid != 0xE5) {
            *saw_id_mismatch = true;
            DELAY_milliseconds(2);
            continue;
        }

        st = i2c_writeReg(addr, ADXL345_REG_POWER_CTL, 0x00);
        if (st != I2C_OK) {
            s_last_i2c_status = st;
            *saw_i2c_error = true;
            if (st == I2C_COLLISION) {
                *saw_collision = true;
                if (!recovered_collision_once) {
                    i2c_recover();
                    recovered_collision_once = true;
                }
            }
            DELAY_milliseconds(2);
            continue;
        }
        DELAY_milliseconds(2);
        st = i2c_writeReg(addr, ADXL345_REG_POWER_CTL, 0x08);
        if (st != I2C_OK) {
            s_last_i2c_status = st;
            *saw_i2c_error = true;
            if (st == I2C_COLLISION) {
                *saw_collision = true;
                if (!recovered_collision_once) {
                    i2c_recover();
                    recovered_collision_once = true;
                }
            }
            DELAY_milliseconds(2);
            continue;
        }

        slave_addr = addr;
        s_last_i2c_status = I2C_OK;
        return ACCEL3_OK;
    }

    if (*saw_i2c_error) {
        return ACCEL3_ERR_I2C;
    }
    return ACCEL3_ERR_ID;
}

ACCEL3_Status_t ACCEL3_Init(const ACCEL3_Config_t *cfg) {
    // Init I2C Bus
    i2c_config_t i2c_cfg = {.bus_hz = 100000, .timeout_ms = 100};
    i2c_init(&i2c_cfg);
    s_last_i2c_status = I2C_OK;

    bool saw_collision = false;
    bool saw_i2c_error = false;
    bool saw_id_mismatch = false;

    if (cfg) {
        s_last_status = accel3_try_init_addr(cfg->i2c_address, &saw_collision, &saw_i2c_error, &saw_id_mismatch);
        return s_last_status;
    }

    ACCEL3_Status_t st = accel3_try_init_addr(ADXL345_ADDR_SDO_HIGH, &saw_collision, &saw_i2c_error, &saw_id_mismatch);
    if (st == ACCEL3_OK) {
        s_last_status = ACCEL3_OK;
        return s_last_status;
    }

    st = accel3_try_init_addr(ADXL345_ADDR_SDO_LOW, &saw_collision, &saw_i2c_error, &saw_id_mismatch);
    if (st == ACCEL3_OK) {
        s_last_status = ACCEL3_OK;
        return s_last_status;
    }

    if (saw_i2c_error || saw_collision) {
        s_last_status = ACCEL3_ERR_I2C;
    } else if (saw_id_mismatch) {
        s_last_status = ACCEL3_ERR_ID;
    } else {
        s_last_status = ACCEL3_ERR_I2C;
    }
    return s_last_status;
}

ACCEL3_Status_t ACCEL3_ReadXYZ(int16_t *x, int16_t *y, int16_t *z) {
    uint8_t data[6];

    // Burst read 6 bytes starting from DATAX0
    i2c_status_t st = i2c_readRegs(slave_addr, ADXL345_REG_DATAX0, data, 6);
    if (st != I2C_OK) {
        s_last_i2c_status = st;
        s_last_status = ACCEL3_ERR_I2C;
        if (x) *x = 0;
        if (y) *y = 0;
        if (z) *z = 0;
        return s_last_status;
    }

    // Combine bytes (Little Endian)
    if (x) *x = (int16_t) ((data[1] << 8) | data[0]);
    if (y) *y = (int16_t) ((data[3] << 8) | data[2]);
    if (z) *z = (int16_t) ((data[5] << 8) | data[4]);

    s_last_status = ACCEL3_OK;
    s_last_i2c_status = I2C_OK;
    return s_last_status;
}

ACCEL3_Status_t ACCEL3_GetLastStatus(void) {
    return s_last_status;
}

i2c_status_t ACCEL3_GetLastI2CStatus(void) {
    return s_last_i2c_status;
}
