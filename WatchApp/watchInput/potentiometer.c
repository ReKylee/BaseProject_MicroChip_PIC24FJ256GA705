/*
 * Implementation of potentiometer input with jitter prevention
 */

#include "potentiometer.h"
#include "../../adcDriver/ADC.h"
#include <stdbool.h>



// ============================================================================
// PRIVATE DATA
// ============================================================================

static uint8_t s_last_menu_selection = 0;
static uint16_t s_last_raw_value = 0;
static bool s_first_read = true;

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void Pot_Init(void) {
     ADC_Config_t adc_config = ADC_GET_DEFAULT_CONFIG(8);
    if (ADC_Init(&adc_config) != ADC_OK) return;

    // Just reset our state
    s_first_read = true;
    s_last_menu_selection = 0;
    s_last_raw_value = 0;
}

uint16_t Pot_GetRaw(void) {
    uint16_t r;
    ADC_ReadRaw(&r);
    return r;
}

uint8_t Pot_GetMapped(uint8_t min, uint8_t max, uint8_t hysteresis) {
    uint16_t raw = Pot_GetRaw();

    // Calculate mapped value
    if (max <= min) {
        s_last_menu_selection = min;
        s_last_raw_value = raw;
        s_first_read = false;
        return min;
    }

    uint32_t range = (uint32_t)(max - min);
    uint32_t mapped = min + ((raw * range) / 1023);

    // Apply hysteresis to prevent jitter
    if (!s_first_read) {
        int16_t diff = (int16_t) raw - (int16_t) s_last_raw_value;
        if (diff < 0) diff = -diff;

        // If change is less than hysteresis, use last value
        if (diff < hysteresis) {
            return s_last_menu_selection; // Use cached value
        }
    }

    s_first_read = false;
    s_last_raw_value = raw;
    s_last_menu_selection = (uint8_t)mapped;

    return (uint8_t) mapped;
}

uint8_t Pot_GetMenuSelection(uint8_t num_items) {
    if (num_items == 0) {
        return 0;
    }

    uint16_t raw = Pot_GetRaw();

    // Divide ADC range into segments for each menu item
    // Add dead zones at boundaries to prevent flickering
    uint16_t segment_size = 1024 / num_items;
    uint8_t selection = raw / segment_size;

    // Clamp to valid range
    if (selection >= num_items) {
        selection = num_items - 1;
    }

    // Apply hysteresis
    if (!s_first_read) {
        int16_t diff = (int16_t) raw - (int16_t) s_last_raw_value;
        if (diff < 0) diff = -diff;

        // Only update if change is significant
        if (diff < POT_MENU_HYSTERESIS) {
            return s_last_menu_selection;
        }
    }

    s_first_read = false;
    s_last_raw_value = raw;
    s_last_menu_selection = selection;

    return selection;
}
