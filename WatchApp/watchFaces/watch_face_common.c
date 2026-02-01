#include "watch_face_common.h"
#include <stdio.h> // For sprintf

// ============================================================================
// COMMON WATCH FACE DRAWING FUNCTIONS
// ============================================================================

void WatchFace_DrawAlarmIcon(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool enabled) {
    uint16_t color = enabled ? COLOR_ACCENT : COLOR_BG;
    uint8_t w = (width < 5) ? 5 : width;
    uint8_t h = (height < 5) ? 5 : height;
    uint8_t cx = x + w / 2;
    uint8_t cy = y + h / 2;
    uint8_t r = (w < h ? w : h) / 2 - 1;

    // Clear area
    oledC_DrawRectangle(x, y, x + w, y + h, COLOR_BG);

    // Bell dome
    oledC_DrawRing(cx, cy, r, 1, color);
    // Clapper
    oledC_DrawPoint(cx, y + h - 1, color);
    // Feet
    oledC_DrawPoint(x + 1, y + h - 2, color);
    oledC_DrawPoint(x + w - 1, y + h - 2, color);
    // Ears
    oledC_DrawPoint(x + 1, y + 1, color);
    oledC_DrawPoint(x + w - 1, y + 1, color);
}

void WatchFace_DrawDate(uint8_t x, uint8_t y, const Date_t* current_date, Date_t* last_date_drawn, uint16_t color, uint16_t bg_color) {
    // Only redraw if date has changed
    if (current_date->day != last_date_drawn->day || current_date->month != last_date_drawn->month) {
        char buf[6];
        
        // Erase previous date
        sprintf(buf, "%02d/%02d", last_date_drawn->day, last_date_drawn->month);
        oledC_DrawString(x, y, 1, 1, (uint8_t*)buf, bg_color);
        
        // Draw new date
        sprintf(buf, "%02d/%02d", current_date->day, current_date->month);
        oledC_DrawString(x, y, 1, 1, (uint8_t*)buf, color);
        
        *last_date_drawn = *current_date; // Update last drawn date
    }
}
