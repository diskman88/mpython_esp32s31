This firmware targets the LABPLUS Ledong Max S31 with 16 MiB external SPI flash and Octal PSRAM.

The GPIO33/34 USB Serial/JTAG port carries ESP-IDF console and panic output. The USB OTG port carries the ESP-VISION IDE connection. UART0 REPL is disabled because the default UART0 pins are camera data lines.

The LCD uses RGB565 for pixels and a separate three-wire SPI bus for ST7102 commands. GPIO20/21/22 carry SCL/SDI/CS and GPIO23 resets the panel. GPIO33/34 are used by the USB Serial/JTAG download port. SDMMC is disabled because the inherited pin assignment overlaps the LCD command bus and I2C0.

The GC0328 camera uses an external oscillator and the Board Manager I2C0 bus for SCCB. Its sensor format is 320×240 YUYV over 8-bit DVP. GPIO49 controls the LCD backlight through LEDC PWM.

The ST7123 touchscreen shares I2C0 with the camera at address `0x55` (SCL GPIO24, SDA GPIO25). Its active-low reset is on GPIO48. Use MicroPython `lcd_touch.Touch().read()` to poll pixel coordinates.
