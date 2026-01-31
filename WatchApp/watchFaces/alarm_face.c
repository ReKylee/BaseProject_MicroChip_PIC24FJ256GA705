#include "alarm_face.h"
#include "../shared/watch_state.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"

// ============================================================================
// CONFIGURATION
// ============================================================================

#define CENTER_X  47
#define CENTER_Y  47
#define RADIUS    40

// Colors for flashing
// #define COLOR_ALARM_BG  COLOR_WARNING // No longer needed
// #define COLOR_ALARM_FG  COLOR_ACCENT // No longer needed

// ============================================================================
// STATE
// ============================================================================

static bool last_flash_state = false;

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void AlarmFace_Init(void) {
    oledC_setBackground(COLOR_WARNING);
    // Could draw a static icon or big circle to indicate alarm
    oledC_DrawCircle(CENTER_X, CENTER_Y, RADIUS, COLOR_ACCENT);
    last_flash_state = false;
}

void AlarmFace_Draw(void) {
    // Full redraw: solid background and icon
    oledC_setBackground(COLOR_WARNING);
    oledC_DrawCircle(CENTER_X, CENTER_Y, RADIUS, COLOR_ACCENT);
}

void AlarmFace_DrawUpdate(void) {
    WatchState_t* state = Watch_GetState();

    // Flashing logic: toggle every second
    bool flash = (state->current_time.second % 2) == 0;

    if (flash != last_flash_state) {
        oledC_setBackground(flash ? COLOR_WARNING : COLOR_BG);
        oledC_DrawCircle(CENTER_X, CENTER_Y, RADIUS, COLOR_ACCENT);
        last_flash_state = flash;
    }
}

