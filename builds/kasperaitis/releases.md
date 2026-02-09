## Pre-built Firmwares & WebUI Assets
  You can download the firmware and flash yourself or you can use my [Web Installer](https://kasperaitis.github.io/ehRadio/firmware.html).
### Notes
  - You can download .bin files and flash to your ESP with `esptool`
  - you will need a firmware file appropriate to your build (see below)
  - depending on your board, choose the appropriate `board_*_bootloader.bin` and `board_*_partitions.bin`
  - for most ESP32s, use:
    - `esptool --chip esp32 --port com14 --baud 460800 write_flash -z 0x1000 board_esp32_bootloader.bin 0x8000 board_esp32_partitions.bin 0x10000 board_esp32.bin`
    - to include spiffs, add this to the above command: `0x390000 board_esp32_spiffs.bin`
  - for ESP32-S3s (like the ESP32-S3-N16R8) use:
    - `esptool --chip esp32s3 --port com14 --baud 460800 write_flash -z 0x0000 board_esp32_s3_n16r8_bootloader.bin 0x8000 board_esp32_s3_n16r8_partitions.bin 0x10000 board_esp32_s3_n16r8.bin`
    - to include spiffs, add this to the above command: `0x670000 board_esp32_s3_n16r8_spiffs.bin`
## Boards
  - each of the pre-built board binaries have pre-set hardware configurations, they cannot be changed
  - to view pin usage, click the link and scroll down then click preview
### Bare board firmwares (no peripherals, may be used for testing)
  - `board_esp32.bin`
  - `board_esp32_s3_n16r8.bin`
### Board Shared Binaries (Bootloader/Partitions)
  - `board_esp32_bootloader.bin` / `board_esp32_partitions.bin` / `board_esp32_spiffs.bin`
  - `board_esp32_s3_n16r8_bootloader.bin` / `board_esp32_s3_n16r8_partitions.bin` / `board_esp32_s3_n16r8_spiffs.bin`
### Kasperaitis Firmware
  - [`esp32_s3_kasperaitis_es3c28p.bin`](https://www.lcdwiki.com/2.8inch_ESP32-S3_Display) (ES3C28P is a ESP32-S3-N16R8 with 2.8inch Display)
### Add Yours
  - you can either fork my `ehradio` repo and edit these files or request a build be added
    - use [the generator](https://trip5.github.io/ehRadio_myoptions/generator.html) and copy the link and include it in your request
### Web Assets
  - all other files are needed for the WebUI functionality
  - they are available here to allow automatic downloading to SPIFFS
  - it is NOT necessary to download them (or the SPIFFS bin) - the radio will download them automatically after network connection is established
