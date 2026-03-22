# Firmware Build Tool

## `fix_web_assets_and_releases.md.py`

This script automatically generates firmware metadata and web assets by parsing the firmware definitions in `myoptions.h`.

### Files Generated

- firmware.txt: Machine-readable list of firmware variants for the build system
- web_assets/manifests/*.json: ESP Web Tools manifest files for each firmware variant
- web_assets/firmware-info.json: Summary file for the web flasher (docs/firmware.html)

### File Patched

- releases.md: Human-readable release notes for GitHub releases

### Usage

Run the script from within the contributor's build folder:

```bash
cd builds/your_username/
python3 fix_web_assets_and_releases.md.py
```

The script will:
1. Parse `myoptions.h` to find all firmware definitions
2. Generate `firmware.txt` in the format: `board_env|chip_family|fw_env|friendly_name`
3. Generate ESP Web Tools manifests for each firmware in `web_assets/manifests/`
4. Generate `web_assets/firmware-info.json` with all variant information
5. Patch `releases.md` with organized firmware listings and flash instructions

### Requirements

Your `myoptions.h` must have firmware definitions in this format:

```cpp
#elif defined(ESP32_S3_YOURBOARD)
  #undef FIRMWARE
  #define FIRMWARE "esp32_s3_your_board.bin" // "board_esp32_s3_n16r8", "ESP32-S3", "YourName"
  #define FIRMWARE_NAME "Your Friendly Name" // "https://optional-url.com"
  #define ARDUINO_ESP32S3_DEV
```

The comments after `FIRMWARE` are critical:
- First field: bootloader board environment (e.g., `"board_esp32_s3_n16r8"`)
- Second field: chip family (e.g., `"ESP32-S3"`, `"ESP32"`, `"ESP32-C3"`)
- Third field: contributor name (e.g., `"Trip5"`, `"Kasperaitis"`)

### Automation

The GitHub workflow will also run this script during the release process but will not update the files.  They will be compared to make sure they match.  You must do that locally and push changes.
