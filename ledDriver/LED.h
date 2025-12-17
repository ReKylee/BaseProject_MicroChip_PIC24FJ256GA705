#ifndef LED_H
#define LED_H

#include <xc.h>
#include <stdint.h>
#include "RGBLED_colors.h"

/* ================= Constants ================= */
#define MAX_DUTY        1023u
#define PWM_RESOLUTION  10

#define LED1_MASK (1u << 8)   /* RA8 */
#define LED2_MASK (1u << 9)   /* RA9 */


/* ================= Helper Macros ================= */
#define CLAMP_MAXDUTY(v)   ((uint16_t)((v) > MAX_DUTY ? MAX_DUTY : (v)))

// SCALE_PWM_ROUNDED calculates: Value * (Intensity + 0.5) / MAX_DUTY)
#define SCALE_PWM_ROUNDED(v, intensity) ((uint16_t)(((uint32_t)(v) * (intensity) + 512u) >> PWM_RESOLUTION))

#define LED_ON(port, mask)   ((port) |=  (mask))
#define LED_OFF(port, mask)  ((port) &= ~(mask))
#define LED_SET(port, mask, on) ((on) ? LED_ON(port, mask) : LED_OFF(port, mask))

// Helper macros to extract individual 8-bit color components
#define GET_RED_8BIT(color)   (((color) >> 16) & 0xFF)
#define GET_GREEN_8BIT(color) (((color) >> 8) & 0xFF)
#define GET_BLUE_8BIT(color)  ((color) & 0xFF)

// Helper macros to convert 8-bit components (0-255) to 10-bit PWM values (0-1023)
// Formula: pwm10 = (value8 * 1023 + 127) / 255  (with rounding)
#define RGB8_TO_PWM10(val8) ((((uint16_t)(val8)) << 2) | (((uint16_t)(val8)) >> 6))

// Extract and convert to 10-bit PWM in one step
#define GET_RED_PWM(color)   RGB8_TO_PWM10(GET_RED_8BIT(color))
#define GET_GREEN_PWM(color) RGB8_TO_PWM10(GET_GREEN_8BIT(color))
#define GET_BLUE_PWM(color)  RGB8_TO_PWM10(GET_BLUE_8BIT(color))


/* ================= Discrete LED Init ================= */
#define LED1_Init() do { \
    TRISA &= ~LED1_MASK; \
    LED_OFF(LATA, LED1_MASK); \
} while (0)

#define LED2_Init() do { \
    TRISA &= ~LED2_MASK; \
    LED_OFF(LATA, LED2_MASK); \
} while (0)

/* ================= RGB Init ================= */
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
} while (0)

/* ================= Discrete LED Control ================= */
#define LED1_On()      LED_ON(LATA, LED1_MASK)
#define LED1_Off()     LED_OFF(LATA, LED1_MASK)
#define LED1_Set(on)   LED_SET(LATA, LED1_MASK, (on))

#define LED2_On()      LED_ON(LATA, LED2_MASK)
#define LED2_Off()     LED_OFF(LATA, LED2_MASK)
#define LED2_Set(on)   LED_SET(LATA, LED2_MASK, (on))

/* ================= RGB Raw PWM ================= */
static inline void RGB_SetRaw(uint16_t r, uint16_t g, uint16_t b) {
    OC1R = CLAMP_MAXDUTY(r);
    OC2R = CLAMP_MAXDUTY(g);
    OC3R = CLAMP_MAXDUTY(b);
}

/* ================= RGB Scaled PWM ================= */
static inline void RGB_Set(uint16_t r, uint16_t g, uint16_t b, uint16_t intensity) {
    OC1R = SCALE_PWM_ROUNDED(CLAMP_MAXDUTY(r), intensity);
    OC2R = SCALE_PWM_ROUNDED(CLAMP_MAXDUTY(g), intensity);
    OC3R = SCALE_PWM_ROUNDED(CLAMP_MAXDUTY(b), intensity);
}

static inline void RGB_SetColor(uint32_t color, uint16_t intensity) {
    RGB_Set(
            GET_RED_PWM(color),
            GET_GREEN_PWM(color),
            GET_BLUE_PWM(color),
            intensity
            );
}

#endif /* LED_H */
