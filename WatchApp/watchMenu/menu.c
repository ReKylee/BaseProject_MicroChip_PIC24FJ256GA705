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

static const char* const s_display_modes[] = {"Digital", "Analog", "Binary"};
static const char* const s_time_formats[] = {"12 Hour", "24 Hour"};
static const uint32_t* const s_display_mode_icons[] = {s_icon_display_digital, s_icon_display_analog, s_icon_display_binary};
static const uint32_t* const s_time_format_icons[] = {s_icon_time_12h, s_icon_time_24h};
static const uint32_t* const s_alarm_toggle_icons[] = {s_icon_alarm_toggle, s_icon_set_alarm};

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
static uint16_t s_pot_filtered = 0xFFFF;
static uint16_t s_pot_last_raw = 0xFFFF;
static uint16_t s_main_last_raw = 0xFFFF;
static uint16_t s_display_last_raw = 0xFFFF;
static uint16_t s_format_last_raw = 0xFFFF;
static uint16_t s_alarm_last_raw = 0xFFFF;
static uint16_t s_edit_last_raw = 0xFFFF;
static uint8_t s_edit_last_val = 0;
static uint8_t s_edit_last_field = 0xFF;
static uint8_t s_edit_last_draw_val = 0xFF;
static uint8_t s_edit_last_draw_field = 0xFF;
static bool s_skip_next_partial = false;
static bool s_edit_full_drawn = false;

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

static const RadialMenuConfig_t* s_active_radial = NULL;

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
        char new_str[9];
        oledC_DrawRectangle(0, MENU_HEADER_Y, 57, MENU_HEADER_Y + MENU_HEADER_H, COLOR_BG);
        sprintf(new_str, "%02d:%02d:%02d", state->current_time.hour, state->current_time.minute, state->current_time.second);
        oledC_DrawString(MENU_TIME_X, MENU_TIME_Y, 1, 1, (uint8_t*)new_str, COLOR_DIM);
        s_last_small_time = state->current_time;
    }
}

static const uint32_t* get_main_menu_icon(uint8_t idx) {
    WatchState_t* state = Watch_GetState();
    if (idx == 1) {
        return (state->time_format == FORMAT_12H) ? s_icon_time_12h : s_icon_time_24h;
    }
    if (idx == 5) {
        return state->alarm.enabled ? s_icon_set_alarm : s_icon_alarm_toggle;
    }
    return s_menu_icons[idx];
}

static const char* get_main_menu_label(uint8_t idx) {
    return main_menu[idx].text;
}

static const char* get_alarm_toggle_label(uint8_t idx) {
    return idx ? "ON" : "OFF";
}

static uint8_t get_main_selection(void) {
    return s_radial_selection;
}

static void set_main_selection(uint8_t idx) {
    s_radial_selection = idx;
}

static uint8_t get_display_selection(void) {
    return Watch_GetState()->watch_face;
}

static void set_display_selection(uint8_t idx) {
    Watch_GetState()->watch_face = idx;
}

static uint8_t get_format_selection(void) {
    return Watch_GetState()->time_format;
}

static void set_format_selection(uint8_t idx) {
    Watch_GetState()->time_format = (TimeFormat_t)idx;
}

static uint8_t get_alarm_toggle_selection(void) {
    return Watch_GetState()->alarm.enabled ? 1 : 0;
}

static void set_alarm_toggle_selection(uint8_t idx) {
    Watch_GetState()->alarm.enabled = (idx != 0);
}

static void menu_on_state_change(MenuState_t new_state, bool seed_pot, uint16_t pot_value) {
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
    s_edit_full_drawn = false;

    if (new_state == MENU_SET_TIME || new_state == MENU_SET_DATE || new_state == MENU_SET_ALARM) {
        s_edit_last_field = state->menu_edit_field;
    }
}

