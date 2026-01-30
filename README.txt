# AT91Bootstrap Project

AT91Bootstrap is the 2nd level bootloader for Microchip microprocessors (aka AT91).
It providing a set of algorithms to manage the hardware initialization such as
clock speed configuration, PIO settings, DRAM initialization, to download your
main application from specified boot media: NAND FLASH, serial FLASH (both
AT25-compatible of DataFlash), serial EEPROM, SD Card, etc. to main memory and
to start it.

## BUILDING

- This project requires **cmake** and **arm-none-eabi-gcc14**

### SD card loading

1. To build and load binaries from the SD card the application must be called **BOOT.BIN** on the SD card and formatted to FAT16

2. In the repo root run `cmake -S . -B build`

3. Run `cmake --build build` or `make -C build` if the SD card is plugged in you can also run `cmake --build build --target flash` to automatically write the BOOT.bin to the SD card. It will also build the project as well

### USART loading

1. To build and remotely load binaries over USART run `cmake -S . -B build -DUSART_BOOT=1`

2. Run `cmake --build build` or `make -C build` if the SD card is plugged in you can also run `cmake --build build --target flash` to automatically write the BOOT.bin to the SD card. It will also build the project as well

## Loading application over USART

1. Once **BOOT.bin** is on the SD card restart the ACU

2. Connect the UART device to PC and ACU on FTDI (J14) TX on 3rd pin on the right from GND and RX on pin to the right of TX

3. Install pyserial and xmodem in your python env of choice

4. Run `python load_binary.py <path to BUILD.bin>`

5. Should see "Wrote binary" if successful and ACU will automatically boot into the app
