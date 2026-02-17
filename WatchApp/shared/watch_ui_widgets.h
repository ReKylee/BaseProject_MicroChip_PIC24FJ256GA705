/*
 * Shared UI widgets for time-like text rendering.
 */

#ifndef WATCH_UI_WIDGETS_H
#define WATCH_UI_WIDGETS_H

#include <stdint.h>

/**
 * @brief X positions for rendering "NN:NN" with mixed scales.
 */
typedef struct {
    /** Left pair start x. */
    uint8_t left_x;
    /** Colon start x. */
    uint8_t colon_x;
    /** Right pair start x. */
    uint8_t right_x;
    /** Total rendered width. */
    uint8_t total_w;
} WatchUi_DualTimeLayout_t;

/**
 * @brief Pixel advance of one glyph at the given scale.
 * @param glyph_width Base glyph width in pixels (usually 5).
 * @param scale Scale multiplier.
 * @param glyph_gap Extra pixels between glyphs.
 * @return Pixel advance for one rendered character cell.
 */
uint8_t WatchUi_GlyphAdvance(uint8_t glyph_width, uint8_t scale, uint8_t glyph_gap);

/**
 * @brief Compute width for monospaced text.
 * @param chars Number of characters.
 * @param glyph_width Base glyph width in pixels (usually 5).
 * @param scale Scale multiplier.
 * @param glyph_gap Extra pixels between glyphs.
 * @return Total width in pixels.
 */
uint8_t WatchUi_TextWidth(uint8_t chars, uint8_t glyph_width, uint8_t scale, uint8_t glyph_gap);

/**
 * @brief Compute centered x positions for "left: right" numeric layout.
 * @param screen_width Target screen width.
 * @param left_digits Number of digits on the left side.
 * @param right_digits Number of digits on the right side.
 * @param left_scale Scale for left digits.
 * @param colon_scale Scale for colon.
 * @param right_scale Scale for right digits.
 * @param glyph_width Base glyph width in pixels (usually 5).
 * @param glyph_gap Extra pixels between glyphs.
 * @param inner_gap Gap around the colon on both sides.
 * @param layout Output structure.
 */
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
);

/**
 * @brief Draw a zero-padded two-digit value.
 * @param value Value to render as "NN".
 * @param x Left x position.
 * @param y Top y position.
 * @param scale_x Horizontal text scale.
 * @param scale_y Vertical text scale.
 * @param fg Foreground color.
 * @param bg Background color.
 */
void WatchUi_DrawNN(
    uint8_t value,
    uint8_t x,
    uint8_t y,
    uint8_t scale_x,
    uint8_t scale_y,
    uint16_t fg,
    uint16_t bg
);

/**
 * @brief Draw a ":" glyph using solid text rendering.
 * @param x Left x position.
 * @param y Top y position.
 * @param scale_x Horizontal text scale.
 * @param scale_y Vertical text scale.
 * @param fg Foreground color.
 * @param bg Background color.
 */
void WatchUi_DrawColon(
    uint8_t x,
    uint8_t y,
    uint8_t scale_x,
    uint8_t scale_y,
    uint16_t fg,
    uint16_t bg
);

#endif // WATCH_UI_WIDGETS_H
