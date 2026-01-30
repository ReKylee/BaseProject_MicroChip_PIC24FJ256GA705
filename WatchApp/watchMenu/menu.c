/*
 * menu.c
 * Implementation of menu system
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
// MENU DEFINITIONS
// ============================================================================

typedef struct {
    const char* text;
    MenuState_t next_state;
} MenuItem_t;

// Main menu items
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

// Display mode options
static const char* display_modes[] = {"Digital", "Analog", "Binary"};
#define DISPLAY_MODE_COUNT 3

// Time format options
static const char* time_formats[] = {"12 Hour", "24 Hour"};
#define TIME_FORMAT_COUNT 2

// ============================================================================
// PRIVATE DATA
// ============================================================================

static uint8_t current_selection = 0;
static uint8_t edit_field = 0;  // For multi-field editing (time, date)
static Time_t temp_time;
static Date_t temp_date;
static uint8_t temp_alarm_hour = 0;
static uint8_t temp_alarm_min = 0;

// ============================================================================
// PRIVATE FUNCTIONS
// ============================================================================

static void DrawSmallTime(void) {
    // Draw current time in top-right corner
    WatchState_t* state = Watch_GetState();
    char time_str[9];
    sprintf(time_str, "%02d:%02d:%02d", 
            state->current_time.hour,
            state->current_time.minute,
            state->current_time.second);
    oledC_DrawString(40, 2, 1, 1, (uint8_t*)time_str, COLOR_DIM);
}

static void DrawMenuItem(uint8_t y, const char* text, bool selected) {
    uint16_t color = selected ? COLOR_PRIMARY : COLOR_DIM;
    
    if (selected) {
        // Draw selection box
        oledC_DrawRectangle(2, y - 2, 93, y + 10, COLOR_PRIMARY);
        // Draw text in inverse
        oledC_DrawString(5, y, 1, 1, (uint8_t*)text, COLOR_BG);
    } else {
        oledC_DrawString(5, y, 1, 1, (uint8_t*)text, color);
    }
}

static void DrawMainMenu(void) {
    oledC_setBackground(COLOR_BG);
    
    // Title
    oledC_DrawString(30, 12, 1, 1, (uint8_t*)"MENU", COLOR_ACCENT);
    
    // Draw menu items (show 3 at a time)
    uint8_t start_idx = (current_selection > 0) ? (current_selection - 1) : 0;
    uint8_t y = 25;
    
    for (uint8_t i = 0; i < 3 && (start_idx + i) < MAIN_MENU_ITEMS; i++) {
        bool selected = (start_idx + i) == current_selection;
        DrawMenuItem(y, main_menu[start_idx + i].text, selected);
        y += 14;
    }
    
    DrawSmallTime();
}

static void DrawDisplayModeMenu(void) {
    WatchState_t* state = Watch_GetState();
    oledC_setBackground(COLOR_BG);
    
    oledC_DrawString(15, 12, 1, 1, (uint8_t*)"DISPLAY MODE", COLOR_ACCENT);
    
    uint8_t y = 30;
    for (uint8_t i = 0; i < DISPLAY_MODE_COUNT; i++) {
        bool selected = (i == state->watch_face);
        DrawMenuItem(y, display_modes[i], selected);
        y += 14;
    }
    
    oledC_DrawString(10, 75, 1, 1, (uint8_t*)"S1:Next S2:Select", COLOR_DIM);
    DrawSmallTime();
}

static void DrawTimeFormatMenu(void) {
    WatchState_t* state = Watch_GetState();
    oledC_setBackground(COLOR_BG);
    
    oledC_DrawString(15, 12, 1, 1, (uint8_t*)"TIME FORMAT", COLOR_ACCENT);
    
    uint8_t y = 35;
    for (uint8_t i = 0; i < TIME_FORMAT_COUNT; i++) {
        bool selected = (i == state->time_format);
        DrawMenuItem(y, time_formats[i], selected);
        y += 14;
    }
    
    oledC_DrawString(10, 75, 1, 1, (uint8_t*)"S1:Next S2:Select", COLOR_DIM);
    DrawSmallTime();
}

static void DrawTimeEdit(void) {
    oledC_setBackground(COLOR_BG);
    
    oledC_DrawString(25, 12, 1, 1, (uint8_t*)"SET TIME", COLOR_ACCENT);
    
    // Draw time with highlighting
    char time_str[9];
    sprintf(time_str, "%02d:%02d:%02d", temp_time.hour, temp_time.minute, temp_time.second);
    
    uint8_t x = 20;
    uint8_t y = 40;
    
    for (uint8_t i = 0; i < 8; i++) {
        bool highlight = false;
        
        // Determine if this character should be highlighted
        if (edit_field == 0 && (i == 0 || i == 1)) highlight = true;  // Hour
        if (edit_field == 1 && (i == 3 || i == 4)) highlight = true;  // Minute
        if (edit_field == 2 && (i == 6 || i == 7)) highlight = true;  // Second
        
        if (highlight) {
            oledC_DrawRectangle(x - 1, y - 1, x + 7, y + 9, COLOR_ACCENT);
            oledC_DrawCharacter(x, y, 1, 1, time_str[i], COLOR_BG);
        } else {
            oledC_DrawCharacter(x, y, 1, 1, time_str[i], COLOR_PRIMARY);
        }
        x += 8;
    }
    
    oledC_DrawString(5, 65, 1, 1, (uint8_t*)"S1:Field Pot:Value", COLOR_DIM);
    oledC_DrawString(15, 75, 1, 1, (uint8_t*)"S2:Confirm", COLOR_DIM);
    DrawSmallTime();
}

static void DrawDateEdit(void) {
    oledC_setBackground(COLOR_BG);
    
    oledC_DrawString(25, 12, 1, 1, (uint8_t*)"SET DATE", COLOR_ACCENT);
    
    // Draw date with highlighting
    char date_str[6];
    sprintf(date_str, "%02d/%02d", temp_date.day, temp_date.month);
    
    uint8_t x = 30;
    uint8_t y = 40;
    
    for (uint8_t i = 0; i < 5; i++) {
        bool highlight = false;
        
        if (edit_field == 0 && (i == 0 || i == 1)) highlight = true;  // Day
        if (edit_field == 1 && (i == 3 || i == 4)) highlight = true;  // Month
        
        if (highlight) {
            oledC_DrawRectangle(x - 1, y - 1, x + 7, y + 9, COLOR_ACCENT);
            oledC_DrawCharacter(x, y, 1, 1, date_str[i], COLOR_BG);
        } else {
            oledC_DrawCharacter(x, y, 1, 1, date_str[i], COLOR_PRIMARY);
        }
        x += 8;
    }
    
    oledC_DrawString(5, 65, 1, 1, (uint8_t*)"S1:Field Pot:Value", COLOR_DIM);
    oledC_DrawString(15, 75, 1, 1, (uint8_t*)"S2:Confirm", COLOR_DIM);
    DrawSmallTime();
}

static void DrawAlarmEdit(void) {
    oledC_setBackground(COLOR_BG);
    
    oledC_DrawString(23, 12, 1, 1, (uint8_t*)"SET ALARM", COLOR_ACCENT);
    
    // Draw alarm time
    char alarm_str[6];
    sprintf(alarm_str, "%02d:%02d", temp_alarm_hour, temp_alarm_min);
    
    uint8_t x = 30;
    uint8_t y = 40;
    
    for (uint8_t i = 0; i < 5; i++) {
        bool highlight = false;
        
        if (edit_field == 0 && (i == 0 || i == 1)) highlight = true;  // Hour
        if (edit_field == 1 && (i == 3 || i == 4)) highlight = true;  // Minute
        
        if (highlight) {
            oledC_DrawRectangle(x - 1, y - 1, x + 7, y + 9, COLOR_ACCENT);
            oledC_DrawCharacter(x, y, 1, 1, alarm_str[i], COLOR_BG);
        } else {
            oledC_DrawCharacter(x, y, 1, 1, alarm_str[i], COLOR_PRIMARY);
        }
        x += 8;
    }
    
    oledC_DrawString(5, 65, 1, 1, (uint8_t*)"S1:Field Pot:Value", COLOR_DIM);
    oledC_DrawString(15, 75, 1, 1, (uint8_t*)"S2:Confirm", COLOR_DIM);
    DrawSmallTime();
}

static void DrawAlarmToggle(void) {
    WatchState_t* state = Watch_GetState();
    oledC_setBackground(COLOR_BG);
    
    oledC_DrawString(20, 12, 1, 1, (uint8_t*)"ALARM STATUS", COLOR_ACCENT);
    
    uint8_t y = 35;
    DrawMenuItem(y, "Disabled", !state->alarm.enabled);
    y += 14;
    DrawMenuItem(y, "Enabled", state->alarm.enabled);
    
    oledC_DrawString(10, 75, 1, 1, (uint8_t*)"S1:Toggle S2:Back", COLOR_DIM);
    DrawSmallTime();
}

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void Menu_Init(void) {
    current_selection = 0;
    edit_field = 0;
}

void Menu_Enter(void) {
    WatchState_t* state = Watch_GetState();
    state->display_mode = MODE_MENU;
    state->menu_state = MENU_MAIN;
    current_selection = 0;
    edit_field = 0;
    state->needs_redraw = true;
}

void Menu_Exit(void) {
    WatchState_t* state = Watch_GetState();
    state->display_mode = MODE_WATCH;
    state->needs_redraw = true;
}

void Menu_HandleInput(ButtonEvent_t btn_event, uint16_t pot_value) {
    WatchState_t* state = Watch_GetState();
    
    switch (state->menu_state) {
        case MENU_MAIN:
            if (btn_event == BTN_S1_SHORT) {
                // Move to next item (cyclic)
                current_selection = (current_selection + 1) % MAIN_MENU_ITEMS;
                state->needs_redraw = true;
            } else if (btn_event == BTN_S2_SHORT) {
                // Select current item
                state->menu_state = main_menu[current_selection].next_state;
                edit_field = 0;
                
                // Initialize temporary values
                if (state->menu_state == MENU_SET_TIME) {
                    temp_time = state->current_time;
                } else if (state->menu_state == MENU_SET_DATE) {
                    temp_date = state->current_date;
                } else if (state->menu_state == MENU_SET_ALARM) {
                    temp_alarm_hour = state->alarm.hour;
                    temp_alarm_min = state->alarm.minute;
                }
                
                state->needs_redraw = true;
            }
            break;
            
        case MENU_DISPLAY_MODE:
            if (btn_event == BTN_S1_SHORT) {
                state->watch_face = (state->watch_face + 1) % FACE_COUNT;
                state->needs_redraw = true;
            } else if (btn_event == BTN_S2_SHORT) {
                state->menu_state = MENU_MAIN;
                state->needs_redraw = true;
            }
            break;
            
        case MENU_TIME_FORMAT:
            if (btn_event == BTN_S1_SHORT) {
                state->time_format = (state->time_format == FORMAT_12H) ? FORMAT_24H : FORMAT_12H;
                state->needs_redraw = true;
            } else if (btn_event == BTN_S2_SHORT) {
                state->menu_state = MENU_MAIN;
                state->needs_redraw = true;
            }
            break;
            
        case MENU_SET_TIME:
            if (btn_event == BTN_S1_SHORT) {
                // Move to next field
                edit_field = (edit_field + 1) % 3;  // Hour, Minute, Second
                state->needs_redraw = true;
            } else if (btn_event == BTN_S2_SHORT) {
                // Confirm and save
                Timekeeper_SetTime(&temp_time);
                state->menu_state = MENU_MAIN;
                state->needs_redraw = true;
            } else {
                // Use potentiometer to adjust value
                uint8_t max_val = (edit_field == 0) ? 23 : 59;
                uint8_t new_val = Pot_GetMapped(0, max_val, 30);
                
                if (edit_field == 0 && new_val != temp_time.hour) {
                    temp_time.hour = new_val;
                    state->needs_redraw = true;
                } else if (edit_field == 1 && new_val != temp_time.minute) {
                    temp_time.minute = new_val;
                    state->needs_redraw = true;
                } else if (edit_field == 2 && new_val != temp_time.second) {
                    temp_time.second = new_val;
                    state->needs_redraw = true;
                }
            }
            break;
            
        case MENU_SET_DATE:
            if (btn_event == BTN_S1_SHORT) {
                edit_field = (edit_field + 1) % 2;  // Day, Month
                state->needs_redraw = true;
            } else if (btn_event == BTN_S2_SHORT) {
                Timekeeper_SetDate(&temp_date);
                state->menu_state = MENU_MAIN;
                state->needs_redraw = true;
            } else {
                uint8_t new_val;
                if (edit_field == 0) {
                    // Day
                    uint8_t max_day = Timekeeper_GetDaysInMonth(temp_date.month);
                    new_val = Pot_GetMapped(1, max_day, 30);
                    if (new_val != temp_date.day) {
                        temp_date.day = new_val;
                        state->needs_redraw = true;
                    }
                } else {
                    // Month
                    new_val = Pot_GetMapped(1, 12, 30);
                    if (new_val != temp_date.month) {
                        temp_date.month = new_val;
                        // Adjust day if needed
                        uint8_t max_day = Timekeeper_GetDaysInMonth(temp_date.month);
                        if (temp_date.day > max_day) {
                            temp_date.day = max_day;
                        }
                        state->needs_redraw = true;
                    }
                }
            }
            break;
            
        case MENU_SET_ALARM:
            if (btn_event == BTN_S1_SHORT) {
                edit_field = (edit_field + 1) % 2;  // Hour, Minute
                state->needs_redraw = true;
            } else if (btn_event == BTN_S2_SHORT) {
                Alarm_SetTime(temp_alarm_hour, temp_alarm_min);
                Alarm_Enable();  // Auto-enable when setting alarm
                state->menu_state = MENU_MAIN;
                state->needs_redraw = true;
            } else {
                uint8_t max_val = (edit_field == 0) ? 23 : 59;
                uint8_t new_val = Pot_GetMapped(0, max_val, 30);
                
                if (edit_field == 0 && new_val != temp_alarm_hour) {
                    temp_alarm_hour = new_val;
                    state->needs_redraw = true;
                } else if (edit_field == 1 && new_val != temp_alarm_min) {
                    temp_alarm_min = new_val;
                    state->needs_redraw = true;
                }
            }
            break;
            
        case MENU_ALARM_TOGGLE:
            if (btn_event == BTN_S1_SHORT) {
                Alarm_Toggle();
                state->needs_redraw = true;
            } else if (btn_event == BTN_S2_SHORT) {
                state->menu_state = MENU_MAIN;
                state->needs_redraw = true;
            }
            break;
            
        case MENU_POMODORO:
            // Enter Pomodoro mode
            state->display_mode = MODE_POMODORO;
            state->needs_redraw = true;
            break;
            
        default:
            break;
    }
}

void Menu_Draw(void) {
    WatchState_t* state = Watch_GetState();
    
    switch (state->menu_state) {
        case MENU_MAIN:
            DrawMainMenu();
            break;
        case MENU_DISPLAY_MODE:
            DrawDisplayModeMenu();
            break;
        case MENU_TIME_FORMAT:
            DrawTimeFormatMenu();
            break;
        case MENU_SET_TIME:
            DrawTimeEdit();
            break;
        case MENU_SET_DATE:
            DrawDateEdit();
            break;
        case MENU_SET_ALARM:
            DrawAlarmEdit();
            break;
        case MENU_ALARM_TOGGLE:
            DrawAlarmToggle();
            break;
        default:
            break;
    }
}

void Menu_Update(void) {
    // Just update the small time display
    DrawSmallTime();
}
