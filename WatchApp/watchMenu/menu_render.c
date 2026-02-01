#include "menu_state.h"
#include "menu_core.h"
#include "menu_layout.h"
#include "../watchFaces/watch_face_geometry.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include <stdio.h>
#include <string.h>

// ============================================================================
// RENDER CONSTANTS
// ============================================================================

static const RadialMenuConfig_t* s_active_radial = NULL;

static inline uint8_t idx_to_sec(uint8_t idx, uint8_t count) {
    return (uint8_t)((idx * NUM_CLOCK_POINTS) / count);
}

static inline void radial_idx_to_xy(uint8_t idx, uint8_t count, uint8_t radius, int *x, int *y) {
    uint8_t sec = idx_to_sec(idx, count);
    int16_t dx = SEC_POINTS[sec][0] - MENU_GEOM_CENTER_X;
    int16_t dy = SEC_POINTS[sec][1] - MENU_GEOM_CENTER_Y;
    int16_t sx = (dx * radius) / MENU_GEOM_RADIUS;
    int16_t sy = (dy * radius) / MENU_GEOM_RADIUS;
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
    cfg->radial->draw_item = draw_radial_item;
    cfg->radial->draw_center = draw_radial_center;
    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    draw_menu_header(cfg->title);
    if (cfg->draw_inner_circle) {
        oledC_DrawCircle(MENU_CENTER_X, MENU_CENTER_Y, MENU_INNER_RADIUS, COLOR_BG);
    }
    MenuCore_DrawRadialFull(cfg->radial);
}

static void draw_radial_menu_partial(const RadialMenuConfig_t* cfg) {
    s_active_radial = cfg;
    cfg->radial->draw_item = draw_radial_item;
    cfg->radial->draw_center = draw_radial_center;
    MenuCore_DrawRadialPartial(cfg->radial);
}

static void get_edit_ring_params(MenuState_t state, uint8_t field, uint8_t* count, uint8_t* step, uint8_t* offset) {
    if (state == MENU_SET_TIME || state == MENU_SET_ALARM) {
        if (field == 0) {
            *count = 24;
            *step = 2;
            *offset = 0;
        } else {
            *count = 60;
            *step = 5;
            *offset = 0;
        }
    } else if (state == MENU_SET_DATE) {
        if (field == 0) {
            *count = 31;
            *step = 5;
            *offset = 1;
        } else {
            *count = 12;
            *step = 1;
            *offset = 1;
        }
    } else {
        if (field == 0) {
            *count = 60;
            *step = 5;
            *offset = 1;
        } else {
            *count = 30;
            *step = 5;
            *offset = 1;
        }
    }
}

static bool edit_label_at_index(MenuState_t state, uint8_t field, uint8_t idx, uint8_t count, uint8_t step) {
    if ((idx % step) != 0) return false;
    if (state == MENU_SET_DATE && field == 0 && count == 31 && idx == 30) {
        return false; // avoid 31 overlapping 1
    }
    return true;
}

