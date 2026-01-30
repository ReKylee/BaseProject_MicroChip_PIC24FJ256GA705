/*
 * analog_face.c
 * Analog watch face using the oledC shape handler.
 */

#include "analog_face.h"
#include "../shared/watch_state.h"
#include "../shared/watch_types.h"
#include "../watchCore/timekeeper.h"
#include "../../oledDriver/oledC.h"
#include "../../oledDriver/oledC_shapes.h"
#include "../../oledDriver/oledC_shapeHandler.h"
#include <stdio.h>
#include <string.h>

// ============================================================================
// CONFIGURATION & SHAPE INDICES
// ============================================================================

#define CENTER_X        47
#define CENTER_Y        47
#define RADIUS          40
#define HOUR_HAND_LEN   20
#define MIN_HAND_LEN    32
#define SEC_HAND_LEN    38

// Shape indices for the oledC_shapeHandler
#define ANALOG_SHAPE_START_IDX  0
#define RING_IDX                (ANALOG_SHAPE_START_IDX + 0)
#define MARKER_START_IDX        (ANALOG_SHAPE_START_IDX + 1) // Uses 12 indices
#define DATE_STR_IDX            (ANALOG_SHAPE_START_IDX + 13)
#define ALARM_ICON_IDX          (ANALOG_SHAPE_START_IDX + 14)
#define HOUR_HAND_IDX           (ANALOG_SHAPE_START_IDX + 15)
#define MIN_HAND_IDX            (ANALOG_SHAPE_START_IDX + 16)
#define SEC_HAND_IDX            (ANALOG_SHAPE_START_IDX + 17)
#define CENTER_DOT_IDX          (ANALOG_SHAPE_START_IDX + 18)
#define ANALOG_SHAPE_COUNT      19

// ============================================================================
// PRECALCULATED UNIT CIRCLE & STATE
// ============================================================================

typedef struct { int8_t x; int8_t y; } Vec2_t;
static const Vec2_t dir60[60] = {
    {  0, -100 }, { 10, -99 }, { 21, -98 }, { 31, -95 }, { 41, -91 },
    { 50, -87 },  { 59, -81 }, { 67, -74 }, { 74, -67 }, { 81, -59 },
    { 87, -50 },  { 91, -41 }, { 95, -31 }, { 98, -21 }, { 99, -10 },
    {100,   0  }, { 99,  10 }, { 98,  21 }, { 95,  31 }, { 91,  41 },
    { 87,  50 },  { 81,  59 }, { 74,  67 }, { 67,  74 }, { 59,  81 },
    { 50,  87 },  { 41,  91 }, { 31,  95 }, { 21,  98 }, { 10,  99 },
    {  0, 100 },  { -10, 99 }, { -21, 98 }, { -31, 95 }, { -41, 91 },
    { -50, 87 }, { -59, 81 }, { -67, 74 }, { -74, 67 }, { -81, 59 },
    { -87, 50 }, { -91, 41 }, { -95, 31 }, { -98, 21 }, { -99, 10 },
    {-100,  0 },  { -99,-10 }, { -98,-21 }, { -95,-31 }, { -91,-41 },
    { -87,-50 }, { -81,-59 }, { -74,-67 }, { -67,-74 }, { -59,-81 },
    { -50,-87 }, { -41,-91 }
};

static Date_t last_date_drawn;
static bool last_alarm_drawn = false;
static char date_str_buffer[6];

// ============================================================================
// PUBLIC API
// ============================================================================

