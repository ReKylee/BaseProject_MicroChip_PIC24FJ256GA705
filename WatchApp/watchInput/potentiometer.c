/*
 * Implementation of potentiometer input with jitter prevention
 */

#include "potentiometer.h"
#include "../shared/fast_math.h"
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

    s_first_read = true;
    s_last_menu_selection = 0;
    s_last_raw_value = 0;
}

uint16_t Pot_GetRaw(void) {
    uint16_t r = s_last_raw_value;
    if (ADC_ReadRaw(&r) != ADC_OK) {
        return s_last_raw_value;
    }
    if (r > 1023U) r = 1023U;
    s_last_raw_value = r;
    return r;
}

uint8_t Pot_GetMapped(uint8_t min, uint8_t max, uint8_t hysteresis) {
    uint16_t raw = Pot_GetRaw();

    if (max <= min) {
        s_last_menu_selection = min;
        s_last_raw_value = raw;
        s_first_read = false;
        return min;
    }

    uint32_t range = (uint32_t)(max - min);
    uint32_t mapped = (uint32_t)min + (((uint32_t)raw * range + 512UL) >> 10);
    if (mapped > (uint32_t)max) {
        mapped = (uint32_t)max;
    }

    if (!s_first_read) {
        if (FastMath_AbsDiffU16(raw, s_last_raw_value) < hysteresis) {
            return s_last_menu_selection;
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

    uint8_t selection = (uint8_t)(((uint32_t)raw * (uint32_t)num_items) >> 10);

    if (selection >= num_items) {
        selection = num_items - 1;
    }

    if (!s_first_read) {
        if (FastMath_AbsDiffU16(raw, s_last_raw_value) < POT_MENU_HYSTERESIS) {
            return s_last_menu_selection;
        }
    }

    s_first_read = false;
    s_last_raw_value = raw;
    s_last_menu_selection = selection;

    return selection;
}
