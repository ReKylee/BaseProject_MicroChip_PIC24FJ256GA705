/*
 * Shared UI widgets for time-like text rendering.
 */

#include "watch_ui_widgets.h"
#include "watch_format.h"
#include "watch_types.h"
#include "ui_layout.h"
#include "../../oledDriver/oledC_shapes.h"

static uint8_t scaled_glyph_w(uint8_t glyph_width, uint8_t scale, uint8_t glyph_gap) {
    return (uint8_t)(glyph_width * scale + glyph_gap);
}

uint8_t WatchUi_GlyphAdvance(uint8_t glyph_width, uint8_t scale, uint8_t glyph_gap) {
    return scaled_glyph_w(glyph_width, scale, glyph_gap);
}

uint8_t WatchUi_TextWidth(uint8_t chars, uint8_t glyph_width, uint8_t scale, uint8_t glyph_gap) {
    return (uint8_t)(chars * scaled_glyph_w(glyph_width, scale, glyph_gap));
}

void WatchUi_ComputeDualTimeLayout(
    uint8_t screen_width,
    uint8_t left_digits,
    uint8_t right_digits,
    uint8_t left_scale,
    uint8_t colon_scale,
    uint8_t right_scale,
    uint8_t glyph_width,
    uint8_t glyph_gap,
    uint8_t inner_gap,
    WatchUi_DualTimeLayout_t* layout
) {
    uint8_t left_step = scaled_glyph_w(glyph_width, left_scale, glyph_gap);
    uint8_t colon_step = scaled_glyph_w(glyph_width, colon_scale, glyph_gap);
    uint8_t right_step = scaled_glyph_w(glyph_width, right_scale, glyph_gap);
    uint8_t left_w = (uint8_t)(left_digits * left_step);
    uint8_t colon_w = colon_step;
    uint8_t right_w = (uint8_t)(right_digits * right_step);

    layout->total_w = (uint8_t)(left_w + colon_w + right_w + (inner_gap << 1));

    layout->left_x = WatchUi_CenterX(screen_width, layout->total_w);
    layout->colon_x = (uint8_t)(layout->left_x + left_w + inner_gap);
    layout->right_x = (uint8_t)(layout->colon_x + colon_w + inner_gap);
}

void WatchUi_DrawNN(
    uint8_t value,
    uint8_t x,
    uint8_t y,
    uint8_t scale_x,
    uint8_t scale_y,
    uint16_t fg,
    uint16_t bg
) {
    char buf[3];
    Watch_Format2D(value, buf);
    oledC_DrawStringSolid(x, y, scale_x, scale_y, (uint8_t*)buf, fg, bg);
}

void WatchUi_DrawColon(
    uint8_t x,
    uint8_t y,
    uint8_t scale_x,
    uint8_t scale_y,
    uint16_t fg,
    uint16_t bg
) {
    oledC_DrawStringSolid(x, y, scale_x, scale_y, (uint8_t*)":", fg, bg);
}
