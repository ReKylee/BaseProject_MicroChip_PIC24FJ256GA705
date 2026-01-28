#ifndef ACCEL3_H
#define ACCEL3_H

#include <stdint.h>
#include <stdbool.h>

/* Addresses */
#define ADXL345_ADDR_SDO_LOW   0x53 
#define ADXL345_ADDR_SDO_HIGH  0x1D 

/* Registers */
#define ADXL345_REG_DEVID       0x00
#define ADXL345_REG_POWER_CTL   0x2D
#define ADXL345_REG_DATA_FORMAT 0x31
#define ADXL345_REG_DATAX0      0x32

typedef struct {
    uint8_t i2c_address;
} ACCEL3_Config_t;

/* Status Codes */
typedef enum {
    ACCEL3_OK = 0,
    ACCEL3_ERR_I2C,
    ACCEL3_ERR_ID,
} ACCEL3_Status_t;

/* API */
ACCEL3_Status_t ACCEL3_Init(const ACCEL3_Config_t *cfg);
ACCEL3_Status_t ACCEL3_ReadXYZ(int16_t *x, int16_t *y, int16_t *z);

#endif