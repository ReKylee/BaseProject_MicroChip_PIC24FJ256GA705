/*
 * Menu drawing logic (full and partial updates).
 */

#include "menu_state.h"
#include "menu_core.h"
#include "menu_layout.h"
#include "../shared/fast_math.h"
#include "../shared/ui_layout.h"
#include "../shared/watch_ui_widgets.h"
#include "../shared/watch_format.h"
#include "../watchFaces/watch_face_geometry.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include "../watchCore/timekeeper.h"
#include <string.h>

// ============================================================================
// RENDER CONSTANTS
// ============================================================================

static const RadialMenuConfig_t* s_active_radial = NULL;
static TimeFormat_t s_last_small_time_format = FORMAT_24H;
static const char* s_last_header_title = NULL;
static bool s_center_label_valid = false;
static char s_center_prev_line1[12] = {0};
static char s_center_prev_line2[12] = {0};
static uint8_t s_center_prev_l1x = 0;
static uint8_t s_center_prev_l1y = 0;
static uint8_t s_center_prev_l2x = 0;
static uint8_t s_center_prev_l2y = 0;
// Main radial menu arc: 45 deg -> 315 deg clockwise (270 deg span).
#define MENU_ARC_START_POINTS_X2 15U
#define MENU_ARC_END_POINTS_X2   105U
#define MENU_FONT_W 5U
#define MENU_FONT_GAP 1U
#define MENU_FONT_SCALE 1U
#define MENU_TIME_CHARS_12H 11U
#define MENU_TIME_CHARS_24H 8U
#define MENU_CENTER_LABEL_MAX_CHARS 11U
#define MENU_CENTER_LABEL_SINGLE_Y_OFFSET 3U
#define MENU_CENTER_LABEL_TOP_Y_OFFSET 7U
#define MENU_CENTER_LABEL_BOTTOM_Y_OFFSET 1U
#define MENU_EDIT_LABEL_X_OFFSET 6U
#define MENU_EDIT_LABEL_Y_OFFSET 3U
#define MENU_FALLBACK_TEXT "Coming Soon"
#define MENU_FALLBACK_TEXT_Y 40U

static inline int16_t divs32_by76_bounded(int32_t v) {
    bool neg = (v < 0);
    uint32_t uv = neg ? (uint32_t)(-v) : (uint32_t)v;
    /* Exact for the bounded range used here (|v| <= ~3500). */
    uint32_t q = (uv * 6899UL) >> 19;
    return neg ? -(int16_t)q : (int16_t)q;
}

static inline uint8_t idx_to_sec_arc(uint8_t idx, uint8_t count) {
    uint16_t sec_x2;
    if (count <= 1U) {
        sec_x2 = (uint16_t)((MENU_ARC_START_POINTS_X2 + MENU_ARC_END_POINTS_X2) >> 1);
    } else {
        if (idx == 0U) return MENU_ARC_START_POINTS_X2;
        if (idx >= (uint8_t)(count - 1U)) return MENU_ARC_END_POINTS_X2;
        uint16_t span_x2 = (uint16_t)(MENU_ARC_END_POINTS_X2 - MENU_ARC_START_POINTS_X2);
        sec_x2 = (uint16_t)(MENU_ARC_START_POINTS_X2 +
                            ((((uint32_t)idx * (uint32_t)span_x2) + ((uint32_t)(count - 1U) >> 1)) /
                             (uint32_t)(count - 1U)));
    }
    return (uint8_t)sec_x2;
}

static inline void arc_point_to_xy(uint8_t sec_x2, uint8_t radius, int *x, int *y) {
    uint8_t sec = (uint8_t)(sec_x2 >> 1);
    uint8_t next = (uint8_t)(sec + 1U);
    if (next >= NUM_CLOCK_POINTS) {
        next = 0U;
    }

    int16_t dx_x2 = (int16_t)(((int16_t)SEC_POINTS[sec][0] - (int16_t)MENU_GEOM_CENTER_X) * 2);
    int16_t dy_x2 = (int16_t)(((int16_t)SEC_POINTS[sec][1] - (int16_t)MENU_GEOM_CENTER_Y) * 2);
    if ((sec_x2 & 1U) != 0U) {
        dx_x2 = (int16_t)(((int16_t)SEC_POINTS[sec][0] - (int16_t)MENU_GEOM_CENTER_X) +
                          ((int16_t)SEC_POINTS[next][0] - (int16_t)MENU_GEOM_CENTER_X));
        dy_x2 = (int16_t)(((int16_t)SEC_POINTS[sec][1] - (int16_t)MENU_GEOM_CENTER_Y) +
                          ((int16_t)SEC_POINTS[next][1] - (int16_t)MENU_GEOM_CENTER_Y));
    }

    int16_t sx = divs32_by76_bounded((int32_t)dx_x2 * (int32_t)radius);
    int16_t sy = divs32_by76_bounded((int32_t)dy_x2 * (int32_t)radius);
    *x = MENU_CENTER_X + sx;
    *y = MENU_CENTER_Y + sy;
}

