#ifndef MENU_H
#define MENU_H

#include "../shared/watch_types.h"

// Menu item structure
typedef struct {
    const char* text;
    MenuState_t next_state;
} MenuItem_t;

extern const MenuItem_t main_menu[];
#define MAIN_MENU_ITEMS (sizeof(main_menu) / sizeof(MenuItem_t))

// ============================================================================
// MENU FUNCTIONS
// ============================================================================

void Menu_Init(void);
void Menu_Enter(void);
void Menu_Exit(void);
void Menu_HandleInput(ButtonEvent_t btn_event, uint16_t pot_value);
void Menu_DrawFull(void);
void Menu_DrawPartial(void);

#endif // MENU_H
