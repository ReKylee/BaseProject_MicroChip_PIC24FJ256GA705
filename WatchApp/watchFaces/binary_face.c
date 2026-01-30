/*
 * binary_face.c
 * Implementation of binary watch face using the oledC shape handler.
 */

#include "binary_face.h"
#include "../shared/watch_state.h"
#include "../shared/watch_types.h"
#include "../watchCore/timekeeper.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include "../../oledDriver/oledC_shapeHandler.h"
#include <stdio.h>
#include <string.h>

// ============================================================================
// CONFIGURATION & SHAPE INDICES
// ============================================================================

#define DOT_SIZE        5
#define DOT_SPACING     10
#define START_X         16
#define START_Y         20

#define BINARY_SHAPE_START_IDX  0
#define LABEL_START_IDX         (BINARY_SHAPE_START_IDX + 0) // 7 labels
#define SEPARATOR_START_IDX     (BINARY_SHAPE_START_IDX + 7) // 2 separators
#define DOT_START_IDX           (BINARY_SHAPE_START_IDX + 9) // 24 dots (6 cols * 4 rows)
#define BINARY_SHAPE_COUNT      (9 + 24)

// ============================================================================
// MODULE STATE
// ============================================================================

static Time_t last_time_drawn;
static TimeFormat_t last_format_drawn;

// ============================================================================
// PRIVATE FUNCTIONS
// ============================================================================

static uint8_t get_bit(uint8_t value, uint8_t bit_pos) {
    return (value >> bit_pos) & 1;
}

// ============================================================================
// PUBLIC API
// ============================================================================

void BinaryFace_Init(void) {
    initShapesMem();
    shape_params_t p;

    // Add static labels
    p.string.color = COLOR_DIM;
    p.string.x = START_X + 5;
    p.string.y = 78;
    p.string.scale_x = 1;
    p.string.scale_y = 1;
    p.string.string = (uint8_t*)"H";
    oledC_addShape(LABEL_START_IDX + 0, OLED_SHAPE_STRING, &p);
    p.string.color = COLOR_DIM;
    p.string.x = START_X + 30;
    p.string.y = 78;
    p.string.scale_x = 1;
    p.string.scale_y = 1;
    p.string.string = (uint8_t*)"M";
    oledC_addShape(LABEL_START_IDX + 1, OLED_SHAPE_STRING, &p);
    p.string.color = COLOR_DIM;
    p.string.x = START_X + 55;
    p.string.y = 78;
    p.string.scale_x = 1;
    p.string.scale_y = 1;
    p.string.string = (uint8_t*)"S";
    oledC_addShape(LABEL_START_IDX + 2, OLED_SHAPE_STRING, &p);
    p.string.color = COLOR_DIM;
    p.string.x = 2;
    p.string.y = START_Y - 3;
    p.string.scale_x = 1;
    p.string.scale_y = 1;
    p.string.string = (uint8_t*)"8";
    oledC_addShape(LABEL_START_IDX + 3, OLED_SHAPE_STRING, &p);
    p.string.color = COLOR_DIM;
    p.string.x = 2;
    p.string.y = START_Y + 10 - 3;
    p.string.scale_x = 1;
    p.string.scale_y = 1;
    p.string.string = (uint8_t*)"4";
    oledC_addShape(LABEL_START_IDX + 4, OLED_SHAPE_STRING, &p);
    p.string.color = COLOR_DIM;
    p.string.x = 2;
    p.string.y = START_Y + 20 - 3;
    p.string.scale_x = 1;
    p.string.scale_y = 1;
    p.string.string = (uint8_t*)"2";
    oledC_addShape(LABEL_START_IDX + 5, OLED_SHAPE_STRING, &p);
    p.string.color = COLOR_DIM;
    p.string.x = 2;
    p.string.y = START_Y + 30 - 3;
    p.string.scale_x = 1;
    p.string.scale_y = 1;
    p.string.string = (uint8_t*)"1";
    oledC_addShape(LABEL_START_IDX + 6, OLED_SHAPE_STRING, &p);

    // Add separators
    p.circle.color = COLOR_DIM;
    p.circle.xc = START_X + 20;
    p.circle.yc = START_Y + 12;
    p.circle.radius = 1;
    oledC_addShape(SEPARATOR_START_IDX + 0, OLED_SHAPE_CIRCLE, &p);
    p.circle.color = COLOR_DIM;
    p.circle.xc = START_X + 20;
    p.circle.yc = START_Y + 22;
    p.circle.radius = 1;
    oledC_addShape(SEPARATOR_START_IDX + 1, OLED_SHAPE_CIRCLE, &p);
    p.circle.color = COLOR_DIM;
    p.circle.xc = START_X + 45;
    p.circle.yc = START_Y + 12;
    p.circle.radius = 1;
    oledC_addShape(SEPARATOR_START_IDX + 2, OLED_SHAPE_CIRCLE, &p);
    p.circle.color = COLOR_DIM;
    p.circle.xc = START_X + 45;
    p.circle.yc = START_Y + 22;
    p.circle.radius = 1;
    oledC_addShape(SEPARATOR_START_IDX + 3, OLED_SHAPE_CIRCLE, &p);
    
    // Add dot shapes (initially all rings for 00:00:00)
    for(uint8_t col = 0; col < 6; col++) {
        for(uint8_t row = 0; row < 4; row++) {
            uint8_t x = START_X + (col * DOT_SPACING) + (col/2 * 5);
            uint8_t y = START_Y + (row * DOT_SPACING);
            p.ring.color = COLOR_DIM;
            p.ring.x0 = x;
            p.ring.y0 = y;
            p.ring.radius = DOT_SIZE/2;
            p.ring.width = 1;
            oledC_addShape(DOT_START_IDX + col*4 + row, OLED_SHAPE_RING, &p);
        }
    }
    memset(&last_time_drawn, 0, sizeof(Time_t));
    last_time_drawn.second = 99; // force redraw
}