static inline void radial_idx_to_xy_arc(uint8_t idx, uint8_t count, uint8_t radius, int *x, int *y) {
    arc_point_to_xy(idx_to_sec_arc(idx, count), radius, x, y);
}

static void draw_center_label(const char *text) {
    char line1[12];
    char line2[12];
    size_t len = strlen(text);
    uint8_t max_chars = FastMath_Div6U8((uint8_t)(MENU_INNER_RADIUS * 2U));
    if (max_chars > MENU_CENTER_LABEL_MAX_CHARS) max_chars = MENU_CENTER_LABEL_MAX_CHARS;

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

    uint8_t line1_w = WatchUi_CharsToPx6(strlen(line1));
    uint8_t line2_w = WatchUi_CharsToPx6(strlen(line2));
    uint8_t l1x = (uint8_t)(MENU_CENTER_X - (line1_w >> 1));
    uint8_t l2x = (uint8_t)(MENU_CENTER_X - (line2_w >> 1));
    uint8_t l1y = (line2[0] == '\0') ? (uint8_t)(MENU_CENTER_Y - MENU_CENTER_LABEL_SINGLE_Y_OFFSET)
                                     : (uint8_t)(MENU_CENTER_Y - MENU_CENTER_LABEL_TOP_Y_OFFSET);
    uint8_t l2y = (uint8_t)(MENU_CENTER_Y + MENU_CENTER_LABEL_BOTTOM_Y_OFFSET);

    if (s_center_label_valid) {
        if (s_center_prev_line1[0] != '\0') {
            oledC_DrawStringSolid(s_center_prev_l1x, s_center_prev_l1y, 1, 1, (uint8_t*)s_center_prev_line1, COLOR_BG, COLOR_BG);
        }
        if (s_center_prev_line2[0] != '\0') {
            oledC_DrawStringSolid(s_center_prev_l2x, s_center_prev_l2y, 1, 1, (uint8_t*)s_center_prev_line2, COLOR_BG, COLOR_BG);
        }
    }

    if (line2[0] == '\0') {
        oledC_DrawStringSolid(l1x, l1y, 1, 1, (uint8_t*)line1, COLOR_PRIMARY, COLOR_BG);
    } else {
        oledC_DrawStringSolid(l1x, l1y, 1, 1, (uint8_t*)line1, COLOR_PRIMARY, COLOR_BG);
        oledC_DrawStringSolid(l2x, l2y, 1, 1, (uint8_t*)line2, COLOR_PRIMARY, COLOR_BG);
    }

    strncpy(s_center_prev_line1, line1, sizeof(s_center_prev_line1) - 1);
    s_center_prev_line1[sizeof(s_center_prev_line1) - 1] = '\0';
    strncpy(s_center_prev_line2, line2, sizeof(s_center_prev_line2) - 1);
    s_center_prev_line2[sizeof(s_center_prev_line2) - 1] = '\0';
    s_center_prev_l1x = l1x;
    s_center_prev_l1y = l1y;
    s_center_prev_l2x = l2x;
    s_center_prev_l2y = l2y;
    s_center_label_valid = true;
}

static void draw_menu_header(const char* title) {
    WatchState_t* state = Watch_GetState();
    oledC_DrawRectangle(0, MENU_HEADER_Y, MENU_SCREEN_MAX_X, MENU_HEADER_Y + MENU_HEADER_H, COLOR_BG);
    if (state->menu_state == MENU_TIME_FORMAT) {
        oledC_DrawStringSolid(MENU_TITLE_X, MENU_TITLE_ALT_Y, 1, 1, (uint8_t*)title, COLOR_ACCENT, COLOR_BG);
    } else {
        oledC_DrawStringSolid(MENU_TITLE_X, MENU_TITLE_Y, 1, 1, (uint8_t*)title, COLOR_ACCENT, COLOR_BG);
    }
    s_last_header_title = title;
}

