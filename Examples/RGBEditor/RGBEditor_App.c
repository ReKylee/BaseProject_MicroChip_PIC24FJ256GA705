#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "../../System/system.h"
#include "../../systemExtensions/systemExtensions.h"
#include "../../switchDriver/Switch.h"
#include "../../adcDriver/ADC.h"
#include "../../ledDriver/LED.h"
#include "../../ledDriver/RGBLED_colors.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include "../../oledDriver/oledC_colors.h"
#include "RGBEditor_App.h"

/**
 * @file app.c
 * @brief Color Picker Application with synchronized LED/OLED output
 */

// ============================================================================
// Configuration & Constants
// ============================================================================

#define UI_BAR_X        15
#define UI_BAR_WIDTH    75
#define UI_BAR_HEIGHT   6
#define UI_BAR_R_Y      20
#define UI_BAR_G_Y      32
#define UI_BAR_B_Y      44
#define UI_PREVIEW_Y    58
#define UI_PREVIEW_SZ   20

#define MAX_ADC_VAL     1023
#define MAX_BAR_WIDTH   UI_BAR_WIDTH

typedef enum {
    MODE_COMPOSITE = 0,
    MODE_INDIVIDUAL = 1
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
    ColorChannel_t current_channel;
    
    // Core State (10-bit values 0-1023)
    uint16_t channel_val[NUM_COLORS]; 
    uint16_t pot_value; 
    bool pot_unlocked;
    uint32_t last_mode_change;

    // Rendering Cache
    DisplayMode_t last_mode;
    uint16_t last_pot_val;
    uint8_t last_bar_width[NUM_COLORS]; 
    uint16_t last_preview_color;
} AppContext_t;

static AppContext_t g_app;

// ============================================================================
// Helper: Safe 32-bit Scaling
// ============================================================================

/**
 * @brief Safely scales a value using 32-bit math to prevent overflow
 * @param val The value to scale (e.g., 0-1023)
 * @param scaler The scaling factor (e.g., 0-1023 or 0-75)
 * @param max_scaler The maximum possible value of the scaler (e.g., 1023)
 * @return Scaled result
 */
static inline uint16_t scale_value(uint16_t val, uint16_t scaler, uint16_t max_scaler) {
    // Cast to uint32_t BEFORE multiplication to handle results > 65535
    return (uint16_t)( ((uint32_t)val * (uint32_t)scaler) / (uint32_t)max_scaler );
}

// ============================================================================
// Setup
// ============================================================================

static bool app_init_hardware(void) {
    SYSTEM_Initialize();
    Timer_initialize();
    oledC_setup();
    Switch_Init();
    LED1_Init();
    LED2_Init();
    RGB_Init();

    ADC_Config_t adc_config = ADC_GET_DEFAULT_CONFIG(8);
    adc_config.resolution = ADC_RES_10BIT;
    if (ADC_Init(&adc_config) != ADC_OK) return false;

    return true;
}

static void app_init_state(void) {
    g_app.mode = MODE_COMPOSITE;
    g_app.current_channel = COLOR_RED;
    // Default to white
    g_app.channel_val[COLOR_RED] = 256;
    g_app.channel_val[COLOR_GREEN] = 256;
    g_app.channel_val[COLOR_BLUE] = 256;
    g_app.pot_value = 0;
    g_app.pot_unlocked = true;
    g_app.last_mode_change = millis();
    g_app.initialized = true;

    // Invalidate cache
    g_app.last_mode = (DisplayMode_t) -1;
    g_app.last_pot_val = 0xFFFF;
    g_app.last_preview_color = 0xFFFF;
    for(int i=0; i<NUM_COLORS; i++) g_app.last_bar_width[i] = 255;
}

