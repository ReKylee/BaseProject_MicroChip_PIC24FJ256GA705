/*
 * analog_face.c
 * Optimized analog watch face with fully precomputed geometry
 * Immediate-mode drawing, minimal runtime math
 */

#include "analog_face.h"
#include "../shared/watch_state.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include <stdio.h>
#include <string.h>





// ============================================================================
// CONFIGURATION
// ============================================================================

#define CENTER_X  47
#define CENTER_Y  47
#define RADIUS    40

#define HOUR_LEN  20
#define MIN_LEN   32
#define SEC_LEN   38

// Marker widths for main (3,6,9,12) vs minor markers
#define MARKER_MAJOR_WIDTH  3
#define MARKER_MINOR_WIDTH  2

// Date position
#define DATE_X  2
#define DATE_Y  5

// Alarm icon position
#define ALARM_X  88
#define ALARM_Y  5
#define ALARM_W  5
#define ALARM_H  5

// Center dot
#define CENTER_DOT_RADIUS  2

// ============================================================================
// PRECOMPUTED HAND ENDPOINTS (absolute screen coordinates)
// ============================================================================

// ============================================================================
// PRECOMPUTED HAND ENDPOINTS (ABSOLUTE SCREEN COORDINATES)
// ============================================================================

static const int8_t hour_pt[60][2] = {
    {47, 27},
    {49, 27},
    {51, 27},
    {53, 28},
    {55, 29},
    {57, 30},
    {59, 31},
    {60, 32},
    {62, 34},
    {63, 35},
    {64, 37},
    {65, 39},
    {66, 41},
    {67, 43},
    {67, 45},
    {67, 47},
    {67, 49},
    {66, 51},
    {65, 53},
    {64, 55},
    {63, 57},
    {62, 59},
    {60, 60},
    {59, 62},
    {57, 63},
    {55, 64},
    {53, 65},
    {51, 66},
    {49, 67},
    {47, 67},
    {45, 67},
    {43, 66},
    {41, 65},
    {39, 64},
    {37, 63},
    {35, 62},
    {34, 60},
    {32, 59},
    {31, 57},
    {30, 55},
    {29, 53},
    {28, 51},
    {27, 49},
    {27, 47},
    {27, 45},
    {28, 43},
    {29, 41},
    {30, 39},
    {31, 37},
    {32, 35},
    {34, 34},
    {35, 32},
    {37, 31},
    {39, 30},
    {41, 29},
    {43, 28},
    {45, 27}
};


static const int8_t min_pt[60][2] = {
    {47, 15},
    {50, 15},
    {53, 16},
    {56, 17},
    {59, 18},
    {62, 20},
    {65, 22},
    {68, 24},
    {71, 27},
    {73, 29},
    {75, 32},
    {77, 35},
    {78, 38},
    {79, 41},
    {79, 44},
    {79, 47},
    {79, 50},
    {78, 53},
    {77, 56},
    {75, 59},
    {73, 62},
    {71, 65},
    {68, 68},
    {65, 71},
    {62, 73},
    {59, 75},
    {56, 77},
    {53, 78},
    {50, 79},
    {47, 79},
    {44, 79},
    {41, 78},
    {38, 77},
    {35, 75},
    {32, 73},
    {29, 71},
    {26, 68},
    {24, 65},
    {22, 62},
    {20, 59},
    {18, 56},
    {17, 53},
    {16, 50},
    {15, 47},
    {15, 44},
    {16, 41},
    {17, 38},
    {18, 35},
    {20, 32},
    {22, 29},
    {24, 27},
    {26, 24},
    {29, 22},
    {32, 20},
    {35, 18},
    {38, 17},
    {41, 16},
    {44, 15}
};


static const int8_t sec_pt[60][2] = {
    {47, 9},
    {51, 10},
    {55, 12},
    {59, 15},
    {63, 18},
    {67, 22},
    {70, 26},
    {73, 30},
    {76, 34},
    {78, 39},
    {80, 43},
    {82, 47},
    {80, 51},
    {78, 55},
    {76, 60},
    {73, 64},
    {70, 68},
    {67, 72},
    {63, 76},
    {59, 79},
    {55, 82},
    {51, 84},
    {47, 85},
    {43, 84},
    {39, 82},
    {35, 79},
    {31, 76},
    {27, 72},
    {24, 68},
    {21, 64},
    {18, 60},
    {16, 55},
    {14, 51},
    {12, 47},
    {14, 43},
    {16, 39},
    {18, 34},
    {21, 30},
    {24, 26},
    {27, 22},
    {31, 18},
    {35, 15},
    {39, 12},
    {43, 10},
    {47, 9},
    {51, 10},
    {55, 12},
    {59, 15},
    {63, 18},
    {67, 22},
    {70, 26},
    {73, 30},
    {76, 34},
    {78, 39},
    {80, 43},
    {82, 47}
};

