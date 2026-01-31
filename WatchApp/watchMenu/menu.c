#include "menu.h"
#include "../shared/watch_state.h"
#include "../watchCore/timekeeper.h"
#include "../watchCore/alarm.h"
#include "../watchInput/potentiometer.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include <stdio.h>
#include <string.h>

// ============================================================================
// MENU DEFINITIONS & STATE
// ============================================================================

typedef struct {
    const char* text;
    MenuState_t next_state;
} MenuItem_t;

static const MenuItem_t main_menu[] = {
    {"Display Mode", MENU_DISPLAY_MODE},
    {"Time Format", MENU_TIME_FORMAT},
    {"Set Time", MENU_SET_TIME},
    {"Set Date", MENU_SET_DATE},
    {"Set Alarm", MENU_SET_ALARM},
    {"Alarm On/Off", MENU_ALARM_TOGGLE},
    {"Pomodoro", MENU_POMODORO}
};
#define MAIN_MENU_ITEMS (sizeof(main_menu) / sizeof(MenuItem_t))

static const char* display_modes[] = {"Digital", "Analog", "Binary"};
#define DISPLAY_MODE_COUNT 3
static const char* time_formats[] = {"12 Hour", "24 Hour"};
#define TIME_FORMAT_COUNT 2

// Temporary editing state
static Time_t temp_time;
static Date_t temp_date;
static Time_t last_small_time;

// Track previous menu state for partial redraws
static uint8_t last_menu_selection = 0xFF;
static uint8_t last_edit_field = 0xFF;
static uint8_t last_list_selection = 0xFF; // For generic list screens

// ============================================================================
// PRIVATE DRAWING HELPERS
// ============================================================================

static void _draw_small_time_update(void) {
    WatchState_t* state = Watch_GetState();
    if (state->current_time.second != last_small_time.second) {
        char old_str[9], new_str[9];
        sprintf(old_str, "%02d:%02d:%02d", last_small_time.hour, last_small_time.minute, last_small_time.second);
        oledC_DrawString(40, 2, 1, 1, (uint8_t*)old_str, COLOR_BG);
        sprintf(new_str, "%02d:%02d:%02d", state->current_time.hour, state->current_time.minute, state->current_time.second);
        oledC_DrawString(40, 2, 1, 1, (uint8_t*)new_str, COLOR_DIM);
        last_small_time = state->current_time;
    }
}

static void _draw_menu_item(uint8_t y, const char* text, bool selected) {
    uint16_t rect_color = selected ? COLOR_PRIMARY : COLOR_BG;
    uint16_t text_color = selected ? COLOR_BG : COLOR_DIM;
    oledC_DrawRectangle(2, y - 2, 93, y + 10, rect_color);
    oledC_DrawString(15, y, 1, 1, (uint8_t*)text, text_color);
}

// --------------------- MAIN MENU ---------------------
static void _draw_main_menu_full(void) {
    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    oledC_DrawString(30, 15, 1, 1, (uint8_t*)"MENU", COLOR_ACCENT);

    WatchState_t* state = Watch_GetState();
    last_menu_selection = 0xFF; // Force redraw
    uint8_t start_idx = 0;
    if (state->menu_selection >= 1) start_idx = state->menu_selection - 1;
    if (state->menu_selection > MAIN_MENU_ITEMS - 2) start_idx = MAIN_MENU_ITEMS - 3;

    for (uint8_t i = 0; i < 3 && (start_idx + i) < MAIN_MENU_ITEMS; i++) {
        uint8_t idx = start_idx + i;
        _draw_menu_item(30 + i * 14, main_menu[idx].text, idx == state->menu_selection);
    }
    last_menu_selection = state->menu_selection;
}

static void _draw_main_menu_partial(void) {
    WatchState_t* state = Watch_GetState();
    uint8_t start_idx = 0;
    if (state->menu_selection >= 1) start_idx = state->menu_selection - 1;
    if (state->menu_selection > MAIN_MENU_ITEMS - 2) start_idx = MAIN_MENU_ITEMS - 3;

    for (uint8_t i = 0; i < 3 && (start_idx + i) < MAIN_MENU_ITEMS; i++) {
        uint8_t idx = start_idx + i;
        bool selected = (idx == state->menu_selection);
        bool was_selected = (idx == last_menu_selection);
        if (selected != was_selected) {
            _draw_menu_item(30 + i * 14, main_menu[idx].text, selected);
        }
    }
    last_menu_selection = state->menu_selection;
}

