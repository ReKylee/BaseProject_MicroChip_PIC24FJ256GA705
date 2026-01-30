/*
 * binary_face.c
 * Binary watch face using immediate-mode drawing (optimized)
 */

#include "binary_face.h"
#include "../shared/watch_state.h"
#include "../shared/watch_types.h"
#include "../watchCore/timekeeper.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// ============================================================================
// CONFIG
// ============================================================================

#define DOT_SIZE        5
#define DOT_SPACING     10
#define START_X         16
#define START_Y         20
#define COL_SPACING_FIX 5  // extra spacing between hours/minutes/seconds

static const uint8_t LABEL_X[3] = {START_X + 5, START_X + 30, START_X + 55};
static const uint8_t LABEL_Y = 78;

static const uint8_t BIT_LABELS_Y[4] = {START_Y - 3, START_Y + 7, START_Y + 17, START_Y + 27};
static const char* BIT_LABELS = "8421";

// Colors per column (hour, min, sec)
static const uint16_t COLORS[6] = {COLOR_PRIMARY, COLOR_PRIMARY,
    COLOR_SECONDARY, COLOR_SECONDARY,
    COLOR_ACCENT, COLOR_ACCENT};

// Precompute dot positions

typedef struct {
    uint8_t x, y;
} DotPos_t;
static DotPos_t dot_pos[6][4]; // col x row

// ============================================================================
// STATE
// ============================================================================

static Time_t last_time_drawn;
static TimeFormat_t last_format_drawn;

// ============================================================================
// PRIVATE FUNCTIONS
// ============================================================================

static inline uint8_t get_bit(uint8_t value, uint8_t bit_pos) {
    return (value >> bit_pos) & 1;
}

static void InitDotPositions(void) {
    for (uint8_t col = 0; col < 6; col++) {
        for (uint8_t row = 0; row < 4; row++) {
            uint8_t x = START_X + col * DOT_SPACING + (col / 2) * COL_SPACING_FIX;
            uint8_t y = START_Y + row * DOT_SPACING;
            dot_pos[col][row].x = x;
            dot_pos[col][row].y = y;
        }
    }
}

// ============================================================================
// PUBLIC API
// ============================================================================

void BinaryFace_Init(void) {
    oledC_setBackground(COLOR_BG);

    InitDotPositions();

    // Draw static labels (H M S)
    for (uint8_t i = 0; i < 3; i++) {
        oledC_DrawString(LABEL_X[i], LABEL_Y, 1, 1, (uint8_t*) (i == 0 ? "H" : i == 1 ? "M" : "S"), COLOR_DIM);
    }

    // Draw bit labels (8,4,2,1)
    for (uint8_t row = 0; row < 4; row++) {

        oledC_DrawString(2, BIT_LABELS_Y[row], 1, 1, (uint8_t[]) {
            BIT_LABELS[row], 0}, COLOR_DIM);
    }

    // Draw separators (simple small rings)
    oledC_DrawCircle(START_X + 20, START_Y + 12, 1, COLOR_DIM);
    oledC_DrawCircle(START_X + 20, START_Y + 22, 1, COLOR_DIM);
    oledC_DrawCircle(START_X + 45, START_Y + 12, 1, COLOR_DIM);
    oledC_DrawCircle(START_X + 45, START_Y + 22, 1, COLOR_DIM);

    // Draw all dots as rings initially
    for (uint8_t col = 0; col < 6; col++) {
        for (uint8_t row = 0; row < 4; row++) {
            oledC_DrawRing(dot_pos[col][row].x, dot_pos[col][row].y, DOT_SIZE / 2, 1, COLOR_DIM);
        }
    }

    memset(&last_time_drawn, 0, sizeof (Time_t));
    last_time_drawn.second = 99; // force full redraw
    last_format_drawn = FORMAT_24H;
}

void BinaryFace_Draw(void) {
    // Full redraw simply re-inits everything
    BinaryFace_Init();
}

void BinaryFace_DrawUpdate(void) {
    WatchState_t* state = Watch_GetState();
    Time_t now = state->current_time;

    // Redraw everything if format changed
    if (state->time_format != last_format_drawn) {
        BinaryFace_Init();
        last_format_drawn = state->time_format;
        return;
    }

    // Extract digits (hour, min, sec)
    uint8_t hour = now.hour;
    uint8_t last_hour = last_time_drawn.hour;
    if (state->time_format == FORMAT_12H) {
        bool is_pm, was_pm;
        hour = Timekeeper_Convert24to12(now.hour, &is_pm);
        last_hour = Timekeeper_Convert24to12(last_time_drawn.hour, &was_pm);
    }

    uint8_t digits[6] = {hour / 10, hour % 10, now.minute / 10, now.minute % 10, now.second / 10, now.second % 10};
    uint8_t last_digits[6] = {last_hour / 10, last_hour % 10, last_time_drawn.minute / 10, last_time_drawn.minute % 10,
        last_time_drawn.second / 10, last_time_drawn.second % 10};

    // Iterate columns and rows
    for (uint8_t col = 0; col < 6; col++) {
        if (digits[col] == last_digits[col]) continue; // skip unchanged digits

        for (uint8_t row = 0; row < 4; row++) {
            bool bit_now = get_bit(digits[col], 3 - row);
            bool bit_last = get_bit(last_digits[col], 3 - row);
            if (bit_now == bit_last) continue;

            uint8_t x = dot_pos[col][row].x;
            uint8_t y = dot_pos[col][row].y;

            if (bit_now) {
                oledC_DrawCircle(x, y, DOT_SIZE / 2, COLORS[col]);
            } else {
                oledC_DrawRing(x, y, DOT_SIZE / 2, 1, COLOR_DIM);
            }
        }
    }

    last_time_drawn = now;
}
