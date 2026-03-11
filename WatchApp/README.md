# WatchApp

Watch application for the PIC24 Curiosity OLED base project.

Hebrew guide: `README_HE.md`

## Features

- Watch faces: Digital, Analog, Binary, Alarm face
- Alarm with auto-dismiss and restore of previous mode/face
- Settings menu (time, date, alarm, display mode, pomodoro)
- Pomodoro timer with work/short/long breaks, cycles target, and progress bar
- Optional debug screen (compile-time)
- Flash-backed settings persistence

## Usage

### Inputs

- `S1`, `S2`
- Potentiometer
- Accelerometer: flip and shake

### Watch Mode

- `S2 short`: cycle watch face
- `S1 long`: open menu
- `S2 long`: open pomodoro
- While alarm is ringing: `S1 short`, `S2 short`, flip, or shake dismisses the alarm

### Menu Mode

- Potentiometer: navigate radial options or edit values
- `S2 short`: select option, next field, or confirm
- `S1 short`: back/cancel to main menu
- Flip or shake: exit menu to watch mode

### Pomodoro Mode

- `S2 short`: start or pause
- `S1 short`: reset
- `S1 long`: enter menu
- `S2 long`: exit to watch mode

Pomodoro edit fields (menu):

- `W` = work minutes
- `B` = short break minutes
- `C` = cycles target (work sessions before stopping)

Long break timing uses `long_break_after_sessions`.

### Debug Mode (when `DEBUG_MODE` is enabled)

- Both buttons long: toggle debug mode on or off
- `S1 short`: advance current date by one day (date rollover test)
- `S2 short`: quick-set alarm to next minute and exit debug
- Shows date step as `DD/MM>DD/MM`

## Persistence

Settings are stored in flash and restored on boot.
This preserves time/date, alarm, and pomodoro settings across reset/power cycle.
Reprogramming may erase the stored data depending on programmer settings.

## Build Configuration Notes

- `default` configuration: `-O2`
- `debug` configuration: no optimization (`-O0`)

## Icon Credits

- famfamfam silk (legacy mirror): <https://github.com/legacy-icons/famfamfam-silk>
- tomato 16x16 pixel art: <https://www.pixilart.com/art/tomato-16x16-sr2a62a94d910aws3>
- rpgiab icon pack: <https://zeromatrix.itch.io/rpgiab-icons>
