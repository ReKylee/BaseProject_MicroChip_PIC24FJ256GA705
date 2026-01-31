#include "menu.h"
#include "menu_icons.h"
#include "../watchFaces/watch_face_geometry.h"
#include "../shared/watch_state.h"
#include "../watchCore/timekeeper.h"
#include "../watchCore/alarm.h"
#include "../watchInput/potentiometer.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include <stdio.h>
#include <string.h>

// ============================================================================
// MENU ITEMS
// ============================================================================

const MenuItem_t main_menu[] = {
    {"Display Mode", MENU_DISPLAY_MODE},
    {"Time Format", MENU_TIME_FORMAT},
    {"Set Time", MENU_SET_TIME},
    {"Set Date", MENU_SET_DATE},
    {"Set Alarm", MENU_SET_ALARM},
    {"Alarm On/Off", MENU_ALARM_TOGGLE},
    {"Pomodoro", MENU_POMODORO}
};

static const char* display_modes[] = {"Digital", "Analog", "Binary"};
static const char* time_formats[] = {"12 Hour", "24 Hour"};

// Temporary editing state
static Time_t temp_time;
static Date_t temp_date;
static Time_t last_small_time;

// ============================================================================
// RADIAL MENU CONFIGURATION
// ============================================================================

#define CENTER_X 47
#define CENTER_Y 47
#define ICON_SIZE 16
#define RING_RADIUS 10

static uint8_t radial_selection = 0;
static uint8_t last_radial_selection = 0xFF;

static inline uint8_t menu_idx_to_sec(uint8_t idx) {
    return idx * (60 / MAIN_MENU_ITEMS);
}

// ============================================================================
// PRIVATE DRAW FUNCTIONS
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

static void _draw_radial_main_menu_full(void) {
    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    oledC_DrawString(30, 15, 1, 1, (uint8_t*)"MENU", COLOR_ACCENT);

    for (uint8_t i = 0; i < MAIN_MENU_ITEMS; i++) {
        uint8_t pt_idx = menu_idx_to_sec(i);
        int x = SEC_POINTS[pt_idx][0], y = SEC_POINTS[pt_idx][1];
        oledC_DrawBitmap(x - ICON_SIZE/2, y - ICON_SIZE/2, COLOR_DIM, ICON_SIZE, ICON_SIZE, (uint32_t*)menu_icons[i], ICON_SIZE);
        if (i == radial_selection) oledC_DrawCircle(x, y, RING_RADIUS, COLOR_PRIMARY);
    }

    const char* name = main_menu[radial_selection].text;
    oledC_DrawRectangle(CENTER_X - 24, CENTER_Y - 6, CENTER_X + 24, CENTER_Y + 6, COLOR_BG);
    oledC_DrawString(CENTER_X - strlen(name)*3, CENTER_Y - 3, 1, 1, (uint8_t*)name, COLOR_PRIMARY);

    last_radial_selection = radial_selection;
}

static void _draw_radial_main_menu_partial(void) {
    if (radial_selection != last_radial_selection) {
        if (last_radial_selection != 0xFF) {
            uint8_t pt_idx = menu_idx_to_sec(last_radial_selection);
            int x = SEC_POINTS[pt_idx][0], y = SEC_POINTS[pt_idx][1];
            oledC_DrawBitmap(x - ICON_SIZE/2, y - ICON_SIZE/2, COLOR_DIM, ICON_SIZE, ICON_SIZE, (uint32_t*)menu_icons[last_radial_selection], ICON_SIZE);
        }
        uint8_t pt_idx = menu_idx_to_sec(radial_selection);
        int x = SEC_POINTS[pt_idx][0], y = SEC_POINTS[pt_idx][1];
        oledC_DrawCircle(x, y, RING_RADIUS, COLOR_PRIMARY);
        const char* name = main_menu[radial_selection].text;
        oledC_DrawRectangle(CENTER_X - 24, CENTER_Y - 6, CENTER_X + 24, CENTER_Y + 6, COLOR_BG);
        oledC_DrawString(CENTER_X - strlen(name)*3, CENTER_Y - 3, 1, 1, (uint8_t*)name, COLOR_PRIMARY);
        last_radial_selection = radial_selection;
    }
}

// ---------------- LIST SCREENS ----------------

