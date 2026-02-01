#include <stdlib.h>

#include "menu_state.h"
#include "menu_icons.h"
#include "../watchFaces/watch_face_common.h"
#include "../watchCore/timekeeper.h"
#include "../watchCore/alarm.h"

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

const char* const s_display_modes[] = {"Digital", "Analog", "Binary"};
const char* const s_time_formats[] = {"12 Hour", "24 Hour"};
const uint32_t* const s_display_mode_icons[] = {s_icon_display_digital, s_icon_display_analog, s_icon_display_binary};
const uint32_t* const s_time_format_icons[] = {s_icon_time_12h, s_icon_time_24h};
const uint32_t* const s_alarm_toggle_icons[] = {s_icon_alarm_toggle, s_icon_set_alarm};

// Temporary editing state
Time_t s_temp_time;
Date_t s_temp_date;
Time_t s_temp_alarm;
uint8_t s_temp_pomo_work;
uint8_t s_temp_pomo_break;
Time_t s_last_small_time;

// Selection state
uint8_t s_radial_selection = 0;
uint8_t s_last_radial_selection = 0xFF;
uint8_t s_display_last_selection = 0xFF;
uint8_t s_format_last_selection = 0xFF;
uint8_t s_alarm_last_selection = 0xFF;
uint8_t s_main_last_sel = 0;
uint8_t s_display_last_sel = 0;
uint8_t s_format_last_sel = 0;
uint8_t s_alarm_last_sel = 0;

// Pot state
uint16_t s_pot_filtered = 0xFFFF;
uint16_t s_pot_last_raw = 0xFFFF;
uint16_t s_main_last_raw = 0xFFFF;
uint16_t s_display_last_raw = 0xFFFF;
uint16_t s_format_last_raw = 0xFFFF;
uint16_t s_alarm_last_raw = 0xFFFF;
uint16_t s_edit_last_raw = 0xFFFF;
uint8_t s_edit_last_val = 0;
uint8_t s_edit_last_field = 0xFF;
uint8_t s_edit_last_draw_val = 0xFF;
uint8_t s_edit_last_draw_field = 0xFF;

// Flags
bool s_skip_next_partial = false;
bool s_edit_full_drawn = false;

// Menu event queue
#define MENU_EVENT_QUEUE_SIZE 8
static MenuEvent_t s_menu_events[MENU_EVENT_QUEUE_SIZE];
static uint8_t s_menu_evt_head = 0;
static uint8_t s_menu_evt_tail = 0;

static bool menu_evt_is_full(uint8_t next_head) {
    return next_head == s_menu_evt_tail;
}

bool MenuEvent_Push(MenuEvent_t ev) {
    uint8_t next_head = (uint8_t)((s_menu_evt_head + 1) % MENU_EVENT_QUEUE_SIZE);
    if (menu_evt_is_full(next_head)) {
        return false;
    }
    s_menu_events[s_menu_evt_head] = ev;
    s_menu_evt_head = next_head;
    return true;
}

bool MenuEvent_Pop(MenuEvent_t* ev) {
    if (s_menu_evt_head == s_menu_evt_tail) {
        return false;
    }
    *ev = s_menu_events[s_menu_evt_tail];
    s_menu_evt_tail = (uint8_t)((s_menu_evt_tail + 1) % MENU_EVENT_QUEUE_SIZE);
    return true;
}

void MenuEvent_Clear(void) {
    s_menu_evt_head = 0;
    s_menu_evt_tail = 0;
}

// Selection accessors for radial menus
static uint8_t get_main_selection(void) { return s_radial_selection; }
static void set_main_selection(uint8_t idx) { s_radial_selection = idx; }
static uint8_t get_display_selection(void) { return Watch_GetState()->watch_face; }
static void set_display_selection(uint8_t idx) { Watch_GetState()->watch_face = idx; }
static uint8_t get_format_selection(void) { return Watch_GetState()->time_format; }
static void set_format_selection(uint8_t idx) { Watch_GetState()->time_format = (TimeFormat_t)idx; }
static uint8_t get_alarm_toggle_selection(void) { return Watch_GetState()->alarm.enabled ? 1 : 0; }
static void set_alarm_toggle_selection(uint8_t idx) { Watch_GetState()->alarm.enabled = (idx != 0); }

const uint32_t* MenuState_GetMainMenuIcon(uint8_t idx) {
    WatchState_t* state = Watch_GetState();
    if (idx == 1) {
        return (state->time_format == FORMAT_12H) ? s_icon_time_12h : s_icon_time_24h;
    }
    if (idx == 5) {
        return state->alarm.enabled ? s_icon_set_alarm : s_icon_alarm_toggle;
    }
    return s_menu_icons[idx];
}

