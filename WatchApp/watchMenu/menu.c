#include "menu.h"
#include "menu_icons.h"
#include "menu_core.h"
#include "../watchFaces/watch_face_geometry.h"
#include "../watchFaces/watch_face_common.h"
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

static const char* s_display_modes[] = {"Digital", "Analog", "Binary"};
static const char* s_time_formats[] = {"12 Hour", "24 Hour"};
static const uint32_t* s_display_mode_icons[] = {s_icon_display_digital, s_icon_display_analog, s_icon_display_binary};
static const uint32_t* s_time_format_icons[] = {s_icon_time_12h, s_icon_time_24h};
static const uint32_t* s_alarm_toggle_icons[] = {s_icon_alarm_toggle, s_icon_set_alarm};

// Temporary editing state
static Time_t s_temp_time;
static Date_t s_temp_date;
static Time_t s_temp_alarm;
static Time_t s_last_small_time;

// ============================================================================
// RADIAL MENU CONFIGURATION
// ============================================================================

#define MENU_CENTER_X 47
#define MENU_CENTER_Y 52
#define MENU_RADIUS 32
#define MENU_INNER_RADIUS (MENU_RADIUS - (MENU_ICON_SIZE/2) - 2)
#define MENU_RING_RADIUS (MENU_ICON_SIZE/2 + 3)
#define SUBMENU_RADIUS 26
#define EDIT_RING_RADIUS 30
#define EDIT_TICK_RADIUS 2
#define MENU_BITMAP_W 32
#define MENU_ICON_ROWS 16
#define MENU_CENTER_LABEL_PAD 4
#define MENU_HEADER_Y 0
#define MENU_HEADER_H 10
#define MENU_TIME_X 2
#define MENU_TIME_Y 2
#define MENU_TITLE_X 58
#define MENU_TITLE_Y 2

static uint8_t s_radial_selection = 0;
static uint8_t s_last_radial_selection = 0xFF;
static uint8_t s_display_last_selection = 0xFF;
static uint8_t s_format_last_selection = 0xFF;
static uint8_t s_alarm_last_selection = 0xFF;
static uint8_t s_main_last_sel = 0;
static uint8_t s_display_last_sel = 0;
static uint8_t s_format_last_sel = 0;
static uint8_t s_alarm_last_sel = 0;
static uint16_t s_main_last_raw = 0xFFFF;
static uint16_t s_display_last_raw = 0xFFFF;
static uint16_t s_format_last_raw = 0xFFFF;
static uint16_t s_alarm_last_raw = 0xFFFF;
static uint16_t s_edit_last_raw = 0xFFFF;
static uint8_t s_edit_last_val = 0;
static uint8_t s_edit_last_field = 0xFF;
static MenuState_t s_last_menu_state = MENU_COUNT;

static inline uint8_t menu_idx_to_sec(uint8_t idx) {
    return (uint8_t)((idx * NUM_CLOCK_POINTS) / MAIN_MENU_ITEMS);
}

static inline uint8_t idx_to_sec(uint8_t idx, uint8_t count) {
    return (uint8_t)((idx * NUM_CLOCK_POINTS) / count);
}

static inline void radial_idx_to_xy(uint8_t idx, uint8_t count, uint8_t radius, int *x, int *y) {
    uint8_t sec = idx_to_sec(idx, count);
    int16_t dx = SEC_POINTS[sec][0] - CENTER_X;
    int16_t dy = SEC_POINTS[sec][1] - CENTER_Y;
    int16_t sx = (dx * radius) / RADIUS;
    int16_t sy = (dy * radius) / RADIUS;
    *x = MENU_CENTER_X + sx;
    *y = MENU_CENTER_Y + sy;
}

static inline void menu_idx_to_xy(uint8_t idx, int *x, int *y) {
    radial_idx_to_xy(idx, MAIN_MENU_ITEMS, MENU_RADIUS, x, y);
}

