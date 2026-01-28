#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

/* Defaults if not provided */
#ifndef FCY
#define FCY _XTAL_FREQ/2
#endif

/* Configuration Struct */
typedef struct {
    uint32_t bus_hz;       // Target I2C freq (e.g., 100000)
    uint16_t timeout_ms;   // Safety timeout (prevents infinite hanging)
} i2c_config_t;

typedef enum {
    I2C_OK = 0,
    I2C_NACK,
    I2C_TIMEOUT,
    I2C_COLLISION,
} i2c_status_t;

/* --- API --- */
void i2c_init(const i2c_config_t *cfg);
i2c_status_t i2c_writeReg(uint8_t addr, uint8_t reg, uint8_t val);
i2c_status_t i2c_readReg(uint8_t addr, uint8_t reg, uint8_t *val);
i2c_status_t i2c_readRegs(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len);

#endif