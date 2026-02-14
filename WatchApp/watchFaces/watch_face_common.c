/*
 * Shared drawing helpers used by multiple watch faces.
 */

#include "watch_face_common.h"
#include "../watchMenu/menu_icons.h"

// ============================================================================
// SHARED DRAW HELPERS
// ============================================================================

void WatchFace_DrawAlarmIcon(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool enabled) {
    uint16_t palette[4];
    (void)width;
    (void)height;

    if (enabled) {
        palette[0] = COLOR_BG;
        palette[1] = s_asset_alarm_indicator.palette[1];
        palette[2] = s_asset_alarm_indicator.palette[2];
        palette[3] = s_asset_alarm_indicator.palette[3];
    } else {
        palette[0] = COLOR_BG;
        palette[1] = COLOR_BG;
        palette[2] = COLOR_BG;
        palette[3] = COLOR_BG;
    }

    oledC_DrawBitmapIndexed2bpp(x, y, ALARM_W, ALARM_H, s_asset_alarm_indicator.pixels, palette);
}

void WatchFace_DrawDate(uint8_t x, uint8_t y, const Date_t* current_date, Date_t* last_date_drawn, uint16_t color, uint16_t bg_color) {
    if (current_date->day != last_date_drawn->day || current_date->month != last_date_drawn->month) {
        char buf[6];
        Watch_FormatDateDDMM(current_date, buf);
        oledC_DrawStringSolid(x, y, 1, 1, (uint8_t*)buf, color, bg_color);
        
        *last_date_drawn = *current_date;
    }
}
