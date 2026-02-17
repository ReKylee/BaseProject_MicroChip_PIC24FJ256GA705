/*
 * Shared text/layout helper utilities for the 96x96 watch UI.
 */

#ifndef UI_LAYOUT_H
#define UI_LAYOUT_H

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Convert character count to pixel width for 6px-wide glyphs.
 * @param chars Number of monospaced characters.
 * @return Width in pixels (chars * 6).
 */
static inline uint8_t WatchUi_CharsToPx6(size_t chars) {
    return (uint8_t)((chars << 2) + (chars << 1));
}

/**
 * @brief Center content horizontally in a given screen width.
 * @param screen_width Total screen width in pixels.
 * @param content_width Content width in pixels.
 * @return Left x position, clamped to 0 if content is wider than screen.
 */
static inline uint8_t WatchUi_CenterX(uint8_t screen_width, uint8_t content_width) {
    if (screen_width <= content_width) {
        return 0U;
    }
    return (uint8_t)((screen_width - content_width) >> 1);
}

/**
 * @brief Center content on the 96px watch display.
 */
static inline uint8_t WatchUi_CenterX96(uint8_t content_width) {
    return WatchUi_CenterX(96U, content_width);
}

/**
 * @brief Right-align content in a given screen width.
 * @param screen_width Total screen width in pixels.
 * @param content_width Content width in pixels.
 * @return Left x position, clamped to 0 if content is wider than screen.
 */
static inline uint8_t WatchUi_RightX(uint8_t screen_width, uint8_t content_width) {
    if (screen_width <= content_width) {
        return 0U;
    }
    return (uint8_t)(screen_width - content_width);
}

/**
 * @brief Right-align content on the 96px watch display.
 */
static inline uint8_t WatchUi_RightX96(uint8_t content_width) {
    return WatchUi_RightX(96U, content_width);
}

#endif // UI_LAYOUT_H
