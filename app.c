#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "System/system.h"
#include "systemExtensions/systemExtensions.h"
#include "switchDriver/Switch.h"
#include "adcDriver/ADC.h"
#include "ledDriver/LED.h"
#include "ledDriver/RGBLED_colors.h"
#include "oledDriver/oledC.h"
#include "oledDriver/oledC_shapes.h"
#include "oledDriver/oledC_colors.h"

/**
 * @file app.c
 * @brief Example application demonstrating improved driver usage
 * 
 * This application demonstrates:
 * - Two display modes toggled by S1
 * - Color intensity control via potentiometer
 * - Proper error handling
 * - Clean state management
 * - Efficient use of all drivers
 */

// ============================================================================
// Application Types
// ============================================================================

typedef enum {
    MODE_COMPOSITE = 0,  ///< Mix all colors based on pot position
    MODE_INDIVIDUAL = 1  ///< Cycle through individual colors
} DisplayMode_t;

typedef enum {
    COLOR_RED = 0,
    COLOR_GREEN = 1,
    COLOR_BLUE = 2,
    NUM_COLORS = 3
} ColorChannel_t;

typedef struct {
    bool initialized;
    DisplayMode_t mode;
    ColorChannel_t current_color;
    uint16_t color_values[NUM_COLORS];  // Stored intensity for each color
    uint16_t pot_value;                 // Current potentiometer reading
    bool pot_unlocked;                  // For smooth color transitions
    uint32_t last_mode_change;          // Debounce mode changes
} AppContext_t;

// ============================================================================
// Global State
// ============================================================================

static AppContext_t g_app = {
    .initialized = false,
    .mode = MODE_COMPOSITE,
    .current_color = COLOR_RED,
    .color_values = {0, 0, 0},
    .pot_value = 0,
    .pot_unlocked = true,
    .last_mode_change = 0
};

// ============================================================================
// Initialization
// ============================================================================

/**
 * @brief Initialize all hardware and drivers
 * @return true on success, false on error
 */
static bool app_init_hardware(void) {
    // Initialize system
    SYSTEM_Initialize();
    Timer_initialize();
    
    // Initialize drivers
    oledC_setup();
    Switch_Init();
    LED1_Init();
    LED2_Init();
    RGB_Init();
    
    
    // Configure ADC for potentiometer on AN8
    ADC_Config_t adc_config = ADC_GET_DEFAULT_CONFIG(8);
    adc_config.resolution = ADC_RES_10BIT;
    adc_config.output_mode = ADC_OUTPUT_INT;
    
    
    
    if (ADC_Init(&adc_config) != ADC_OK) {
        // Signal error with LED1
        LED1_On();
        return false;
    }
    
    return true;
}

/**
 * @brief Initialize application state
 */
static void app_init_state(void) {
    g_app.mode = MODE_COMPOSITE;
    g_app.current_color = COLOR_RED;
    g_app.color_values[COLOR_RED] = 0;
    g_app.color_values[COLOR_GREEN] = 0;
    g_app.color_values[COLOR_BLUE] = 0;
    g_app.pot_value = 0;
    g_app.pot_unlocked = true;
    g_app.last_mode_change = millis();
    g_app.initialized = true;
}

/**
 * @brief One-time setup
 * @return true on success, false on error
 */
bool app_setup(void) {
    if (!app_init_hardware()) {
        return false;
    }
    
    app_init_state();
    
    // Initial display state
    RGB_Off();
    LED1_Off();
    LED2_Off();
    oledC_clearScreen();
    oledC_setBackground(OLEDC_COLOR_ALICEBLUE);
    
    return true;
}

// ============================================================================
// Mode: Composite Display
// ============================================================================

/**
 * @brief Composite mode - blend all three colors based on pot position
 * 
 * Pot position determines which color(s) are active:
 * - 0-341:    Only RED, fading in
 * - 342-682:  RED fading out, GREEN fading in
 * - 683-1023: GREEN fading out, BLUE fading in
 */
static void mode_composite_update(void) {
    // Read potentiometer
    uint16_t pot;
    if (ADC_ReadRaw(&pot) != ADC_OK) {
        return;  // Skip this update on error
    }
    
    g_app.pot_value = pot;
    
    // Calculate color intensities based on pot position
    uint16_t red, green, blue;
    
    if (pot < 341) {
        // First third: Red fading in
        red = pot * 3;  // 0 to ~1023
        green = 0;
        blue = 0;
    } else if (pot < 682) {
        // Second third: Red fading out, Green fading in
        uint16_t position = pot - 341;
        red = 1023 - (position * 3);
        green = position * 3;
        blue = 0;
    } else {
        // Last third: Green fading out, Blue fading in
        uint16_t position = pot - 682;
        red = 0;
        green = 1023 - (position * 3);
        blue = position * 3;
    }
    
    // Apply to RGB LED (using raw mode since we calculated the blend)
    RGB_SetRaw(red, green, blue);
    
    // Update stored values for mode transition
    g_app.color_values[COLOR_RED] = red;
    g_app.color_values[COLOR_GREEN] = green;
    g_app.color_values[COLOR_BLUE] = blue;
}

