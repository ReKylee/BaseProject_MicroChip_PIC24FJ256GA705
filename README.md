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
