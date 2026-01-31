#ifndef WATCH_FACE_COMMON_H
#define WATCH_FACE_COMMON_H

#include <stdbool.h>
#include <stdint.h>
#include "../shared/watch_state.h"
#include "../shared/watch_types.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"

// ============================================================================
// COMMON WATCH FACE DRAWING FUNCTIONS
// ============================================================================

/**
 * @brief Draws or erases the alarm icon.
 * @param x X coordinate of the top-left corner.
 * @param y Y coordinate of the top-left corner.
 * @param width Width of the icon.
 * @param height Height of the icon.
 * @param enabled True to draw (COLOR_ACCENT), false to erase (COLOR_BG).
 */
void WatchFace_DrawAlarmIcon(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool enabled);

/**
 * @brief Draws or erases the current date.
 * @param x X coordinate of the top-left corner.
 * @param y Y coordinate of the top-left corner.
 * @param current_date The date to draw.
 * @param last_date_drawn The previously drawn date (for partial erase).
 * @param color The color to draw the date.
 * @param bg_color The background color for erasing.
 */
void WatchFace_DrawDate(uint8_t x, uint8_t y, const Date_t* current_date, Date_t* last_date_drawn, uint16_t color, uint16_t bg_color);


#endif // WATCH_FACE_COMMON_H