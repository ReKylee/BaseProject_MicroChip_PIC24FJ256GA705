/*
 * binary_face.c
 * Binary watch face using immediate-mode drawing (optimized)
 */

#include "binary_face.h"
#include "../shared/watch_state.h"
#include "../shared/watch_types.h"
#include "../watchCore/timekeeper.h"
#include "watch_face_common.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// ============================================================================
// CONFIG
// ============================================================================

#define DOT_SIZE        5
#define DOT_SPACING     9
#define COL_SPACING_FIX 4  // extra spacing between hours/minutes/seconds
#define GRID_ROWS       4
#define GRID_COLS       6
#define SCREEN_W        96
#define SCREEN_H        96

static uint8_t s_origin_x = 0;
static uint8_t s_origin_y = 0;
static uint8_t s_label_x[3];
static uint8_t s_label_y = 0;
static uint8_t s_bit_labels_y[4];
static const char* s_bit_labels = "8421";

// Colors per column (hour, min, sec)
static const uint16_t s_colors[6] = {COLOR_PRIMARY, COLOR_PRIMARY,
    COLOR_SECONDARY, COLOR_SECONDARY,
    COLOR_ACCENT, COLOR_ACCENT};

// Precompute dot positions

typedef struct {
    uint8_t x, y;
} DotPos_t;
static DotPos_t s_dot_pos[GRID_COLS][GRID_ROWS]; // col x row

// ============================================================================
// STATE
// ============================================================================

static Time_t s_last_time_drawn;
static TimeFormat_t s_last_format_drawn;
static Date_t s_last_date_drawn;

// ============================================================================
// PRIVATE FUNCTIONS
// ============================================================================

static inline uint8_t get_bit(uint8_t value, uint8_t bit_pos) {
    return (value >> bit_pos) & 1;
}

static void init_dot_positions(void) {
    uint8_t grid_w = (GRID_COLS - 1) * DOT_SPACING + 2 * COL_SPACING_FIX;
    uint8_t grid_h = (GRID_ROWS - 1) * DOT_SPACING;
    s_origin_x = (uint8_t)((SCREEN_W - grid_w) / 2);
    s_origin_y = 20;

    for (uint8_t col = 0; col < GRID_COLS; col++) {
        for (uint8_t row = 0; row < GRID_ROWS; row++) {
            uint8_t x = s_origin_x + col * DOT_SPACING + (col / 2) * COL_SPACING_FIX;
            uint8_t y = s_origin_y + row * DOT_SPACING;
            s_dot_pos[col][row].x = x;
            s_dot_pos[col][row].y = y;
        }
    }

    s_label_x[0] = s_origin_x + 4;
    s_label_x[1] = s_origin_x + DOT_SPACING * 2 + COL_SPACING_FIX + 4;
    s_label_x[2] = s_origin_x + DOT_SPACING * 4 + COL_SPACING_FIX * 2 + 4;
    s_label_y = s_origin_y + grid_h + 16;

    for (uint8_t row = 0; row < GRID_ROWS; row++) {
        s_bit_labels_y[row] = s_origin_y + row * DOT_SPACING - 4;
    }
}

static void draw_dot(uint8_t x, uint8_t y, bool on, uint16_t color_on) {
    uint8_t half = DOT_SIZE / 2;
    oledC_DrawRectangle(x - half - 1, y - half - 1, x + half + 1, y + half + 1, COLOR_BG);
    if (on) {
        oledC_DrawCircle(x, y, half, color_on);
    } else {
        oledC_DrawRing(x, y, half, 1, COLOR_DIM);
    }
}

// ============================================================================
// PUBLIC API
// ============================================================================