const char* MenuState_GetMainMenuLabel(uint8_t idx) {
    return main_menu[idx].text;
}

const char* MenuState_GetAlarmToggleLabel(uint8_t idx) {
    return idx ? "ON" : "OFF";
}

// Radial menu definitions
MenuRadial_t s_main_menu_radial = {
    .count = MAIN_MENU_ITEMS,
    .draw_item = NULL,
    .draw_center = NULL,
    .get_selection = get_main_selection,
    .set_selection = set_main_selection,
    .last_selection = &s_last_radial_selection,
    .last_sel = &s_main_last_sel,
    .last_raw = &s_main_last_raw,
};

MenuRadial_t s_display_menu_radial = {
    .count = DISPLAY_MODE_COUNT,
    .draw_item = NULL,
    .draw_center = NULL,
    .get_selection = get_display_selection,
    .set_selection = set_display_selection,
    .last_selection = &s_display_last_selection,
    .last_sel = &s_display_last_sel,
    .last_raw = &s_display_last_raw,
};

MenuRadial_t s_format_menu_radial = {
    .count = TIME_FORMAT_COUNT,
    .draw_item = NULL,
    .draw_center = NULL,
    .get_selection = get_format_selection,
    .set_selection = set_format_selection,
    .last_selection = &s_format_last_selection,
    .last_sel = &s_format_last_sel,
    .last_raw = &s_format_last_raw,
};

MenuRadial_t s_alarm_toggle_radial = {
    .count = 2,
    .draw_item = NULL,
    .draw_center = NULL,
    .get_selection = get_alarm_toggle_selection,
    .set_selection = set_alarm_toggle_selection,
    .last_selection = &s_alarm_last_selection,
    .last_sel = &s_alarm_last_sel,
    .last_raw = &s_alarm_last_raw,
};

const RadialMenuConfig_t s_main_menu_cfg = {
    .title = "MENU",
    .radius = 32,
    .draw_inner_circle = false,
    .icons = s_menu_icons,
    .labels = NULL,
    .get_icon = MenuState_GetMainMenuIcon,
    .get_label = MenuState_GetMainMenuLabel,
    .radial = &s_main_menu_radial,
};

const RadialMenuConfig_t s_display_menu_cfg = {
    .title = "DISPLAY",
    .radius = 26,
    .draw_inner_circle = true,
    .icons = s_display_mode_icons,
    .labels = s_display_modes,
    .get_icon = NULL,
    .get_label = NULL,
    .radial = &s_display_menu_radial,
};

const RadialMenuConfig_t s_format_menu_cfg = {
    .title = "FORMAT",
    .radius = 26,
    .draw_inner_circle = true,
    .icons = s_time_format_icons,
    .labels = s_time_formats,
    .get_icon = NULL,
    .get_label = NULL,
    .radial = &s_format_menu_radial,
};

const RadialMenuConfig_t s_alarm_toggle_cfg = {
    .title = "ALARM",
    .radius = 26,
    .draw_inner_circle = true,
    .icons = s_alarm_toggle_icons,
    .labels = NULL,
    .get_icon = NULL,
    .get_label = MenuState_GetAlarmToggleLabel,
    .radial = &s_alarm_toggle_radial,
};

void MenuState_OnChange(MenuState_t new_state, bool seed_pot, uint16_t pot_value) {
    WatchState_t* state = Watch_GetState();
    state->menu_state = new_state;

    s_main_last_raw = 0xFFFF;
    s_display_last_raw = 0xFFFF;
    s_format_last_raw = 0xFFFF;
    s_alarm_last_raw = 0xFFFF;
    s_edit_last_raw = 0xFFFF;
    s_edit_last_val = 0;
    s_edit_last_field = 0xFF;
    s_edit_last_draw_val = 0xFF;
    s_edit_last_draw_field = 0xFF;
    s_edit_full_drawn = false;

    s_last_radial_selection = s_radial_selection;
    s_display_last_selection = state->watch_face;
    s_format_last_selection = state->time_format;
    s_alarm_last_selection = state->alarm.enabled ? 1 : 0;

    s_main_last_sel = s_radial_selection;
    s_display_last_sel = state->watch_face;
    s_format_last_sel = state->time_format;
    s_alarm_last_sel = state->alarm.enabled ? 1 : 0;

    s_pot_filtered = seed_pot ? pot_value : 0xFFFF;
    s_pot_last_raw = seed_pot ? pot_value : 0xFFFF;
    s_skip_next_partial = true;

    MenuEvent_Clear();

    if (new_state == MENU_SET_TIME || new_state == MENU_SET_DATE ||
        new_state == MENU_SET_ALARM || new_state == MENU_POMODORO) {
        s_edit_last_field = state->menu_edit_field;
    }
}
