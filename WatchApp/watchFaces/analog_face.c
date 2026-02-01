/*
 * analog_face.c
 * Optimized analog watch face with fully precomputed geometry
 * Immediate-mode drawing, minimal runtime math
 */

#include "analog_face.h"
#include "watch_face_geometry.h"
#include "watch_face_common.h"
#include "../shared/watch_state.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include <stdio.h>
#include <string.h>

// ============================================================================
// CONFIGURATION
// ============================================================================



#define HOUR_LEN  20
#define MIN_LEN   32
#define SEC_LEN   38

// Marker widths for main (3,6,9,12) vs minor markers
#define MARKER_MAJOR_WIDTH  3
#define MARKER_MINOR_WIDTH  1

// Date position
// #define DATE_X  2
// #define DATE_Y  5

// Alarm icon position
// #define ALARM_X  88
// #define ALARM_Y  5
// #define ALARM_W  5
// #define ALARM_H  5

// Center dot
#define CENTER_DOT_RADIUS  2

// ============================================================================
// STATE
// ============================================================================

static uint8_t s_last_hour = 255;
static uint8_t s_last_min = 255;
static uint8_t s_last_sec = 255;
static Date_t s_last_date_drawn;

// Draw clock hands (erase previous, draw new)

static void draw_markers(void) {
    for (uint8_t i = 0; i < 12; i++) {
        uint8_t idx = i * 5;
        uint8_t width = (i == 0 || i == 3 || i == 6 || i == 9) ? MARKER_MAJOR_WIDTH : MARKER_MINOR_WIDTH;
        oledC_DrawLine(HOUR_POINTS[idx][0], HOUR_POINTS[idx][1],
                MIN_POINTS[idx][0], MIN_POINTS[idx][1],
                width,
                COLOR_DIM);
    }
    oledC_DrawRing(CENTER_X, CENTER_Y, RADIUS, 1, COLOR_DIM);
}

static void draw_hands(uint8_t hour, uint8_t min, uint8_t sec) {
    // Erase previous hands
    if (s_last_hour != 255)
        oledC_DrawLine(CENTER_X, CENTER_Y, HOUR_POINTS[s_last_hour][0], HOUR_POINTS[s_last_hour][1], 3, COLOR_BG);
    if (s_last_min != 255)
        oledC_DrawLine(CENTER_X, CENTER_Y, MIN_POINTS[s_last_min][0], MIN_POINTS[s_last_min][1], 2, COLOR_BG);
    if (s_last_sec != 255)
        oledC_DrawLine(CENTER_X, CENTER_Y, SEC_POINTS[s_last_sec][0], SEC_POINTS[s_last_sec][1], 1, COLOR_BG);

    // Restore markers and ring after erasing
    draw_markers();

    // Draw current hands (always)
    oledC_DrawLine(CENTER_X, CENTER_Y, HOUR_POINTS[hour][0], HOUR_POINTS[hour][1], 3, COLOR_SECONDARY);
    oledC_DrawLine(CENTER_X, CENTER_Y, MIN_POINTS[min][0], MIN_POINTS[min][1], 2, COLOR_PRIMARY);
    oledC_DrawLine(CENTER_X, CENTER_Y, SEC_POINTS[sec][0], SEC_POINTS[sec][1], 1, COLOR_ACCENT);

    // Redraw center dot to hide joins
    oledC_DrawCircle(CENTER_X, CENTER_Y, CENTER_DOT_RADIUS, COLOR_ACCENT);

    // Update last state
    s_last_hour = hour;
    s_last_min = min;
    s_last_sec = sec;
}

// ============================================================================
// PUBLIC API
// ============================================================================

void AnalogFace_Init(void) {
    oledC_setBackground(COLOR_BG);
    memset(&s_last_date_drawn, 0, sizeof(Date_t)); // Initialize last_date_drawn

    draw_markers();

    // Date - Initial draw
    WatchState_t* state = Watch_GetState();
    WatchFace_DrawDate(DATE_X, DATE_Y, &state->current_date, &s_last_date_drawn, COLOR_DIM, COLOR_BG);

    // Reset hand state
    s_last_hour = s_last_min = s_last_sec = 255;
}

void AnalogFace_DrawUpdate(void) {
    WatchState_t* s = Watch_GetState();

    uint8_t sec = s->current_time.second;
    uint8_t min = s->current_time.minute;
    uint8_t hour = (s->current_time.hour % 12) * 5 + min / 12;

    draw_hands(hour, min, sec);
    WatchFace_DrawAlarmIcon(ALARM_X, ALARM_Y, ALARM_W, ALARM_H, s->alarm.enabled);
    WatchFace_DrawDate(DATE_X, DATE_Y, &s->current_date, &s_last_date_drawn, COLOR_DIM, COLOR_BG);
}

void AnalogFace_Draw(void) {
    AnalogFace_DrawUpdate();
}
