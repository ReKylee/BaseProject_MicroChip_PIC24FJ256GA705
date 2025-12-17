#include <xc.h>
#include "LED.h"
#include "LED_tests.h"
#include "RGBLED_colors.h"
#include "../System/delay.h"

// --- FIX 1: Define a static variable to track the intensity state ---
// This replaces the global state variable removed from LED.c
static uint16_t current_intensity = MAX_DUTY; 
// Note: MAX_DUTY (1023) is defined in LED.h

/* Test discrete LEDs (LED1 and LED2) */
void test_discrete_leds(void) {
    // Test LED1
    LED1_On();
    DELAY_milliseconds(500);
    LED1_Off();
    DELAY_milliseconds(500);

    // Test LED2
    LED2_On();
    DELAY_milliseconds(500);
    LED2_Off();
    DELAY_milliseconds(500);

    // Test both together
    LED1_On();
    LED2_On();
    DELAY_milliseconds(500);
    LED1_Off();
    LED2_Off();
    DELAY_milliseconds(500);

    // Fast blink both
    for (int i = 0; i < 5; i++) {
        LED1_On();
        LED2_On();
        DELAY_milliseconds(100);
        LED1_Off();
        LED2_Off();
        DELAY_milliseconds(100);
    }
}

/* Test RAW PWM control (direct, no intensity scaling) */
void test_rgb_raw_pwm(void) {
    // Test direct PWM values - NOT affected by intensity

    // Full RED PWM
    RGB_SetRaw(1023, 0, 0);
    DELAY_milliseconds(1000);

    // Half RED PWM
    RGB_SetRaw(512, 0, 0);
    DELAY_milliseconds(1000);

    // Quarter RED PWM
    RGB_SetRaw(256, 0, 0);
    DELAY_milliseconds(1000);

    // Full GREEN PWM
    RGB_SetRaw(0, 1023, 0);
    DELAY_milliseconds(1000);

    // Full BLUE PWM
    RGB_SetRaw(0, 0, 1023);
    DELAY_milliseconds(1000);

    // Mixed PWM
    RGB_SetRaw(512, 512, 512);
    DELAY_milliseconds(1000);

    // OFF
    RGB_SetRaw(0, 0, 0);
    DELAY_milliseconds(500);
}

/* Test color constants with predefined colors */
void test_rgb_color_constants(void) {
    // Test predefined color constants
    
    // --- FIX 2: Update local state instead of calling RGB_SetIntensity() ---
    current_intensity = 1023; // Full brightness

    // --- FIX 3: Pass current_intensity to RGB_SetColor() ---
    RGB_SetColor(RGBLED_COLOR_RED, current_intensity);
    DELAY_milliseconds(1000);

    RGB_SetColor(RGBLED_COLOR_GREEN, current_intensity);
    DELAY_milliseconds(1000);

    RGB_SetColor(RGBLED_COLOR_BLUE, current_intensity);
    DELAY_milliseconds(1000);

    RGB_SetColor(RGBLED_COLOR_YELLOW, current_intensity);
    DELAY_milliseconds(1000);

    RGB_SetColor(RGBLED_COLOR_CYAN, current_intensity);
    DELAY_milliseconds(1000);

    RGB_SetColor(RGBLED_COLOR_MAGENTA, current_intensity);
    DELAY_milliseconds(1000);

    RGB_SetColor(RGBLED_COLOR_WHITE, current_intensity);
    DELAY_milliseconds(1000);

    RGB_SetColor(RGBLED_COLOR_ORANGE, current_intensity);
    DELAY_milliseconds(1000);

    RGB_SetColor(RGBLED_COLOR_PURPLE, current_intensity);
    DELAY_milliseconds(1000);

    RGB_SetColor(RGBLED_COLOR_LIME, current_intensity);
    DELAY_milliseconds(1000);

    // OFF
    RGB_SetColor(RGBLED_COLOR_BLACK, current_intensity);
    DELAY_milliseconds(500);
}

