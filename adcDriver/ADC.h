#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include "../System/delay.h"

// Supported ADC resolutions
typedef enum {
    ADC_RES_10BIT = 0,
    ADC_RES_12BIT = 1
} ADC_Resolution_t;

// Supported output modes
typedef enum {
    ADC_OUTPUT_INT,       // integer raw value
    ADC_OUTPUT_FLOAT      // normalized float 0.0 - 1.0
} ADC_OutputMode_t;

// ADC configuration structure
typedef struct {
    uint8_t channel;          // ANx channel number
    ADC_Resolution_t res;     // ADC resolution
    ADC_OutputMode_t mode;    // output mode
} ADC_Config_t;

// Initialize ADC with user configuration
void ADC_Init(const ADC_Config_t* cfg);

// Read raw ADC value (integer or fractional)
uint16_t ADC_ReadRaw(void);

// Read normalized float 0.0 - 1.0
float ADC_ReadFloat(void);

#endif
