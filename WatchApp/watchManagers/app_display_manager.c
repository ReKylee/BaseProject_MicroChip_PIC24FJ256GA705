/*
 * Routes full/partial draw calls to the active UI module.
 */

#include "app_display_manager.h"
#include "../watchFaces/alarm_face.h" 
#include "../watchMenu/menu.h" 
#include "../shared/watch_state.h"
#include "../../oledDriver/oledC.h"
#include "../watchFaces/digital_face.h"
#include "../watchFaces/analog_face.h"
#include "../watchFaces/binary_face.h"
#include "../pomodoroTimer/pomodoro.h"
#include "../watchCore/alarm.h"
#include "../watchCore/timekeeper.h"
#ifdef DEBUG_MODE
#include "../watchDebug/debug_menu.h"
#endif

// -----------------------------------------------------------------------------
// PRIVATE HELPERS
// -----------------------------------------------------------------------------


static void app_draw_full(WatchState_t* state) {

    switch (state->display_mode) {
        case MODE_WATCH:
            switch (state->watch_face) {
                case FACE_DIGITAL: DigitalFace_Draw();
                    break;
                case FACE_ANALOG: AnalogFace_Draw();
                    break;
                case FACE_BINARY: BinaryFace_Draw();
                    break;
                case FACE_ALARM: AlarmFace_Draw();
                    break;
                default: break;
            }
            break;

        case MODE_MENU: Menu_DrawFull();
            break;
        case MODE_POMODORO: Pomodoro_Draw();
            break;
#ifdef DEBUG_MODE
        case MODE_DEBUG: DebugMenu_DrawFull();
            break;
#endif

        default: break;
    }
}

static void app_draw_partial(WatchState_t* state) {
    switch (state->display_mode) {
        case MODE_WATCH:
            switch (state->watch_face) {
                case FACE_DIGITAL: DigitalFace_DrawUpdate();
                    break;
                case FACE_ANALOG: AnalogFace_DrawUpdate();
                    break;
                case FACE_BINARY: BinaryFace_DrawUpdate();
                    break;
                case FACE_ALARM: AlarmFace_DrawUpdate();
                    break; 
                default: break;
            }
            break;

        case MODE_MENU:
            Menu_DrawPartial();
            break;
        case MODE_POMODORO:
            Pomodoro_DrawUpdate();
            break;
#ifdef DEBUG_MODE
        case MODE_DEBUG:
            DebugMenu_DrawUpdate();
            break;
#endif
        default:
            break;
    }
}

// -----------------------------------------------------------------------------
// PUBLIC API
// -----------------------------------------------------------------------------

void APP_UpdateDisplay(void) {
    WatchState_t* state = Watch_GetState();

    if (state->needs_full_redraw) {
        state->needs_full_redraw = false;
        state->needs_redraw = false;
        app_draw_full(state);
        return;
    }

    if (state->needs_redraw) {
        state->needs_redraw = false;
        app_draw_partial(state);
    }
}
