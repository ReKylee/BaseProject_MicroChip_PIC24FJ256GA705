#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "menu.h"
#include "menu_core.h"
#include "../shared/watch_state.h"
#include "../shared/watch_types.h"

// Menu content
extern const MenuItem_t main_menu[];
extern const char* const s_display_modes[];
extern const char* const s_time_formats[];
extern const uint32_t* const s_display_mode_icons[];
extern const uint32_t* const s_time_format_icons[];
extern const uint32_t* const s_alarm_toggle_icons[];

// Temporary editing state
extern Time_t s_temp_time;
extern Date_t s_temp_date;
extern Time_t s_temp_alarm;
extern uint8_t s_temp_pomo_work;
extern uint8_t s_temp_pomo_break;
extern Time_t s_last_small_time;

// Selection state
extern uint8_t s_radial_selection;
extern uint8_t s_last_radial_selection;
extern uint8_t s_display_last_selection;
extern uint8_t s_format_last_selection;
extern uint8_t s_alarm_last_selection;
extern uint8_t s_main_last_sel;
extern uint8_t s_display_last_sel;
extern uint8_t s_format_last_sel;
extern uint8_t s_alarm_last_sel;

// Pot state
extern uint16_t s_pot_filtered;
extern uint16_t s_pot_last_raw;
extern uint16_t s_main_last_raw;
extern uint16_t s_display_last_raw;
extern uint16_t s_format_last_raw;
extern uint16_t s_alarm_last_raw;
extern uint16_t s_edit_last_raw;
extern uint8_t s_edit_last_val;
extern uint8_t s_edit_last_field;
extern uint8_t s_edit_last_draw_val;
extern uint8_t s_edit_last_draw_field;

// Flags
extern bool s_skip_next_partial;
extern bool s_edit_full_drawn;

// Pot tuning
#define POT_DEADBAND 6
#define POT_FAST_THRESHOLD 80
#define POT_SMOOTH_NUM 1
#define POT_SMOOTH_DEN 2

typedef struct {
    const char* title;
    uint8_t radius;
    bool draw_inner_circle;
    const uint32_t* const* icons;
    const char* const* labels;
    const uint32_t* (*get_icon)(uint8_t idx);
    const char* (*get_label)(uint8_t idx);
    MenuRadial_t* radial;
} RadialMenuConfig_t;

typedef struct {
    const char* title;
    uint8_t count;
    uint8_t label_step;
    uint8_t label_offset;
    uint8_t selected;
} EditRingSpec_t;

typedef struct {
    uint8_t min0;
    uint8_t max0;
    uint8_t min1;
    uint8_t max1;
    uint8_t* val0;
    uint8_t* val1;
    void (*on_commit)(void);
} EditInputConfig_t;

// Radial menus
extern MenuRadial_t s_main_menu_radial;
extern MenuRadial_t s_display_menu_radial;
extern MenuRadial_t s_format_menu_radial;
extern MenuRadial_t s_alarm_toggle_radial;

extern const RadialMenuConfig_t s_main_menu_cfg;
extern const RadialMenuConfig_t s_display_menu_cfg;
extern const RadialMenuConfig_t s_format_menu_cfg;
extern const RadialMenuConfig_t s_alarm_toggle_cfg;

// State helpers
void MenuState_OnChange(MenuState_t new_state, bool seed_pot, uint16_t pot_value);
const uint32_t* MenuState_GetMainMenuIcon(uint8_t idx);
const char* MenuState_GetMainMenuLabel(uint8_t idx);
const char* MenuState_GetAlarmToggleLabel(uint8_t idx);

#endif // MENU_STATE_H