static void draw_center_label(const char *text) {
    char line1[12];
    char line2[12];
    size_t len = strlen(text);
    uint8_t max_chars = (uint8_t)((MENU_INNER_RADIUS * 2) / 6);
    if (max_chars > 11) max_chars = 11;

    line1[0] = '\0';
    line2[0] = '\0';

    if (len <= max_chars) {
        strncpy(line1, text, sizeof(line1) - 1);
        line1[sizeof(line1) - 1] = '\0';
    } else {
        size_t split = 0;
        for (size_t i = 0; i < len && i < max_chars; i++) {
            if (text[i] == ' ') split = i;
        }
        if (split == 0 || split >= max_chars) split = max_chars;
        strncpy(line1, text, split);
        line1[split] = '\0';
        while (text[split] == ' ') split++;
        strncpy(line2, text + split, sizeof(line2) - 1);
        line2[sizeof(line2) - 1] = '\0';
    }

    uint8_t line1_w = (uint8_t)(strlen(line1) * 6);
    uint8_t line2_w = (uint8_t)(strlen(line2) * 6);
    uint8_t box_w = (line1_w > line2_w ? line1_w : line2_w) + MENU_CENTER_LABEL_PAD * 2;
    uint8_t box_h = (line2[0] != '\0') ? 18 : 12;
    uint8_t x0 = MENU_CENTER_X - (box_w / 2);
    uint8_t y0 = MENU_CENTER_Y - (box_h / 2);
    uint8_t x1 = MENU_CENTER_X + (box_w / 2);
    uint8_t y1 = MENU_CENTER_Y + (box_h / 2);

    oledC_DrawRectangle(x0, y0, x1, y1, COLOR_BG);
    if (line2[0] == '\0') {
        oledC_DrawString(MENU_CENTER_X - (line1_w / 2), MENU_CENTER_Y - 3, 1, 1, (uint8_t*)line1, COLOR_PRIMARY);
    } else {
        oledC_DrawString(MENU_CENTER_X - (line1_w / 2), MENU_CENTER_Y - 7, 1, 1, (uint8_t*)line1, COLOR_PRIMARY);
        oledC_DrawString(MENU_CENTER_X - (line2_w / 2), MENU_CENTER_Y + 1, 1, 1, (uint8_t*)line2, COLOR_PRIMARY);
    }
}

static void draw_menu_header(const char* title) {
    oledC_DrawRectangle(0, MENU_HEADER_Y, 95, MENU_HEADER_Y + MENU_HEADER_H, COLOR_BG);
    oledC_DrawString(MENU_TITLE_X, MENU_TITLE_Y, 1, 1, (uint8_t*)title, COLOR_ACCENT);
}

// range mapping handled in menu_core

// ============================================================================
// PRIVATE DRAW FUNCTIONS
// ============================================================================

static void draw_small_time_update(void) {
    WatchState_t* state = Watch_GetState();
    if (state->current_time.second != s_last_small_time.second) {
        char old_str[9], new_str[9];
        sprintf(old_str, "%02d:%02d:%02d", s_last_small_time.hour, s_last_small_time.minute, s_last_small_time.second);
        oledC_DrawRectangle(0, MENU_HEADER_Y, 57, MENU_HEADER_Y + MENU_HEADER_H, COLOR_BG);
        oledC_DrawString(MENU_TIME_X, MENU_TIME_Y, 1, 1, (uint8_t*)old_str, COLOR_BG);
        sprintf(new_str, "%02d:%02d:%02d", state->current_time.hour, state->current_time.minute, state->current_time.second);
        oledC_DrawString(MENU_TIME_X, MENU_TIME_Y, 1, 1, (uint8_t*)new_str, COLOR_DIM);
        s_last_small_time = state->current_time;
    }
}

static const uint32_t* get_main_menu_icon(uint8_t idx, const WatchState_t* state) {
    if (idx == 1) {
        return (state->time_format == FORMAT_12H) ? s_icon_time_12h : s_icon_time_24h;
    }
    if (idx == 5) {
        return state->alarm.enabled ? s_icon_set_alarm : s_icon_alarm_toggle;
    }
    return s_menu_icons[idx];
}

