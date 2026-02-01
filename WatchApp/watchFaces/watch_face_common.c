#include "watch_face_common.h"
#include <stdio.h> // For sprintf

// ============================================================================
// COMMON WATCH FACE DRAWING FUNCTIONS
// ============================================================================

void WatchFace_DrawAlarmIcon(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool enabled) {
    uint16_t color = enabled ? COLOR_ACCENT : COLOR_BG;
    uint8_t w = (width < 9) ? 9 : width;
    uint8_t h = (height < 9) ? 9 : height;
    uint8_t cx = x + w / 2;
    uint8_t cy = y + h / 2;
    (void)w;
    (void)h;

    // Clear area
    oledC_DrawRectangle(x, y, x + w, y + h, COLOR_BG);

    // If disabled, just clear the area.
    if (!enabled) return;

    // Small clock icon: filled face with bg-color hands (12 and 3)
    oledC_DrawCircle(cx, cy, 6, color);
    oledC_DrawLine(cx, (uint8_t)(cy - 5), cx, (uint8_t)(cy - 1), 1, COLOR_BG);
    oledC_DrawLine((uint8_t)(cx + 1), cy, (uint8_t)(cx + 5), cy, 1, COLOR_BG);
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
