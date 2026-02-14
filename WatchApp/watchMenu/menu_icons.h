/*
 * Bitmap icon assets used by menu screens.
 */

#ifndef MENU_ICONS_H
#define MENU_ICONS_H

#include <stdint.h>

// Icon size
#ifndef MENU_ICON_SIZE
#define MENU_ICON_SIZE 16
#endif

// Each icon is 16x16 pixels, 1-bit monochrome.
// Stored as 16 uint32_t rows, centered in a 32-bit scanline.

// 1. Display Mode (Watch face icon)
static const uint32_t s_icon_display_mode[16] = {
    0xFFFFFFFF,
    0xFFF00FFF,
    0xFFF00FFF,
    0xFFC003FF,
    0xFFDBDBFF,
    0xFFDBDBFF,
    0xFFDB1BFF,
    0xFFDBDBFF,
    0xFFF00FFF,
    0xFFDBDBFF,
    0xFFDBDBFF,
    0xFFC003FF,
    0xFFF00FFF,
    0xFFF00FFF,
    0xFFFFFFFF,
    0xFFFFFFFF
};

// 2. Set Time (Clock)
static const uint32_t s_icon_set_time[16] = {
    0xFFFFFFFF,
    0xFFF81FFF,
    0xFFF7EFFF,
    0xFFEC37FF,
    0xFFDBDBFF,
    0xFFDBDBFF,
    0xFFDB1BFF,
    0xFFDBDBFF,
    0xFFD8DBFF,
    0xFFDB5BFF,
    0xFFEC37FF,
    0xFFF7EFFF,
    0xFFF81FFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF
};

// 3. Set Date (Calendar)
static const uint32_t s_icon_set_date[16] = {
    0xFFFFFFFF,
    0xFFC003FF,
    0xFFD99BFF,
    0xFFDFFBFF,
    0xFFC003FF,
    0xFFD99BFF,
    0xFFD99BFF,
    0xFFDFFBFF,
    0xFFD99BFF,
    0xFFD99BFF,
    0xFFDFFBFF,
    0xFFC003FF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF
};

// 4. Set Alarm (Classic Alarm Clock)
static const uint32_t s_icon_set_alarm[16] = {
    0xFFFFFFFF,
    0xFFE7E7FF,
    0xFFC3C3FF,
    0xFFDBDBFF,
    0xFFEFF7FF,
    0xFFD81BFF,
    0xFFDBDBFF,
    0xFFDBDBFF,
    0xFFD81BFF,
    0xFFEFF7FF,
    0xFFF3CFFF,
    0xFFF81FFF,
    0xFFFDBFFF,
    0xFFFBDFFF,
    0xFFFFFFFF,
    0xFFFFFFFF
};

// 5. Alarm Toggle (Alarm with Slash)
static const uint32_t s_icon_alarm_toggle[16] = {
    0xFFFFFDFF,
    0xFFE7E5FF,
    0xFFC3C3FF,
    0xFFDBDBFF,
    0xFFEFF7FF,
    0xFFD81BFF,
    0xFFDBDBFF,
    0xFFDBDBFF,
    0xFFD81BFF,
    0xFFEFF7FF,
    0xFFF3CFFF,
    0xFFF81FFF,
    0xFFFDBFFF,
    0xFFFBDFFF,
    0xFFF7EFFF,
    0xFFFFFFFF
};

// 6. Pomodoro (Tomato)
static const uint32_t s_icon_pomodoro[16] = {
    0xFFFFFFFF,
    0xFFFE7FFF,
    0xFFFC3FFF,
    0xFFF81FFF,
    0xFFE007FF,
    0xFFC003FF,
    0xFFC003FF,
    0xFFC003FF,
    0xFFC003FF,
    0xFFC003FF,
    0xFFE007FF,
    0xFFF00FFF,
    0xFFFC3FFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF
};

// 7. Time Format (12H / 24H)
static const uint32_t s_icon_time_12h[16] = {
    0xFFFFFFFF,
    0xFFF81FFF,
    0xFFE7E7FF,
    0xFFDBDBFF,
    0xFFDB1BFF,
    0xFFDBDBFF,
    0xFFE7E7FF,
    0xFFF81FFF,
    0xFFFFFFFF,
    0xFFF3F3FF,
    0xFFF3CFFF,
    0xFFCF3FFF,
    0xFFF0FFFF,
    0xFFC0CFFF,
    0xFFFFFFFF,
    0xFFFFFFFF
};

static const uint32_t s_icon_time_24h[16] = {
    0xFFFFFFFF,
    0xFFF81FFF,
    0xFFE7E7FF,
    0xFFDBDBFF,
    0xFFDB1BFF,
    0xFFDBDBFF,
    0xFFE7E7FF,
    0xFFF81FFF,
    0xFFFFFFFF,
    0xFFCFF3FF,
    0xFFCF33FF,
    0xFFC0F3FF,
    0xFFCFF3FF,
    0xFFC0C3FF,
    0xFFFFFFFF,
    0xFFFFFFFF
};

// 8. Display Mode Options
static const uint32_t s_icon_display_digital[16] = {
    0xFFFFFFFF,
    0xFFF03FFF,
    0xFFEFDFFF,
    0xFFECDFFF,
    0xFFECDFFF,
    0xFFEFDFFF,
    0xFFF03FFF,
    0xFFFFFFFF,
    0xFFFC0FFF,
    0xFFFBF7FF,
    0xFFFB37FF,
    0xFFFB37FF,
    0xFFFBF7FF,
    0xFFFC0FFF,
    0xFFFFFFFF,
    0xFFFFFFFF
};

static const uint32_t s_icon_display_analog[16] = {
    0xFFFFFFFF,
    0xFFF81FFF,
    0xFFF7EFFF,
    0xFFEC37FF,
    0xFFDBDBFF,
    0xFFDB5BFF,
    0xFFDBDBFF,
    0xFFDBDBFF,
    0xFFD81BFF,
    0xFFEFF7FF,
    0xFFF7EFFF,
    0xFFF81FFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF
};

static const uint32_t s_icon_display_binary[16] = {
    0xFFFFFFFF,
    0xFFF333FF,
    0xFFF333FF,
    0xFFFFFFFF,
    0xFFF333FF,
    0xFFF333FF,
    0xFFFFFFFF,
    0xFFF333FF,
    0xFFF333FF,
    0xFFFFFFFF,
    0xFFF333FF,
    0xFFF333FF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF
};

// Main array of all menu icons
static const uint32_t* s_menu_icons[] = {
    s_icon_display_mode,
    s_icon_time_12h,
    s_icon_set_time,
    s_icon_set_date,
    s_icon_set_alarm,
    s_icon_alarm_toggle,
    s_icon_pomodoro
};

#endif // MENU_ICONS_H