static uint8_t get_main_selection(void) {
    return s_radial_selection;
}

static void set_main_selection(uint8_t idx) {
    s_radial_selection = idx;
}

static void draw_main_item(uint8_t idx, bool selected) {
    WatchState_t* state = Watch_GetState();
    int x, y;
    menu_idx_to_xy(idx, &x, &y);
    const uint32_t* icon = get_main_menu_icon(idx, state);
    if (selected) {
        oledC_DrawCircle(x, y, MENU_RING_RADIUS, COLOR_PRIMARY);
        oledC_DrawBitmap(x - (MENU_BITMAP_W/2), y - (MENU_ICON_SIZE/2), COLOR_BG, 1, 1, (uint32_t*)icon, MENU_ICON_ROWS);
    } else {
        oledC_DrawCircle(x, y, MENU_RING_RADIUS, COLOR_BG);
        oledC_DrawBitmap(x - (MENU_BITMAP_W/2), y - (MENU_ICON_SIZE/2), COLOR_DIM, 1, 1, (uint32_t*)icon, MENU_ICON_ROWS);
    }
}

static void draw_main_center(uint8_t idx) {
    draw_center_label(main_menu[idx].text);
}

static uint8_t get_display_selection(void) {
    return Watch_GetState()->watch_face;
}

static void set_display_selection(uint8_t idx) {
    Watch_GetState()->watch_face = idx;
}

static void draw_display_item(uint8_t idx, bool selected) {
    int x, y;
    radial_idx_to_xy(idx, DISPLAY_MODE_COUNT, SUBMENU_RADIUS, &x, &y);
    const uint32_t* icon = s_display_mode_icons[idx];
    if (selected) {
        oledC_DrawCircle(x, y, MENU_RING_RADIUS, COLOR_PRIMARY);
        oledC_DrawBitmap(x - (MENU_BITMAP_W/2), y - (MENU_ICON_SIZE/2), COLOR_BG, 1, 1, (uint32_t*)icon, MENU_ICON_ROWS);
    } else {
        oledC_DrawCircle(x, y, MENU_RING_RADIUS, COLOR_BG);
        oledC_DrawBitmap(x - (MENU_BITMAP_W/2), y - (MENU_ICON_SIZE/2), COLOR_DIM, 1, 1, (uint32_t*)icon, MENU_ICON_ROWS);
    }
}

static void draw_display_center(uint8_t idx) {
    draw_center_label(s_display_modes[idx]);
}

static uint8_t get_format_selection(void) {
    return Watch_GetState()->time_format;
}

static void set_format_selection(uint8_t idx) {
    Watch_GetState()->time_format = (TimeFormat_t)idx;
}

static void draw_format_item(uint8_t idx, bool selected) {
    int x, y;
    radial_idx_to_xy(idx, TIME_FORMAT_COUNT, SUBMENU_RADIUS, &x, &y);
    const uint32_t* icon = s_time_format_icons[idx];
    if (selected) {
        oledC_DrawCircle(x, y, MENU_RING_RADIUS, COLOR_PRIMARY);
        oledC_DrawBitmap(x - (MENU_BITMAP_W/2), y - (MENU_ICON_SIZE/2), COLOR_BG, 1, 1, (uint32_t*)icon, MENU_ICON_ROWS);
    } else {
        oledC_DrawCircle(x, y, MENU_RING_RADIUS, COLOR_BG);
        oledC_DrawBitmap(x - (MENU_BITMAP_W/2), y - (MENU_ICON_SIZE/2), COLOR_DIM, 1, 1, (uint32_t*)icon, MENU_ICON_ROWS);
    }
}

static void draw_format_center(uint8_t idx) {
    draw_center_label(s_time_formats[idx]);
}

static uint8_t get_alarm_toggle_selection(void) {
    return Watch_GetState()->alarm.enabled ? 1 : 0;
}

static void set_alarm_toggle_selection(uint8_t idx) {
    Watch_GetState()->alarm.enabled = (idx != 0);
}

