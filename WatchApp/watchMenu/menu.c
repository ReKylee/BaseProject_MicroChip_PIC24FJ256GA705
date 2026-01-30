/*
 * menu.c
 * Implementation of menu system with partial (regional) redraws.
 */

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

// State for edit screens
static Time_t temp_time;
static Date_t temp_date;
static Time_t last_small_time;

// ============================================================================
// PRIVATE DRAWING FUNCTIONS
// ============================================================================

static void draw_small_time_update(void) {
    WatchState_t* state = Watch_GetState();
    if (state->current_time.second != last_small_time.second) {
        char time_str[9];
        sprintf(time_str, "%02d:%02d:%02d", last_small_time.hour, last_small_time.minute, last_small_time.second);
        oledC_DrawString(40, 2, 1, 1, (uint8_t*)time_str, COLOR_BG);
        sprintf(time_str, "%02d:%02d:%02d", state->current_time.hour, state->current_time.minute, state->current_time.second);
        oledC_DrawString(40, 2, 1, 1, (uint8_t*)time_str, COLOR_DIM);
        last_small_time = state->current_time;
    }
}

static void draw_menu_item(uint8_t y, const char* text, bool selected) {
    // This function draws a single item, assuming the background is already cleared.
    uint16_t rect_color = selected ? COLOR_PRIMARY : COLOR_BG;
    uint16_t text_color = selected ? COLOR_BG : COLOR_DIM;
    
    oledC_DrawRectangle(2, y - 2, 93, y + 10, rect_color);
    oledC_DrawString(15, y, 1, 1, (uint8_t*)text, text_color);
}

static void draw_main_menu_screen(void) {
    WatchState_t* state = Watch_GetState();
    
    // Clear only the menu's region, leaving the top time display intact
    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    
    oledC_DrawString(30, 15, 1, 1, (uint8_t*)"MENU", COLOR_ACCENT);

    // This menu uses a scrolling window of 3 items
    uint8_t start_idx = 0;
    if (state->menu_selection >= 1) {
        start_idx = state->menu_selection -1;
    }
    if (state->menu_selection > MAIN_MENU_ITEMS - 2) {
        start_idx = MAIN_MENU_ITEMS - 3;
    }
    
    uint8_t y = 30;
    for (uint8_t i = 0; i < 3 && (start_idx + i) < MAIN_MENU_ITEMS; i++) {
        bool selected = (start_idx + i) == state->menu_selection;
        draw_menu_item(y, main_menu[start_idx + i].text, selected);
        y += 14;
    }
}

static void draw_generic_list_screen(const char* title, const char** options, uint8_t count, uint8_t selection) {
    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    oledC_DrawString(15, 15, 1, 1, (uint8_t*)title, COLOR_ACCENT);
    
    uint8_t y = 30;
    for (uint8_t i = 0; i < count; i++) {
        draw_menu_item(y, options[i], i == selection);
        y += 14;
    }
}

static void draw_time_edit_screen(void) {
    WatchState_t* state = Watch_GetState();
    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    oledC_DrawString(25, 15, 1, 1, (uint8_t*)"SET TIME", COLOR_ACCENT);
    
    char time_str[9];
    sprintf(time_str, "%02d:%02d:%02d", temp_time.hour, temp_time.minute, temp_time.second);
    
    // Draw the full string first
    oledC_DrawString(20, 40, 2, 2, (uint8_t*)time_str, COLOR_PRIMARY);
    
    // Draw highlight box over the selected field
    uint8_t field_x = 18 + (state->menu_edit_field * 28);
    oledC_DrawRectangle(field_x, 38, field_x + 20, 56, COLOR_ACCENT);

    // Redraw the text for that field in the inverted color
    char field_str[3];
    if (state->menu_edit_field == 0) sprintf(field_str, "%02d", temp_time.hour);
    if (state->menu_edit_field == 1) sprintf(field_str, "%02d", temp_time.minute);
    if (state->menu_edit_field == 2) sprintf(field_str, "%02d", temp_time.second);
    oledC_DrawString(field_x+1, 40, 2, 2, (uint8_t*)field_str, COLOR_BG);
}


// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void Menu_Init(void) {
    memset(&last_small_time, 0, sizeof(Time_t));
    last_small_time.second = 99; // force draw
}

