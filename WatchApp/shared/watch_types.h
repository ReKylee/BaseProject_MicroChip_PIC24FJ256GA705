/*
 * watch_types.h
 * Shared type definitions for the watch application
 */

#ifndef WATCH_TYPES_H
#define WATCH_TYPES_H

#include <stdint.h>
#include <stdbool.h>

// ============================================================================
// TIME & DATE TYPES
// ============================================================================

typedef struct {
    uint8_t hour;       // 0-23
    uint8_t minute;     // 0-59
    uint8_t second;     // 0-59
} Time_t;

typedef struct {
    uint8_t day;        // 1-31
    uint8_t month;      // 1-12
} Date_t;

typedef enum {
    FORMAT_12H = 0,
    FORMAT_24H = 1
} TimeFormat_t;

// ============================================================================
// WATCH FACE TYPES
// ============================================================================

typedef enum {
    FACE_DIGITAL = 0,
    FACE_ANALOG,
    FACE_BINARY,
    FACE_COUNT          // Number of watch faces
} WatchFace_t;

// ============================================================================
// ALARM TYPES
// ============================================================================

typedef struct {
    uint8_t hour;       // 0-23
    uint8_t minute;     // 0-59
    bool enabled;
    bool triggered;
    uint8_t trigger_count; // For auto-off after 20s
} Alarm_t;

// ============================================================================
// MENU TYPES
// ============================================================================

typedef enum {
    MODE_WATCH = 0,     // Normal watch display
    MODE_MENU,          // Menu navigation
    MODE_POMODORO       // Pomodoro timer
} DisplayMode_t;

typedef enum {
    MENU_MAIN = 0,
    MENU_DISPLAY_MODE,
    MENU_TIME_FORMAT,
    MENU_SET_TIME,
    MENU_SET_DATE,
    MENU_SET_ALARM,
    MENU_ALARM_TOGGLE,
    MENU_POMODORO,
    MENU_COUNT
} MenuState_t;

// ============================================================================
// INPUT TYPES
// ============================================================================

typedef enum {
    BTN_NONE = 0,
    BTN_S1_SHORT,
    BTN_S1_LONG,
    BTN_S2_SHORT
} ButtonEvent_t;

typedef enum {
    ACCEL_NONE = 0,
    ACCEL_FLIP,
    ACCEL_SHAKE
} AccelEvent_t;

// ============================================================================
// POMODORO TYPES
// ============================================================================

typedef enum {
    POMODORO_IDLE = 0,
    POMODORO_WORK,
    POMODORO_SHORT_BREAK,
    POMODORO_LONG_BREAK
} PomodoroState_t;

typedef struct {
    PomodoroState_t state;
    uint16_t remaining_seconds;
    uint8_t work_sessions;      // Count completed work sessions
    bool paused;
} Pomodoro_t;

// ============================================================================
// COLOR DEFINITIONS (RGB565 format)
// ============================================================================

// Carefully chosen palette for good contrast on 96x96 OLED
#define COLOR_BG        0x0000  // Black background
#define COLOR_PRIMARY   0x07FF  // Cyan (good visibility)
#define COLOR_SECONDARY 0xFD20  // Orange
#define COLOR_TEXT      0xFFFF  // White
#define COLOR_ACCENT    0xF81F  // Magenta
#define COLOR_WARNING   0xF800  // Red
#define COLOR_SUCCESS   0x07E0  // Green
#define COLOR_DIM       0x7BEF  // Light gray

#endif // WATCH_TYPES_H