static void draw_alarm_toggle_item(uint8_t idx, bool selected) {
    int x, y;
    radial_idx_to_xy(idx, 2, SUBMENU_RADIUS, &x, &y);
    const uint32_t* icon = s_alarm_toggle_icons[idx];
    if (selected) {
        oledC_DrawCircle(x, y, MENU_RING_RADIUS, COLOR_PRIMARY);
        oledC_DrawBitmap(x - (MENU_BITMAP_W/2), y - (MENU_ICON_SIZE/2), COLOR_BG, 1, 1, (uint32_t*)icon, MENU_ICON_ROWS);
    } else {
        oledC_DrawCircle(x, y, MENU_RING_RADIUS, COLOR_BG);
        oledC_DrawBitmap(x - (MENU_BITMAP_W/2), y - (MENU_ICON_SIZE/2), COLOR_DIM, 1, 1, (uint32_t*)icon, MENU_ICON_ROWS);
    }
}

static void draw_alarm_toggle_center(uint8_t idx) {
    draw_center_label(idx ? "ON" : "OFF");
}

static MenuRadial_t s_main_menu_radial = {
    .count = MAIN_MENU_ITEMS,
    .draw_item = draw_main_item,
    .draw_center = draw_main_center,
    .get_selection = get_main_selection,
    .set_selection = set_main_selection,
    .last_selection = &s_last_radial_selection,
    .last_sel = &s_main_last_sel,
    .last_raw = &s_main_last_raw,
};

static MenuRadial_t s_display_menu_radial = {
    .count = DISPLAY_MODE_COUNT,
    .draw_item = draw_display_item,
    .draw_center = draw_display_center,
    .get_selection = get_display_selection,
    .set_selection = set_display_selection,
    .last_selection = &s_display_last_selection,
    .last_sel = &s_display_last_sel,
    .last_raw = &s_display_last_raw,
};

static MenuRadial_t s_format_menu_radial = {
    .count = TIME_FORMAT_COUNT,
    .draw_item = draw_format_item,
    .draw_center = draw_format_center,
    .get_selection = get_format_selection,
    .set_selection = set_format_selection,
    .last_selection = &s_format_last_selection,
    .last_sel = &s_format_last_sel,
    .last_raw = &s_format_last_raw,
};

static MenuRadial_t s_alarm_toggle_radial = {
    .count = 2,
    .draw_item = draw_alarm_toggle_item,
    .draw_center = draw_alarm_toggle_center,
    .get_selection = get_alarm_toggle_selection,
    .set_selection = set_alarm_toggle_selection,
    .last_selection = &s_alarm_last_selection,
    .last_sel = &s_alarm_last_sel,
    .last_raw = &s_alarm_last_raw,
};

static void draw_radial_main_menu_full(void) {
    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    draw_menu_header("MENU");
    MenuCore_DrawRadialFull(&s_main_menu_radial);
}

static void draw_radial_main_menu_partial(void) {
    MenuCore_DrawRadialPartial(&s_main_menu_radial);
}

// ---------------- COMPACT RADIAL SUBMENUS ----------------

static void draw_compact_radial_full(const MenuRadial_t* menu, const char* title) {
    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    draw_menu_header(title);
    oledC_DrawCircle(MENU_CENTER_X, MENU_CENTER_Y, MENU_INNER_RADIUS, COLOR_BG);
    MenuCore_DrawRadialFull(menu);
}

// ---------------- TIME EDIT ----------------