static void draw_radial_item(uint8_t idx, bool selected);
static void draw_radial_center(uint8_t idx);
static void draw_edit_tick_partial(uint8_t old_val, uint8_t new_val, uint8_t count);

static MenuRadial_t s_main_menu_radial = {
    .count = MAIN_MENU_ITEMS,
    .draw_item = draw_radial_item,
    .draw_center = draw_radial_center,
    .get_selection = get_main_selection,
    .set_selection = set_main_selection,
    .last_selection = &s_last_radial_selection,
    .last_sel = &s_main_last_sel,
    .last_raw = &s_main_last_raw,
};

static MenuRadial_t s_display_menu_radial = {
    .count = DISPLAY_MODE_COUNT,
    .draw_item = draw_radial_item,
    .draw_center = draw_radial_center,
    .get_selection = get_display_selection,
    .set_selection = set_display_selection,
    .last_selection = &s_display_last_selection,
    .last_sel = &s_display_last_sel,
    .last_raw = &s_display_last_raw,
};

static MenuRadial_t s_format_menu_radial = {
    .count = TIME_FORMAT_COUNT,
    .draw_item = draw_radial_item,
    .draw_center = draw_radial_center,
    .get_selection = get_format_selection,
    .set_selection = set_format_selection,
    .last_selection = &s_format_last_selection,
    .last_sel = &s_format_last_sel,
    .last_raw = &s_format_last_raw,
};

static MenuRadial_t s_alarm_toggle_radial = {
    .count = 2,
    .draw_item = draw_radial_item,
    .draw_center = draw_radial_center,
    .get_selection = get_alarm_toggle_selection,
    .set_selection = set_alarm_toggle_selection,
    .last_selection = &s_alarm_last_selection,
    .last_sel = &s_alarm_last_sel,
    .last_raw = &s_alarm_last_raw,
};

static const RadialMenuConfig_t s_main_menu_cfg = {
    .title = "MENU",
    .radius = MENU_RADIUS,
    .draw_inner_circle = false,
    .icons = s_menu_icons,
    .labels = NULL,
    .get_icon = get_main_menu_icon,
    .get_label = get_main_menu_label,
    .radial = &s_main_menu_radial,
};

static const RadialMenuConfig_t s_display_menu_cfg = {
    .title = "DISPLAY",
    .radius = SUBMENU_RADIUS,
    .draw_inner_circle = true,
    .icons = s_display_mode_icons,
    .labels = s_display_modes,
    .get_icon = NULL,
    .get_label = NULL,
    .radial = &s_display_menu_radial,
};

static const RadialMenuConfig_t s_format_menu_cfg = {
    .title = "FORMAT",
    .radius = SUBMENU_RADIUS,
    .draw_inner_circle = true,
    .icons = s_time_format_icons,
    .labels = s_time_formats,
    .get_icon = NULL,
    .get_label = NULL,
    .radial = &s_format_menu_radial,
};

static const RadialMenuConfig_t s_alarm_toggle_cfg = {
    .title = "ALARM",
    .radius = SUBMENU_RADIUS,
    .draw_inner_circle = true,
    .icons = s_alarm_toggle_icons,
    .labels = NULL,
    .get_icon = NULL,
    .get_label = get_alarm_toggle_label,
    .radial = &s_alarm_toggle_radial,
};

static void draw_radial_item(uint8_t idx, bool selected) {
    if (!s_active_radial) return;
    int x, y;
    radial_idx_to_xy(idx, s_active_radial->radial->count, s_active_radial->radius, &x, &y);
    const uint32_t* icon = s_active_radial->get_icon ? s_active_radial->get_icon(idx) : s_active_radial->icons[idx];
    if (selected) {
        oledC_DrawCircle(x, y, MENU_RING_RADIUS, COLOR_PRIMARY);
        oledC_DrawBitmap(x - (MENU_BITMAP_W/2), y - (MENU_ICON_SIZE/2), COLOR_BG, 1, 1, (uint32_t*)icon, MENU_ICON_ROWS);
    } else {
        oledC_DrawCircle(x, y, MENU_RING_RADIUS, COLOR_BG);
        oledC_DrawBitmap(x - (MENU_BITMAP_W/2), y - (MENU_ICON_SIZE/2), COLOR_DIM, 1, 1, (uint32_t*)icon, MENU_ICON_ROWS);
    }
}