static void fill_edit_spec(MenuState_t state, EditRingSpec_t* spec, char* center_text) {
    WatchState_t* w = Watch_GetState();
    uint8_t field = w->menu_edit_field;
    if (state == MENU_SET_TIME) {
        spec->title = "TIME";
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
        spec->title = "DATE";
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
    } else if (state == MENU_POMODORO) {
        spec->title = "POMO";
        if (field == 0) {
            spec->count = 60;
            spec->label_step = 5;
            spec->label_offset = 1;
            spec->selected = (uint8_t)(s_temp_pomo_work - 1);
        } else {
            spec->count = 30;
            spec->label_step = 5;
            spec->label_offset = 1;
            spec->selected = (uint8_t)(s_temp_pomo_break - 1);
        }
        sprintf(center_text, "W%02d B%02d", s_temp_pomo_work, s_temp_pomo_break);
    } else {
        spec->title = "ALARM";
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

static void draw_edit_ring_labels(MenuState_t state, uint8_t field) {
    uint8_t count = 0;
    uint8_t step = 1;
    uint8_t offset = 0;
    get_edit_ring_params(state, field, &count, &step, &offset);

    for (uint8_t i = 0; i < count; i++) {
        if (!edit_label_at_index(state, field, i, count, step)) continue;
        int x, y;
        radial_idx_to_xy(i, count, MENU_EDIT_RING_RADIUS, &x, &y);
        char label[3];
        sprintf(label, "%02d", (uint8_t)(i + offset));
        oledC_DrawString(x - 6, y - 3, 1, 1, (uint8_t*)label, COLOR_DIM);
    }
}

static void clear_edit_ring_area(void) {
    uint8_t inner = (uint8_t)(MENU_EDIT_RING_RADIUS > 7 ? (MENU_EDIT_RING_RADIUS - 7) : 0);
    uint8_t outer = (uint8_t)(MENU_EDIT_RING_RADIUS + 7);
    uint8_t radius = (uint8_t)((inner + outer) / 2);
    uint8_t width = (uint8_t)(outer - inner + 1);
    oledC_DrawRing(MENU_CENTER_X, MENU_CENTER_Y, radius, width, COLOR_BG);
}

static void draw_edit_tick_partial(MenuState_t state, uint8_t field,
                                   uint8_t old_val, uint8_t new_val,
                                   uint8_t count, uint8_t step, uint8_t offset) {
    if (old_val == new_val) return;
    int x, y;
    radial_idx_to_xy(old_val, count, MENU_EDIT_RING_RADIUS, &x, &y);
    oledC_DrawCircle(x, y, MENU_EDIT_TICK_RADIUS, COLOR_BG);
    if (edit_label_at_index(state, field, old_val, count, step)) {
        char label[3];
        sprintf(label, "%02d", (uint8_t)(old_val + offset));
        oledC_DrawString(x - 6, y - 3, 1, 1, (uint8_t*)label, COLOR_DIM);
    }
    radial_idx_to_xy(new_val, count, MENU_EDIT_RING_RADIUS, &x, &y);
    oledC_DrawCircle(x, y, MENU_EDIT_TICK_RADIUS, COLOR_PRIMARY);
}

static void draw_edit_full(MenuState_t state) {
    EditRingSpec_t spec;
    char center_text[9];
    fill_edit_spec(state, &spec, center_text);

    oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
    draw_menu_header(spec.title);
    draw_edit_ring_labels(state, Watch_GetState()->menu_edit_field);
    draw_center_label(center_text);

    int sx, sy;
    radial_idx_to_xy(spec.selected, spec.count, MENU_EDIT_RING_RADIUS, &sx, &sy);
    oledC_DrawCircle(sx, sy, MENU_EDIT_TICK_RADIUS, COLOR_PRIMARY);
    s_edit_last_draw_val = spec.selected;
    s_edit_last_draw_field = Watch_GetState()->menu_edit_field;
    s_edit_full_drawn = true;
}

static void draw_edit_field_update(MenuState_t state) {
    EditRingSpec_t spec;
    char center_text[9];
    fill_edit_spec(state, &spec, center_text);

    clear_edit_ring_area();
    draw_edit_ring_labels(state, Watch_GetState()->menu_edit_field);
    draw_center_label(center_text);
    int sx, sy;
    radial_idx_to_xy(spec.selected, spec.count, MENU_EDIT_RING_RADIUS, &sx, &sy);
    oledC_DrawCircle(sx, sy, MENU_EDIT_TICK_RADIUS, COLOR_PRIMARY);
    s_edit_last_draw_val = spec.selected;
    s_edit_last_draw_field = Watch_GetState()->menu_edit_field;
    s_edit_full_drawn = true;
}

static void draw_edit_value_update(MenuState_t state) {
    EditRingSpec_t spec;
    char center_text[9];
    fill_edit_spec(state, &spec, center_text);

    if (!s_edit_full_drawn || s_edit_last_draw_val == 0xFF ||
        s_edit_last_draw_field != Watch_GetState()->menu_edit_field) {
        draw_edit_field_update(state);
        return;
    }

    uint8_t last_count = spec.count;
    uint8_t step = spec.label_step;
    uint8_t offset = spec.label_offset;
    if (state == MENU_SET_TIME || state == MENU_SET_ALARM) {
        last_count = (s_edit_last_draw_field == 0) ? 24 : 60;
        step = (s_edit_last_draw_field == 0) ? 2 : 5;
        offset = 0;
    } else if (state == MENU_SET_DATE) {
        last_count = (s_edit_last_draw_field == 0) ? 31 : 12;
        step = (s_edit_last_draw_field == 0) ? 5 : 1;
        offset = 1;
    } else if (state == MENU_POMODORO) {
        last_count = (s_edit_last_draw_field == 0) ? 60 : 30;
        step = 5;
        offset = 1;
    }

    draw_edit_tick_partial(state, Watch_GetState()->menu_edit_field,
                           s_edit_last_draw_val, spec.selected, last_count, step, offset);
    draw_center_label(center_text);
    s_edit_last_draw_val = spec.selected;
    s_edit_last_draw_field = Watch_GetState()->menu_edit_field;
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
        case MENU_POMODORO: draw_edit_full(MENU_POMODORO); break;
        case MENU_ALARM_TOGGLE: draw_radial_menu_full(&s_alarm_toggle_cfg); break;
        default:
            oledC_DrawRectangle(0, 12, 95, 95, COLOR_BG);
            oledC_DrawString(10, 40, 1, 1, (uint8_t*)"Coming Soon", COLOR_PRIMARY);
            break;
    }
}

void Menu_DrawPartial(void) {
    if (s_skip_next_partial) {
        s_skip_next_partial = false;
        return;
    }
    draw_small_time_update();
    WatchState_t* state = Watch_GetState();
    MenuEvent_t ev;
    bool had_event = false;
    bool field_updated = false;
    while (MenuEvent_Pop(&ev)) {
        had_event = true;
        switch (ev.type) {
            case MENU_EVT_RADIAL_SELECT:
                switch(state->menu_state) {
                    case MENU_MAIN: draw_radial_menu_partial(&s_main_menu_cfg); break;
                    case MENU_DISPLAY_MODE: draw_radial_menu_partial(&s_display_menu_cfg); break;
                    case MENU_TIME_FORMAT: draw_radial_menu_partial(&s_format_menu_cfg); break;
                    case MENU_ALARM_TOGGLE: draw_radial_menu_partial(&s_alarm_toggle_cfg); break;
                    default: break;
                }
                break;
            case MENU_EVT_EDIT_FIELD:
                if (state->menu_state == MENU_SET_TIME) draw_edit_field_update(MENU_SET_TIME);
                else if (state->menu_state == MENU_SET_DATE) draw_edit_field_update(MENU_SET_DATE);
                else if (state->menu_state == MENU_SET_ALARM) draw_edit_field_update(MENU_SET_ALARM);
                else if (state->menu_state == MENU_POMODORO) draw_edit_field_update(MENU_POMODORO);
                field_updated = true;
                break;
            case MENU_EVT_EDIT_VALUE:
                if (field_updated) break;
                if (state->menu_state == MENU_SET_TIME) draw_edit_value_update(MENU_SET_TIME);
                else if (state->menu_state == MENU_SET_DATE) draw_edit_value_update(MENU_SET_DATE);
                else if (state->menu_state == MENU_SET_ALARM) draw_edit_value_update(MENU_SET_ALARM);
                else if (state->menu_state == MENU_POMODORO) draw_edit_value_update(MENU_POMODORO);
                break;
            default:
                break;
        }
    }

    if (!had_event && state->menu_state == MENU_POMODORO) {
        draw_edit_value_update(MENU_POMODORO);
    }
}