/* Test intensity scaling feature */
void test_rgb_intensity_scaling(void) {
    // Set a color and test different intensity levels
    
    // --- FIX 4: Set color first, then update intensity state and call again ---
    RGB_SetColor(RGBLED_COLOR_WHITE, current_intensity);

    // 100% intensity
    current_intensity = 1023;
    RGB_SetColor(RGBLED_COLOR_WHITE, current_intensity);
    DELAY_milliseconds(1000);

    // 75% intensity
    current_intensity = 768;
    RGB_SetColor(RGBLED_COLOR_WHITE, current_intensity);
    DELAY_milliseconds(1000);

    // 50% intensity
    current_intensity = 512;
    RGB_SetColor(RGBLED_COLOR_WHITE, current_intensity);
    DELAY_milliseconds(1000);

    // 25% intensity
    current_intensity = 256;
    RGB_SetColor(RGBLED_COLOR_WHITE, current_intensity);
    DELAY_milliseconds(1000);

    // 10% intensity
    current_intensity = 102;
    RGB_SetColor(RGBLED_COLOR_WHITE, current_intensity);
    DELAY_milliseconds(1000);

    // Back to full
    current_intensity = 1023;
    RGB_SetColor(RGBLED_COLOR_WHITE, current_intensity);
    DELAY_milliseconds(1000);

    // Test with different color
    current_intensity = 1023; // Reset before changing color
    RGB_SetColor(RGBLED_COLOR_PURPLE, current_intensity);
    
    current_intensity = 512; // 50% brightness
    RGB_SetColor(RGBLED_COLOR_PURPLE, current_intensity);
    DELAY_milliseconds(1000);

    current_intensity = 1023; // Full brightness
    RGB_SetColor(RGBLED_COLOR_PURPLE, current_intensity);
    DELAY_milliseconds(1000);

    // OFF
    RGB_SetColor(RGBLED_COLOR_BLACK, current_intensity);
    DELAY_milliseconds(500);
}

/* Test that RAW functions ignore intensity */
void test_raw_vs_scaled(void) {
    // Set intensity to 25%
    current_intensity = 256;

    // Use color function - SHOULD be affected by intensity (25% bright)
    RGB_SetColor(RGBLED_COLOR_RED, current_intensity);
    DELAY_milliseconds(1500);

    // Use RAW function - should NOT be affected by intensity (full brightness)
    RGB_SetRaw(1023, 0, 0);
    DELAY_milliseconds(1500);

    // Back to color function - affected by intensity again (25% bright)
    RGB_SetColor(RGBLED_COLOR_RED, current_intensity);
    DELAY_milliseconds(1500);

    // Reset intensity to full
    current_intensity = 1023;
    RGB_SetColor(RGBLED_COLOR_RED, current_intensity);
    DELAY_milliseconds(1500);

    // OFF
    RGB_SetRaw(0, 0, 0);
    DELAY_milliseconds(500);
}

/* Test smooth fade using intensity */
void test_rgb_intensity_fade(void) {
    // Set a nice color and fade it
    // --- FIX 5: Use a default intensity for the initial color call ---
    current_intensity = 1023; 
    RGB_SetColor(RGBLED_COLOR_CYAN, current_intensity);

    // Fade in
    for (uint16_t i = 0; i <= 1023; i += 32) {
        // --- FIX 6: Update state, then call RGB_SetColor() with that state ---
        current_intensity = i;
        RGB_SetColor(RGBLED_COLOR_CYAN, current_intensity);
        DELAY_milliseconds(20);
    }

    // Fade out
    for (int16_t i = 1023; i >= 0; i -= 32) {
        current_intensity = i;
        RGB_SetColor(RGBLED_COLOR_CYAN, current_intensity);
        DELAY_milliseconds(20);
    }

    // Try with different color
    current_intensity = 1023;
    RGB_SetColor(RGBLED_COLOR_ORANGE, current_intensity);

    // Fade in
    for (uint16_t i = 0; i <= 1023; i += 32) {
        current_intensity = i;
        RGB_SetColor(RGBLED_COLOR_ORANGE, current_intensity);
        DELAY_milliseconds(20);
    }

    // Fade out
    for (int16_t i = 1023; i >= 0; i -= 32) {
        current_intensity = i;
        RGB_SetColor(RGBLED_COLOR_ORANGE, current_intensity);
        DELAY_milliseconds(20);
    }

    current_intensity = 1023; // Reset to full
    RGB_SetColor(RGBLED_COLOR_BLACK, current_intensity);
    DELAY_milliseconds(300);
}