// ============================================================================
// STATE
// ============================================================================

static uint8_t last_hour = 255;
static uint8_t last_min = 255;
static uint8_t last_sec = 255;
static bool last_alarm = false;
static uint8_t last_day = 255;
static uint8_t last_month = 255;

// Temporary buffer for date string
static char date_buf[6];


// ============================================================================
// INTERNAL HELPERS
// ============================================================================

static void DrawAlarmIcon(bool enabled) {
    if (enabled != last_alarm) {
        if (!enabled)
            oledC_DrawRectangle(ALARM_X, ALARM_Y, ALARM_W, ALARM_H, COLOR_BG);
        else
            oledC_DrawRectangle(ALARM_X, ALARM_Y, ALARM_X + ALARM_W, ALARM_Y + ALARM_H, COLOR_ACCENT);
        last_alarm = enabled;
    }
}

static void DrawDate(Date_t current_date) {
    if (current_date.day != last_day || current_date.month != last_month) {
        sprintf(date_buf, "%02d/%02d", current_date.day, current_date.month);

        // Erase previous date
        oledC_DrawRectangle(DATE_X, DATE_Y, DATE_X + 34, DATE_Y + 8, COLOR_BG);

        oledC_DrawString(DATE_X, DATE_Y, 1, 1, (uint8_t*) date_buf, COLOR_DIM);

        last_day = current_date.day;
        last_month = current_date.month;
    }
}

// Draw clock hands (erase previous, draw new)

static void DrawHands(uint8_t hour, uint8_t min, uint8_t sec) {
    // Erase old hands
    if (last_hour != 255 && hour != last_hour)
        oledC_DrawLine(CENTER_X, CENTER_Y, hour_pt[last_hour][0], hour_pt[last_hour][1], 3, COLOR_BG);
    if (last_min != 255 && min != last_min)
        oledC_DrawLine(CENTER_X, CENTER_Y, min_pt[last_min][0], min_pt[last_min][1], 2, COLOR_BG);
    if (last_sec != 255 && sec != last_sec)
        oledC_DrawLine(CENTER_X, CENTER_Y, sec_pt[last_sec][0], sec_pt[last_sec][1], 1, COLOR_BG);

    // Draw new hands
    if (hour != last_hour)
        oledC_DrawLine(CENTER_X, CENTER_Y, hour_pt[hour][0], hour_pt[hour][1], 3, COLOR_SECONDARY);
    if (min != last_min)
        oledC_DrawLine(CENTER_X, CENTER_Y, min_pt[min][0], min_pt[min][1], 2, COLOR_PRIMARY);
    if (sec != last_sec)
        oledC_DrawLine(CENTER_X, CENTER_Y, sec_pt[sec][0], sec_pt[sec][1], 1, COLOR_ACCENT);

    // Redraw center dot to hide joins
    oledC_DrawCircle(CENTER_X, CENTER_Y, CENTER_DOT_RADIUS, COLOR_ACCENT);

    // Update last state
    last_hour = hour;
    last_min = min;
    last_sec = sec;
}

// ============================================================================
// PUBLIC API
// ============================================================================

void AnalogFace_Init(void) {
    oledC_setBackground(COLOR_BG);

    // Outer ring
    oledC_DrawRing(CENTER_X, CENTER_Y, RADIUS, 1, COLOR_PRIMARY);

    // Hour markers
    for (uint8_t i = 0; i < 12; i++) {
        uint8_t idx = i * 5;
        uint8_t width = (i == 0 || i == 3 || i == 6 || i == 9) ? MARKER_MAJOR_WIDTH : MARKER_MINOR_WIDTH;

        oledC_DrawLine(hour_pt[idx][0], hour_pt[idx][1],
                min_pt[idx][0], min_pt[idx][1],
                width,
                COLOR_PRIMARY);
    }

    // Date
    oledC_DrawString(DATE_X, DATE_Y, 1, 1, (uint8_t*) date_buf, COLOR_DIM);

    // Center dot
    oledC_DrawCircle(CENTER_X, CENTER_Y, CENTER_DOT_RADIUS, COLOR_ACCENT);

    // Reset hand state
    last_hour = last_min = last_sec = 255;
}

void AnalogFace_DrawUpdate(void) {
    WatchState_t* s = Watch_GetState();

    uint8_t sec = s->current_time.second;
    uint8_t min = s->current_time.minute;
    uint8_t hour = (s->current_time.hour % 12) * 5 + min / 12;

    DrawHands(hour, min, sec);
    DrawAlarmIcon(s->alarm.enabled);
    DrawDate(s->current_date);
}

void AnalogFace_Draw(void) {
    AnalogFace_DrawUpdate();
}
