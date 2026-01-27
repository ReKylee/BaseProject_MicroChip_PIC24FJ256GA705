#include <xc.h>
#include <stdlib.h>
#include "ADC.h"
#include "../System/delay.h"

/**
 * @file ADC.c
 * @brief ADC driver implementation with error handling
 */

// ============================================================================
// Private State
// ============================================================================

static ADC_Config_t current_config;
static bool is_initialized = false;

// Conversion timeout (in loop iterations)
#define ADC_TIMEOUT_ITERATIONS 10000

// ============================================================================
// Private Helper Functions
// ============================================================================

/**
 * @brief Validate channel number
 * @param channel Channel to validate
 * @return true if valid, false otherwise
 */
static inline bool is_valid_channel(uint8_t channel) {
    return (channel <= 15);
}

/**
 * @brief Configure pin as analog input
 * @param channel Channel number
 */
static void configure_pin_analog(uint8_t channel) {
    if (channel <= 15) {
        // Configure as input
        TRISB |= (1 << channel);
        // Configure as analog
        ANSELB |= (1 << channel);
    }
}

// ============================================================================
// Public Functions
// ============================================================================

ADC_Error_t ADC_Init(const ADC_Config_t* config) {
    if (config == NULL) {
        return ADC_ERR_INVALID_CH;
    }
    
    if (!is_valid_channel(config->channel)) {
        return ADC_ERR_INVALID_CH;
    }
    
    // Save configuration
    current_config = *config;
    
    // Disable ADC during configuration
    AD1CON1bits.ADON = 0;
    
    // Configure the pin
    configure_pin_analog(config->channel);
    
    // Configure channel
    AD1CHSbits.CH0NA = 0;  // Negative input = AVss
    AD1CHSbits.CH0SA = config->channel;  // Positive input = ANx
    
    // Configure control register 1
    AD1CON1bits.SSRC = 0b111;  // Auto-convert after sampling
    AD1CON1bits.ASAM = 0;       // Manual sampling start
    
    // Set output format
    if (config->output_mode == ADC_OUTPUT_FLOAT) {
        AD1CON1bits.FORM = 0b10;  // Unsigned fractional (0x0000 - 0xFFFF)
    } else {
        AD1CON1bits.FORM = 0;      // Integer (0x0000 - 0x0FFF or 0x03FF)
    }
    
    // Set resolution
    if (config->resolution == ADC_RES_10BIT) {
        AD1CON1bits.MODE12 = 0;  // 10-bit mode
    } else {
        AD1CON1bits.MODE12 = 1;  // 12-bit mode
    }
    
    // Configure control register 2
    AD1CON2 = 0;  // Default: no scan, MUX A only
    
    // Configure control register 3
    AD1CON3bits.ADRC = 0;  // Clock from system clock
    AD1CON3bits.SAMC = config->sample_time;  // Sample time
    AD1CON3bits.ADCS = config->conversion_clock;  // Conversion clock
    
    // Enable ADC
    AD1CON1bits.ADON = 1;
    
    is_initialized = true;
    return ADC_OK;
}

ADC_Error_t ADC_SetChannel(uint8_t channel) {
    if (!is_initialized) {
        return ADC_ERR_NOT_INIT;
    }
    
    if (!is_valid_channel(channel)) {
        return ADC_ERR_INVALID_CH;
    }
    
    // Disable ADC
    AD1CON1bits.ADON = 0;
    
    // Configure new pin
    configure_pin_analog(channel);
    
    // Update channel
    AD1CHSbits.CH0SA = channel;
    current_config.channel = channel;
    
    // Re-enable ADC
    AD1CON1bits.ADON = 1;
    
    return ADC_OK;
}

ADC_Error_t ADC_ReadRaw(uint16_t* value) {
    if (!is_initialized) {
        return ADC_ERR_NOT_INIT;
    }
    
    if (value == NULL) {
        return ADC_ERR_INVALID_CH;
    }
    
    // Start sampling
    AD1CON1bits.SAMP = 1;
    
    // Wait sample time
    DELAY_microseconds(10);
    
    // Start conversion
    AD1CON1bits.SAMP = 0;
    
    // Wait for conversion to complete with timeout
    uint16_t timeout = ADC_TIMEOUT_ITERATIONS;
    while (!AD1CON1bits.DONE && timeout > 0) {
        timeout--;
    }
    
    if (timeout == 0) {
        return ADC_ERR_TIMEOUT;
    }
    
    // Read result
    *value = ADC1BUF0;
    
    return ADC_OK;
}

ADC_Error_t ADC_ReadFloat(float* value) {
    if (!is_initialized) {
        return ADC_ERR_NOT_INIT;
    }
    
    if (value == NULL) {
        return ADC_ERR_INVALID_CH;
    }
    
    uint16_t raw_value;
    ADC_Error_t err = ADC_ReadRaw(&raw_value);
    
    if (err != ADC_OK) {
        return err;
    }
    
    // Convert to float based on resolution
    if (current_config.resolution == ADC_RES_10BIT) {
        if (current_config.output_mode == ADC_OUTPUT_FLOAT) {
            // Already in fractional format
            *value = (float)raw_value / 65535.0f;
        } else {
            // Integer format
            *value = (float)raw_value / 1023.0f;
        }
    } else {  // 12-bit
        if (current_config.output_mode == ADC_OUTPUT_FLOAT) {
            // Already in fractional format
            *value = (float)raw_value / 65535.0f;
        } else {
            // Integer format
            *value = (float)raw_value / 4095.0f;
        }
    }
    
    return ADC_OK;
}

bool ADC_IsInitialized(void) {
    return is_initialized;
}

ADC_Error_t ADC_GetConfig(ADC_Config_t* config) {
    if (!is_initialized) {
        return ADC_ERR_NOT_INIT;
    }
    
    if (config == NULL) {
        return ADC_ERR_INVALID_CH;
    }
    
    *config = current_config;
    return ADC_OK;
}

void ADC_Disable(void) {
    AD1CON1bits.ADON = 0;
    is_initialized = false;
}
