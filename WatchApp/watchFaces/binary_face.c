/*
 * binary_face.c
 * Implementation of binary watch face
 * Format: Each column represents a time component in binary
 *         HH : MM : SS
 *         Each time component split into two 4-bit BCD digits
 */

#include "binary_face.h"
#include "../shared/watch_state.h"
#include "../shared/watch_types.h"
#include "../watchCore/timekeeper.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include <stdio.h>

// ============================================================================
// CONFIGURATION
// ============================================================================

#define DOT_SIZE        6       // Size of each binary dot
#define DOT_SPACING     10      // Spacing between dots
#define COLUMN_SPACING  16      // Spacing between time component columns
#define START_X         12      // Starting X position
#define START_Y         25      // Starting Y position
#define LABEL_Y         75      // Y position for labels

// ============================================================================
// PRIVATE FUNCTIONS
// ============================================================================

static void DrawBinaryDigit(uint8_t x, uint8_t y, uint8_t digit, uint16_t color) {
    // Draw 4 bits vertically (MSB at top)
    for (uint8_t bit = 0; bit < 4; bit++) {
        uint8_t dot_y = y + (bit * DOT_SPACING);
        
        if (digit & (1 << (3 - bit))) {
            // Bit is 1 - draw filled circle
            oledC_DrawCircle(x, dot_y, DOT_SIZE / 2, color);
        } else {
            // Bit is 0 - draw empty ring
            oledC_DrawRing(x, dot_y, DOT_SIZE / 2, 1, COLOR_DIM);
        }
    }
}

static void DrawBinaryPair(uint8_t x, uint8_t y, uint8_t value, uint16_t color) {
    // Split value into two BCD digits and draw them side by side
    uint8_t tens = value / 10;
    uint8_t ones = value % 10;
    
    DrawBinaryDigit(x, y, tens, color);
    DrawBinaryDigit(x + DOT_SPACING, y, ones, color);
}

static void DrawSeparator(uint8_t x, uint8_t y) {
    // Draw two dots as time separator
    oledC_DrawCircle(x, y + 15, 2, COLOR_ACCENT);
    oledC_DrawCircle(x, y + 25, 2, COLOR_ACCENT);
}

static void DrawLabels(void) {
    // Draw time component labels
    oledC_DrawString(START_X + 3, LABEL_Y, 1, 1, (uint8_t*)"H", COLOR_DIM);
    oledC_DrawString(START_X + 33, LABEL_Y, 1, 1, (uint8_t*)"M", COLOR_DIM);
    oledC_DrawString(START_X + 63, LABEL_Y, 1, 1, (uint8_t*)"S", COLOR_DIM);
    
    // Draw bit position labels (8,4,2,1)
    oledC_DrawString(2, START_Y, 1, 1, (uint8_t*)"8", COLOR_DIM);
    oledC_DrawString(2, START_Y + 10, 1, 1, (uint8_t*)"4", COLOR_DIM);
    oledC_DrawString(2, START_Y + 20, 1, 1, (uint8_t*)"2", COLOR_DIM);
    oledC_DrawString(2, START_Y + 30, 1, 1, (uint8_t*)"1", COLOR_DIM);
}

static void DrawDateAndAlarm(void) {
    WatchState_t* state = Watch_GetState();
    
    // Draw date
    char date_str[6];
    sprintf(date_str, "%02d/%02d", state->current_date.day, state->current_date.month);
    oledC_DrawString(55, 5, 1, 1, (uint8_t*)date_str, COLOR_DIM);
    
    // Draw alarm icon if enabled
    if (state->alarm.enabled) {
        oledC_DrawRectangle(2, 5, 6, 10, COLOR_ACCENT);
    }
    
    // Draw format indicator
    if (state->time_format == FORMAT_12H) {
        bool is_pm;
        Timekeeper_Convert24to12(state->current_time.hour, &is_pm);
        const char* ampm = is_pm ? "PM" : "AM";
        oledC_DrawString(10, 5, 1, 1, (uint8_t*)ampm, COLOR_SECONDARY);
    }
}

// ============================================================================
// PUBLIC FUNCTIONS
// ============================================================================

void BinaryFace_Init(void) {
    // Nothing to initialize
}

void BinaryFace_Draw(void) {
    WatchState_t* state = Watch_GetState();
    
    // Clear screen
    oledC_setBackground(COLOR_BG);
    
    // Get time
    uint8_t hour = state->current_time.hour;
    uint8_t minute = state->current_time.minute;
    uint8_t second = state->current_time.second;
    
    // Convert to 12h if needed
    if (state->time_format == FORMAT_12H) {
        bool is_pm;
        hour = Timekeeper_Convert24to12(hour, &is_pm);
    }
    
    // Draw binary representation
    uint8_t x = START_X;
    
    // Hours (in cyan)
    DrawBinaryPair(x, START_Y, hour, COLOR_PRIMARY);
    x += COLUMN_SPACING + 4;
    
    // Separator
    DrawSeparator(x, START_Y);
    x += 8;
    
    // Minutes (in orange)
    DrawBinaryPair(x, START_Y, minute, COLOR_SECONDARY);
    x += COLUMN_SPACING + 4;
    
    // Separator
    DrawSeparator(x, START_Y);
    x += 8;
    
    // Seconds (in magenta)
    DrawBinaryPair(x, START_Y, second, COLOR_ACCENT);
    
    // Draw labels
    DrawLabels();
    
    // Draw date and alarm
    DrawDateAndAlarm();
}

void BinaryFace_Update(void) {
    // Redraw everything (binary display is compact)
    BinaryFace_Draw();
}
