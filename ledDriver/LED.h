#ifndef LED_H
#define LED_H

#include <xc.h>
#include <stdint.h>
#include "RGBLED_colors.h"

/**
 * @file LED.h
 * @brief LED driver for discrete and RGB LEDs on PIC24FJ256GA705
 * 
 * Features:
 * - Two discrete LEDs (LED1, LED2)
 * - One RGB LED with PWM control
 * - Raw PWM control (no scaling)
 * - Intensity-scaled PWM control
 * - Color constant library support
 * - Zero-overhead macros for discrete LEDs
 * 
 * IMPORTANT: Intensity Management
 * --------------------------------
 * The RGB LED has TWO control modes:
 * 
 * 1. RAW MODE (RGB_SetRaw):
 *    - Direct hardware PWM control (0-1023)
 *    - NO intensity scaling applied
 *    - Use for maximum brightness or direct control
 * 
 * 2. SCALED MODE (RGB_Set, RGB_SetColor):
 *    - Intensity parameter scales the color (0-1023)
 *    - intensity=1023 = full brightness
 *    - intensity=512  = 50% brightness
 *    - intensity=0    = off
 *    - Color values are scaled by intensity before output
 * 
 * @example Basic Usage
 * // Initialize
 * RGB_Init();
 * 
 * // Set red at full brightness
 * RGB_SetColor(RGBLED_COLOR_RED, 1023);
 * 
 * // Set red at 50% brightness
 * RGB_SetColor(RGBLED_COLOR_RED, 512);
 * 
 * // Set custom color at 75% brightness
 * RGB_Set(1023, 512, 0, 768);  // Orange at 75%
 * 
 * // Raw control (ignores intensity, always full)
 * RGB_SetRaw(1023, 0, 0);  // Full red, no scaling
 */

// ============================================================================
// Constants
// ============================================================================

#define MAX_DUTY        1023u   ///< Maximum PWM duty cycle (10-bit)
#define PWM_RESOLUTION  10      ///< PWM resolution in bits

#define LED1_MASK (1u << 8)     ///< RA8
#define LED2_MASK (1u << 9)     ///< RA9

// ============================================================================
// Helper Macros (Internal Use)
// ============================================================================

/** @brief Clamp value to MAX_DUTY */
#define CLAMP_MAXDUTY(v) ((uint16_t)((v) > MAX_DUTY ? MAX_DUTY : (v)))

/** @brief Scale PWM value by intensity with rounding
 *  Formula: (value * intensity + 512) / 1024
 */
#define SCALE_PWM_ROUNDED(v, intensity) \
    ((uint16_t)(((uint32_t)(v) * (intensity) + 512u) >> PWM_RESOLUTION))

// ============================================================================
// Color Conversion Macros
// ============================================================================

/** @brief Extract red component (0-255) from 32-bit color */
#define GET_RED_8BIT(color)   (((color) >> 16) & 0xFF)

/** @brief Extract green component (0-255) from 32-bit color */
#define GET_GREEN_8BIT(color) (((color) >> 8) & 0xFF)

/** @brief Extract blue component (0-255) from 32-bit color */
#define GET_BLUE_8BIT(color)  ((color) & 0xFF)

/** @brief Convert 8-bit color value (0-255) to 10-bit PWM (0-1023)
 *  Formula: pwm10 = (value8 << 2) | (value8 >> 6)
 *  This provides better distribution than simple multiplication
 */
#define RGB8_TO_PWM10(val8) \
    ((((uint16_t)(val8)) << 2) | (((uint16_t)(val8)) >> 6))

/** @brief Extract and convert red to 10-bit PWM */
#define GET_RED_PWM(color)   RGB8_TO_PWM10(GET_RED_8BIT(color))

/** @brief Extract and convert green to 10-bit PWM */
#define GET_GREEN_PWM(color) RGB8_TO_PWM10(GET_GREEN_8BIT(color))

/** @brief Extract and convert blue to 10-bit PWM */
#define GET_BLUE_PWM(color)  RGB8_TO_PWM10(GET_BLUE_8BIT(color))

// ============================================================================
// Discrete LED Macros (Zero Overhead)
// ============================================================================

/**
 * @brief Initialize LED1 (configure as output, turn off)
 */
#define LED1_Init() do { \
    TRISA &= ~LED1_MASK; \
    LATA &= ~LED1_MASK; \
} while(0)

/**
 * @brief Initialize LED2 (configure as output, turn off)
 */
#define LED2_Init() do { \
    TRISA &= ~LED2_MASK; \
    LATA &= ~LED2_MASK; \
} while(0)

/**
 * @brief Turn LED1 on
 */
#define LED1_On()  (LATA |= LED1_MASK)

/**
 * @brief Turn LED1 off
 */
#define LED1_Off() (LATA &= ~LED1_MASK)

/**
 * @brief Set LED1 state
 * @param on true to turn on, false to turn off
 */
#define LED1_Set(on) ((on) ? LED1_On() : LED1_Off())

/**
 * @brief Toggle LED1 state
 */
#define LED1_Toggle() (LATA ^= LED1_MASK)

/**
 * @brief Turn LED2 on
 */
#define LED2_On()  (LATA |= LED2_MASK)

/**
 * @brief Turn LED2 off
 */
#define LED2_Off() (LATA &= ~LED2_MASK)

/**
 * @brief Set LED2 state
 * @param on true to turn on, false to turn off
 */