void AnalogFace_Init(void) {
    // Clear shape memory and add all shapes for this face
    initShapesMem();
    
    shape_params_t p;

    // Add outer ring
    p.ring.color = COLOR_PRIMARY;
    p.ring.x0 = CENTER_X;
    p.ring.y0 = CENTER_Y;
    p.ring.radius = RADIUS;
    p.ring.width = 1;
    oledC_addShape(RING_IDX, OLED_SHAPE_RING, &p);

    // Add 12 hour markers
    for (uint8_t i = 0; i < 12; i++) {
        uint8_t pos = i * 5;
                        p.line.color = COLOR_PRIMARY;
                        p.line.xs = CENTER_X + ((RADIUS - 4) * dir60[pos].x) / 100;
                        p.line.ys = CENTER_Y + ((RADIUS - 4) * dir60[pos].y) / 100;
                        p.line.width = 2;
                        p.line.xe = CENTER_X + (RADIUS * dir60[pos].x) / 100;
                        p.line.ye = CENTER_Y + (RADIUS * dir60[pos].y) / 100;        oledC_addShape(MARKER_START_IDX + i, OLED_SHAPE_LINE, &p);
    }
    
    // Add text/icon shapes (initially inactive/blank)
    p.string.color = COLOR_DIM;
    p.string.x = 2;
    p.string.y = 5;
    p.string.scale_x = 1;
    p.string.scale_y = 1;
    p.string.string = (uint8_t*)date_str_buffer;
    oledC_addShape(DATE_STR_IDX, OLED_SHAPE_STRING, &p);
    p.rectangle.color = COLOR_ACCENT;
    p.rectangle.xs = 88;
    p.rectangle.ys = 5;
    p.rectangle.xe = 93;
    p.rectangle.ye = 10;
    oledC_addShape(ALARM_ICON_IDX, OLED_SHAPE_RECTANGLE, &p);
    oledC_getShape(ALARM_ICON_IDX)->active = false; // Hide alarm icon initially

    // Add hand shapes
    p.line.color = COLOR_SECONDARY;
    p.line.xs = CENTER_X;
    p.line.ys = CENTER_Y;
    p.line.width = 3;
    p.line.xe = CENTER_X;
    p.line.ye = CENTER_Y;
    oledC_addShape(HOUR_HAND_IDX, OLED_SHAPE_LINE, &p);
    p.line.color = COLOR_PRIMARY;
    p.line.xs = CENTER_X;
    p.line.ys = CENTER_Y;
    p.line.width = 2;
    p.line.xe = CENTER_X;
    p.line.ye = CENTER_Y;
    oledC_addShape(MIN_HAND_IDX, OLED_SHAPE_LINE, &p);
    p.line.color = COLOR_ACCENT;
    p.line.xs = CENTER_X;
    p.line.ys = CENTER_Y;
    p.line.width = 1;
    p.line.xe = CENTER_X;
    p.line.ye = CENTER_Y;
    oledC_addShape(SEC_HAND_IDX, OLED_SHAPE_LINE, &p);
    
    // Add center dot
    p.circle.color = COLOR_ACCENT;
    p.circle.xc = CENTER_X;
    p.circle.yc = CENTER_Y;
    p.circle.radius = 2;
    oledC_addShape(CENTER_DOT_IDX, OLED_SHAPE_CIRCLE, &p);
}

void AnalogFace_Draw(void) {
    // A full draw involves updating all dynamic shapes and then redrawing everything
    AnalogFace_DrawUpdate();
    oledC_redrawAll();
}

void AnalogFace_DrawUpdate(void) {
    WatchState_t* state = Watch_GetState();
    
    // Update Date/Alarm if needed
    if (state->current_date.day != last_date_drawn.day || state->alarm.enabled != last_alarm_drawn) {
        oledC_eraseShape(DATE_STR_IDX, COLOR_BG);
        sprintf(date_str_buffer, "%02d/%02d", state->current_date.day, state->current_date.month);
        last_date_drawn = state->current_date;
        
        oledC_getShape(ALARM_ICON_IDX)->active = state->alarm.enabled;
        if(!state->alarm.enabled) oledC_eraseShape(ALARM_ICON_IDX, COLOR_BG);
        last_alarm_drawn = state->alarm.enabled;

        oledC_redrawIndex(DATE_STR_IDX);
        oledC_redrawIndex(ALARM_ICON_IDX);
    }
    


    // Get shape pointers
    shape_t* hour_hand = oledC_getShape(HOUR_HAND_IDX);
    shape_t* min_hand = oledC_getShape(MIN_HAND_IDX);
    shape_t* sec_hand = oledC_getShape(SEC_HAND_IDX);

    // Calculate new hand positions
    uint8_t sec_pos  = state->current_time.second;
    uint8_t min_pos  = state->current_time.minute;
    uint8_t hour_pos = (state->current_time.hour % 12) * 5 + (min_pos / 12);

    // Update hand shape parameters
    hour_hand->params.line.xe = CENTER_X + (HOUR_HAND_LEN * dir60[hour_pos].x) / 100;
    hour_hand->params.line.ye = CENTER_Y + (HOUR_HAND_LEN * dir60[hour_pos].y) / 100;

    min_hand->params.line.xe = CENTER_X + (MIN_HAND_LEN * dir60[min_pos].x) / 100;
    min_hand->params.line.ye = CENTER_Y + (MIN_HAND_LEN * dir60[min_pos].y) / 100;

    sec_hand->params.line.xe = CENTER_X + (SEC_HAND_LEN * dir60[sec_pos].x) / 100;
    sec_hand->params.line.ye = CENTER_Y + (SEC_HAND_LEN * dir60[sec_pos].y) / 100;
    
    // Redraw just the hands and center dot
    oledC_redrawSome(HOUR_HAND_IDX, ANALOG_SHAPE_COUNT);
}
