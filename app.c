#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "System/system.h"
#include "System/delay.h"
#include "systemExtensions/systemExtensions.h"
#include "oledDriver/oledC.h"
#include "oledDriver/oledC_colors.h"
#include "oledDriver/oledC_shapes.h"
#include "oledDriver/oledC_shapeHandler.h"
#include "adcDriver/ADC.h"
#include "switchDriver/Switch.h"
#include "ledDriver/LED.h"
#include "ledDriver/RGBLED_colors.h"

typedef enum {
    COMPOSITE = 0,
    COLOR = 1
} DisplayMode_t;

typedef enum {
    RED_IDX = 0,
    GREEN_IDX = 1,
    BLUE_IDX = 2,
    NUM_COLORS = 3
} ColorIndex_t;

typedef struct {
    bool is_initialized;
    DisplayMode_t display_mode;
    uint8_t current_color_idx;
    uint16_t color_intensity[NUM_COLORS];
    bool is_pot_unlocked;
} AppContext;

static const uint32_t COLOR_CYCLE[] = {
    RGBLED_COLOR_RED,
    RGBLED_COLOR_GREEN,
    RGBLED_COLOR_BLUE
};

AppContext* getAppContext() {
    static AppContext ctx = {
        .is_initialized = false,
        .display_mode = COMPOSITE,
        .current_color_idx = RED_IDX,
        .color_intensity = {0, 0, 0},
        .is_pot_unlocked = true
    };
    return &ctx;
}

void app_setup() {
    AppContext* ctx = getAppContext();
    if (ctx->is_initialized) return;
    
    SYSTEM_Initialize();
    Timer_initialize();
    
    ADC_Config_t cfg = {
        .channel = 8,
        .res = ADC_RES_10BIT,
        .mode = ADC_OUTPUT_INT
    };
    ADC_Init(&cfg);
    
    S1_Init();
    S2_Init();
    LED1_Init();
    LED2_Init();
    RGB_Init();
    
    ctx->is_initialized = true;
}

// Helper: Save current color intensity if pot is unlocked
static inline void save_current_color_intensity(AppContext* ctx, uint16_t pot_value) {
    if (ctx->is_pot_unlocked) {
        ctx->color_intensity[ctx->current_color_idx] = pot_value;
    }
}

// Helper: Check and update pot unlock status
static inline void update_pot_lock_status(AppContext* ctx, uint16_t pot_value) {
    if (!ctx->is_pot_unlocked) {
        uint16_t stored = ctx->color_intensity[ctx->current_color_idx];
        if (pot_value == stored) {
            ctx->is_pot_unlocked = true;
        }
    }
}

// Helper: Get current display value (pot if unlocked, stored if locked)
static inline uint16_t get_display_value(AppContext* ctx, uint16_t pot_value) {
    return ctx->is_pot_unlocked ? pot_value : ctx->color_intensity[ctx->current_color_idx];
}

// Helper: Move to next color and lock pot
static inline void cycle_to_next_color(AppContext* ctx) {
    ctx->current_color_idx = (ctx->current_color_idx + 1) % NUM_COLORS;
    ctx->is_pot_unlocked = false;
}

void composite_display(AppContext* ctx) {
    float pot_relative = ADC_ReadFloat(); // [0..1]
    RGB_SetRaw(
        ctx->color_intensity[RED_IDX] * pot_relative,
        ctx->color_intensity[GREEN_IDX] * pot_relative,
        ctx->color_intensity[BLUE_IDX] * pot_relative
    );
}

void color_display(AppContext* ctx) {
    uint16_t pot = ADC_ReadRaw();
    
    // Handle S2 press: save current and switch to next color
    if (S2_WasPressed()) {
        save_current_color_intensity(ctx, pot);
        cycle_to_next_color(ctx);
    }
    
    // Check if pot should unlock
    update_pot_lock_status(ctx, pot);
    
    // Get display value and update if unlocked
    uint16_t display_value = get_display_value(ctx, pot);
    save_current_color_intensity(ctx, pot);
    
    // Display current color
    RGB_SetColor(COLOR_CYCLE[ctx->current_color_idx], display_value);
}

void app(void) {
    AppContext* ctx = getAppContext();
    
    LED1_Set(S1_ISDOWN());
    LED2_Set(S2_ISDOWN());
    
    // Handle mode switching with S1
    if (S1_WasPressed()) {
        if (ctx->display_mode == COLOR) {
            // Save current color before switching to composite
            save_current_color_intensity(ctx, ADC_ReadRaw());
        }
        ctx->display_mode = (ctx->display_mode == COMPOSITE) ? COLOR : COMPOSITE;
    }
    
    // Execute current mode
    if (ctx->display_mode == COMPOSITE) {
        composite_display(ctx);
    } else {
        color_display(ctx);
    }
}