static uint8_t small_time_x_start(const WatchState_t* state) {
    uint8_t chars = (state->time_format == FORMAT_12H) ? MENU_TIME_CHARS_12H : MENU_TIME_CHARS_24H;
    uint8_t width = WatchUi_TextWidth(chars, MENU_FONT_W, MENU_FONT_SCALE, MENU_FONT_GAP);
    return WatchUi_RightX96(width);
}

static void draw_small_time_common(const WatchState_t* state) {
    uint8_t x = small_time_x_start(state);
    uint8_t step = WatchUi_GlyphAdvance(MENU_FONT_W, MENU_FONT_SCALE, MENU_FONT_GAP);
    uint8_t hour = state->current_time.hour;
    bool is_pm = false;

    if (state->time_format == FORMAT_12H) {
        hour = Timekeeper_Convert24to12(hour, &is_pm);
    }

    oledC_DrawRectangle(0, MENU_HEADER_Y,
                        MENU_SCREEN_MAX_X, MENU_HEADER_Y + MENU_HEADER_H,
                        COLOR_BG);
    if (s_last_header_title) {
        if (state->menu_state == MENU_TIME_FORMAT) {
            oledC_DrawStringSolid(MENU_TITLE_X, MENU_TITLE_ALT_Y, 1, 1, (uint8_t*)s_last_header_title, COLOR_ACCENT, COLOR_BG);
        } else {
            oledC_DrawStringSolid(MENU_TITLE_X, MENU_TITLE_Y, 1, 1, (uint8_t*)s_last_header_title, COLOR_ACCENT, COLOR_BG);
            if (state->menu_state == MENU_DISPLAY_MODE) {
                oledC_DrawStringSolid(MENU_BACK_ARROW_X, MENU_TITLE_Y, 1, 1, (uint8_t*)"<", COLOR_DIM, COLOR_BG);
            }
        }
    }

    WatchUi_DrawNN(hour, x, MENU_TIME_Y, 1U, 1U, COLOR_DIM, COLOR_BG);
    x = (uint8_t)(x + (uint8_t)(2U * step));
    WatchUi_DrawColon(x, MENU_TIME_Y, 1U, 1U, COLOR_DIM, COLOR_BG);
    x = (uint8_t)(x + step);

    WatchUi_DrawNN(state->current_time.minute, x, MENU_TIME_Y, 1U, 1U, COLOR_DIM, COLOR_BG);
    x = (uint8_t)(x + (uint8_t)(2U * step));
    WatchUi_DrawColon(x, MENU_TIME_Y, 1U, 1U, COLOR_DIM, COLOR_BG);
    x = (uint8_t)(x + step);

    WatchUi_DrawNN(state->current_time.second, x, MENU_TIME_Y, 1U, 1U, COLOR_DIM, COLOR_BG);
    x = (uint8_t)(x + (uint8_t)(2U * step));

    if (state->time_format == FORMAT_12H) {
        x = (uint8_t)(x + step); // visual spacing before AM/PM
        oledC_DrawStringSolid(x, MENU_TIME_Y, 1, 1, (uint8_t*)(is_pm ? "PM" : "AM"), COLOR_DIM, COLOR_BG);
    }

    s_last_small_time = state->current_time;
    s_last_small_time_format = state->time_format;
}

static void draw_small_time_update(void) {
    WatchState_t* state = Watch_GetState();
    if (state->current_time.second != s_last_small_time.second ||
        state->time_format != s_last_small_time_format) {
        draw_small_time_common(state);
    }
}

static void draw_small_time_full(void) {
    WatchState_t* state = Watch_GetState();
    draw_small_time_common(state);
}

