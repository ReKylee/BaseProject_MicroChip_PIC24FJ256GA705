/*
 * digital_face.c
 * Implementation of digital watch face
 */

#include "digital_face.h"
#include "../shared/watch_state.h"
#include "../shared/watch_types.h"
#include "../watchCore/timekeeper.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include <stdio.h>

// ============================================================================
// CONFIGURATION
// ============================================================================

#define DIGIT_SCALE_X   3       // Large digits (3x horizontal)
#define DIGIT_SCALE_Y   4       // Large digits (4x vertical)
#define TIME_Y          30      // Vertical position of time
#define DATE_Y          5       // Vertical position of date
#define AMPM_Y          70      // Vertical position of AM/PM
#define ALARM_ICON_X    2       // Alarm icon position
#define ALARM_ICON_Y    85

// ============================================================================
// PRIVATE FUNCTIONS
// ============================================================================

static void DrawLargeDigit(uint8_t x, uint8_t y, uint8_t digit, uint16_t color) {
    char str[2];
    str[0] = '0' + digit;
    str[1] = '\0';
    oledC_DrawCharacter(x, y, DIGIT_SCALE_X, DIGIT_SCALE_Y, str[0], color);
}

static void DrawColon(uint8_t x, uint8_t y, uint16_t color) {
    oledC_DrawCharacter(x, y, DIGIT_SCALE_X, DIGIT_SCALE_Y, ':', color);
}

static void DrawAlarmIcon(uint16_t color) {
    // Draw simple bell icon (5x5 pixels)
    oledC_DrawRectangle(ALARM_ICON_X, ALARM_ICON_Y, 
                       ALARM_ICON_X + 4, ALARM_ICON_Y + 4, color);
    oledC_DrawPoint(ALARM_ICON_X + 2, ALARM_ICON_Y + 5, color);
}

static void DrawDate(uint8_t day, uint8_t month) {
    char date_str[6];
    sprintf(date_str, "%02d/%02d", day, month);
    oledC_DrawString(70, DATE_Y, 1, 1, (uint8_t*)date_str, COLOR_DIM);
}

static void DrawAMPM(bool is_pm) {
    const char* str = is_pm ? "PM" : "AM";
    oledC_DrawString(70, AMPM_Y, 1, 1, (uint8_t*)str, COLOR_SECONDARY);
}

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void DigitalFace_Init(void) {
    // Nothing to initialize
}

void DigitalFace_Draw(void) {
    WatchState_t* state = Watch_GetState();
    
    // Clear screen
    oledC_setBackground(COLOR_BG);
    
    // Get time
    uint8_t hour = state->current_time.hour;
    uint8_t minute = state->current_time.minute;
    uint8_t second = state->current_time.second;
    
    // Convert to 12h format if needed
    bool is_pm = false;
    if (state->time_format == FORMAT_12H) {
        hour = Timekeeper_Convert24to12(hour, &is_pm);
    }
    
    // Draw time digits (HH:MM:SS)
    uint8_t x = 8;  // Starting X position
    
    // Hours
    DrawLargeDigit(x, TIME_Y, hour / 10, COLOR_PRIMARY);
    x += 18;
    DrawLargeDigit(x, TIME_Y, hour % 10, COLOR_PRIMARY);
    x += 18;
    
    // Colon
    DrawColon(x, TIME_Y, COLOR_PRIMARY);
    x += 12;
    
    // Minutes
    DrawLargeDigit(x, TIME_Y, minute / 10, COLOR_PRIMARY);
    x += 18;
    DrawLargeDigit(x, TIME_Y, minute % 10, COLOR_PRIMARY);
    
    // Small seconds in corner
    char sec_str[3];
    sprintf(sec_str, "%02d", second);
    oledC_DrawString(75, TIME_Y + 20, 1, 1, (uint8_t*)sec_str, COLOR_DIM);
    
    // Draw date
    DrawDate(state->current_date.day, state->current_date.month);
    
    // Draw AM/PM if in 12h mode
    if (state->time_format == FORMAT_12H) {
        DrawAMPM(is_pm);
    }
    
    // Draw alarm icon if enabled
    if (state->alarm.enabled) {
        DrawAlarmIcon(COLOR_ACCENT);
    }
}

void DigitalFace_Update(void) {
    // Just redraw everything
    DigitalFace_Draw();
}
