# WatchApp

Watch application for the PIC24 Curiosity OLED base project.

Hebrew guide: `README_HE.md`

It includes:

- Multiple watch faces
- Alarm with alarm face
- Settings menu
- Pomodoro timer
- Optional debug screen
- Flash-backed settings persistence

## Quick Start

`main.c` calls `watch_main()` from `WatchApp/watch_main.c`.

Main loop:

1. Update time and alarm once per second
2. Read button and accelerometer events
3. Route input by current mode
4. Draw full or partial UI update

## Controls

Hardware inputs used by the app:

- `S1`
- `S2`
- Potentiometer
- Flip and shake events from accelerometer

## Mode Controls

### Watch Mode

Mode constant: `MODE_WATCH`

- `S2 short`: cycle watch face
- `S1 long`: open menu
- `S2 long`: open pomodoro
- While alarm is ringing, `S1 short`, `S2 short`, flip, or shake dismisses the alarm

### Menu Mode

Mode constant: `MODE_MENU`

- Potentiometer: navigate radial options or edit values
- `S2 short`: select option, next field, or confirm
- `S1 short`: back/cancel to main menu
- Flip or shake: exit menu to watch mode

### Pomodoro Mode

Mode constant: `MODE_POMODORO`

- `S2 short`: start or pause
- `S1 short`: reset
- `S1 long`: enter menu
- `S2 long`: exit to watch mode

### Debug Mode

Mode constant: `MODE_DEBUG` (only when `DEBUG_MODE` is enabled)

- Both buttons long: toggle debug mode on or off
- `S1 short`: advance current date by one day (for date rollover testing)
- `S2 short`: quick-set alarm to next minute and exit debug
- Debug screen shows the last date step as `DD/MM>DD/MM` for instant rollover confirmation

## Features

### Watch Faces

- Digital
- Analog
- Binary
- Alarm face (used when alarm triggers)

### Alarm

- Time-based trigger at `HH:MM:00`
- Auto-dismiss timeout
- Restores previous mode and face after dismiss

### Menu

- Display mode selection
- Time format (12h/24h)
- Set time
- Set date
- Set alarm
- Alarm on/off
- Pomodoro settings

### Pomodoro

- Work and break cycles (short + long break)
- Session counter (completed work sessions)
- Cycles target (number of work sessions before stopping)
- Progress bar showing elapsed time within the current phase
- Pause and reset

Pomodoro edit fields (menu):
- `W` = work minutes
- `B` = short break minutes
- `C` = cycles target

Long break timing uses `long_break_after_sessions`.

## Persistence

Settings are stored in flash and restored on boot. This preserves time/date, alarm, and pomodoro settings across reset/power cycle. Reprogramming may erase the stored data depending on programmer settings.

## Build Configuration Notes

- `default` configuration: `-O2`
- `debug` configuration: no optimization (`-O0`)

## Folder Guide

- `shared/`: global types and state
- `watchCore/`: timekeeper and alarm logic
- `watchFaces/`: face drawing implementations
- `watchMenu/`: menu state, input, and rendering
- `watchInput/`: button, pot, and accelerometer input helpers
- `watchManagers/`: app-level routing for time/input/display
- `watchDebug/`: debug screen
- `pomodoroTimer/`: pomodoro logic and drawing

## Shared Helper APIs

Common cross-module helpers live in `WatchApp/shared/`:

- `fast_math.h`
  Constant-time helpers for common numeric transforms (for example `/10`, `/6`, `*60`, `*3600`, `/86400`).
- `watch_format.h`
  Formatting helpers for time/date text:
  - `Watch_SplitDigits10`
  - `Watch_Format2D`
  - `Watch_FormatDateDDMM`
- `watch_ui_widgets.h` + `watch_ui_widgets.c`
  Reusable draw/layout helpers for clock-like UI:
  - `WatchUi_DrawNN`
  - `WatchUi_DrawColon`
  - `WatchUi_ComputeDualTimeLayout`
  - width/advance utilities for scaled glyphs
- `watch_settings_store.h` (implementation in `shared/watch_state.c`)
  Persistent settings interface:
  - `WatchSettingsStore_Load` / `WatchSettingsStore_Save`
  - `WatchSettingsStore_LoadState` / `WatchSettingsStore_SaveState`
  - snapshot conversion helpers (`FromState`, `ApplyToState`)

Guideline:
- Use these shared APIs instead of re-implementing formatting/layout/math logic inside faces, menu, or pomodoro modules.

## Notes for Development

- Display updates use two flags in shared state:
  - `needs_full_redraw`
  - `needs_redraw`
- Full redraw is used for mode switches and large state changes.
- Partial redraw is used for normal ticking updates.

## Icon Credits

- famfamfam silk (legacy mirror): https://github.com/legacy-icons/famfamfam-silk
- tomato 16x16 pixel art: https://www.pixilart.com/art/tomato-16x16-sr2a62a94d910aws3
- rpgiab icon pack: https://zeromatrix.itch.io/rpgiab-icons
