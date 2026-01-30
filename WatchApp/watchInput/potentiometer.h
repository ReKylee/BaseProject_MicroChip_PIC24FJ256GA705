/*
 * potentiometer.h
 * Potentiometer input with jitter prevention
 */

#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <stdint.h>

// ============================================================================
// POTENTIOMETER FUNCTIONS
// ============================================================================

/**
 * @brief Initialize potentiometer module
 */
void Pot_Init(void);

/**
 * @brief Get current potentiometer value (0-1023)
 * @return Raw ADC value
 */
uint16_t Pot_GetRaw(void);

/**
 * @brief Get potentiometer value mapped to range with hysteresis
 * @param min Minimum value of range
 * @param max Maximum value of range
 * @param hysteresis Hysteresis threshold (prevents jitter)
 * @return Mapped value in range [min, max]
 */
uint8_t Pot_GetMapped(uint8_t min, uint8_t max, uint8_t hysteresis);

/**
 * @brief Get menu selection from potentiometer
 * @param num_items Number of menu items
 * @return Selected item index (0 to num_items-1)
 */
uint8_t Pot_GetMenuSelection(uint8_t num_items);

#endif // POTENTIOMETER_H