/* Test color wheel using RGB_Set with intensity */
void test_rgb_color_wheel(void) {
    current_intensity = 1023; // Full brightness

    // Transition through colors smoothly
    for (int step = 0; step < 6; step++) {
        for (uint16_t i = 0; i <= 1023; i += 64) {
            switch (step) {
                // --- FIX 7: Pass current_intensity to RGB_Set() ---
                case 0: RGB_Set(1023, i, 0, current_intensity);
                    break; // RED to YELLOW
                case 1: RGB_Set(1023 - i, 1023, 0, current_intensity);
                    break; // YELLOW to GREEN
                case 2: RGB_Set(0, 1023, i, current_intensity);
                    break; // GREEN to CYAN
                case 3: RGB_Set(0, 1023 - i, 1023, current_intensity);
                    break; // CYAN to BLUE
                case 4: RGB_Set(i, 0, 1023, current_intensity);
                    break; // BLUE to MAGENTA
                case 5: RGB_Set(1023, 0, 1023 - i, current_intensity);
                    break; // MAGENTA to RED
            }
            DELAY_milliseconds(20);
        }
    }
    RGB_Set(0, 0, 0, current_intensity);
    DELAY_milliseconds(500);
}

/* Test edge cases and clamping */
void test_rgb_edge_cases(void) {
    current_intensity = 1023; // Full intensity

    // Test minimum value (0)
    RGB_Set(0, 0, 0, current_intensity);
    DELAY_milliseconds(500);

    // Test maximum value (1023)
    RGB_Set(1023, 1023, 1023, current_intensity);
    DELAY_milliseconds(500);

    // Test intensity clamping
    RGB_SetColor(RGBLED_COLOR_WHITE, current_intensity);
    // The clamp is now handled by CLAMP_MAXDUTY inside the test file (if used), 
    // or by the macro in LED.h when setting PWM registers.
    current_intensity = 5000; // Value is clamped inside the macro/inline
    RGB_SetColor(RGBLED_COLOR_WHITE, current_intensity);
    DELAY_milliseconds(500);

    current_intensity = 1023; // Reset
    RGB_Set(0, 0, 0, current_intensity);
    DELAY_milliseconds(500);
}

/* Test custom colors using RGB macro */
void test_custom_colors(void) {
    current_intensity = 1023; // Full brightness

    // Custom colors using RGB() macro
    RGB_SetColor(RGB(255, 128, 0), current_intensity); // Orange
    DELAY_milliseconds(1000);

    RGB_SetColor(RGB(128, 0, 255), current_intensity); // Purple
    DELAY_milliseconds(1000);

    RGB_SetColor(RGB(0, 255, 128), current_intensity); // Spring green
    DELAY_milliseconds(1000);

    RGB_SetColor(RGB(255, 0, 128), current_intensity); // Pink-red
    DELAY_milliseconds(1000);

    RGB_SetColor(RGB(128, 255, 0), current_intensity); // Lime-yellow
    DELAY_milliseconds(1000);

    RGB_SetColor(RGB(64, 64, 64), current_intensity); // Dim gray
    DELAY_milliseconds(1000);

    RGB_SetColor(RGB(192, 192, 64), current_intensity); // Olive
    DELAY_milliseconds(1000);

    // OFF
    RGB_SetColor(RGBLED_COLOR_BLACK, current_intensity);
    DELAY_milliseconds(500);
}