void Menu_Enter(void) {
    WatchState_t* state = Watch_GetState();
    state->display_mode = MODE_MENU;
    state->menu_state = MENU_MAIN;
    state->menu_selection = 0;
    state->needs_full_redraw = true; // A full redraw is necessary when entering
}

void Menu_Exit(void) {
    WatchState_t* state = Watch_GetState();
    state->display_mode = MODE_WATCH;
    state->needs_full_redraw = true;
}

void Menu_HandleInput(ButtonEvent_t btn, uint16_t pot_value) {
    WatchState_t* state = Watch_GetState();
    
    // On any input, we will need to redraw the menu
    if (btn != BTN_NONE) {
        state->needs_redraw = true;
    }

    switch (state->menu_state) {
        case MENU_MAIN:
            if (btn == BTN_S1_SHORT) {
                state->menu_selection = (state->menu_selection + 1) % MAIN_MENU_ITEMS;
            } else if (btn == BTN_S2_SHORT) {
                state->menu_state = main_menu[state->menu_selection].next_state;
                // Prepare for new screen
                if (state->menu_state == MENU_SET_TIME) temp_time = state->current_time;
                if (state->menu_state == MENU_SET_DATE) temp_date = state->current_date;
                state->menu_selection = 0;
                state->menu_edit_field = 0;
            }
            break;
            
        case MENU_DISPLAY_MODE:
            if (btn == BTN_S1_SHORT) state->watch_face = (state->watch_face + 1) % FACE_COUNT_SELECTABLE;
            else if (btn == BTN_S2_SHORT) state->menu_state = MENU_MAIN;
            break;
            
        case MENU_TIME_FORMAT:
            if (btn == BTN_S1_SHORT) state->time_format = (state->time_format == FORMAT_12H) ? FORMAT_24H : FORMAT_12H;
            else if (btn == BTN_S2_SHORT) state->menu_state = MENU_MAIN;
            break;

        case MENU_SET_TIME: {
            uint8_t old_h = temp_time.hour, old_m = temp_time.minute, old_s = temp_time.second;
            if (btn == BTN_S1_SHORT) {
                state->menu_edit_field = (state->menu_edit_field + 1) % 3;
            } else if (btn == BTN_S2_SHORT) {
                Timekeeper_SetTime(&temp_time);
                state->menu_state = MENU_MAIN;
            } else { // Potentiometer
                if (state->menu_edit_field == 0) temp_time.hour = Pot_GetMapped(0, 23, 40);
                if (state->menu_edit_field == 1) temp_time.minute = Pot_GetMapped(0, 59, 40);
                if (state->menu_edit_field == 2) temp_time.second = Pot_GetMapped(0, 59, 40);
            }
            if(old_h != temp_time.hour || old_m != temp_time.minute || old_s != temp_time.second) {
                state->needs_redraw = true;
            }
            break;
        }
        case MENU_ALARM_TOGGLE:
             if (btn == BTN_S1_SHORT) Alarm_Toggle();
             else if (btn == BTN_S2_SHORT) state->menu_state = MENU_MAIN;
             break;
        // Other states would be handled here...
        default:
             if (btn == BTN_S2_SHORT) state->menu_state = MENU_MAIN;
             break;
    }
}

void Menu_Draw(void) {
    draw_small_time_update();

    switch (Watch_GetState()->menu_state) {
        case MENU_MAIN:
            draw_main_menu_screen();
            break;
        case MENU_DISPLAY_MODE:
            draw_generic_list_screen("Display Mode", display_modes, DISPLAY_MODE_COUNT, Watch_GetState()->watch_face);
            break;
        case MENU_TIME_FORMAT:
            draw_generic_list_screen("Time Format", time_formats, TIME_FORMAT_COUNT, Watch_GetState()->time_format);
            break;
        case MENU_SET_TIME:
            draw_time_edit_screen();
            break;
        case MENU_ALARM_TOGGLE:
            draw_generic_list_screen("Alarm", (const char*[]){"Off", "On"}, 2, Watch_GetState()->alarm.enabled);
            break;
        // Other screens...
        default:
            // Draw a "Not Implemented" screen
            oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
            oledC_DrawString(10, 40, 1, 1, (uint8_t*)"Coming Soon", COLOR_PRIMARY);
            break;
    }
}
