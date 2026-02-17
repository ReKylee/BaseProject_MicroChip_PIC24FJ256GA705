# Curiosity OLED Base Project

Base MPLAB X project for the **Microchip PIC24FJ256GA705 Curiosity board**.
This repo is set up as a reusable starting point for board drivers, small demos, and the watch-style app in `WatchApp/`.

## What This Project Includes

### Drivers

- `ledDriver/`
  LED and RGB LED control helpers.
- `switchDriver/`
  Push-button/switch input helpers.
- `adcDriver/`
  ADC setup + raw read utilities (used for potentiometer input).
- `i2cDriver/`
  I2C communication helpers.
- `spiDriver/`
  SPI communication helpers.
- `oledDriver/`
  OLED setup, color handling, shapes, bitmap/text drawing.
- `accel3Driver/`
  ADXL345 accelerometer support (read X/Y/Z, basic setup).
- `Timers/`
  Timer setup and tick helpers.
- `System/`
  Core generated system code (clock, pins, interrupts, delays, traps).

### Application Modules

- `WatchApp/`
  Main watch application logic:
  - watch faces (digital, analog, binary, alarm)
  - alarm system
  - menu system
  - pomodoro timer
  - input/display/time managers
- `flash_generated/`
  MCC-generated flash driver used by watch settings persistence.

WatchApp documentation:
- English: `WatchApp/README.md`
- Hebrew: `WatchApp/README_HE.md`

### Examples

- `Examples/ACCEL3/ADXL345.c`
  Reads accelerometer values and displays them on OLED.
- `Examples/RGBEditor/`
  RGB color editor app with OLED UI + potentiometer/switch control.
- `Examples/SPI/bitbanging_example.c`
  Basic SPI bit-banging demonstration.

## Build and Run

1. Open project in **MPLAB X**.
2. Select target device/configuration.
3. Build and flash to the Curiosity board.

Current app entry point:

- `main.c` -> `watch_main()` in `WatchApp/watch_main.c`

## Folder Notes

- `build/`, `dist/`, `.generated_files/` are build/generated outputs.
- `nbproject/` contains MPLAB project configuration.

## Watch Shared APIs

Recent watch-side shared helpers are in `WatchApp/shared/`:

- `fast_math.h`
  Division/multiplication helpers that avoid heavy runtime div paths for common constants.
- `watch_format.h`
  Numeric/date text formatting helpers (`Watch_SplitDigits10`, `Watch_Format2D`, `Watch_FormatDateDDMM`).
- `watch_ui_widgets.h` and `watch_ui_widgets.c`
  Shared UI primitives for two-digit rendering, colon rendering, and centered dual-time layout math.
- `watch_settings_store.h` (implemented in `WatchApp/shared/watch_state.c`)
  Flash-backed persistence API for loading/saving a compact settings snapshot and applying it to runtime state.

## OLED Driver Updates (`oledDriver/`)

The following changes were made in `oledDriver/oledC.c`, `oledDriver/oledC_shapes.c`, and `oledDriver/oledC_shapes.h`:

1. Streaming performance improvements in `oledC.c`
- Added explicit stream ownership handling for OLED write/read RAM streaming.
- Kept SPI open during active pixel streams instead of opening/closing per pixel transfer.
- Added proper stream stop behavior before sending non-stream commands.
- Updated write/read paths to require active stream ownership before exchanging pixel data.
- Result: lower command/transaction overhead during heavy drawing (text, shapes, fills).

2. New solid text APIs in `oledC_shapes`
- Added `oledC_DrawCharacterSolid(...)`.
- Added `oledC_DrawStringSolid(...)`.
- Added declarations in `oledC_shapes.h`.
- Solid text draws both foreground and background pixels for each glyph cell.
- This allows faster fixed-area text redraws (no separate clear step required for same-area updates).

3. New indexed palette bitmap API (2bpp)
- Added `oledC_DrawBitmapIndexed2bpp(...)` in `oledC_shapes`.
- Supports 4-color palette icons using packed 2-bit indices.
- Packing format is row-major, 4 pixels per byte:
  - bits `[7:6]` = pixel 0
  - bits `[5:4]` = pixel 1
  - bits `[3:2]` = pixel 2
  - bits `[1:0]` = pixel 3
- Uses a single OLED address window and streamed pixel writes for efficiency.

4. Solid glyph raster order fix
- Fixed pixel traversal order in `oledC_DrawCharacterSolid(...)` to match OLED RAM window expectations.
- Result: prevents garbled text rendering when using solid text functions.

5. Backward compatibility
- Existing transparent APIs (`oledC_DrawCharacter`, `oledC_DrawString`) are still present and unchanged.
- Existing call sites can continue using transparent text where overlay behavior is desired.