/* Test rainbow sequence with named colors */
void test_rainbow_sequence(void) {
    current_intensity = 1023; // Full brightness

    const uint32_t rainbow[] = {
        RGBLED_COLOR_RED,
        RGBLED_COLOR_ORANGERED,
        RGBLED_COLOR_ORANGE,
        RGBLED_COLOR_GOLD,
        RGBLED_COLOR_YELLOW,
        RGBLED_COLOR_GREENYELLOW,
        RGBLED_COLOR_LIME,
        RGBLED_COLOR_SPRINGGREEN,
        RGBLED_COLOR_DEEPSKYBLUE,
        RGBLED_COLOR_BLUE,
        RGBLED_COLOR_BLUEVIOLET,
        RGBLED_COLOR_PURPLE,
        RGBLED_COLOR_DEEPPINK
    };

    const uint8_t count = sizeof (rainbow) / sizeof (rainbow[0]);

    // Cycle through rainbow twice
    for (uint8_t j = 0; j < 2; j++) {
        for (uint8_t i = 0; i < count; i++) {
            RGB_SetColor(rainbow[i], current_intensity);
            DELAY_milliseconds(300);
        }
    }

    RGB_SetColor(RGBLED_COLOR_BLACK, current_intensity);
    DELAY_milliseconds(500);
}

/* Test intensity persistence across color changes */
void test_intensity_persistence(void) {
    // Set intensity to 50%
    current_intensity = 512;

    RGB_SetColor(RGBLED_COLOR_RED, current_intensity);
    DELAY_milliseconds(800);

    RGB_SetColor(RGBLED_COLOR_GREEN, current_intensity);
    DELAY_milliseconds(800);

    RGB_SetColor(RGBLED_COLOR_BLUE, current_intensity);
    DELAY_milliseconds(800);

    RGB_SetColor(RGBLED_COLOR_YELLOW, current_intensity);
    DELAY_milliseconds(800);

    // Change intensity, colors persist (by passing the new intensity)
    current_intensity = 256; // 25%
    RGB_SetColor(RGBLED_COLOR_YELLOW, current_intensity);
    DELAY_milliseconds(800);

    current_intensity = 1023; // 100%
    RGB_SetColor(RGBLED_COLOR_YELLOW, current_intensity);
    DELAY_milliseconds(800);

    RGB_SetColor(RGBLED_COLOR_BLACK, current_intensity);
    current_intensity = 1023; // Reset for next test
    DELAY_milliseconds(500);
}

/* Main test function */
void LED_RunTests(void) {
    // Initialize all LEDs
    LED1_Init();
    LED2_Init();
    RGB_Init();
    
    // Set initial intensity state for testing
    current_intensity = MAX_DUTY; 

    while (1) {
        // Test 1: Discrete LEDs
        test_discrete_leds();
        DELAY_milliseconds(1000);

        // Test 2: RAW PWM Control (no scaling)
        test_rgb_raw_pwm();
        DELAY_milliseconds(1000);

        // Test 3: Color Constants
        test_rgb_color_constants();
        DELAY_milliseconds(1000);

        // Test 4: Intensity Scaling
        test_rgb_intensity_scaling();
        DELAY_milliseconds(1000);

        // Test 5: RAW vs Scaled Comparison
        test_raw_vs_scaled();
        DELAY_milliseconds(1000);

        // Test 6: Intensity Fade
        test_rgb_intensity_fade();
        DELAY_milliseconds(1000);

        // Test 7: Color Wheel
        test_rgb_color_wheel();
        DELAY_milliseconds(1000);

        // Test 8: Edge Cases & Clamping
        test_rgb_edge_cases();
        DELAY_milliseconds(1000);

        // Test 9: Custom Colors
        test_custom_colors();
        DELAY_milliseconds(1000);

        // Test 10: Rainbow Sequence
        test_rainbow_sequence();
        DELAY_milliseconds(1000);

        // Test 11: Intensity Persistence
        test_intensity_persistence();
        DELAY_milliseconds(1000);

        // Long pause before repeating
        DELAY_milliseconds(3000);
    }
}