static void draw_time_edit_full(void) {
    WatchState_t* state = Watch_GetState();
    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    draw_menu_header("SET TIME");

    uint8_t count = 60;
    uint8_t label_step = 5;
    if (state->menu_edit_field == 0) {
        count = 24;
        label_step = 2;
    }

    for (uint8_t i = 0; i < count; i++) {
        if ((i % label_step) != 0) continue;
        int x, y;
        radial_idx_to_xy(i, count, EDIT_RING_RADIUS, &x, &y);
        char label[3];
        uint8_t value = i;
        if (state->menu_edit_field == 0) {
            value = (uint8_t)(i);
        }
        sprintf(label, "%02d", value);
        oledC_DrawString(x - 6, y - 3, 1, 1, (uint8_t*)label, COLOR_DIM);
    }

    char time_str[9];
    sprintf(time_str, "%02d:%02d:%02d", s_temp_time.hour, s_temp_time.minute, s_temp_time.second);
    draw_center_label(time_str);

    uint8_t sel = 0;
    if (state->menu_edit_field == 0) sel = s_temp_time.hour;
    if (state->menu_edit_field == 1) sel = s_temp_time.minute;
    if (state->menu_edit_field == 2) sel = s_temp_time.second;
    int sx, sy;
    radial_idx_to_xy(sel, count, EDIT_RING_RADIUS, &sx, &sy);
    oledC_DrawCircle(sx, sy, EDIT_TICK_RADIUS, COLOR_PRIMARY);
}

static void draw_date_edit_full(void) {
    WatchState_t* state = Watch_GetState();
    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    draw_menu_header("SET DATE");

    uint8_t count = (state->menu_edit_field == 0) ? 31 : 12;
    uint8_t label_step = (state->menu_edit_field == 0) ? 5 : 1;

    for (uint8_t i = 1; i <= count; i++) {
        if (((i - 1) % label_step) != 0) continue;
        int x, y;
        radial_idx_to_xy((uint8_t)(i - 1), count, EDIT_RING_RADIUS, &x, &y);
        char label[3];
        sprintf(label, "%02d", i);
        oledC_DrawString(x - 6, y - 3, 1, 1, (uint8_t*)label, COLOR_DIM);
    }

    char date_str[6];
    sprintf(date_str, "%02d/%02d", s_temp_date.day, s_temp_date.month);
    draw_center_label(date_str);

    uint8_t sel = (state->menu_edit_field == 0) ? (uint8_t)(s_temp_date.day - 1) : (uint8_t)(s_temp_date.month - 1);
    int sx, sy;
    radial_idx_to_xy(sel, count, EDIT_RING_RADIUS, &sx, &sy);
    oledC_DrawCircle(sx, sy, EDIT_TICK_RADIUS, COLOR_PRIMARY);
}

static void draw_alarm_edit_full(void) {
    WatchState_t* state = Watch_GetState();
    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    draw_menu_header("SET ALARM");

    uint8_t count = (state->menu_edit_field == 0) ? 24 : 60;
    uint8_t label_step = (state->menu_edit_field == 0) ? 2 : 5;

    for (uint8_t i = 0; i < count; i++) {
        if ((i % label_step) != 0) continue;
        int x, y;
        radial_idx_to_xy(i, count, EDIT_RING_RADIUS, &x, &y);
        char label[3];
        sprintf(label, "%02d", i);
        oledC_DrawString(x - 6, y - 3, 1, 1, (uint8_t*)label, COLOR_DIM);
    }

    char alarm_str[6];
    sprintf(alarm_str, "%02d:%02d", s_temp_alarm.hour, s_temp_alarm.minute);
    draw_center_label(alarm_str);

    uint8_t sel = (state->menu_edit_field == 0) ? s_temp_alarm.hour : s_temp_alarm.minute;
    int sx, sy;
    radial_idx_to_xy(sel, count, EDIT_RING_RADIUS, &sx, &sy);
    oledC_DrawCircle(sx, sy, EDIT_TICK_RADIUS, COLOR_PRIMARY);
}

static void draw_compact_radial_partial(const MenuRadial_t* menu) {
    MenuCore_DrawRadialPartial(menu);
}

