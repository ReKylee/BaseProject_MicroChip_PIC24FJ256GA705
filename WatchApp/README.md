# WatchApp

A wristwatch-style application for the PIC24FJ256GA705 Curiosity board with a 96x96 color OLED display.
Supports multiple watch faces, an alarm, a pomodoro timer, and a radial settings menu.

Hebrew guide: `README_HE.md`

## Hardware Inputs

| Input         | Hardware                        |
| ------------- | ------------------------------- |
| S1, S2        | On-board push buttons           |
| Potentiometer | On-board Potentiometer          |
| Accelerometer | ADXL345 (flip and shake events) |

Button presses are classified as **short** (<2s) or **long** (>=2s hold).

## Modes

The app has four display modes. Each mode owns its own input handling and draw logic.

### Watch Mode

The default mode. Shows the current time on one of three selectable faces:

- **Digital** -- large HH:MM with an arc-shaped seconds trail
- **Analog** -- clock hands drawn from a precomputed 60-point geometry table
- **Binary** -- time encoded in binary

Controls:

| Input    | Action                   |
| -------- | ------------------------ |
| S2 short | Cycle to next watch face |
| S1 long  | Open settings menu       |
| S2 long  | Open pomodoro timer      |

When the alarm triggers, the display switches to a dedicated alarm face.
Dismiss it with S1 short, S2 short, flip, or shake. The watch restores
the previous face and mode automatically.

### Menu Mode

A radial menu navigated with the potentiometer. Menu items are arranged in a
circle; turning the pot highlights different options.

| Input      | Action                                      |
| ---------- | ------------------------------------------- |
| Pot turn   | Navigate options / adjust edit values       |
| S2 short   | Select item, advance to next field, confirm |
| S1 short   | Back to main menu / cancel                  |
| Flip/Shake | Exit menu, return to watch                  |

Available settings:

| Menu Item    | Fields                                    |
| ------------ | ----------------------------------------- |
| Set Time     | Hour (0-23), Minute (0-59)                |
| Set Date     | Day (1-31), Month (1-12)                  |
| Set Alarm    | Hour (0-23), Minute (0-59)                |
| Alarm Toggle | Enable / Disable                          |
| Time Format  | 12H / 24H                                 |
| Display Mode | Digital / Analog / Binary                 |
| Pomodoro     | Work mins (W), Break mins (B), Cycles (C) |

### Pomodoro Mode

A configurable work/break timer with session tracking.

| Input    | Action                |
| -------- | --------------------- |
| S2 short | Start or pause        |
| S1 short | Reset current session |
| S1 long  | Open settings menu    |
| S2 long  | Exit to watch mode    |

The timer cycles through: **Work -> Short Break -> Work -> ... -> Long Break**.
A long break triggers after every N work sessions (set by `long_break_after_sessions`).
The cycles target (C) sets how many work sessions to run before stopping.

The display shows a MM:SS countdown, a state label
(WORK / BREAK / LONG), a progress bar, and session indicators.

### Debug Mode

Only available when compiled with `DEBUG_MODE` defined.

| Input        | Action                                  |
| ------------ | --------------------------------------- |
| S1 + S2 long | Toggle debug mode on/off                |
| S1 short     | Advance date by one day (rollover test) |
| S2 short     | Set alarm to next minute, exit debug    |

## Architecture

```
WatchApp/
  watch_main.c/h          Entry point and 10ms main loop
  app_init.c/h            Hardware init (OLED, I2C, accel, timers)

  shared/                 Types, state, math, formatting, UI helpers
    watch_types.h         Enums and structs (WatchFace_t, MenuState_t, etc.)
    watch_state.h/c       Global WatchState_t singleton
    watch_settings_store  Flash persistence (CRC-validated)
    fast_math.h           Division-free math for common constants
    watch_format.h        Numeric/date text formatting
    watch_ui_widgets      Shared rendering primitives
    ui_layout.h           Centering and sizing helpers

  watchCore/              Timekeeper and alarm logic
  watchFaces/             Face renderers (digital, analog, binary, alarm)
  watchInput/             Button debounce, potentiometer, accelerometer events
  watchManagers/          Coordinators (input routing, display, time updates)
  watchMenu/              Radial menu system (state, input, rendering, icons)
  pomodoroTimer/          Pomodoro state machine and UI
  watchDebug/             Debug screen (compile-time optional)
```

Each face and mode implements a `Draw()` (full redraw) and `DrawUpdate()` (incremental
partial update) pair. The main loop calls the appropriate update function on each tick,
with full redraws triggered by mode transitions or flag changes.

## Persistence

Settings are stored in flash at address `0x2A000` and restored on boot.
The flash record includes a magic word, version byte, and CRC-16 (CCITT-FALSE)
for validation. Persisted fields:

- Time and date
- Time format (12H/24H)
- Active watch face
- Alarm time and enabled state
- Pomodoro durations and cycles target

Reprogramming may erase the stored data depending on programmer memory settings.

## Build Configurations

| Config    | Optimization |
| --------- | ------------ |
| `default` | `-O2`        |
| `debug`   | `-O0`        |

## Icon Credits

- [famfamfam silk](https://github.com/legacy-icons/famfamfam-silk) (legacy mirror)
- [tomato 16x16 pixel art](https://www.pixilart.com/art/tomato-16x16-sr2a62a94d910aws3)
- [rpgiab icon pack](https://zeromatrix.itch.io/rpgiab-icons)
