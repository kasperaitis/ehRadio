# ehRadio AI Coding Guide

## ⚠️ Critical Rules
- **Rule #1**: Always confirm with user BEFORE making more than 10 lines of changes at once.
- **Rule #2**: NEVER edit `src/core/options.h`. Use `myoptions.h` for all hardware/settings overrides.
- **Rule #3**: ehRadio is for ESP32/ESP32-S3. Assume I2S audio unless VS1053 pins are defined.

## Project Structure
- **Config Cascade**: `options.h` (Internal Defaults) → `myoptions.h` (Hardware) → `mytheme.h` (UI).
- **Core logic**: `src/core/` (Player, Display, Network, Config, Controls).
- **Audio path**: `src/audioI2S/` (Software codecs) vs `src/audioVS1053/` (Hardware chip).
- **UI**: Widgets in `src/displays/widgets/`, drivers in `src/displays/`.
- **Plugins**: Class-based hooks in `src/plugins/`, registered in `main.cpp`.

## Build Patterns
- **Hardware defines**: Use macros like `DSP_MODEL` and `AUDIO_MODEL` in `myoptions.h`.
- **Memory**: ESP32-S3 usually has PSRAM (`BOARD_HAS_PSRAM`) and uses Native USB.
- **Storage**: SPIFFS is the default filesystem for `/data` (WebUI/Playlists).

## Development Tasks
- **Adding hardware**: Add specific defines to a block in `myoptions.h`. 
- **Modifying UI**: Edit widget source or add new model to `src/displays/`.