# ehRadio AI Coding Guide

## Project Overview
ehRadio is an ESP32-based Internet radio player forked from yoRadio. The codebase is actively merging improvements from both projects while adding new features.

- **Current Repository**: https://github.com/trip5/ehRadio/
- **Upstream Project**: https://github.com/e2002/yoradio/
- **Active Development**: Regularly absorbing yoRadio changes while maintaining independent improvements
- **Codec Implementation**: Custom audio decoder work by maleksm

⚠️ **Critical Rule**: Always confirm with me before making more than 10 lines of changes at once

## Build System Architecture

### PlatformIO Multi-Environment Setup
The build system uses PlatformIO with multiple hardware configurations defined in `platformio.ini`:

- **Build environments** are hardware-specific (e.g., `esp32_s3_es3c28p`, `board_esp32_s3_n16r8`)
- **Configuration cascade**: `src/core/options.h` → `myoptions.h` → `mytheme.h`
- **Never edit** `src/core/options.h` directly - all customizations go in `myoptions.h`

### Configuration Pattern
```cpp
// Hardware configs define compile-time constants in myoptions.h
#if defined(ESP32_S3_TRIP5_SH1106_PCM_REMOTE)
  #define DSP_MODEL DSP_SH1106
  #define AUDIO_MODEL AUDIO_I2S
#endif
```

### Building and Releasing
- **Local builds**: Store configs in `builds/<username>/` with `platformio.ini`, `myoptions.h`, `mytheme.h`
- **Auto-build trigger**: Git tags (e.g., `git tag 2025.08.31; git push origin 2025.08.31`)
- **Pre-build script**: `replace_font.py` injects custom glyphs into displays
- **CI/CD**: GitHub workflow compiles all configs and publishes releases

## Core Architecture

### Main Components (in `src/core/`)
1. **Player** (`player.h/cpp`): Extends `Audio` class, manages stream playback and codec selection
2. **Display** (`display.h/cpp`): Hardware-abstracted display driver with widget system
3. **Network** (`network.h/cpp`): WiFi management, time sync, captive portal (Soft AP mode)
4. **Config** (`config.h/cpp`): Settings persistence via Preferences (not EEPROM), CSV playlist handling
5. **NetServer** (`netserver.h/cpp`): AsyncWebServer for WebUI and API endpoints
6. **Controls** (`controls.h/cpp`): Input handling (buttons, IR remote, rotary encoder, touchscreen)

### Audio Path
```
HTTP/SD Stream → Audio class → Codec Decoder (AAC/MP3/FLAC/Opus/Vorbis) 
                              → I2S or VS1053 → Speakers
```

- **I2S Audio**: PCM5102, ES8388, ES8311 DACs (src/audioI2S/)
- **VS1053 Decoder**: Hardware codec chip (src/audioVS1053/)
- **Codec selection**: Automatic based on stream format in `audioI2S/Audio.cpp`

### Display System
- **30+ display models** supported via `DSP_MODEL` defines (see `src/core/options.h` lines 28-56)
- **Widget-based rendering**: Text scroll, VU meter, clock, metadata (`src/displays/widgets/`)
- **Framebuffer optimization**: Auto-enabled on ESP32-S3 with PSRAM (`USE_FBUFFER`)
- **Custom drivers** for uncommon displays in subdirectories (e.g., `src/Adafruit_GC9106Ex/`)

### Plugin System
Located in `src/plugins/` and `src/pluginsManager/`:

```cpp
class MyPlugin : public Plugin {
  void on_setup() override { /* init code */ }
  void on_start_play() override { /* playback started */ }
  void on_track_change() override { /* metadata updated */ }
};
```

Hooks: `on_setup()`, `on_end_setup()`, `on_connect()`, `on_start_play()`, `on_stop_play()`, `on_track_change()`

## Critical Development Patterns

### Hardware Abstraction
Every hardware feature uses conditional compilation:
```cpp
#if VS1053_CS==255  // No VS1053 chip
  // Use I2S audio
#else
  // Use VS1053 hardware decoder
#endif
```

### Configuration Defaults
Since 2025.08.12, many settings can have defaults set in `myoptions.h`:
```cpp
#define SOUND_VOLUME 12
#define CLOCK_TWELVE true
#define MQTT_ENABLE
```

### Memory Management
- **ESP32 (4MB)**: Use `4MBflash.csv` partition scheme, limited HTTPS support
- **ESP32-S3 (16MB PSRAM)**: Full features, framebuffer, multiple streams
- **Optimization**: `build_src_filter` in platformio.ini excludes unused code

### File Storage
- **SPIFFS**: WebUI files (`data/www/`), config files (`data/`)
- **Compressed assets**: `.gz` files for space efficiency (except `rb_srvrs.json`)
- **Online updates**: ESPFileUpdater library downloads firmware and data files

### Version Synchronization
- Version defined in `src/core/options.h` as `#define RADIOVERSION "2025.08.31"`
- GitHub workflow auto-updates `timezones.json.gz` and `rb_srvrs.json` on commits
- OTA updates check version at `CHECKUPDATEURL` and download from `UPDATEURL`

## Common Development Tasks

### Adding a New Display Driver
1. Add `#define DSP_NEWMODEL` constant in `src/core/options.h`
2. Create display-specific code in `src/displays/`
3. Add hardware config block in `myoptions.h` with pin definitions
4. Update `platformio.ini` with required library dependencies

### Creating a Plugin
1. Place in `src/plugins/<PluginName>/`
2. Inherit from `Plugin` class and override lifecycle hooks
3. Register in main.cpp via PluginManager (`pm`)
4. See `examples/plugins/` for reference implementations

### Debugging Build Issues
- Use `#define DEBUG_MYOPTIONS` in myoptions.h to test specific hardware configs
- Check `CORE_DEBUG_LEVEL` in platformio.ini (0=none, 5=verbose)
- Enable `#define ESPFILEUPDATER_DEBUG` for update troubleshooting

### Working with yoRadio Updates
- Compare commits between ehRadio and yoRadio repos
- Test display compatibility (most stable merge point)
- Update version in `src/core/options.h` and tag release
- Audio codec changes require careful integration (maleksm's work differs from upstream)

## Key Files Reference
- **Build config**: `platformio.ini`, `myoptions.h`, `mytheme.h`
- **Main entry**: `src/main.cpp` (setup/loop), `ehRadio.ino` (legacy Arduino compatibility)
- **Core services**: `src/core/` (player, display, network, config, controls)
- **Audio decoders**: `src/audioI2S/` (I2S with codecs) or `src/audioVS1053/` (hardware decoder)
- **Display drivers**: `src/displays/` (widgets, fonts, per-model implementations)
- **Web assets**: `data/www/` (HTML/JS/CSS for control interface)
- **HA integration**: `HA/custom_components/ehradio/` (Home Assistant)

## Testing and QA
- **Primary test platform**: ESP32-S3 with various displays
- **Limited support**: ESP8266 dropped, some ESP32 variants untested
- **Display validation**: Boot logo, text scrolling, VU meter, screensaver
- **Audio validation**: Multiple codec formats (AAC, MP3, FLAC, Opus, Vorbis)

## Community and Support
- Automatic builds in Releases for common hardware configs
- Shared configs in `builds/` directory for collaboration
- Online config generator: https://trip5.github.io/ehRadio_myoptions/generator.html