static void draw_radial_item(uint8_t idx, bool selected) {
    if (!s_active_radial) return;
    int x, y;
    radial_idx_to_xy_arc(idx, s_active_radial->radial->count, s_active_radial->radius, &x, &y);

    if (s_active_radial == &s_main_menu_cfg && idx == 1U) {
        WatchState_t* state = Watch_GetState();
        const char* tf = (state->time_format == FORMAT_12H) ? "12H" : "24H";
        uint8_t w = WatchUi_CharsToPx6(strlen(tf));
        if (selected) {
            oledC_DrawCircle(x, y, MENU_RING_RADIUS, COLOR_PRIMARY);
            oledC_DrawStringSolid((uint8_t)(x - (w >> 1)), (uint8_t)(y - 3), 1, 1, (uint8_t*)tf, COLOR_BG, COLOR_PRIMARY);
        } else {
            oledC_DrawCircle(x, y, MENU_RING_RADIUS, COLOR_BG);
            oledC_DrawStringSolid((uint8_t)(x - (w >> 1)), (uint8_t)(y - 3), 1, 1, (uint8_t*)tf, COLOR_PRIMARY, COLOR_BG);
        }
        return;
    }

    if (s_active_radial == &s_format_menu_cfg) {
        const char* tf = (idx == 0U) ? "12H" : "24H";
        uint8_t w = WatchUi_CharsToPx6(strlen(tf));
        if (selected) {
            oledC_DrawCircle(x, y, MENU_RING_RADIUS, COLOR_PRIMARY);
            oledC_DrawStringSolid((uint8_t)(x - (w >> 1)), (uint8_t)(y - 3), 1, 1, (uint8_t*)tf, COLOR_BG, COLOR_PRIMARY);
        } else {
            oledC_DrawCircle(x, y, MENU_RING_RADIUS, COLOR_BG);
            oledC_DrawStringSolid((uint8_t)(x - (w >> 1)), (uint8_t)(y - 3), 1, 1, (uint8_t*)tf, COLOR_PRIMARY, COLOR_BG);
        }
        return;
    }
    const IconAsset_t* icon_asset = s_active_radial->get_icon ? s_active_radial->get_icon(idx) : s_active_radial->icons[idx];
    const uint8_t* icon = icon_asset->pixels;
    uint16_t palette[4];
    if (selected) {
        oledC_DrawCircle(x, y, MENU_RING_RADIUS, COLOR_PRIMARY);
        palette[0] = COLOR_PRIMARY;
    } else {
        oledC_DrawCircle(x, y, MENU_RING_RADIUS, COLOR_BG);
        palette[0] = COLOR_BG;
    }
    palette[1] = icon_asset->palette[1];
    palette[2] = icon_asset->palette[2];
    palette[3] = icon_asset->palette[3];
    const uint8_t icon_offset = (uint8_t)((MENU_ICON_SIZE - 1U) >> 1);
    oledC_DrawBitmapIndexed2bpp((uint8_t)(x - icon_offset),
                                (uint8_t)(y - icon_offset),
                                MENU_ICON_SIZE, MENU_ICON_SIZE,
                                icon, palette);
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
    oledC_DrawRectangle(0, MENU_CONTENT_TOP_Y, MENU_SCREEN_MAX_X, MENU_SCREEN_MAX_X, COLOR_BG);
    draw_menu_header(cfg->title);
    draw_small_time_full();
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

static bool edit_label_at_index(uint8_t idx, uint8_t count, uint8_t step) {
    uint8_t reduced = idx;
    if (idx == 0U || idx == (uint8_t)(count - 1U)) return true;
    while (reduced >= step) {
        reduced = (uint8_t)(reduced - step);
    }
    return reduced == 0U;
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
        Watch_Format2D(s_temp_time.hour, &center_text[0]);
        center_text[2] = ':';
        Watch_Format2D(s_temp_time.minute, &center_text[3]);
        center_text[5] = '\0';
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
        Watch_Format2D(s_temp_date.day, &center_text[0]);
        center_text[2] = '/';
        Watch_Format2D(s_temp_date.month, &center_text[3]);
        center_text[5] = '\0';
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
        center_text[0] = 'W';
        Watch_Format2D(s_temp_pomo_work, &center_text[1]);
        center_text[3] = ' ';
        center_text[4] = 'B';
        Watch_Format2D(s_temp_pomo_break, &center_text[5]);
        center_text[7] = '\0';
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
        Watch_Format2D(s_temp_alarm.hour, &center_text[0]);
        center_text[2] = ':';
        Watch_Format2D(s_temp_alarm.minute, &center_text[3]);
        center_text[5] = '\0';
    }
}

static void draw_edit_ring_labels(MenuState_t state, uint8_t field) {
    uint8_t count = 0;
    uint8_t step = 1;
    uint8_t offset = 0;
    get_edit_ring_params(state, field, &count, &step, &offset);

    for (uint8_t i = 0; i < count; i++) {
        if (!edit_label_at_index(i, count, step)) continue;
        int x, y;
        radial_idx_to_xy_arc(i, count, MENU_EDIT_LABEL_RADIUS, &x, &y);
        WatchUi_DrawNN((uint8_t)(i + offset),
                       (uint8_t)(x - MENU_EDIT_LABEL_X_OFFSET),
                       (uint8_t)(y - MENU_EDIT_LABEL_Y_OFFSET),
                       1U, 1U, COLOR_DIM, COLOR_BG);
    }
}