// --------------------- LIST SCREENS ---------------------
static void _draw_list_screen(const char* title, const char** options, uint8_t count, uint8_t selection) {
    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    oledC_DrawString(15, 15, 1, 1, (uint8_t*)title, COLOR_ACCENT);

    for (uint8_t i = 0; i < count; i++) {
        _draw_menu_item(30 + i * 14, options[i], i == selection);
    }
}

// Partial redraw for generic list screens
static void _draw_list_screen_partial(const char** options, uint8_t count, uint8_t current_selection) {
    // Redraw only items that changed selection
    if (last_list_selection != current_selection) {
        // Unhighlight old selection
        if (last_list_selection != 0xFF && last_list_selection < count) {
            uint8_t y_old = 30 + last_list_selection * 14;
            _draw_menu_item(y_old, options[last_list_selection], false); // Unselect old
        }

        // Highlight new selection
        if (current_selection != 0xFF && current_selection < count) {
            uint8_t y_new = 30 + current_selection * 14;
            _draw_menu_item(y_new, options[current_selection], true); // Select new
        }
    }
    last_list_selection = current_selection;
}

// --------------------- TIME EDIT ---------------------
static void _draw_time_edit_full(void) {
    WatchState_t* state = Watch_GetState();
    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    oledC_DrawString(25, 15, 1, 1, (uint8_t*)"SET TIME", COLOR_ACCENT);

    char time_str[9];
    sprintf(time_str, "%02d:%02d:%02d", temp_time.hour, temp_time.minute, temp_time.second);
    oledC_DrawString(20, 40, 2, 2, (uint8_t*)time_str, COLOR_PRIMARY);

    last_edit_field = 0xFF; // Force redraw of highlight
    uint8_t field_x = 18 + (state->menu_edit_field * 28);
    oledC_DrawRectangle(field_x, 38, field_x + 20, 56, COLOR_ACCENT);

    char field_str[3];
    switch(state->menu_edit_field) {
        case 0: sprintf(field_str, "%02d", temp_time.hour); break;
        case 1: sprintf(field_str, "%02d", temp_time.minute); break;
        case 2: sprintf(field_str, "%02d", temp_time.second); break;
    }
    oledC_DrawString(field_x + 1, 40, 2, 2, (uint8_t*)field_str, COLOR_BG);
}

static void _draw_time_edit_partial(void) {
    WatchState_t* state = Watch_GetState();
    if (state->menu_edit_field == last_edit_field) return; // Nothing changed

    uint8_t field_x = 18 + (state->menu_edit_field * 28);
    oledC_DrawRectangle(field_x, 38, field_x + 20, 56, COLOR_ACCENT);

    char field_str[3];
    switch(state->menu_edit_field) {
        case 0: sprintf(field_str, "%02d", temp_time.hour); break;
        case 1: sprintf(field_str, "%02d", temp_time.minute); break;
        case 2: sprintf(field_str, "%02d", temp_time.second); break;
    }
    oledC_DrawString(field_x + 1, 40, 2, 2, (uint8_t*)field_str, COLOR_BG);

    last_edit_field = state->menu_edit_field;
}

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void Menu_Init(void) {
    memset(&last_small_time, 0, sizeof(Time_t));
    last_small_time.second = 99;
    last_menu_selection = 0xFF;
    last_edit_field = 0xFF;
    last_list_selection = 0xFF; // Initialize for generic lists
}

void Menu_Enter(void) {
    WatchState_t* state = Watch_GetState();
    state->display_mode = MODE_MENU;
    state->menu_state = MENU_MAIN;
    state->menu_selection = 0;
    state->menu_edit_field = 0;
    state->needs_full_redraw = true;
    last_menu_selection = 0xFF;
    last_edit_field = 0xFF;
    last_list_selection = 0xFF; // Initialize for generic lists
}

void Menu_Exit(void) {
    WatchState_t* state = Watch_GetState();
    state->display_mode = MODE_WATCH;
    state->needs_full_redraw = true;
}

