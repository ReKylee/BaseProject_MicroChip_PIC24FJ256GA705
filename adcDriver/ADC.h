#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @file ADC.h
 * @brief Analog-to-Digital Converter driver for PIC24FJ256GA705
 * 
 * Features:
 * - Configurable resolution (10-bit or 12-bit)
 * - Multiple output formats (integer or float)
 * - Single-channel conversion
 * - Error handling
 * - Minimal overhead
 */

// ============================================================================
// Type Definitions
// ============================================================================

/**
 * @brief ADC resolution options
 */
typedef enum {
    ADC_RES_10BIT = 0,  ///< 10-bit resolution (0-1023)
    ADC_RES_12BIT = 1   ///< 12-bit resolution (0-4095)
} ADC_Resolution_t;

/**
 * @brief ADC output mode
 */
typedef enum {
    ADC_OUTPUT_INT,     ///< Raw integer value
    ADC_OUTPUT_FLOAT    ///< Normalized float (0.0 - 1.0)
} ADC_OutputMode_t;

/**
 * @brief ADC error codes
 */
typedef enum {
    ADC_OK = 0,              ///< No error
    ADC_ERR_NOT_INIT = -1,   ///< ADC not initialized
    ADC_ERR_INVALID_CH = -2, ///< Invalid channel number
    ADC_ERR_TIMEOUT = -3     ///< Conversion timeout
} ADC_Error_t;

/**
 * @brief ADC configuration structure
 */
typedef struct {
    uint8_t channel;              ///< ANx channel number (0-15)
    ADC_Resolution_t resolution;  ///< ADC resolution
    ADC_OutputMode_t output_mode; ///< Output format
    uint16_t sample_time;         ///< Sample time (TAD cycles, default: 16)
    uint8_t conversion_clock;     ///< Conversion clock divider (default: 2)
} ADC_Config_t;

// ============================================================================
// Default Configuration
// ============================================================================

/**
 * @brief Get default ADC configuration
 * @param channel ADC channel to use (0-15)
 * @return Default configuration structure
 * 
 * @example
 * ADC_Config_t cfg = ADC_GetDefaultConfig(8);  // AN8
 * ADC_Init(&cfg);
 */
#define ADC_GET_DEFAULT_CONFIG(ch) ((ADC_Config_t){ \
	.channel = (ch), \
	.resolution = ADC_RES_10BIT, \
	.output_mode = ADC_OUTPUT_INT, \
	.sample_time = 16, \
	.conversion_clock = 2 \
})


// ============================================================================
// Function Prototypes
// ============================================================================

/**
 * @brief Initialize ADC with specified configuration
 * @param config Pointer to configuration structure
 * @return ADC_OK on success, error code otherwise
 * 
 * @example
 * ADC_Config_t cfg = ADC_GET_DEFAULT_CONFIG(8);
 * if (ADC_Init(&cfg) != ADC_OK) {
 *     // Handle error
 * }
 */
ADC_Error_t ADC_Init(const ADC_Config_t* config);

/**
 * @brief Change ADC channel after initialization
 * @param channel New channel number (0-15)
 * @return ADC_OK on success, error code otherwise
 * 
 * @note This is faster than re-initializing if only the channel changes
 */
ADC_Error_t ADC_SetChannel(uint8_t channel);

/**
 * @brief Read raw ADC value
 * @param value Pointer to store result
 * @return ADC_OK on success, error code otherwise
 * 
 * @example
 * uint16_t adc_value;
 * if (ADC_ReadRaw(&adc_value) == ADC_OK) {
 *     // Use adc_value
 * }
 */
ADC_Error_t ADC_ReadRaw(uint16_t* value);

/**
 * @brief Read normalized ADC value as float (0.0 - 1.0)
 * @param value Pointer to store result
 * @return ADC_OK on success, error code otherwise
 * 
 * @example
 * float voltage_ratio;
 * if (ADC_ReadFloat(&voltage_ratio) == ADC_OK) {
 *     float voltage = voltage_ratio * 3.3f;  // Assuming 3.3V reference
 * }
 */
ADC_Error_t ADC_ReadFloat(float* value);

/**
 * @brief Check if ADC is initialized
 * @return true if initialized, false otherwise
 */
bool ADC_IsInitialized(void);

/**
 * @brief Get current ADC configuration
 * @param config Pointer to store current configuration
 * @return ADC_OK on success, error code otherwise
 */
ADC_Error_t ADC_GetConfig(ADC_Config_t* config);

/**
 * @brief Disable ADC to save power
 * @note Must call ADC_Init() again to re-enable
 */
void ADC_Disable(void);

#endif // ADC_H
