/*
 * menu.h
 * Menu system for watch configuration
 */

#ifndef MENU_H
#define MENU_H

#include "../shared/watch_types.h"

// ============================================================================
// MENU FUNCTIONS
// ============================================================================

/**
 * @brief Initialize menu system
 */
void Menu_Init(void);

/**
 * @brief Handle menu input and navigation
 * @param btn_event Button event
 * @param pot_value Potentiometer value (0-1023)
 */
void Menu_HandleInput(ButtonEvent_t btn_event, uint16_t pot_value);

/**
 * @brief Draw current menu screen
 */
void Menu_Draw(void);

/**
 * @brief Update menu (called every second to update time display)
 */
void Menu_Update(void);

/**
 * @brief Enter menu mode
 */
void Menu_Enter(void);

/**
 * @brief Exit menu mode (return to watch display)
 */
void Menu_Exit(void);

#endif // MENU_H