#define LED2_Set(on) ((on) ? LED2_On() : LED2_Off())

/**
 * @brief Toggle LED2 state
 */
#define LED2_Toggle() (LATA ^= LED2_MASK)

// ============================================================================
// RGB LED Initialization Macro
// ============================================================================

/**
 * @brief Initialize RGB LED PWM channels
 * 
 * Configures:
 * - Output Compare modules 1, 2, 3 for PWM
 * - Pins RA0 (OC1/Red), RA1 (OC2/Green), RC7 (OC3/Blue)
 * - 10-bit PWM resolution
 * - Initial state: OFF (all channels at 0)
 */
#define RGB_Init() do { \
    TRISAbits.TRISA0 = 0; \
    TRISAbits.TRISA1 = 0; \
    TRISCbits.TRISC7 = 0; \
    RPOR13bits.RP26R = 13; \
    RPOR13bits.RP27R = 14; \
    RPOR11bits.RP23R = 15; \
    OC1RS = MAX_DUTY; \
    OC2RS = MAX_DUTY; \
    OC3RS = MAX_DUTY; \
    OC1CON2bits.SYNCSEL = 0x1F; \
    OC1CON2bits.OCTRIG  = 0; \
    OC1CON1bits.OCTSEL  = 0b111; \
    OC1CON1bits.OCM     = 0b110; \
    OC1CON2bits.TRIGSTAT = 1; \
    OC2CON2bits.SYNCSEL = 0x1F; \
    OC2CON2bits.OCTRIG  = 0; \
    OC2CON1bits.OCTSEL  = 0b111; \
    OC2CON1bits.OCM     = 0b110; \
    OC2CON2bits.TRIGSTAT = 1; \
    OC3CON2bits.SYNCSEL = 0x1F; \
    OC3CON2bits.OCTRIG  = 0; \
    OC3CON1bits.OCTSEL  = 0b111; \
    OC3CON1bits.OCM     = 0b110; \
    OC3CON2bits.TRIGSTAT = 1; \
    OC1R = 0; OC2R = 0; OC3R = 0; \
} while(0)

// ============================================================================
// RGB LED Functions
// ============================================================================

/**
 * @brief Set RGB LED with raw PWM values (NO intensity scaling)
 * @param r Red channel PWM (0-1023)
 * @param g Green channel PWM (0-1023)
 * @param b Blue channel PWM (0-1023)
 * 
 * @note Values are clamped to MAX_DUTY (1023)
 * @note This function bypasses any intensity scaling
 * 
 * @example
 * RGB_SetRaw(1023, 0, 0);  // Full brightness red
 * RGB_SetRaw(512, 512, 0); // Medium yellow
 */
static inline void RGB_SetRaw(uint16_t r, uint16_t g, uint16_t b) {
    OC1R = CLAMP_MAXDUTY(r);
    OC2R = CLAMP_MAXDUTY(g);
    OC3R = CLAMP_MAXDUTY(b);
}

/**
 * @brief Set RGB LED with intensity scaling
 * @param r Red channel value (0-1023)
 * @param g Green channel value (0-1023)
 * @param b Blue channel value (0-1023)
 * @param intensity Brightness scaling factor (0-1023)
 *        - 1023 = 100% brightness (no scaling)
 *        - 512  = 50% brightness
 *        - 0    = off
 * 
 * @note Final PWM values are: (channel_value * intensity) / 1024
 * @note All values are clamped to MAX_DUTY
 * 
 * @example
 * // Red at full brightness
 * RGB_Set(1023, 0, 0, 1023);
 * 
 * // White at 50% brightness
 * RGB_Set(1023, 1023, 1023, 512);
 * 
 * // Blue at 25% brightness
 * RGB_Set(0, 0, 1023, 256);
 */
static inline void RGB_Set(uint16_t r, uint16_t g, uint16_t b, uint16_t intensity) {
    OC1R = SCALE_PWM_ROUNDED(CLAMP_MAXDUTY(r), intensity);
    OC2R = SCALE_PWM_ROUNDED(CLAMP_MAXDUTY(g), intensity);
    OC3R = SCALE_PWM_ROUNDED(CLAMP_MAXDUTY(b), intensity);
}

/**
 * @brief Set RGB LED using a 32-bit color constant with intensity scaling
 * @param color 32-bit color value (0x00RRGGBB format, each component 0-255)
 *        Use RGBLED_COLOR_* constants from RGBLED_colors.h
 * @param intensity Brightness scaling factor (0-1023)
 * 
 * @note Color components are automatically converted from 8-bit to 10-bit PWM
 * @note Final values are scaled by intensity parameter
 * 
 * @example
 * // Red at full brightness
 * RGB_SetColor(RGBLED_COLOR_RED, 1023);
 * 
 * // Green at 50% brightness
 * RGB_SetColor(RGBLED_COLOR_GREEN, 512);
 * 
 * // Custom color at 75% brightness
 * RGB_SetColor(RGB(255, 128, 0), 768);  // Orange
 */
static inline void RGB_SetColor(uint32_t color, uint16_t intensity) {
    RGB_Set(
        GET_RED_PWM(color),
        GET_GREEN_PWM(color),
        GET_BLUE_PWM(color),
        intensity
    );
}

/**
 * @brief Turn off RGB LED
 */
static inline void RGB_Off(void) {
    RGB_SetRaw(0, 0, 0);
}

#endif /* LED_H */
