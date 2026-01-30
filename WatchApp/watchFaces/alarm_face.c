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
#define COLOR_ALARM_BG  COLOR_WARNING
#define COLOR_ALARM_FG  COLOR_ACCENT

// ============================================================================
// STATE
// ============================================================================

static bool last_flash_state = false;

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void AlarmFace_Init(void) {
    oledC_setBackground(COLOR_ALARM_BG);
    // Could draw a static icon or big circle to indicate alarm
    oledC_DrawCircle(CENTER_X, CENTER_Y, RADIUS, COLOR_ALARM_FG);
    last_flash_state = false;
}

void AlarmFace_Draw(void) {
    // Full redraw: solid background and icon
    oledC_setBackground(COLOR_ALARM_BG);
    oledC_DrawCircle(CENTER_X, CENTER_Y, RADIUS, COLOR_ALARM_FG);
}

void AlarmFace_DrawUpdate(void) {
    WatchState_t* state = Watch_GetState();

    // Flashing logic: toggle every second
    bool flash = (state->current_time.second % 2) == 0;

    if (flash != last_flash_state) {
        oledC_setBackground(flash ? COLOR_ALARM_BG : COLOR_BG);
        oledC_DrawCircle(CENTER_X, CENTER_Y, RADIUS, COLOR_ALARM_FG);
        last_flash_state = flash;
    }
}