void BinaryFace_Init(void) {
    oledC_setBackground(COLOR_BG);

    init_dot_positions();

    // Draw static labels (H M S)
    for (uint8_t i = 0; i < 3; i++) {
        oledC_DrawString(s_label_x[i], s_label_y, 1, 1, (uint8_t*) (i == 0 ? "H" : i == 1 ? "M" : "S"), COLOR_TEXT);
    }

    // Draw bit labels (8,4,2,1)
    for (uint8_t row = 0; row < 4; row++) {

        oledC_DrawString(2, s_bit_labels_y[row], 1, 1, (uint8_t[]) {
            s_bit_labels[row], 0}, COLOR_TEXT);
    }

    // Draw separators (simple small rings) centered between HH|MM|SS
    uint8_t sep1_x = (uint8_t)((s_dot_pos[1][0].x + s_dot_pos[2][0].x) / 2);
    uint8_t sep2_x = (uint8_t)((s_dot_pos[3][0].x + s_dot_pos[4][0].x) / 2);
    uint8_t sep_y0 = s_dot_pos[0][1].y;
    uint8_t sep_y1 = s_dot_pos[0][2].y;
    oledC_DrawCircle(sep1_x, sep_y0, 1, COLOR_DIM);
    oledC_DrawCircle(sep1_x, sep_y1, 1, COLOR_DIM);
    oledC_DrawCircle(sep2_x, sep_y0, 1, COLOR_DIM);
    oledC_DrawCircle(sep2_x, sep_y1, 1, COLOR_DIM);

    // Draw all dots as rings initially
    for (uint8_t col = 0; col < 6; col++) {
        for (uint8_t row = 0; row < 4; row++) {
            oledC_DrawRing(s_dot_pos[col][row].x, s_dot_pos[col][row].y, DOT_SIZE / 2, 1, COLOR_DIM);
        }
    }

    memset(&s_last_time_drawn, 0, sizeof (Time_t));
    s_last_time_drawn.second = 99; // force full redraw
    s_last_format_drawn = FORMAT_24H;
    memset(&s_last_date_drawn, 0, sizeof(Date_t));
}

void BinaryFace_Draw(void) {
    // Full redraw relies on BinaryFace_Init being called on face entry.
    BinaryFace_DrawUpdate();
}

void BinaryFace_DrawUpdate(void) {
    WatchState_t* state = Watch_GetState();
    Time_t now = state->current_time;

    // Redraw everything if format changed
    if (state->time_format != s_last_format_drawn) {
        BinaryFace_Init();
        s_last_format_drawn = state->time_format;
        return;
    }

    // Extract digits (hour, min, sec)
    uint8_t hour = now.hour;
    uint8_t last_hour = s_last_time_drawn.hour;
    if (state->time_format == FORMAT_12H) {
        bool is_pm, was_pm;
        hour = Timekeeper_Convert24to12(now.hour, &is_pm);
        last_hour = Timekeeper_Convert24to12(s_last_time_drawn.hour, &was_pm);
    }

    uint8_t digits[6] = {hour / 10, hour % 10, now.minute / 10, now.minute % 10, now.second / 10, now.second % 10};
    uint8_t last_digits[6] = {last_hour / 10, last_hour % 10, s_last_time_drawn.minute / 10, s_last_time_drawn.minute % 10,
        s_last_time_drawn.second / 10, s_last_time_drawn.second % 10};

    // Iterate columns and rows
    for (uint8_t col = 0; col < 6; col++) {
        if (digits[col] == last_digits[col]) continue; // skip unchanged digits

        for (uint8_t row = 0; row < 4; row++) {
            bool bit_now = get_bit(digits[col], 3 - row);
            bool bit_last = get_bit(last_digits[col], 3 - row);
            if (bit_now == bit_last) continue;

            uint8_t x = s_dot_pos[col][row].x;
            uint8_t y = s_dot_pos[col][row].y;

            draw_dot(x, y, bit_now, s_colors[col]);
        }
    }

    s_last_time_drawn = now;

    // Date
    uint8_t date_text_w = 30;
    uint8_t date_x = (uint8_t)((SCREEN_W - date_text_w) / 2);
    WatchFace_DrawDate(date_x, 82, &state->current_date, &s_last_date_drawn, COLOR_DIM, COLOR_BG);
}