static void draw_edit_tick_partial(uint8_t old_val, uint8_t new_val, uint8_t count) {
    if (old_val == new_val) return;
    int x, y;
    radial_idx_to_xy(old_val, count, EDIT_RING_RADIUS, &x, &y);
    oledC_DrawCircle(x, y, EDIT_TICK_RADIUS, COLOR_BG);
    radial_idx_to_xy(new_val, count, EDIT_RING_RADIUS, &x, &y);
    oledC_DrawCircle(x, y, EDIT_TICK_RADIUS, COLOR_PRIMARY);
}

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void Menu_Init(void) {
    memset(&s_last_small_time, 0, sizeof(Time_t));
    s_last_small_time.second = 99;
    s_last_radial_selection = 0xFF;
    s_main_last_raw = 0xFFFF;
    s_edit_last_raw = 0xFFFF;
    s_edit_last_val = 0;
    s_edit_last_field = 0xFF;
    s_last_menu_state = MENU_COUNT;
    s_display_last_selection = 0xFF;
    s_format_last_selection = 0xFF;
    s_alarm_last_selection = 0xFF;
    s_main_last_sel = 0;
    s_display_last_sel = 0;
    s_format_last_sel = 0;
    s_alarm_last_sel = 0;
    s_display_last_raw = 0xFFFF;
    s_format_last_raw = 0xFFFF;
    s_alarm_last_raw = 0xFFFF;
}