static void draw_radial_center(uint8_t idx) {
    if (!s_active_radial) return;
    const char* label = s_active_radial->get_label ? s_active_radial->get_label(idx) : s_active_radial->labels[idx];
    draw_center_label(label);
}

static void draw_radial_menu_full(const RadialMenuConfig_t* cfg) {
    s_active_radial = cfg;
    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    draw_menu_header(cfg->title);
    if (cfg->draw_inner_circle) {
        oledC_DrawCircle(MENU_CENTER_X, MENU_CENTER_Y, MENU_INNER_RADIUS, COLOR_BG);
    }
    MenuCore_DrawRadialFull(cfg->radial);
}

static void draw_radial_menu_partial(const RadialMenuConfig_t* cfg) {
    s_active_radial = cfg;
    MenuCore_DrawRadialPartial(cfg->radial);
}

// ---------------- TIME EDIT ----------------

static void fill_edit_spec(MenuState_t state, EditRingSpec_t* spec, char* center_text) {
    WatchState_t* w = Watch_GetState();
    uint8_t field = w->menu_edit_field;
    if (state == MENU_SET_TIME) {
        spec->title = "SET TIME";
        if (field == 0) {
            spec->count = 24;
            spec->label_step = 2;
            spec->label_offset = 0;
            spec->selected = s_temp_time.hour;
        } else {
            spec->count = 60;
            spec->label_step = 5;
            spec->label_offset = 0;
            spec->selected = s_temp_time.minute;
        }
        sprintf(center_text, "%02d:%02d", s_temp_time.hour, s_temp_time.minute);
    } else if (state == MENU_SET_DATE) {
        spec->title = "SET DATE";
        if (field == 0) {
            spec->count = 31;
            spec->label_step = 5;
            spec->label_offset = 1;
            spec->selected = (uint8_t)(s_temp_date.day - 1);
        } else {
            spec->count = 12;
            spec->label_step = 1;
            spec->label_offset = 1;
            spec->selected = (uint8_t)(s_temp_date.month - 1);
        }
        sprintf(center_text, "%02d/%02d", s_temp_date.day, s_temp_date.month);
    } else {
        spec->title = "SET ALARM";
        if (field == 0) {
            spec->count = 24;
            spec->label_step = 2;
            spec->label_offset = 0;
            spec->selected = s_temp_alarm.hour;
        } else {
            spec->count = 60;
            spec->label_step = 5;
            spec->label_offset = 0;
            spec->selected = s_temp_alarm.minute;
        }
        sprintf(center_text, "%02d:%02d", s_temp_alarm.hour, s_temp_alarm.minute);
    }
}

static void draw_edit_full(MenuState_t state) {
    EditRingSpec_t spec;
    char center_text[6];
    fill_edit_spec(state, &spec, center_text);

    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    draw_menu_header(spec.title);

    for (uint8_t i = 0; i < spec.count; i++) {
        if ((i % spec.label_step) != 0) continue;
        int x, y;
        radial_idx_to_xy(i, spec.count, EDIT_RING_RADIUS, &x, &y);
        char label[3];
        sprintf(label, "%02d", (uint8_t)(i + spec.label_offset));
        oledC_DrawString(x - 6, y - 3, 1, 1, (uint8_t*)label, COLOR_DIM);
    }

    draw_center_label(center_text);
    int sx, sy;
    radial_idx_to_xy(spec.selected, spec.count, EDIT_RING_RADIUS, &sx, &sy);
    oledC_DrawCircle(sx, sy, EDIT_TICK_RADIUS, COLOR_PRIMARY);
    s_edit_last_draw_val = spec.selected;
    s_edit_last_draw_field = Watch_GetState()->menu_edit_field;
    s_edit_full_drawn = true;
}