static void draw_static_interface(void) {
    oledC_setBackground(OLEDC_COLOR_ALICEBLUE);
    oledC_clearScreen();
    
    oledC_DrawString(2, UI_BAR_R_Y, 1, 1, (uint8_t*)"R", OLEDC_COLOR_RED);
    oledC_DrawString(2, UI_BAR_G_Y, 1, 1, (uint8_t*)"G", OLEDC_COLOR_GREEN);
    oledC_DrawString(2, UI_BAR_B_Y, 1, 1, (uint8_t*)"B", OLEDC_COLOR_BLUE);
    
    uint16_t outline_color = OLEDC_COLOR_GRAY;
    oledC_DrawRectangle(UI_BAR_X-1, UI_BAR_R_Y-1, UI_BAR_X + UI_BAR_WIDTH + 1, UI_BAR_R_Y + UI_BAR_HEIGHT + 1, outline_color);
    oledC_DrawRectangle(UI_BAR_X-1, UI_BAR_G_Y-1, UI_BAR_X + UI_BAR_WIDTH + 1, UI_BAR_G_Y + UI_BAR_HEIGHT + 1, outline_color);
    oledC_DrawRectangle(UI_BAR_X-1, UI_BAR_B_Y-1, UI_BAR_X + UI_BAR_WIDTH + 1, UI_BAR_B_Y + UI_BAR_HEIGHT + 1, outline_color);
}

bool app_setup(void) {
    if (!app_init_hardware()) return false;
    app_init_state();
    RGB_Off();
    draw_static_interface();
    return true;
}

// ============================================================================
// Logic Update
// ============================================================================

static void update_inputs(void) {
    uint16_t raw_pot;
    if (ADC_ReadRaw(&raw_pot) == ADC_OK) {
        g_app.pot_value = raw_pot;
    }
}

static void logic_composite(void) {
    // Composite Mode: Logic happens in rendering (scaling)
}

static void logic_individual(void) {
    if (S2_WasPressed()) {
        if (g_app.pot_unlocked) {
            g_app.channel_val[g_app.current_channel] = g_app.pot_value;
        }
        g_app.current_channel = (g_app.current_channel + 1) % NUM_COLORS;
        g_app.pot_unlocked = false;
    }

    if (!g_app.pot_unlocked) {
        uint16_t stored = g_app.channel_val[g_app.current_channel];
        if (g_app.pot_value >= (stored > 50 ? stored - 50 : 0) && 
            g_app.pot_value <= (stored + 50)) {
            g_app.pot_unlocked = true;
        }
    }

    if (g_app.pot_unlocked) {
        g_app.channel_val[g_app.current_channel] = g_app.pot_value;
    }
}

// ============================================================================
// Core Rendering (Synchronized)
// ============================================================================

