#include "app_display_manager.h"
#include "../watchFaces/alarm_face.h" // Added this include
#include "../watchMenu/menu.h" // Include menu header for new drawing functions

// -----------------------------------------------------------------------------
// PRIVATE HELPERS
// -----------------------------------------------------------------------------

// Draw the current display mode and watch face entirely
static void _APP_DrawFull(WatchState_t* state) {
    switch (state->display_mode) {
        case MODE_WATCH:
            switch (state->watch_face) {
                case FACE_DIGITAL: DigitalFace_Draw(); break;
                case FACE_ANALOG:  AnalogFace_Draw(); break;
                case FACE_BINARY:  BinaryFace_Draw(); break;
                case FACE_ALARM:   AlarmFace_Draw(); break; // Handle FACE_ALARM
                default: break;
            }
            break;

        case MODE_MENU:      Menu_DrawFull(); break; // Call Menu_DrawFull
        case MODE_POMODORO:  Pomodoro_Draw(); break;

        default: break;
    }
}

// Perform partial updates for the current watch face
static void _APP_DrawPartial(WatchState_t* state) {
    switch (state->display_mode) {
        case MODE_WATCH:
            switch (state->watch_face) {
                case FACE_DIGITAL: DigitalFace_DrawUpdate(); break;
                case FACE_ANALOG:  AnalogFace_DrawUpdate(); break;
                case FACE_BINARY:  BinaryFace_DrawUpdate(); break;
                case FACE_ALARM:   AlarmFace_DrawUpdate(); break; // Handle FACE_ALARM
                default: break;
            }
            break;

        case MODE_MENU:
            Menu_DrawPartial(); // Call Menu_DrawPartial
            break;
        case MODE_POMODORO:
            Pomodoro_Draw(); // Pomodoro has no partial update, so call full draw.
            break;
        default:
            break;
    }
}

// -----------------------------------------------------------------------------
// PUBLIC API
// -----------------------------------------------------------------------------

void APP_UpdateDisplay(void) {
    WatchState_t* state = Watch_GetState();

    // Full redraw has priority
    if (state->needs_full_redraw) {
        state->needs_full_redraw = false;
        state->needs_redraw = false;
        _APP_DrawFull(state);
        return;
    }

    // If a partial redraw is requested
    if (state->needs_redraw) {
        state->needs_redraw = false;
        _APP_DrawPartial(state); // Call partial draw directly
    }
}