void BinaryFace_Draw(void) {
    oledC_redrawAll();
}

void BinaryFace_DrawUpdate(void) {
    WatchState_t* state = Watch_GetState();
    Time_t now = state->current_time;

    if (state->time_format != last_format_drawn) {
        // Redrawing everything is too complex, just re-init and redraw
        BinaryFace_Init();
        oledC_redrawAll();
        last_format_drawn = state->time_format;
        return;
    }

    uint8_t time_digits[6];
    uint8_t last_time_digits[6];

    uint8_t hour = now.hour;
    uint8_t last_hour = last_time_drawn.hour;
    if (state->time_format == FORMAT_12H) {
        bool is_pm, was_pm;
        hour = Timekeeper_Convert24to12(now.hour, &is_pm);
        last_hour = Timekeeper_Convert24to12(last_time_drawn.hour, &was_pm);
    }
    
    time_digits[0] = hour / 10; time_digits[1] = hour % 10;
    time_digits[2] = now.minute / 10; time_digits[3] = now.minute % 10;
    time_digits[4] = now.second / 10; time_digits[5] = now.second % 10;

    last_time_digits[0] = last_hour / 10; last_time_digits[1] = last_hour % 10;
    last_time_digits[2] = last_time_drawn.minute / 10; last_time_digits[3] = last_time_drawn.minute % 10;
    last_time_digits[4] = last_time_drawn.second / 10; last_time_digits[5] = last_time_drawn.second % 10;

    uint16_t colors[] = {COLOR_PRIMARY, COLOR_PRIMARY, COLOR_SECONDARY, COLOR_SECONDARY, COLOR_ACCENT, COLOR_ACCENT};

    // Iterate through all 24 bits
    for (uint8_t col = 0; col < 6; col++) {
        if (time_digits[col] == last_time_digits[col]) continue;

        for (uint8_t row = 0; row < 4; row++) {
            uint8_t bit_pos = 3 - row;
            bool bit_now = get_bit(time_digits[col], bit_pos);
            bool bit_last = get_bit(last_time_digits[col], bit_pos);

            if (bit_now != bit_last) {
                uint8_t shape_idx = DOT_START_IDX + col * 4 + row;
                uint8_t x = START_X + (col * DOT_SPACING) + (col/2 * 5);
                uint8_t y = START_Y + (row * DOT_SPACING);
                shape_params_t p;
                shape_t* current_shape = oledC_getShape(shape_idx);

                if (bit_now) { // Flipped from 0 to 1
                    p.circle.xc = x;
                    p.circle.yc = y;
                    p.circle.radius = DOT_SIZE/2;
                    p.circle.color = colors[col];
                    oledC_createShape(OLED_SHAPE_CIRCLE, &p, current_shape);
                } else { // Flipped from 1 to 0
                    p.ring.x0 = x;
                    p.ring.y0 = y;
                    p.ring.radius = DOT_SIZE/2;
                    p.ring.width = 1;
                    p.ring.color = COLOR_DIM;
                    oledC_createShape(OLED_SHAPE_RING, &p, current_shape);
                }
                oledC_redrawIndex(shape_idx);
            }
        }
    }
    last_time_drawn = now;
}
