#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stdbool.h>
#include <xc.h>
#include "../System/clock.h"

/* Defaults if not provided */
#ifndef FCY
#define FCY CLOCK_PeripheralFrequencyGet()
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

#ifndef I2C1_CONFIG_TR_QUEUE_LENGTH
#define I2C1_CONFIG_TR_QUEUE_LENGTH 1
#endif

#ifndef I2C1_ENABLE_10BIT
#define I2C1_ENABLE_10BIT 0
#endif

#ifndef I2C1_ENABLE_QUEUE
#define I2C1_ENABLE_QUEUE 1
#endif

#ifndef I2C1_ENABLE_ERROR_COUNT
#define I2C1_ENABLE_ERROR_COUNT 1
#endif

/* --- API --- */
void i2c_init(const i2c_config_t *cfg);
i2c_status_t i2c_writeReg(uint8_t addr, uint8_t reg, uint8_t val);
i2c_status_t i2c_readReg(uint8_t addr, uint8_t reg, uint8_t *val);
i2c_status_t i2c_readRegs(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len);

#endif