static void draw_edit_partial(MenuState_t state) {
    EditRingSpec_t spec;
    char center_text[6];
    fill_edit_spec(state, &spec, center_text);

    if (!s_edit_full_drawn || s_edit_last_draw_val == 0xFF) {
        return;
    }
    if (s_edit_last_draw_field != Watch_GetState()->menu_edit_field) {
        return;
    }

    draw_edit_tick_partial(s_edit_last_draw_val, spec.selected, spec.count);
    draw_center_label(center_text);
    s_edit_last_draw_val = spec.selected;
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
    menu_on_state_change(MENU_MAIN, false, 0);
    s_skip_next_partial = false;
}

void Menu_Enter(void) {
    WatchState_t* state = Watch_GetState();
    state->display_mode = MODE_MENU;
    s_radial_selection = 0;
    state->menu_edit_field = 0;
    menu_on_state_change(MENU_MAIN, false, 0);
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
    bool pot_changed = true;
    uint16_t pot_delta = 0;

    if (s_pot_last_raw == 0xFFFF) {
        s_pot_last_raw = pot_value;
    }
    pot_delta = (pot_value > s_pot_last_raw) ? (pot_value - s_pot_last_raw) : (s_pot_last_raw - pot_value);
    s_pot_last_raw = pot_value;
    if (pot_delta < POT_DEADBAND) {
        pot_changed = false;
    }

    if (s_pot_filtered == 0xFFFF) {
        s_pot_filtered = pot_value;
    } else {
        s_pot_filtered = (uint16_t)((s_pot_filtered * POT_SMOOTH_NUM + pot_value) / POT_SMOOTH_DEN);
    }

    if (state->menu_state == MENU_MAIN) {
        if (pot_changed) {
            if (MenuCore_HandlePot(&s_main_menu_radial, s_pot_filtered, 24)) changed = true;
            if (pot_delta > POT_FAST_THRESHOLD) {
                if (MenuCore_HandlePot(&s_main_menu_radial, s_pot_filtered, 24)) changed = true;
            }
        }

        if (btn == BTN_S2_SHORT) {
            MenuState_t next_state = main_menu[s_radial_selection].next_state;
            if (next_state == MENU_SET_TIME || next_state == MENU_SET_DATE || next_state == MENU_SET_ALARM) {
                state->menu_edit_field = 0;
            }
            menu_on_state_change(next_state, true, pot_value);
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
        if (pot_changed) {
            if (MenuCore_HandlePot(&s_display_menu_radial, s_pot_filtered, 20)) changed = true;
            if (pot_delta > POT_FAST_THRESHOLD) {
                if (MenuCore_HandlePot(&s_display_menu_radial, s_pot_filtered, 20)) changed = true;
            }
        }
        if (btn == BTN_S1_SHORT || btn == BTN_S2_SHORT) {
            menu_on_state_change(MENU_MAIN, true, pot_value);
            state->needs_full_redraw = true;
        }
    } else if (state->menu_state == MENU_TIME_FORMAT) {
        if (pot_changed) {
            if (MenuCore_HandlePot(&s_format_menu_radial, s_pot_filtered, 20)) changed = true;
            if (pot_delta > POT_FAST_THRESHOLD) {
                if (MenuCore_HandlePot(&s_format_menu_radial, s_pot_filtered, 20)) changed = true;
            }
        }
        if (btn == BTN_S1_SHORT || btn == BTN_S2_SHORT) {
            menu_on_state_change(MENU_MAIN, true, pot_value);
            state->needs_full_redraw = true;
        }
    } else if (state->menu_state == MENU_ALARM_TOGGLE) {
        if (pot_changed) {
            if (MenuCore_HandlePot(&s_alarm_toggle_radial, s_pot_filtered, 20)) changed = true;
            if (pot_delta > POT_FAST_THRESHOLD) {
                if (MenuCore_HandlePot(&s_alarm_toggle_radial, s_pot_filtered, 20)) changed = true;
            }
        }
        if (btn == BTN_S1_SHORT || btn == BTN_S2_SHORT) {
            menu_on_state_change(MENU_MAIN, true, pot_value);
            state->needs_full_redraw = true;
        }
    } else if (state->menu_state == MENU_SET_TIME) {
        if (s_edit_last_field != state->menu_edit_field) {
            s_edit_last_raw = s_pot_filtered;
            s_edit_last_field = state->menu_edit_field;
            s_edit_last_val = (state->menu_edit_field == 0) ? s_temp_time.hour : s_temp_time.minute;
            s_edit_last_draw_val = 0xFF;
            s_edit_last_draw_field = 0xFF;
            state->needs_full_redraw = true;
        }

        if (pot_changed) {
            uint16_t hys = (pot_delta > POT_FAST_THRESHOLD) ? 6 : 10;
            if (state->menu_edit_field == 0) {
                if (MenuCore_HandleRange(s_pot_filtered, 0, 23, hys, &s_edit_last_raw, &s_edit_last_val, &s_temp_time.hour)) {
                    changed = true;
                }
            } else {
                if (MenuCore_HandleRange(s_pot_filtered, 0, 59, (uint16_t)(hys - 2), &s_edit_last_raw, &s_edit_last_val, &s_temp_time.minute)) {
                    changed = true;
                }
            }
        }

        if (btn == BTN_S1_SHORT) {
            menu_on_state_change(MENU_MAIN, true, pot_value);
            state->needs_full_redraw = true;
        } else if (btn == BTN_S2_SHORT) {
            if (state->menu_edit_field < 1) {
                state->menu_edit_field++;
                state->needs_full_redraw = true;
            } else {
                s_temp_time.second = 0;
                Timekeeper_SetTime(&s_temp_time);
                state->current_time = s_temp_time;
                menu_on_state_change(MENU_MAIN, true, pot_value);
                state->needs_full_redraw = true;
            }
            changed = true;
        }
    } else if (state->menu_state == MENU_SET_DATE) {
        if (s_edit_last_field != state->menu_edit_field) {
            s_edit_last_raw = s_pot_filtered;
            s_edit_last_field = state->menu_edit_field;
            s_edit_last_val = (state->menu_edit_field == 0) ? s_temp_date.day : s_temp_date.month;
            s_edit_last_draw_val = 0xFF;
            s_edit_last_draw_field = 0xFF;
            state->needs_full_redraw = true;
        }

        if (pot_changed) {
            uint16_t hys = (pot_delta > POT_FAST_THRESHOLD) ? 6 : 10;
            if (state->menu_edit_field == 0) {
                if (MenuCore_HandleRange(s_pot_filtered, 1, 31, hys, &s_edit_last_raw, &s_edit_last_val, &s_temp_date.day)) {
                    changed = true;
                }
            } else {
                if (MenuCore_HandleRange(s_pot_filtered, 1, 12, hys, &s_edit_last_raw, &s_edit_last_val, &s_temp_date.month)) {
                    changed = true;
                }
            }
        }

        if (btn == BTN_S1_SHORT) {
            menu_on_state_change(MENU_MAIN, true, pot_value);
            state->needs_full_redraw = true;
        } else if (btn == BTN_S2_SHORT) {
            if (state->menu_edit_field < 1) {
                state->menu_edit_field++;
                state->needs_full_redraw = true;
            } else {
                Timekeeper_SetDate(&s_temp_date);
                state->current_date = s_temp_date;
                menu_on_state_change(MENU_MAIN, true, pot_value);
                state->needs_full_redraw = true;
            }
            changed = true;
        }
    } else if (state->menu_state == MENU_SET_ALARM) {
        if (s_edit_last_field != state->menu_edit_field) {
            s_edit_last_raw = s_pot_filtered;
            s_edit_last_field = state->menu_edit_field;
            s_edit_last_val = (state->menu_edit_field == 0) ? s_temp_alarm.hour : s_temp_alarm.minute;
            s_edit_last_draw_val = 0xFF;
            s_edit_last_draw_field = 0xFF;
            state->needs_full_redraw = true;
        }

        if (pot_changed) {
            uint16_t hys = (pot_delta > POT_FAST_THRESHOLD) ? 6 : 10;
            if (state->menu_edit_field == 0) {
                if (MenuCore_HandleRange(s_pot_filtered, 0, 23, hys, &s_edit_last_raw, &s_edit_last_val, &s_temp_alarm.hour)) {
                    changed = true;
                }
            } else {
                if (MenuCore_HandleRange(s_pot_filtered, 0, 59, (uint16_t)(hys - 2), &s_edit_last_raw, &s_edit_last_val, &s_temp_alarm.minute)) {
                    changed = true;
                }
            }
        }

        if (btn == BTN_S1_SHORT) {
            menu_on_state_change(MENU_MAIN, true, pot_value);
            state->needs_full_redraw = true;
        } else if (btn == BTN_S2_SHORT) {
            if (state->menu_edit_field < 1) {
                state->menu_edit_field++;
                state->needs_full_redraw = true;
            } else {
                state->alarm.hour = s_temp_alarm.hour;
                state->alarm.minute = s_temp_alarm.minute;
                menu_on_state_change(MENU_MAIN, true, pot_value);
                state->needs_full_redraw = true;
            }
            changed = true;
        }
    }

    if (changed && !state->needs_full_redraw) state->needs_redraw = true;
}

void Menu_DrawFull(void) {
    draw_small_time_update();
    WatchState_t* state = Watch_GetState();

    s_skip_next_partial = true;
    switch(state->menu_state) {
        case MENU_MAIN: draw_radial_menu_full(&s_main_menu_cfg); break;
        case MENU_DISPLAY_MODE: draw_radial_menu_full(&s_display_menu_cfg); break;
        case MENU_TIME_FORMAT: draw_radial_menu_full(&s_format_menu_cfg); break;
        case MENU_SET_TIME: draw_edit_full(MENU_SET_TIME); break;
        case MENU_SET_DATE: draw_edit_full(MENU_SET_DATE); break;
        case MENU_SET_ALARM: draw_edit_full(MENU_SET_ALARM); break;
        case MENU_ALARM_TOGGLE: draw_radial_menu_full(&s_alarm_toggle_cfg); break;
        default: oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG); oledC_DrawString(10, 40, 1, 1, (uint8_t*)"Coming Soon", COLOR_PRIMARY); break;
    }
}

void Menu_DrawPartial(void) {
    if (s_skip_next_partial) {
        s_skip_next_partial = false;
        return;
    }
    draw_small_time_update();
    WatchState_t* state = Watch_GetState();

    switch(state->menu_state) {
        case MENU_MAIN:
            draw_radial_menu_partial(&s_main_menu_cfg);
            break;
        case MENU_DISPLAY_MODE:
            draw_radial_menu_partial(&s_display_menu_cfg);
            break;
        case MENU_TIME_FORMAT:
            draw_radial_menu_partial(&s_format_menu_cfg);
            break;
        case MENU_ALARM_TOGGLE:
            draw_radial_menu_partial(&s_alarm_toggle_cfg);
            break;
        case MENU_SET_TIME: {
            draw_edit_partial(MENU_SET_TIME);
            break;
        }
        case MENU_SET_DATE: {
            draw_edit_partial(MENU_SET_DATE);
            break;
        }
        case MENU_SET_ALARM: {
            draw_edit_partial(MENU_SET_ALARM);
            break;
        }
        default:
            Menu_DrawFull();
            break;
    }
}
