#ifndef MENU_ICONS_H
#define MENU_ICONS_H

#include <stdint.h>

// Icon size definition (matches ICON_SIZE in menu.c)
#define MENU_ICON_SIZE 16

// Each icon is 16x16 pixels, 1-bit monochrome.
// Stored as 8 uint32_t values, where each uint32_t holds two 16-bit rows.

// 1. Display Mode (Monitor/Screen icon)
static const uint32_t icon_display_mode[8] = {
    0x00000000,
    0x7FFE3FFC,
    0x40024004,
    0x40024004,
    0x40024004,
    0x40024004,
    0x7FFE3FFC,
    0x00000000
};

// 2. Time Format (Clock with "12/24")
static const uint32_t icon_time_format[8] = {
    0x00000000,
    0x1FFC0FF0,
    0x30062008,
    0x62034204,
    0x42044204,
    0x20083006,
    0x0FF01FFC,
    0x00000000
};

// 3. Set Time
static const uint32_t icon_set_time[8] = {
    0x00000000,
    0x1FFC0FF0,
    0x34862808,
    0x64834404,
    0x44044404,
    0x28083486,
    0x0FF01FFC,
    0x00000000
};

// 4. Set Date (Calendar)
static const uint32_t icon_set_date[8] = {
    0x00000000,
    0x7FFE3FFC,
    0x60062004,
    0x6AAE2AAC,
    0x4AA42AA2,
    0x4AA42AA2,
    0x7FFE3FFC,
    0x00000000
};

// 5. Set Alarm
static const uint32_t icon_set_alarm[8] = {
    0x00000000,
    0x10080810,
    0x2FF817F4,
    0x4809280A,
    0x4AA92AAA,
    0x280A140A,
    0x0FF007F0,
    0x00000000
};

// 6. Alarm On/Off
static const uint32_t icon_alarm_toggle[8] = {
    0x00000000,
    0x00000000,
    0x1FFC0FF0,
    0x30062008,
    0x37862F08,
    0x37862F08,
    0x1FFC0FF0,
    0x00000000
};

// 7. Pomodoro
static const uint32_t icon_pomodoro[8] = {
    0x00000000,
    0x0FF807E0,
    0x181C1024,
    0x300A2012,
    0x300A2012,
    0x1024181C,
    0x07E00FF8,
    0x00000000
};

// Main array of all menu icons
static const uint32_t* menu_icons[] = {
    icon_display_mode,
    icon_time_format,
    icon_set_time,
    icon_set_date,
    icon_set_alarm,
    icon_alarm_toggle,
    icon_pomodoro
};

#endif // MENU_ICONS_H
