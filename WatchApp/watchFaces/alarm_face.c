#include <stdlib.h>

#include "alarm_face.h"
#include "../shared/watch_state.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include "watch_face_common.h"

// ============================================================================
// CONFIGURATION
// ============================================================================

#define ALARM_CLOCK_R 28

// ============================================================================
// STATE
// ============================================================================

static bool s_last_flash_state = false;
static bool s_drawn = false;

static void draw_alarm_icon(void) {
    // Clock ring
    oledC_DrawRing(CENTER_X, CENTER_Y, ALARM_CLOCK_R, 2, COLOR_ACCENT);
    oledC_DrawRing(CENTER_X, CENTER_Y, (uint8_t)(ALARM_CLOCK_R - 3), 1, COLOR_WARNING);

    // Hands (10:10 style)
    oledC_DrawLine(CENTER_X, CENTER_Y, (uint8_t)(CENTER_X + 14), (uint8_t)(CENTER_Y - 4), 3, COLOR_ACCENT);
    oledC_DrawLine(CENTER_X, CENTER_Y, (uint8_t)(CENTER_X - 4), (uint8_t)(CENTER_Y - 14), 3, COLOR_ACCENT);

    // Center cap
    oledC_DrawCircle(CENTER_X, CENTER_Y, 3, COLOR_WARNING);
}

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void AlarmFace_Init(void) {
    oledC_setBackground(COLOR_WARNING);
    oledC_sendCommand(OLEDC_CMD_SET_DISPLAY_MODE_ON, NULL, 0);
    draw_alarm_icon();
    s_last_flash_state = false;
    s_drawn = true;
}

void AlarmFace_Draw(void) {
    // Full redraw: solid background and icon
    oledC_setBackground(COLOR_WARNING);
    oledC_sendCommand(OLEDC_CMD_SET_DISPLAY_MODE_ON, NULL, 0);
    draw_alarm_icon();
    s_last_flash_state = false;
    s_drawn = true;
}

void AlarmFace_DrawUpdate(void) {
    WatchState_t* state = Watch_GetState();

    if (!s_drawn) {
        AlarmFace_Draw();
        return;
    }

    // Flashing logic: toggle every second
    bool flash = (state->current_time.second % 2) == 0;

    if (flash != s_last_flash_state) {
        oledC_sendCommand(flash ? OLEDC_CMD_SET_DISPLAY_MODE_INVERSE
                                : OLEDC_CMD_SET_DISPLAY_MODE_ON,
                          NULL, 0);
        s_last_flash_state = flash;
    }
}