void Menu_Enter(void) {
    WatchState_t* state = Watch_GetState();
    state->display_mode = MODE_MENU;
    state->menu_state = MENU_MAIN;
    s_radial_selection = 0;
    s_last_radial_selection = 0xFF;
    state->menu_edit_field = 0;
    s_main_last_raw = 0xFFFF;
    s_edit_last_raw = 0xFFFF;
    s_edit_last_val = 0;
    s_edit_last_field = 0xFF;
    s_last_menu_state = MENU_COUNT;
    s_display_last_selection = 0xFF;
    s_format_last_selection = 0xFF;
    s_alarm_last_selection = 0xFF;
    s_main_last_sel = 0;
    s_display_last_sel = 0;
    s_format_last_sel = 0;
    s_alarm_last_sel = 0;
    s_display_last_raw = 0xFFFF;
    s_format_last_raw = 0xFFFF;
    s_alarm_last_raw = 0xFFFF;
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

    if (state->menu_state != s_last_menu_state) {
        s_main_last_raw = 0xFFFF;
        s_edit_last_raw = 0xFFFF;
        s_edit_last_val = 0;
        s_edit_last_field = 0xFF;
        s_display_last_selection = 0xFF;
        s_format_last_selection = 0xFF;
        s_alarm_last_selection = 0xFF;
        s_main_last_sel = 0;
        s_display_last_sel = 0;
        s_format_last_sel = 0;
        s_alarm_last_sel = 0;
        s_display_last_raw = 0xFFFF;
        s_format_last_raw = 0xFFFF;
        s_alarm_last_raw = 0xFFFF;
        MenuCore_ResetState(&s_main_menu_radial);
        MenuCore_ResetState(&s_display_menu_radial);
        MenuCore_ResetState(&s_format_menu_radial);
        MenuCore_ResetState(&s_alarm_toggle_radial);
        s_last_menu_state = state->menu_state;
    }

    if (state->menu_state == MENU_MAIN) {
        if (MenuCore_HandlePot(&s_main_menu_radial, pot_value, 30)) {
            changed = true;
        }

        if (btn == BTN_S2_SHORT) {
            state->menu_state = main_menu[s_radial_selection].next_state;
            state->menu_edit_field = 0;
            if (state->menu_state == MENU_SET_TIME) s_temp_time = state->current_time;
            if (state->menu_state == MENU_SET_DATE) s_temp_date = state->current_date;
            if (state->menu_state == MENU_SET_ALARM) {
                s_temp_alarm.hour = state->alarm.hour;
                s_temp_alarm.minute = state->alarm.minute;
                s_temp_alarm.second = 0;
            }
            state->needs_full_redraw = true;
            changed = true;
        }
    } else if (state->menu_state == MENU_DISPLAY_MODE) {
        if (MenuCore_HandlePot(&s_display_menu_radial, pot_value, 25)) {
            changed = true;
        }
        if (btn == BTN_S1_SHORT || btn == BTN_S2_SHORT) {
            state->menu_state = MENU_MAIN;
            state->needs_full_redraw = true;
        }
    } else if (state->menu_state == MENU_TIME_FORMAT) {
        if (MenuCore_HandlePot(&s_format_menu_radial, pot_value, 25)) {
            changed = true;
        }
        if (btn == BTN_S1_SHORT || btn == BTN_S2_SHORT) {
            state->menu_state = MENU_MAIN;
            state->needs_full_redraw = true;
        }
    } else if (state->menu_state == MENU_ALARM_TOGGLE) {
        if (MenuCore_HandlePot(&s_alarm_toggle_radial, pot_value, 25)) {
            changed = true;
        }
        if (btn == BTN_S1_SHORT || btn == BTN_S2_SHORT) {
            state->menu_state = MENU_MAIN;
            state->needs_full_redraw = true;
        }
    } else if (state->menu_state == MENU_SET_TIME) {
        if (s_edit_last_field != state->menu_edit_field) {
            s_edit_last_raw = 0xFFFF;
            s_edit_last_field = state->menu_edit_field;
        }

        if (state->menu_edit_field == 0) {
            if (MenuCore_HandleRange(pot_value, 0, 23, 8, &s_edit_last_raw, &s_edit_last_val, &s_temp_time.hour)) {
                changed = true;
            }
        } else if (state->menu_edit_field == 1) {
            if (MenuCore_HandleRange(pot_value, 0, 59, 6, &s_edit_last_raw, &s_edit_last_val, &s_temp_time.minute)) {
                changed = true;
            }
        } else {
            if (MenuCore_HandleRange(pot_value, 0, 59, 6, &s_edit_last_raw, &s_edit_last_val, &s_temp_time.second)) {
                changed = true;
            }
        }

        if (btn == BTN_S1_SHORT) {
            state->menu_state = MENU_MAIN;
            state->needs_full_redraw = true;
        } else if (btn == BTN_S2_SHORT) {
            if (state->menu_edit_field < 2) {
                state->menu_edit_field++;
            } else {
                Timekeeper_SetTime(&s_temp_time);
                state->current_time = s_temp_time;
                state->menu_state = MENU_MAIN;
                state->needs_full_redraw = true;
            }
            changed = true;
        }
    } else if (state->menu_state == MENU_SET_DATE) {
        if (s_edit_last_field != state->menu_edit_field) {
            s_edit_last_raw = 0xFFFF;
            s_edit_last_field = state->menu_edit_field;
        }

        if (state->menu_edit_field == 0) {
            if (MenuCore_HandleRange(pot_value, 1, 31, 8, &s_edit_last_raw, &s_edit_last_val, &s_temp_date.day)) {
                changed = true;
            }
        } else {
            if (MenuCore_HandleRange(pot_value, 1, 12, 8, &s_edit_last_raw, &s_edit_last_val, &s_temp_date.month)) {
                changed = true;
            }
        }

        if (btn == BTN_S1_SHORT) {
            state->menu_state = MENU_MAIN;
            state->needs_full_redraw = true;
        } else if (btn == BTN_S2_SHORT) {
            if (state->menu_edit_field < 1) {
                state->menu_edit_field++;
            } else {
                Timekeeper_SetDate(&s_temp_date);
                state->current_date = s_temp_date;
                state->menu_state = MENU_MAIN;
                state->needs_full_redraw = true;
            }
            changed = true;
        }
    } else if (state->menu_state == MENU_SET_ALARM) {
        if (s_edit_last_field != state->menu_edit_field) {
            s_edit_last_raw = 0xFFFF;
            s_edit_last_field = state->menu_edit_field;
        }

        if (state->menu_edit_field == 0) {
            if (MenuCore_HandleRange(pot_value, 0, 23, 8, &s_edit_last_raw, &s_edit_last_val, &s_temp_alarm.hour)) {
                changed = true;
            }
        } else {
            if (MenuCore_HandleRange(pot_value, 0, 59, 6, &s_edit_last_raw, &s_edit_last_val, &s_temp_alarm.minute)) {
                changed = true;
            }
        }

        if (btn == BTN_S1_SHORT) {
            state->menu_state = MENU_MAIN;
            state->needs_full_redraw = true;
        } else if (btn == BTN_S2_SHORT) {
            if (state->menu_edit_field < 1) {
                state->menu_edit_field++;
            } else {
                state->alarm.hour = s_temp_alarm.hour;
                state->alarm.minute = s_temp_alarm.minute;
                state->menu_state = MENU_MAIN;
                state->needs_full_redraw = true;
            }
            changed = true;
        }
    }

    if (changed) state->needs_redraw = true;
}