// ============================================================================
// Mode: Individual Color Display
// ============================================================================

/**
 * @brief Individual mode - cycle through colors, pot controls intensity
 * 
 * Features:
 * - S2 advances to next color
 * - Pot controls intensity of current color
 * - Smooth transitions when switching colors (pot locking)
 */
static void mode_individual_update(void) {
    // Read potentiometer
    uint16_t pot;
    if (ADC_ReadRaw(&pot) != ADC_OK) {
        return;
    }
    
    g_app.pot_value = pot;
    
    // Handle color change (S2 pressed)
    if (S2_WasPressed()) {
        // Save current color intensity
        if (g_app.pot_unlocked) {
            g_app.color_values[g_app.current_color] = pot;
        }
        
        // Advance to next color
        g_app.current_color = (g_app.current_color + 1) % NUM_COLORS;
        
        // Lock pot until it matches the new color's stored value
        g_app.pot_unlocked = false;
    }
    
    // Check if pot should unlock
    if (!g_app.pot_unlocked) {
        uint16_t stored = g_app.color_values[g_app.current_color];
        // Unlock when pot is within 5% of stored value
        if (pot >= stored - 50 && pot <= stored + 50) {
            g_app.pot_unlocked = true;
        }
    }
    
    // Update current color intensity
    uint16_t display_value;
    if (g_app.pot_unlocked) {
        g_app.color_values[g_app.current_color] = pot;
        display_value = pot;
    } else {
        display_value = g_app.color_values[g_app.current_color];
    }
    
    // Display current color
    const uint32_t colors[NUM_COLORS] = {
        RGBLED_COLOR_RED,
        RGBLED_COLOR_GREEN,
        RGBLED_COLOR_BLUE
    };
    
    RGB_SetColor(colors[g_app.current_color], display_value);
}
// ============================================================================
// OLED Feedback
// ============================================================================

static void oled_render(void) {
	char line[32];


	// Line 1: Mode
	if (g_app.mode == MODE_COMPOSITE) {
		oledC_DrawString(0, 0, 0, 0, (uint8_t*)"Mode: COMPOSITE", OLEDC_COLOR_BLACK );
	} else {
		oledC_DrawString(0, 0, 0, 0, (uint8_t*)"Mode: INDIVIDUAL", OLEDC_COLOR_BLACK);
	}

	// Line 2: Pot value
	snprintf(line, sizeof(line), "Pot: %4u", g_app.pot_value);
	oledC_DrawString(0, 16, 0, 16, (uint8_t*)line, OLEDC_COLOR_BLACK);

	// Line 3: Details
	if (g_app.mode == MODE_COMPOSITE) {
		snprintf(
			line, sizeof(line),
			"R:%3u G:%3u B:%3u",
			g_app.color_values[COLOR_RED] / 4,
			g_app.color_values[COLOR_GREEN] / 4,
			g_app.color_values[COLOR_BLUE] / 4
		);
	} else {
		const char *names[] = {"RED", "GREEN", "BLUE"};
		snprintf(
			line, sizeof(line),
			"%s: %4u",
			names[g_app.current_color],
			g_app.color_values[g_app.current_color]
		);
	}

	oledC_DrawString(0, 32, 0, 32, (uint8_t*)line, OLEDC_COLOR_BLACK);
    
	
}

// ============================================================================
// Mode Management
// ============================================================================

/**
 * @brief Handle mode switching
 */
static void handle_mode_switch(void) {
    uint32_t now = millis();

    // Only allow mode change if enough time has passed
    if ((now - g_app.last_mode_change) < 200) {
        return;
    }

    // Detect a press edge using the debounced driver
    if (S1_WasPressed()) {
        // Toggle mode
        g_app.mode = (g_app.mode == MODE_COMPOSITE) ? MODE_INDIVIDUAL : MODE_COMPOSITE;
        g_app.last_mode_change = now;

        // Unlock pot if switching to individual mode
        if (g_app.mode == MODE_INDIVIDUAL) {
            g_app.pot_unlocked = true;
        }
    }
}


// ============================================================================
// Main Application Loop
// ============================================================================

/**
 * @brief Main application update (call repeatedly)
 */
void app_loop(void) {
	if (!g_app.initialized) {
		return;
	}

	handle_mode_switch();

	switch (g_app.mode) {
		case MODE_COMPOSITE:
			mode_composite_update();
			break;

		case MODE_INDIVIDUAL:
			mode_individual_update();
			break;
	}

	LED2_Set(S2_IsDown());
    LED1_Set(S1_IsDown());
	oled_render();   // ? NEW
}


/**
 * @brief Get current application mode
 * @return Current display mode
 */
DisplayMode_t app_get_mode(void) {
    return g_app.mode;
}

/**
 * @brief Get current potentiometer value
 * @return Pot value (0-1023)
 */
uint16_t app_get_pot_value(void) {
    return g_app.pot_value;
}
