#include "watch_face_common.h"
#include <stdio.h> // For sprintf

// ============================================================================
// COMMON WATCH FACE DRAWING FUNCTIONS
// ============================================================================

void WatchFace_DrawAlarmIcon(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool enabled) {
    if (enabled) {
        oledC_DrawRectangle(x, y, x + width, y + height, COLOR_ACCENT);
    } else {
        oledC_DrawRectangle(x, y, x + width, y + height, COLOR_BG);
    }
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
