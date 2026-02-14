/*
 * Shared menu state model and helper APIs.
 */

#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "menu.h"
#include "menu_core.h"
#include "icon_asset.h"
#include "../shared/watch_state.h"
#include "../shared/watch_types.h"

// Menu content
extern const MenuItem_t main_menu[];
extern const char* const s_display_modes[];
extern const char* const s_time_formats[];
extern const IconAsset_t* const s_display_mode_icons[];
extern const IconAsset_t* const s_alarm_toggle_icons[];

typedef struct {
    // Temporary editing state
    Time_t temp_time;
    Date_t temp_date;
    Time_t temp_alarm;
    uint8_t temp_pomo_work;
    uint8_t temp_pomo_break;
    Time_t last_small_time;

    // Selection state
    uint8_t radial_selection;
    uint8_t last_radial_selection;
    uint8_t display_last_selection;
    uint8_t format_last_selection;
    uint8_t alarm_last_selection;
    uint8_t main_last_sel;
    uint8_t display_last_sel;
    uint8_t format_last_sel;
    uint8_t alarm_last_sel;

    // Pot state
    uint16_t pot_filtered;
    uint16_t pot_last_raw;
    uint16_t main_last_raw;
    uint16_t display_last_raw;
    uint16_t format_last_raw;
    uint16_t alarm_last_raw;
    uint16_t edit_last_raw;
    uint8_t edit_last_val;
    uint8_t edit_last_field;
    uint8_t edit_last_draw_val;
    uint8_t edit_last_draw_field;

    // Flags
    bool skip_next_partial;
    bool edit_full_drawn;
} MenuStateData_t;

extern MenuStateData_t g_menu_data;

#define s_temp_time (g_menu_data.temp_time)
#define s_temp_date (g_menu_data.temp_date)
#define s_temp_alarm (g_menu_data.temp_alarm)
#define s_temp_pomo_work (g_menu_data.temp_pomo_work)
#define s_temp_pomo_break (g_menu_data.temp_pomo_break)
#define s_last_small_time (g_menu_data.last_small_time)

#define s_radial_selection (g_menu_data.radial_selection)
#define s_last_radial_selection (g_menu_data.last_radial_selection)
#define s_display_last_selection (g_menu_data.display_last_selection)
#define s_format_last_selection (g_menu_data.format_last_selection)
#define s_alarm_last_selection (g_menu_data.alarm_last_selection)
#define s_main_last_sel (g_menu_data.main_last_sel)
#define s_display_last_sel (g_menu_data.display_last_sel)
#define s_format_last_sel (g_menu_data.format_last_sel)
#define s_alarm_last_sel (g_menu_data.alarm_last_sel)

#define s_pot_filtered (g_menu_data.pot_filtered)
#define s_pot_last_raw (g_menu_data.pot_last_raw)
#define s_main_last_raw (g_menu_data.main_last_raw)
#define s_display_last_raw (g_menu_data.display_last_raw)
#define s_format_last_raw (g_menu_data.format_last_raw)
#define s_alarm_last_raw (g_menu_data.alarm_last_raw)
#define s_edit_last_raw (g_menu_data.edit_last_raw)
#define s_edit_last_val (g_menu_data.edit_last_val)
#define s_edit_last_field (g_menu_data.edit_last_field)
#define s_edit_last_draw_val (g_menu_data.edit_last_draw_val)
#define s_edit_last_draw_field (g_menu_data.edit_last_draw_field)

#define s_skip_next_partial (g_menu_data.skip_next_partial)
#define s_edit_full_drawn (g_menu_data.edit_full_drawn)

typedef enum {
    MENU_EVT_NONE = 0,
    MENU_EVT_RADIAL_SELECT,
    MENU_EVT_EDIT_VALUE,
    MENU_EVT_EDIT_FIELD
} MenuEventType_t;

typedef struct {
    MenuEventType_t type;
    MenuState_t state;
} MenuEvent_t;

bool MenuEvent_Push(MenuEvent_t ev);
bool MenuEvent_Pop(MenuEvent_t* ev);
void MenuEvent_Clear(void);

// Pot tuning
#define POT_DEADBAND 6
#define POT_FAST_THRESHOLD 24
#define POT_SMOOTH_NUM 1
#define POT_SMOOTH_DEN 2

typedef struct {
    const char* title;
    uint8_t radius;
    bool draw_inner_circle;
    const IconAsset_t* const* icons;
    const char* const* labels;
    const IconAsset_t* (*get_icon)(uint8_t idx);
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
const IconAsset_t* MenuState_GetMainMenuIcon(uint8_t idx);
const char* MenuState_GetMainMenuLabel(uint8_t idx);
const char* MenuState_GetAlarmToggleLabel(uint8_t idx);
void MenuState_SetSkipNextPartial(bool skip);
bool MenuState_ConsumeSkipNextPartial(void);
void MenuState_SetEditFullDrawn(bool drawn);
bool MenuState_IsEditFullDrawn(void);
void MenuState_SeedEditBuffers(MenuState_t state);

#endif // MENU_STATE_H