static void _draw_list_screen(const char* title, const char** options, uint8_t count, uint8_t selection) {
    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    oledC_DrawString(15, 15, 1, 1, (uint8_t*)title, COLOR_ACCENT);
    for (uint8_t i = 0; i < count; i++) {
        uint16_t rect_color = (i == selection) ? COLOR_PRIMARY : COLOR_BG;
        uint16_t text_color = (i == selection) ? COLOR_BG : COLOR_DIM;
        oledC_DrawRectangle(2, 28 + i*14, 93, 28 + i*14 + 12, rect_color);
        oledC_DrawString(15, 30 + i*14, 1, 1, (uint8_t*)options[i], text_color);
    }
}

static void _draw_list_screen_partial(const char** options, uint8_t count, uint8_t selection) {
    oledC_DrawRectangle(2, 28, 93, 28 + count*14, COLOR_BG);
    for (uint8_t i = 0; i < count; i++) {
        uint16_t rect_color = (i == selection) ? COLOR_PRIMARY : COLOR_BG;
        uint16_t text_color = (i == selection) ? COLOR_BG : COLOR_DIM;
        oledC_DrawRectangle(2, 28 + i*14, 93, 28 + i*14 + 12, rect_color);
        oledC_DrawString(15, 30 + i*14, 1, 1, (uint8_t*)options[i], text_color);
    }
}

// ---------------- TIME EDIT ----------------

static void _draw_time_edit_full(void) {
    WatchState_t* state = Watch_GetState();
    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    oledC_DrawString(25, 15, 1, 1, (uint8_t*)"SET TIME", COLOR_ACCENT);
    char time_str[9];
    sprintf(time_str, "%02d:%02d:%02d", temp_time.hour, temp_time.minute, temp_time.second);
    oledC_DrawString(20, 40, 2, 2, (uint8_t*)time_str, COLOR_PRIMARY);
    uint8_t field_x = 18 + state->menu_edit_field * 28;
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
    uint8_t field_x = 18 + state->menu_edit_field * 28;
    oledC_DrawRectangle(field_x, 38, field_x + 20, 56, COLOR_ACCENT);
    char field_str[3];
    switch(state->menu_edit_field) {
        case 0: sprintf(field_str, "%02d", temp_time.hour); break;
        case 1: sprintf(field_str, "%02d", temp_time.minute); break;
        case 2: sprintf(field_str, "%02d", temp_time.second); break;
    }
    oledC_DrawString(field_x + 1, 40, 2, 2, (uint8_t*)field_str, COLOR_BG);
}

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void Menu_Init(void) {
    memset(&last_small_time, 0, sizeof(Time_t));
    last_small_time.second = 99;
    last_radial_selection = 0xFF;
}

void Menu_Enter(void) {
    WatchState_t* state = Watch_GetState();
    state->display_mode = MODE_MENU;
    state->menu_state = MENU_MAIN;
    radial_selection = 0;
    last_radial_selection = 0xFF;
    state->needs_full_redraw = true;
}

void Menu_Exit(void) {
    WatchState_t* state = Watch_GetState();
    state->display_mode = MODE_WATCH;
    state->needs_full_redraw = true;
}

void Menu_HandleInput(ButtonEvent_t btn, uint16_t pot_value) {
    WatchState_t* state = Watch_GetState();
    bool changed = false;

    if (state->menu_state == MENU_MAIN) {
        radial_selection = Pot_GetMapped(0, MAIN_MENU_ITEMS - 1, 40);
        if (radial_selection != last_radial_selection) changed = true;

        if (btn == BTN_S2_SHORT) {
            state->menu_state = main_menu[radial_selection].next_state;
            if (state->menu_state == MENU_SET_TIME) temp_time = state->current_time;
            if (state->menu_state == MENU_SET_DATE) temp_date = state->current_date;
            changed = true;
        }
    }

    if (changed) state->needs_redraw = true;
}

void Menu_DrawFull(void) {
    _draw_small_time_update();
    WatchState_t* state = Watch_GetState();

    switch(state->menu_state) {
        case MENU_MAIN: _draw_radial_main_menu_full(); break;
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
        case MENU_MAIN: _draw_radial_main_menu_partial(); break;
        case MENU_DISPLAY_MODE: _draw_list_screen_partial(display_modes, DISPLAY_MODE_COUNT, state->watch_face); break;
        case MENU_TIME_FORMAT: _draw_list_screen_partial(time_formats, TIME_FORMAT_COUNT, state->time_format); break;
        case MENU_SET_TIME: _draw_time_edit_partial(); break;
        case MENU_ALARM_TOGGLE: _draw_list_screen_partial((const char*[]){"Off","On"}, 2, state->alarm.enabled); break;
        default: Menu_DrawFull(); break;
    }
}