void Menu_DrawFull(void) {
    draw_small_time_update();
    WatchState_t* state = Watch_GetState();

    switch(state->menu_state) {
        case MENU_MAIN: draw_radial_main_menu_full(); break;
        case MENU_DISPLAY_MODE: draw_compact_radial_full(&s_display_menu_radial, "DISPLAY"); break;
        case MENU_TIME_FORMAT: draw_compact_radial_full(&s_format_menu_radial, "FORMAT"); break;
        case MENU_SET_TIME: draw_time_edit_full(); break;
        case MENU_SET_DATE: draw_date_edit_full(); break;
        case MENU_SET_ALARM: draw_alarm_edit_full(); break;
        case MENU_ALARM_TOGGLE: draw_compact_radial_full(&s_alarm_toggle_radial, "ALARM"); break;
        default: oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG); oledC_DrawString(10, 40, 1, 1, (uint8_t*)"Coming Soon", COLOR_PRIMARY); break;
    }
}

void Menu_DrawPartial(void) {
    draw_small_time_update();
    WatchState_t* state = Watch_GetState();

    switch(state->menu_state) {
        case MENU_MAIN:
            draw_radial_main_menu_partial();
            break;
        case MENU_DISPLAY_MODE:
            draw_compact_radial_partial(&s_display_menu_radial);
            break;
        case MENU_TIME_FORMAT:
            draw_compact_radial_partial(&s_format_menu_radial);
            break;
        case MENU_ALARM_TOGGLE:
            draw_compact_radial_partial(&s_alarm_toggle_radial);
            break;
        case MENU_SET_TIME: {
            uint8_t count = (state->menu_edit_field == 0) ? 24 : 60;
            uint8_t new_val = (state->menu_edit_field == 0) ? s_temp_time.hour :
                              (state->menu_edit_field == 1) ? s_temp_time.minute : s_temp_time.second;
            draw_edit_tick_partial(s_edit_last_val, new_val, count);
            char time_str[9];
            sprintf(time_str, "%02d:%02d:%02d", s_temp_time.hour, s_temp_time.minute, s_temp_time.second);
            draw_center_label(time_str);
            s_edit_last_val = new_val;
            break;
        }
        case MENU_SET_DATE: {
            uint8_t count = (state->menu_edit_field == 0) ? 31 : 12;
            uint8_t new_val = (state->menu_edit_field == 0) ? (uint8_t)(s_temp_date.day - 1) : (uint8_t)(s_temp_date.month - 1);
            draw_edit_tick_partial(s_edit_last_val, new_val, count);
            char date_str[6];
            sprintf(date_str, "%02d/%02d", s_temp_date.day, s_temp_date.month);
            draw_center_label(date_str);
            s_edit_last_val = new_val;
            break;
        }
        case MENU_SET_ALARM: {
            uint8_t count = (state->menu_edit_field == 0) ? 24 : 60;
            uint8_t new_val = (state->menu_edit_field == 0) ? s_temp_alarm.hour : s_temp_alarm.minute;
            draw_edit_tick_partial(s_edit_last_val, new_val, count);
            char alarm_str[6];
            sprintf(alarm_str, "%02d:%02d", s_temp_alarm.hour, s_temp_alarm.minute);
            draw_center_label(alarm_str);
            s_edit_last_val = new_val;
            break;
        }
        default:
            Menu_DrawFull();
            break;
    }
}