static void update_outputs_and_render(void) {
    char text_buf[20];
    
    // ------------------------------------------------------------------------
    // 1. Calculate TRUE Output Values (0-1023)
    // ------------------------------------------------------------------------
    uint16_t r_final, g_final, b_final;

    if (g_app.mode == MODE_COMPOSITE) {
        // Use custom scale_value helper to ensure 32-bit math
        // This fixes overflow issues when pot_value and channel_val are both high
        r_final = scale_value(g_app.channel_val[COLOR_RED], g_app.pot_value, MAX_ADC_VAL);
        g_final = scale_value(g_app.channel_val[COLOR_GREEN], g_app.pot_value, MAX_ADC_VAL);
        b_final = scale_value(g_app.channel_val[COLOR_BLUE], g_app.pot_value, MAX_ADC_VAL);
    } else {
        r_final = g_app.channel_val[COLOR_RED];
        g_final = g_app.channel_val[COLOR_GREEN];
        b_final = g_app.channel_val[COLOR_BLUE];
    }

    // ------------------------------------------------------------------------
    // 2. Hardware Update 
    // ------------------------------------------------------------------------
    RGB_SetRaw(r_final, g_final, b_final);

    // ------------------------------------------------------------------------
    // 3. OLED UI Update
    // ------------------------------------------------------------------------
    
    // --- Header ---
    if (g_app.mode != g_app.last_mode) {
        oledC_DrawRectangle(0, 0, 95, 10, OLEDC_COLOR_BLACK);
        const char* m = (g_app.mode == MODE_COMPOSITE) ? "ALL" : "INDIV";
        oledC_DrawString(2, 1, 1, 1, (uint8_t*)m, OLEDC_COLOR_WHITE);
        g_app.last_mode = g_app.mode;
        g_app.last_pot_val = 0xFFFF; 
    }

    if (g_app.pot_value != g_app.last_pot_val) {
        oledC_DrawRectangle(50, 0, 95, 10, OLEDC_COLOR_BLACK); 
        snprintf(text_buf, sizeof(text_buf), "POT:%4u", g_app.pot_value);
        oledC_DrawString(50, 1, 1, 1, (uint8_t*)text_buf, OLEDC_COLOR_WHITE);
        g_app.last_pot_val = g_app.pot_value;
    }

    // --- Dynamic Sliders ---
    uint16_t final_vals[3] = {r_final, g_final, b_final};
    uint8_t y_positions[3] = {UI_BAR_R_Y, UI_BAR_G_Y, UI_BAR_B_Y};
    uint16_t bar_colors[3] = {OLEDC_COLOR_RED, OLEDC_COLOR_GREEN, OLEDC_COLOR_BLUE};
    
    for(int i=0; i<3; i++) {
        // Safe Scaling for Bar Width using helper
        // Maps 0-1023 -> 0-75
        uint8_t width = (uint8_t)scale_value(final_vals[i], UI_BAR_WIDTH, MAX_ADC_VAL);
        
        if (width != g_app.last_bar_width[i]) {
            if (width > g_app.last_bar_width[i]) {
                oledC_DrawRectangle(
                    UI_BAR_X + g_app.last_bar_width[i], y_positions[i], 
                    UI_BAR_X + width, y_positions[i] + UI_BAR_HEIGHT, 
                    bar_colors[i]
                );
            } else {
                oledC_DrawRectangle(
                    UI_BAR_X + width, y_positions[i], 
                    UI_BAR_X + g_app.last_bar_width[i], y_positions[i] + UI_BAR_HEIGHT, 
                    OLEDC_COLOR_ALICEBLUE
                );
            }
            g_app.last_bar_width[i] = width;
        }
        
        if (g_app.mode == MODE_INDIVIDUAL) {
            uint16_t ind_color = (g_app.current_channel == i) ? OLEDC_COLOR_BLACK : OLEDC_COLOR_ALICEBLUE;
            oledC_DrawRectangle(0, y_positions[i]+2, 1, y_positions[i]+4, ind_color);
        }
    }

    // --- Color Preview ---
    // Accurate 5-6-5 conversion
    // Red/Blue: 1023 -> 31
    // Green:    1023 -> 63
    uint16_t preview_color = oledC_parseRGBToInt(
        scale_value(r_final, 31, MAX_ADC_VAL),
        scale_value(g_final, 63, MAX_ADC_VAL),
        scale_value(b_final, 31, MAX_ADC_VAL)
    );

    if (preview_color != g_app.last_preview_color) {
        uint8_t start_x = (96 - UI_PREVIEW_SZ) / 2;
        oledC_DrawRectangle(
            start_x, UI_PREVIEW_Y, 
            start_x + UI_PREVIEW_SZ, UI_PREVIEW_Y + UI_PREVIEW_SZ, 
            preview_color
        );
        
        
        g_app.last_preview_color = preview_color;
    }
}

// ============================================================================
// Main Loop
// ============================================================================

void app_loop(void) {
    if (!g_app.initialized) return;

    uint32_t now = millis();
    if ((now - g_app.last_mode_change) > 200 && S1_WasPressed()) {
        g_app.mode = (g_app.mode == MODE_COMPOSITE) ? MODE_INDIVIDUAL : MODE_COMPOSITE;
        g_app.last_mode_change = now;
        g_app.pot_unlocked = true;
        g_app.last_mode = (DisplayMode_t)-1; 
    }

    update_inputs();

    if (g_app.mode == MODE_COMPOSITE) {
        logic_composite();
    } else {
        logic_individual();
    }

    update_outputs_and_render();
    LED1_Set(g_app.mode == MODE_INDIVIDUAL);
}
