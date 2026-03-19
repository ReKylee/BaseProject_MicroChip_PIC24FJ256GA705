# Curiosity OLED Base Project

A reusable driver base for the **PIC24FJ256GA705 Curiosity Development Board**, built in MPLAB X with the XC16 compiler. Provides peripheral drivers for the board's OLED display, buttons, potentiometer, LEDs, and I2C/SPI buses, plus support for the MikroElektronika Accel Click (ADXL345).

The current application built on top of these drivers is a watch project in `WatchApp/`.

## Requirements

- **MPLAB X** v6.05+
- **XC16** compiler v2.10+
- PIC24FJ256GA705 Curiosity Development Board
- MikroElektronika Accel Click (ADXL345) on mikroBUS slot (optional, for accelerometer features)

## Build

1. Open the project in MPLAB X.
2. Select a configuration (`default` for `-O2`, `debug` for `-O0`).
3. Build and program the board.

Entry point: `main.c` currently calls `watch_main()` in `WatchApp/watch_main.c`.

## Drivers

Each driver is self-contained in its own folder and can be used independently.

| Folder             | Description                                                  |
| ------------------ | ------------------------------------------------------------ |
| `oledDriver/`      | 96x96 color OLED: commands, shapes, solid text, 2bpp bitmaps |
| `i2cDriver/`       | I2C master with bus recovery and PIC24FJ errata workaround   |
| `spiDriver/`       | SPI communication                                            |
| `accel3Driver/`    | ADXL345 accelerometer (auto-detect I2C address, XYZ read)    |
| `adcDriver/`       | ADC for potentiometer input                                  |
| `switchDriver/`    | Push-button input with debounce                              |
| `ledDriver/`       | LED and RGB LED control                                      |
| `Timers/`          | Timer setup and tick helpers                                 |
| `System/`          | MCC-generated system code (clock, pins, delays, traps)       |
| `flash_generated/` | MCC-generated flash driver                                   |

### OLED Driver Highlights

- SPI stream ownership for reduced per-pixel overhead during bulk drawing
- `oledC_DrawStringSolid`: draws foreground and background pixels per glyph, enabling flicker-free text updates without a separate clear step
- `oledC_DrawBitmapIndexed2bpp`: 4-color palette bitmaps using packed 2-bit indices (row-major, 4 pixels/byte)
- Original transparent text APIs (`oledC_DrawString`) remain available

### I2C Driver Highlights

- Bus recovery for stuck slaves: batched SCL clocking (9 pulses/batch, up to 6 batches) with SDA verification between each
- PIC24FJ silicon errata workaround: SDA held low for >= 150ns after enabling I2CEN to prevent false bus collision on first START

## Examples

Standalone demos that use the drivers above:

| Folder                              | Description                                |
| ----------------------------------- | ------------------------------------------ |
| `Examples/ACCEL3/ADXL345.c`        | Read accelerometer values, display on OLED |
| `Examples/RGBEditor/`              | RGB color editor with pot/switch control   |
| `Examples/SPI/bitbanging_example.c` | SPI bit-banging demo                       |

## WatchApp

The current application built on these drivers. A watch with multiple faces, alarm, pomodoro timer, and radial settings menu.

Full documentation: [`WatchApp/README.md`](WatchApp/README.md) | [Hebrew](WatchApp/README_HE.md)

## Icon Credits

- [famfamfam silk](https://github.com/legacy-icons/famfamfam-silk) (legacy mirror)
- [tomato 16x16 pixel art](https://www.pixilart.com/art/tomato-16x16-sr2a62a94d910aws3)
- [rpgiab icon pack](https://zeromatrix.itch.io/rpgiab-icons)
