#include <xc.h>

#include "ADC.h"

// Current ADC config
static ADC_Config_t adc_cfg;

// Initialize ADC
void ADC_Init(const ADC_Config_t* cfg)
{
    adc_cfg = *cfg;

    // Turn off ADC
    AD1CON1bits.ADON = 0;

    // Configure selected ANx pin as analog input
    if (adc_cfg.channel <= 15) { // AN0-AN15 on PORTB for example
        TRISB |= (1 << adc_cfg.channel);        // input
        ANSELB |= (1 << adc_cfg.channel);       // analog
    }

    // Select analog channel
    AD1CHSbits.CH0NA = 0;                // negative input = AVss
    AD1CHSbits.CH0SA = adc_cfg.channel;  // positive input = ANx

    // ADC control registers
    AD1CON1bits.SSRC = 0b111;           // auto-convert after sampling
    AD1CON1bits.ASAM = 0;                // manual sampling

    // Output format
    if (adc_cfg.mode == ADC_OUTPUT_FLOAT) {
        AD1CON1bits.FORM = 0b10;        // unsigned fractional
    } else {
        AD1CON1bits.FORM = 0;           // integer
    }

    // Set resolution
    if (adc_cfg.res == ADC_RES_10BIT) {
        AD1CON1bits.MODE12 = 0;          // 10-bit
    } else {
        AD1CON1bits.MODE12 = 1;          // 12-bit
    }

    AD1CON2 = 0;                         // default buffer, MUX A only
    AD1CON3bits.ADRC = 0;                // clock from system
    AD1CON3bits.SAMC = 16;               // sample time
    AD1CON3bits.ADCS = 2;                // conversion clock

    // Enable ADC
    AD1CON1bits.ADON = 1;
}

// Read raw ADC value (integer or fractional)
uint16_t ADC_ReadRaw(void)
{
    AD1CON1bits.SAMP = 1;        // start sampling
    DELAY_microseconds(10);
    AD1CON1bits.SAMP = 0;        // stop sampling, start conversion
    while (!AD1CON1bits.DONE);
    return ADC1BUF0;
}

// Read normalized float 0.0 - 1.0
float ADC_ReadFloat(void)
{
    uint16_t raw = ADC_ReadRaw();

    if (adc_cfg.res == ADC_RES_10BIT) {
        if (adc_cfg.mode == ADC_OUTPUT_FLOAT) {
            return (float)raw / 0x03FF;   // 10-bit fractional
        } else {
            return (float)raw / 1023.0f;  // integer -> float
        }
    } else { // 12-bit
        if (adc_cfg.mode == ADC_OUTPUT_FLOAT) {
            return (float)raw / 0x0FFF;   // 12-bit fractional
        } else {
            return (float)raw / 4095.0f;  // integer -> float
        }
    }
}