static void clear_edit_ring_area(void) {
    uint8_t max_r = MENU_EDIT_RING_RADIUS;
    if (MENU_EDIT_LABEL_RADIUS > max_r) max_r = MENU_EDIT_LABEL_RADIUS;
    uint8_t outer = (uint8_t)(max_r + 7);
    oledC_DrawCircle(MENU_CENTER_X, MENU_CENTER_Y, outer, COLOR_BG);
}

static void draw_edit_tick(uint8_t value, uint8_t count, uint16_t color) {
    int x, y;
    radial_idx_to_xy_arc(value, count, MENU_EDIT_TICK_ORBIT_RADIUS, &x, &y);
    oledC_DrawCircle(x, y, MENU_EDIT_TICK_RADIUS, color);
}

static const char* edit_title_for_state(MenuState_t state) {
    switch (state) {
        case MENU_SET_TIME: return "TIME";
        case MENU_SET_DATE: return "DATE";
        case MENU_SET_ALARM: return "ALARM";
        case MENU_POMODORO: return "POMO";
        default: return "EDIT";
    }
}

static void set_edit_draw_cache(uint8_t selected, uint8_t field) {
    s_edit_last_draw_val = selected;
    s_edit_last_draw_field = field;
    MenuState_SetEditFullDrawn(true);
}

static void draw_edit_core(MenuState_t state, bool clear_ring_only) {
    EditRingSpec_t spec;
    char center_text[9];
    uint8_t field = Watch_GetState()->menu_edit_field;
    fill_edit_spec(state, &spec, center_text);

    if (clear_ring_only) {
        clear_edit_ring_area();
    }
    draw_edit_ring_labels(state, field);
    draw_center_label(center_text);
    draw_edit_tick(spec.selected, spec.count, COLOR_PRIMARY);
    set_edit_draw_cache(spec.selected, field);
}

static void draw_edit_full(MenuState_t state) {
    oledC_DrawRectangle(0, MENU_CONTENT_TOP_Y, MENU_SCREEN_MAX_X, MENU_SCREEN_MAX_X, COLOR_BG);
    draw_menu_header(edit_title_for_state(state));
    draw_small_time_full();
    draw_edit_core(state, false);
}

static void draw_edit_field_update(MenuState_t state) {
    draw_edit_core(state, true);
}

static void draw_edit_value_update(MenuState_t state) {
    EditRingSpec_t spec;
    char center_text[9];
    uint8_t field = Watch_GetState()->menu_edit_field;
    fill_edit_spec(state, &spec, center_text);

    if (!MenuState_IsEditFullDrawn() || s_edit_last_draw_val == 0xFF ||
        s_edit_last_draw_field != field) {
        draw_edit_field_update(state);
        return;
    }

    if (spec.selected != s_edit_last_draw_val) {
        draw_edit_tick(s_edit_last_draw_val, spec.count, COLOR_BG);
        draw_edit_tick(spec.selected, spec.count, COLOR_PRIMARY);
        draw_center_label(center_text);
        s_edit_last_draw_val = spec.selected;
    }
}

static bool is_edit_state(MenuState_t state) {
    return state == MENU_SET_TIME ||
           state == MENU_SET_DATE ||
           state == MENU_SET_ALARM ||
           state == MENU_POMODORO;
}

static void draw_edit_field_for_state(MenuState_t state) {
    if (!is_edit_state(state)) return;
    draw_edit_field_update(state);
}

static void draw_edit_value_for_state(MenuState_t state) {
    if (!is_edit_state(state)) return;
    draw_edit_value_update(state);
}

void Menu_DrawFull(void) {
    WatchState_t* state = Watch_GetState();

    MenuState_SetSkipNextPartial(true);
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
            oledC_DrawRectangle(0, MENU_CONTENT_TOP_Y, MENU_SCREEN_MAX_X, MENU_SCREEN_MAX_X, COLOR_BG);
            oledC_DrawStringSolid(WatchUi_CenterX96(WatchUi_CharsToPx6(strlen(MENU_FALLBACK_TEXT))),
                                  MENU_FALLBACK_TEXT_Y, 1, 1, (uint8_t*)MENU_FALLBACK_TEXT, COLOR_PRIMARY, COLOR_BG);
            break;
    }
}

void Menu_DrawPartial(void) {
    if (MenuState_ConsumeSkipNextPartial()) {
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
                draw_edit_field_for_state(state->menu_state);
                field_updated = true;
                break;
            case MENU_EVT_EDIT_VALUE:
                if (field_updated) break;
                draw_edit_value_for_state(state->menu_state);
                break;
            default:
                break;
        }
    }

    if (!had_event && state->menu_state == MENU_POMODORO) {
        draw_edit_value_for_state(state->menu_state);
    }
}

