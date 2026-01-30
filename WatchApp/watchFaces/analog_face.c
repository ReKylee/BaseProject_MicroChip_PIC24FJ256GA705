/*
 * analog_face.c
 * Analog watch face using a single precalculated 60-point direction table
 */

#include "analog_face.h"
#include "../shared/watch_state.h"
#include "../shared/watch_types.h"
#include "../watchCore/timekeeper.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include <stdio.h>

// ============================================================================
// CONFIGURATION
// ============================================================================

#define CENTER_X        48
#define CENTER_Y        48
#define RADIUS          40

#define HOUR_HAND_LEN   20
#define MIN_HAND_LEN    32
#define SEC_HAND_LEN    38

#define HOUR_HAND_WIDTH 3
#define MIN_HAND_WIDTH  2
#define SEC_HAND_WIDTH  1

// ============================================================================
// PRECALCULATED 60-POINT UNIT CIRCLE (×100 FIXED POINT)
// 0 = 12 o'clock, clockwise
// ============================================================================

typedef struct {
    int8_t x;
    int8_t y;
} Vec2_t;

static const Vec2_t dir60[60] = {
    {  0, -100 }, { 10, -99 }, { 21, -98 }, { 31, -95 }, { 41, -91 },
    { 50, -87 },  { 59, -81 }, { 67, -74 }, { 74, -67 }, { 81, -59 },
    { 87, -50 },  { 91, -41 }, { 95, -31 }, { 98, -21 }, { 99, -10 },
    {100,   0  },
    { 99,  10 },  { 98,  21 }, { 95,  31 }, { 91,  41 },
    { 87,  50 },  { 81,  59 }, { 74,  67 }, { 67,  74 },
    { 59,  81 },  { 50,  87 }, { 41,  91 }, { 31,  95 },
    { 21,  98 },  { 10,  99 },
    {  0, 100 },  { -10, 99 }, { -21, 98 }, { -31, 95 },
    { -41, 91 },  { -50, 87 }, { -59, 81 }, { -67, 74 },
    { -74, 67 },  { -81, 59 }, { -87, 50 }, { -91, 41 },
    { -95, 31 },  { -98, 21 }, { -99, 10 },
    {-100,  0 },  { -99,-10 }, { -98,-21 }, { -95,-31 },
    { -91,-41 },  { -87,-50 }, { -81,-59 }, { -74,-67 },
    { -67,-74 },  { -59,-81 }, { -50,-87 }, { -41,-91 }
};

// ============================================================================
// STATE
// ============================================================================

static uint8_t last_hour_pos = 255;
static uint8_t last_min_pos  = 255;
static uint8_t last_sec_pos  = 255;

// ============================================================================
// DRAW HELPERS
// ============================================================================

static inline void DrawScaledLine(
    uint8_t pos,
    uint8_t length,
    uint8_t width,
    uint16_t color
) {
    if (pos >= 60) return;

    int16_t x = CENTER_X + (length * dir60[pos].x) / 100;
    int16_t y = CENTER_Y + (length * dir60[pos].y) / 100;

    oledC_DrawLine(CENTER_X, CENTER_Y, x, y, width, color);
}

static inline void EraseScaledLine(uint8_t pos, uint8_t length, uint8_t width) {
    DrawScaledLine(pos, length, width, COLOR_BG);
}

static void DrawHourMarkers(void) {
    for (uint8_t i = 0; i < 60; i += 5) {

        int16_t x_outer = CENTER_X + (RADIUS * dir60[i].x) / 100;
        int16_t y_outer = CENTER_Y + (RADIUS * dir60[i].y) / 100;

        int16_t x_inner = CENTER_X + (RADIUS * 9 * dir60[i].x) / 1000;
        int16_t y_inner = CENTER_Y + (RADIUS * 9 * dir60[i].y) / 1000;

        oledC_DrawLine(x_inner, y_inner, x_outer, y_outer, 2, COLOR_PRIMARY);
    }
}

static void DrawCenterDot(void) {
    oledC_DrawCircle(CENTER_X, CENTER_Y, 2, COLOR_ACCENT);
}

static void DrawDateAndAlarm(void) {
    WatchState_t* state = Watch_GetState();

    char date_str[6];
    sprintf(date_str, "%02d/%02d",
            state->current_date.day,
            state->current_date.month);

    oledC_DrawString(60, 5, 1, 1, (uint8_t*)date_str, COLOR_DIM);

    bool is_pm;
    Timekeeper_Convert24to12(state->current_time.hour, &is_pm);
    oledC_DrawString(65, 85, 1, 1,
        (uint8_t*)(is_pm ? "PM" : "AM"),
        COLOR_SECONDARY);

    if (state->alarm.enabled) {
        oledC_DrawRectangle(2, 85, 6, 90, COLOR_ACCENT);
    }
}

// ============================================================================
// PUBLIC API
// ============================================================================

void AnalogFace_Init(void) {
    last_hour_pos = last_min_pos = last_sec_pos = 255;
}

void AnalogFace_Draw(void) {
    WatchState_t* state = Watch_GetState();

    oledC_setBackground(COLOR_BG);
    oledC_DrawRing(CENTER_X, CENTER_Y, RADIUS, 1, COLOR_PRIMARY);

    DrawHourMarkers();

    uint8_t sec_pos  = state->current_time.second;
    uint8_t min_pos  = state->current_time.minute;
    uint8_t hour_pos = (state->current_time.hour % 12) * 5 + (min_pos / 12);

    DrawScaledLine(hour_pos, HOUR_HAND_LEN, HOUR_HAND_WIDTH, COLOR_SECONDARY);
    DrawScaledLine(min_pos,  MIN_HAND_LEN,  MIN_HAND_WIDTH,  COLOR_PRIMARY);
    DrawScaledLine(sec_pos,  SEC_HAND_LEN,  SEC_HAND_WIDTH,  COLOR_ACCENT);

    DrawCenterDot();
    DrawDateAndAlarm();

    last_hour_pos = hour_pos;
    last_min_pos  = min_pos;
    last_sec_pos  = sec_pos;
}

void AnalogFace_Update(void) {
    WatchState_t* state = Watch_GetState();

    uint8_t sec_pos  = state->current_time.second;
    uint8_t min_pos  = state->current_time.minute;
    uint8_t hour_pos = (state->current_time.hour % 12) * 5 + (min_pos / 12);

    if (last_sec_pos != 255) {
        EraseScaledLine(last_sec_pos, SEC_HAND_LEN, SEC_HAND_WIDTH);
    }

    if (min_pos != last_min_pos && last_min_pos != 255) {

        EraseScaledLine(last_min_pos,  MIN_HAND_LEN,  MIN_HAND_WIDTH);
        EraseScaledLine(last_hour_pos, HOUR_HAND_LEN, HOUR_HAND_WIDTH);

        DrawScaledLine(hour_pos, HOUR_HAND_LEN, HOUR_HAND_WIDTH, COLOR_SECONDARY);
        DrawScaledLine(min_pos,  MIN_HAND_LEN,  MIN_HAND_WIDTH,  COLOR_PRIMARY);
    }

    DrawScaledLine(sec_pos, SEC_HAND_LEN, SEC_HAND_WIDTH, COLOR_ACCENT);

    DrawCenterDot();
    DrawDateAndAlarm();

    last_hour_pos = hour_pos;
    last_min_pos  = min_pos;
    last_sec_pos  = sec_pos;
}
