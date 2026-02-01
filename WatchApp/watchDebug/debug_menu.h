#ifndef DEBUG_MENU_H
#define DEBUG_MENU_H

#include "../shared/watch_types.h"

// ============================================================================
// DEBUG MENU FUNCTIONS (only compiled when DEBUG_MODE is defined)
// ============================================================================

void DebugMenu_Enter(void);
void DebugMenu_Exit(void);
void DebugMenu_Toggle(void);
void DebugMenu_DrawFull(void);
void DebugMenu_DrawUpdate(void);
void DebugMenu_HandleInput(ButtonEvent_t btn);

#endif // DEBUG_MENU_H