void Menu_HandleInput(ButtonEvent_t btn, uint16_t pot_value) {
    WatchState_t* state = Watch_GetState();
    bool changed = false;

    switch(state->menu_state) {
        case MENU_MAIN:
            if (btn == BTN_S1_SHORT) { state->menu_selection = (state->menu_selection + 1) % MAIN_MENU_ITEMS; changed = true; }
            else if (btn == BTN_S2_SHORT) {
                state->menu_state = main_menu[state->menu_selection].next_state;
                if (state->menu_state == MENU_SET_TIME) temp_time = state->current_time;
                if (state->menu_state == MENU_SET_DATE) temp_date = state->current_date;
                state->menu_selection = 0; // Reset selection for new menu
                state->menu_edit_field = 0; // Reset edit field for new menu
                last_list_selection = 0xFF; // Reset for new list screen
                changed = true;
            }
            break;

        case MENU_DISPLAY_MODE:
            if (btn == BTN_S1_SHORT) { state->watch_face = (state->watch_face + 1) % FACE_COUNT_SELECTABLE; changed = true; }
            else if (btn == BTN_S2_SHORT) { state->menu_state = MENU_MAIN; last_list_selection = 0xFF; changed = true; } // Reset on exit
            break;

        case MENU_TIME_FORMAT:
            if (btn == BTN_S1_SHORT) { state->time_format = (state->time_format == FORMAT_12H) ? FORMAT_24H : FORMAT_12H; changed = true; }
            else if (btn == BTN_S2_SHORT) { state->menu_state = MENU_MAIN; last_list_selection = 0xFF; changed = true; } // Reset on exit
            break;

        case MENU_SET_TIME:
            if (btn == BTN_S1_SHORT) { state->menu_edit_field = (state->menu_edit_field + 1) % 3; changed = true; }
            else if (btn == BTN_S2_SHORT) { Timekeeper_SetTime(&temp_time); state->menu_state = MENU_MAIN; changed = true; }
            else { // Potentiometer adjustment
                uint8_t old_h = temp_time.hour, old_m = temp_time.minute, old_s = temp_time.second;
                if (state->menu_edit_field == 0) temp_time.hour = Pot_GetMapped(0, 23, 40);
                if (state->menu_edit_field == 1) temp_time.minute = Pot_GetMapped(0, 59, 40);
                if (state->menu_edit_field == 2) temp_time.second = Pot_GetMapped(0, 59, 40);
                if (old_h != temp_time.hour || old_m != temp_time.minute || old_s != temp_time.second)
                    changed = true;
            }
            break;

        case MENU_ALARM_TOGGLE:
            if (btn == BTN_S1_SHORT) { Alarm_Toggle(); changed = true; }
            else if (btn == BTN_S2_SHORT) { state->menu_state = MENU_MAIN; last_list_selection = 0xFF; changed = true; } // Reset on exit
            break;

        default:
            if (btn == BTN_S2_SHORT) { state->menu_state = MENU_MAIN; last_list_selection = 0xFF; changed = true; } // Reset on exit
            break;
    }

    if (changed) state->needs_redraw = true;
}

void Menu_DrawFull(void) {
    _draw_small_time_update();
    WatchState_t* state = Watch_GetState();

    switch(state->menu_state) {
        case MENU_MAIN: _draw_main_menu_full(); break;
        case MENU_DISPLAY_MODE: _draw_list_screen("Display Mode", display_modes, DISPLAY_MODE_COUNT, state->watch_face); break;
        case MENU_TIME_FORMAT: _draw_list_screen("Time Format", time_formats, TIME_FORMAT_COUNT, state->time_format); break;
        case MENU_SET_TIME: _draw_time_edit_full(); break;
        case MENU_ALARM_TOGGLE: _draw_list_screen("Alarm", (const char*[]){"Off","On"}, 2, state->alarm.enabled); break;
        default: oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG); oledC_DrawString(10, 40, 1, 1, (uint8_t*)"Coming Soon", COLOR_PRIMARY); break;
    }
}

void Menu_DrawPartial(void) {
    _draw_small_time_update();
    WatchState_t* state = Watch_GetState();

    switch(state->menu_state) {
        case MENU_MAIN: _draw_main_menu_partial(); break;
        case MENU_DISPLAY_MODE:
            _draw_list_screen_partial(display_modes, DISPLAY_MODE_COUNT, state->watch_face);
            break;

        case MENU_TIME_FORMAT:
            _draw_list_screen_partial(time_formats, TIME_FORMAT_COUNT, state->time_format);
            break;

        case MENU_SET_TIME:
            _draw_time_edit_partial(); // Only draw changed field
            break;

        case MENU_ALARM_TOGGLE:
            _draw_list_screen_partial((const char*[]){"Off","On"}, 2, state->alarm.enabled);
            break;

        default:
            Menu_DrawFull(); // Fallback for any unsupported partial draws
            break;
    }
}
