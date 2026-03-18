# ehRadio AI Coding Guide

## About
- **ehRadio**: A fork of [yoRadio](https://github.com/e2002/yoradio) with added Web UI functionality, improved Web UI, usability, and customization.
- **Arduino**: Trip5 hosts firmware files, flashing tools, and Releases on the [Github Repo](https://github.com/trip5/ehRadio) and [Github Page](https://trip5.github.io/ehRadio/)
- **Online Flasher**: Releases are also available through the [ESP Web Tool](https://trip5.github.io/ehRadio/firmware.html)
- **Online Updating**: Files on a running device are updated using ESPFileUpdater from the Releases on the Github Repo.

## ⚠️ Critical Rules
- **Rule #1**: Before making changes spanning more than 25 lines, explain what changes will be made and ask the user to confirm before proceeding.
- **Rule #2**: Before making changes spanning more than 50 lines, stop and tell the user: "This change is large. Please switch to Plan mode so we can review a plan before making edits." Only proceed if the user confirms or switches to Plan mode.
- **Rule #3**: Do not edit `myoptions.h`, `src/core/options.h`, or `platformio.ini` without explicit user confirmation first.

## Project Structure
- **Config Cascade**: `platformio.ini` (env #define) → `myoptions.h` (hardware profile, user defaults) → `mytheme.h` (UI theme) → `options.h` (fallback defaults for anything undefined).
- **Core logic**: `src/core/` (Player, Display, Network, Config, Controls).
- **Libraries path**: Software codecs: `libraries/I2S_Audio/`, `libraries/ES8311_Audio` / Hardware decoder: `libraries/VS1053_Audio/` (Hardware chip), other folders are custom drivers for other display, touchscreen, and other hardware.
- **UI**: Widgets in `src/displays/widgets/`, drivers in `src/displays/`.
- **Plugins**: Class-based hooks in `src/plugins/`, registered in `main.cpp`.
- **Web UI**: Most files in `data/www` are served with headers in `src/core/netserver.h`. `search.html` and `curated.html` are not.

## Functionality
- **Hardware**: The firmware is built according to the hardware that is connected to it and users who will use it.  These are defined by files listed in Config Cascade.
- **Software**: `src/core/options.h` and the Config Cascade should not be used to keep functionality. `#if defined` and `#ifndef` should not be used for configuration not related to hardware.
- **Granular Control in Web UI**: If not hardware-related, functionality should be changeable in the Web UI, not controlled by a `#define` in Config Cascade.
