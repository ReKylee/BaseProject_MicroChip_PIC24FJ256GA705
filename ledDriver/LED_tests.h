#ifndef LED_TEST_H
#define LED_TEST_H

/**
 * Main test runner - executes all LED tests in sequence
 * Loops continuously through all test functions
 */
void LED_RunTests(void);

/**
 * Test discrete on/off LEDs (LED1 and LED2)
 * Tests individual control and combined operation
 */
void test_discrete_leds(void);

/**
 * Test RAW PWM control (direct hardware access, no intensity scaling)
 * Demonstrates RGB_SetRaw() functions that bypass intensity
 */
void test_rgb_raw_pwm(void);

/**
 * Test predefined color constants
 * Uses RGB_SetColor() with RGBLED_COLOR_* constants
 */
void test_rgb_color_constants(void);

/**
 * Test intensity scaling feature
 * Shows how RGB_SetIntensity() affects color brightness
 */
void test_rgb_intensity_scaling(void);

/**
 * Test comparison between RAW and scaled functions
 * Demonstrates that RAW functions ignore intensity setting
 */
void test_raw_vs_scaled(void);

/**
 * Test smooth fading using intensity control
 * Fades colors in and out by adjusting intensity
 */
void test_rgb_intensity_fade(void);

/**
 * Test smooth color transitions (color wheel effect)
 * Cycles through RGB color space
 */
void test_rgb_color_wheel(void);

/**
 * Test edge cases and value clamping
 * Verifies that out-of-range values are properly clamped
 */
void test_rgb_edge_cases(void);

/**
 * Test custom colors using RGB() macro
 * Demonstrates creating colors from 8-bit RGB values
 */
void test_custom_colors(void);

/**
 * Test rainbow sequence using named color constants
 * Cycles through a predefined array of rainbow colors
 */
void test_rainbow_sequence(void);

/**
 * Test that intensity setting persists across color changes
 * Verifies intensity remains constant when changing colors
 */
void test_intensity_persistence(void);

#endif /* LED_TEST_H */