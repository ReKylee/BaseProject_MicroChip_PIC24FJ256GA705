#include "app_display_manager.h"

void APP_UpdateDisplay(void) {
    WatchState_t* state = Watch_GetState();

    // --- DRAWING LOGIC ---
    if (state->needs_full_redraw) {
        state->needs_full_redraw = false;
        state->needs_redraw = false;

        oledC_setBackground(COLOR_BG);

        switch (state->display_mode) {
            case MODE_WATCH:
                switch(state->watch_face) {
                    case FACE_DIGITAL: DigitalFace_Draw(); break;
                    case FACE_ANALOG: AnalogFace_Draw(); break;
                    case FACE_BINARY: BinaryFace_Draw(); break;
                    default: break;
                }
                break;
            case MODE_MENU: Menu_Draw(); break;
            case MODE_POMODORO: Pomodoro_Draw(); break;
            default: break;
        }
    } else if (state->needs_redraw) {
        state->needs_redraw = false;

        switch (state->display_mode) {
            case MODE_WATCH: {
                static bool last_alarm_ringing = false; // Tracks if alarm was ringing in the previous second
                static uint8_t last_alarm_second_flash_check = 99; // To control flashing rate

                bool current_alarm_ringing = Alarm_IsRinging();

                if (current_alarm_ringing) {
                    // If alarm just started ringing, or if the second has changed for flashing
                    if (!last_alarm_ringing || (state->current_time.second != last_alarm_second_flash_check)) {
                        // Toggle background every second
                        if ((state->current_time.second % 2) == 0) {
                            oledC_setBackground(COLOR_WARNING);
                        } else {
                            oledC_setBackground(COLOR_BG);
                        }
                        // Always redraw face after background change to ensure visibility
                        switch(state->watch_face) {
                            case FACE_DIGITAL: DigitalFace_Draw(); break;
                            case FACE_ANALOG: AnalogFace_Draw(); break;
                            case FACE_BINARY: BinaryFace_Draw(); break;
                            default: break;
                        }
                        last_alarm_second_flash_check = state->current_time.second;
                    }
                } else {
                    // Alarm is not ringing.
                    // If alarm just stopped ringing, ensure background is normal and force a full redraw.
                    if (last_alarm_ringing) {
                        oledC_setBackground(COLOR_BG);
                        state->needs_full_redraw = true; // Force full redraw to clean up any alarm remnants
                        // Don't break, let the needs_full_redraw block handle the drawing
                    }
                    // If not alarm and no full redraw needed, proceed with partial updates
                    // This block will only execute if state->needs_full_redraw was not set above
                    if (!state->needs_full_redraw) {
                        switch(state->watch_face) {
                            case FACE_DIGITAL: DigitalFace_DrawUpdate(); break;
                            case FACE_ANALOG: AnalogFace_DrawUpdate(); break;
                            case FACE_BINARY: BinaryFace_DrawUpdate(); break;
                            default: break;
                        }
                    }
                }
                last_alarm_ringing = current_alarm_ringing; // Update for next second
                break;
            }
            case MODE_MENU:
                Menu_Draw();
                break;
            case MODE_POMODORO:
                Pomodoro_Draw();
                break;
            default: break;
        }
    }
}