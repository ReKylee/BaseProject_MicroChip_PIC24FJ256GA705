#include <stdlib.h>

#include "alarm_face.h"
#include "../shared/watch_state.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include "watch_face_common.h"

// ============================================================================
// CONFIGURATION
// ============================================================================

#define ALARM_ICON_R_OUTER 28
#define ALARM_ICON_R_INNER 24
#define ALARM_HAND_MIN_LEN 18
#define ALARM_HAND_HOUR_LEN 12

// ============================================================================
// STATE
// ============================================================================

static bool s_last_flash_state = false;
static bool s_drawn = false;

static void draw_alarm_icon(void) {
    // Clock ring
    oledC_DrawRing(CENTER_X, CENTER_Y, ALARM_ICON_R_OUTER, 2, COLOR_ACCENT);
    oledC_DrawRing(CENTER_X, CENTER_Y, ALARM_ICON_R_INNER, 1, COLOR_ACCENT);

    // 12/3/6/9 markers
    oledC_DrawLine(CENTER_X, CENTER_Y - ALARM_ICON_R_INNER, CENTER_X, CENTER_Y - (ALARM_ICON_R_INNER - 4), 2, COLOR_ACCENT);
    oledC_DrawLine(CENTER_X + ALARM_ICON_R_INNER, CENTER_Y, CENTER_X + (ALARM_ICON_R_INNER - 4), CENTER_Y, 2, COLOR_ACCENT);
    oledC_DrawLine(CENTER_X, CENTER_Y + ALARM_ICON_R_INNER, CENTER_X, CENTER_Y + (ALARM_ICON_R_INNER - 4), 2, COLOR_ACCENT);
    oledC_DrawLine(CENTER_X - ALARM_ICON_R_INNER, CENTER_Y, CENTER_X - (ALARM_ICON_R_INNER - 4), CENTER_Y, 2, COLOR_ACCENT);

    // Hands (10:10 style)
    oledC_DrawLine(CENTER_X, CENTER_Y, CENTER_X + ALARM_HAND_MIN_LEN, CENTER_Y - 6, 2, COLOR_ACCENT);
    oledC_DrawLine(CENTER_X, CENTER_Y, CENTER_X - 6, CENTER_Y - ALARM_HAND_HOUR_LEN, 3, COLOR_ACCENT);

    // Center dot
    oledC_DrawCircle(CENTER_X, CENTER_Y, 2, COLOR_ACCENT);
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

