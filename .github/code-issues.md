# code-issues.md — ehRadio Issue Tracker

Working document for audit findings. Does **not** replace `code-summary.md` (the permanent operational bible).
Delete this file once all items are resolved or explicitly accepted.
Add `(FIXED)` to title after issue is resolved.

**Severity**: `[HIGH]` = silent data corruption or crash risk | `[MEDIUM]` = incorrect behavior or user-facing bug | `[LOW]` = code quality / inconsistency | `[TRIVIAL]` = naming / doc only

---

## [X] 1. Dead or Misnamed Macros (Silent Failure Risk) (ALL FIXED)

These macros are mentioned in comments in `myoptions.h` as something a user can define, but they are **never consumed anywhere in `src/`**. Defining them produces no effect and no error — pure silent failure.

| Macro | Where it appears | Silent-failure scenario |
|---|---|---|
| `WEATHER_IMPERIAL` | `myoptions.h` comment | User defines it expecting imperial units. Nothing changes. Correct macros are `WEATHER_TEMPERATURE_F`, `WEATHER_PRESSURE_MMHG`, `WEATHER_WIND_SPEED_UNITS` (set by `#define WEATHER_METRIC false` in `options.h`). |
| `WEBUI_LANGUAGE_STRING` | `myoptions.h` comment | User defines it expecting to set the WebUI language. Nothing changes. Correct macro is `WEBUI_LOCALE` (used in `src/core/locale.h`). |

**Action**: Remove misleading comments, add correct names with examples in `myoptions.h`. `[MEDIUM]` — user-facing documentation bug.

---

## [X] 2. Dead Defines (Defined But Never Consumed) (ALL FIXED)

These macros are actually **defined** (not just commented) in `myoptions.h` board profiles but are **never read by any code in `src/`**.

| Fixed | Macro | Defined in | Notes |
|---|---|---|---|
| [x] | `PA_ENABLE` | `myoptions.h` ES3C28P profile | Defined as `1`. Zero matches in all of `src/` and in `ES8311_Audio/`. **The actual amp-enable is fully implemented via `MUTE_PIN 1` / `MUTE_VAL HIGH` in `player.cpp` (lines ~54 and ~214).** `PA_ENABLE` is a dead legacy name for the same GPIO — `MUTE_PIN` replaced it. Safe to remove from the profile. |
| [X] | `GFX_BL` | `myoptions.h` (commented out) | Zero matches in `src/`. Possibly a leftover from an alternate display backlight approach. |
| [x] | `TFT_MOSI`, `TFT_SCLK`, `TFT_MISO` | `myoptions.h` ES3C28P profile (values 11, 12, 13) | Zero matches in `src/`. Adafruit_ILI9341 does not read these macros — it takes a `SPIClass*` and calls `spi->begin()` with the bus defaults. Confirmed from `variants/esp32s3/pins_arduino.h`: ESP32-S3 devkitc-1 default SPI pins are exactly `MOSI=11, MISO=13, SCK=12`. These macros are 100% redundant — they match hardware defaults and are never consumed. |
| [x] | `TFT_BL` | `myoptions.h` ES3C28P profile (value 45) | Only exists to be aliased as `#define BRIGHTNESS_PIN TFT_BL`. `BRIGHTNESS_PIN` is the macro actually consumed by `main.cpp` (multiple sites) and has an `options.h` fallback (=255). No library reads `TFT_BL` directly. Could be collapsed to `#define BRIGHTNESS_PIN 45` removing the intermediate name. |
| [x] | `FF_FS_EXFAT` | `myoptions.h` comment — "Does this get carried to SD Lib?" | The comment itself expresses uncertainty. Zero matches in `src/`. Whether it propagates to the SD library at the linker/compile level is unclear. |

**Action**: Remove `PA_ENABLE` — amp control is covered by `MUTE_PIN`. Remove `TFT_MOSI`/`TFT_SCLK`/`TFT_MISO` — confirmed redundant to board defaults. Optionally collapse `TFT_BL` + `BRIGHTNESS_PIN` to a single define. Clarify `FF_FS_EXFAT`. `[LOW]` to `[MEDIUM]`.

---

## [ ] 3. Macros Without `options.h` Fallback

These macros are consumed in `src/` via `#ifdef`/`#if defined` guards (so they are safe when undefined), but they have **no fallback default in `options.h`**. This is inconsistent with how most settings are managed and makes them invisible to someone reading `options.h` for the full feature list.

| Fixed | Macro | Consumed in | Fallback location | Notes |
|---|---|---|---|---|
| [X] | `BIG_BOOT_LOGO` | `displayILI9488.h`, `displayST7796.h`, conf files | None — `#ifdef` only | Safe: undefined = no big logo. But undocumented in `options.h`. |
| [ ] | `DOWN_LEVEL` | `main.cpp` (heavily, with `#ifdef`) | None — optional feature | Safe: undefined = feature disabled. Only present in ILI9488 board profile. |
| [ ] | `DOWN_INTERVAL` | `main.cpp` (heavily, with `#ifdef`) | None — optional feature | Same as `DOWN_LEVEL`. |
| [X] | `FIRMWARE_NAME` | `network.cpp` lines ~337–346 via `#ifdef` | None | Safe: undefined = no firmware name in eHDP discovery. But boards built without a profile won't get a name, and there's no documented way to add one without knowing this macro exists. |
| [x] | `SDSPISPEED` | `sdmanager.cpp` | Fallback defined **inside `sdmanager.cpp`** itself (`#ifndef SDSPISPEED #define SDSPISPEED 20000000`), NOT in `options.h` | Inconsistent pattern. Works fine, but breaks the convention that `options.h` is the canonical fallback location. |
| [X] | `ESPFILEUPDATER_DEBUG` | `config.h` line ~13 via `#ifdef` | None — intentional debug flag | Safe but worth noting in `options.h` as a commented-out debug option. |
| [X] | `MQTT_ENABLE` | `mqtt.h`, `mqtt.cpp`, `netserver.cpp`, `player.cpp`, `commandhandler.cpp`, `main.cpp` — guards the entire MQTT subsystem | None — opt-in feature | Undefined = MQTT disabled. No `#ifndef MQTT_ENABLE` entry in `options.h`. Should appear as a commented-out stub so it's discoverable without consulting board profiles or README. |
| [X] | `RGB_LED_PIN` | `rgbled.cpp` — `#if defined(RGB_LED_PIN) && (RGB_LED_PIN!=255)` guards the entire NeoPixel module | None for `RGB_LED_PIN` itself; `RGB_LED_ORDER` falls back inside `rgbled.cpp`; `NUM_RGB_LEDS` is hardcoded as `1` in `rgbled.cpp` | Undefined = NeoPixel disabled. The `=255 means disabled` convention used for all other pin macros (MUTE_PIN, BRIGHTNESS_PIN, etc.) is not applied here — no options.h entry at all. |
| [X] | `MAX_PL_READ_BYTES` | `netserver.cpp` line ~312 — caps playlist body size during HTTP upload | None anywhere | Undefined = no upper limit on playlist read size. Tuning parameter that should have an options.h default (e.g., something like `65536`). |
| [X] | `PLAYLIST_DEFAULT_URL` | `config.cpp` line ~1307 — seeds default playlist on first boot | None | Undefined = no default playlist URL seeded. Silent, no fallback. Should have a commented stub in `options.h`. |
| [ ] | `SD_SPIPINS` | `config.cpp` line ~75, `sdmanager.h/cpp` — custom SPI pin tuple for SD card | None | Paired feature with `SD_HSPI` which HAS an `options.h` fallback, but `SD_SPIPINS` itself does not. Inconsistent. |
| [ ] | `TS_SPIPINS` | `touchscreen.cpp` lines ~27, ~46 — custom SPI pin tuple for touchscreen | None | Same asymmetry as `SD_SPIPINS` vs `SD_HSPI`. `TS_HSPI` has an `options.h` fallback; `TS_SPIPINS` does not. |
| [X] | `DEBUG_V`, `CORS_DEBUG`, `BATTERY_DEBUG` | Various `src/core/` files | None — intentional debug flags | Same category as `ESPFILEUPDATER_DEBUG`. Three separate debug flags with no options.h entry. Should be grouped as commented-out debug stubs. |

**Action**: Consider documenting these in `options.h` as commented-out stubs so they are discoverable. Move the `SDSPISPEED` fallback from `sdmanager.cpp` to `options.h`. Add `RGB_LED_PIN 255` default following the existing `=255 means disabled` pin convention. Add a default for `MAX_PL_READ_BYTES`. `[LOW]`.

---

## [ ] 4. Write-Only Variables (Set But Never Read)

### [ ] 4.1 `network.trueWeather` `[MEDIUM]`

- **Declaration**: `bool trueWeather;` in `src/core/network.h` line ~24
- **Written**: `config.cpp` (3 assignments), `network.cpp` `getWeather()` return value stored here (2 assignments including the return)
- **Read**: **Zero occurrences anywhere in `src/`**
- **Analysis**: `getWeather()` returns a `bool` indicating whether real weather data was received. The caller stores this in `trueWeather`, but no code path ever checks `trueWeather`. The variable appears intended to track "we have real data vs. placeholder" but the consuming logic was never written (or was removed). The indicator is silently discarded every time.
- **Action**: Either add consuming logic that uses `trueWeather` (e.g., suppress stale display when false), or remove the variable and ignore the return value explicitly at the call sites.

- Trip5 note: This is supposed to track if weathher info held in cache is valid.  Is it seriously not being checked anywhere?  It's supposed to be refreshed according to config.store... weather interval?

---

## [ ] 5. Dead / Unreachable Code

### [ ] 5.1 Duplicate `balance` handler in `commandhandler.cpp` `[MEDIUM]`

- **Line ~30**: `if (strEquals(command, "balance")) { config.setBalance(atoi(value)); return true; }`
- **Line ~118**: `if (strEquals(command, "balance")) { config.setBalance(static_cast<uint8_t>(atoi(value))); return true; }`
- **Analysis**: The handler at line ~30 runs first and always returns `true`. The handler at line ~118 (inside the `//<-----TODO` block) is **unreachable dead code**. It will never execute.
- **Side effect of the dead code**: The cast at line ~118 is also wrong — it casts to `uint8_t` before passing to `int8_t`, which corrupts negative balance values (e.g., -10 → `uint8_t` 246 → `int8_t` -10 by accident in twos-complement, but values like -100 → `uint8_t` 156 → `int8_t` -100, so actually they happen to be equivalent for most values due to twos-complement... BUT the intent is wrong and a future reader would see a bogus cast).
- **The live handler (line ~30)** has its own problem: it passes raw `int` from `atoi()` directly with no cast and no range clamp (see Section 6.1 below).
- **TODO block context**: The `//<-----TODO` marker separates two groups of handlers. Commands BELOW the marker (`volume`, `sdpos`, `shuffle`, `reboot`, `format`, `submitplaylist`, `irbtn`, `chkid`, `irclr`, etc.) are **not duplicates** — they are the only handlers for those commands. Only `balance` is accidentally duplicated. This indicates an **incomplete refactoring**: some commands were being migrated or reworked, but the work stopped partway. The entire EQ missing-handler situation (`treble`, `bass`, `middle`) is a direct result of this same incomplete state — see Section 8.1.
- **Action**: Remove the dead handler at line ~118. Fix the live handler at line ~30 (see Section 6.1).

### [ ] 5.2 `|| true` dead branch in `player.cpp` `[LOW]`

- **Line 132**: `if (strlen(file)==0 || true) return; //TODO Read TAGs`
- **Analysis**: `|| true` permanently short-circuits to `true`. Any code below this `return` is unreachable. This appears to be an acknowledged TODO — someone commented out the tag-reading functionality with `|| true` as a temporary measure that became permanent.
- **Action**: Either implement the tag-reading block and remove `|| true`, or remove the `|| true` and let `strlen(file)==0` be the real condition. The current state is confusing because it looks like a real condition check when it is not.

---

## [ ] 6. Incorrect Casts / Type Safety Issues

- [ ] Extra: sort and comment all commands in `commandhandler.cpp` according to their order in WebUI

### [ ] 6.1 `balance` command — no range clamp, implicit narrowing `[MEDIUM]`

- **File**: `src/core/commandhandler.cpp` line ~30
- **Code**: `config.setBalance(atoi(value))`
- **Signature**: `Config::setBalance(int8_t balance)` in `config.cpp`
- **Problem**: `atoi()` returns `int`. Passing it to `int8_t` is an implicit narrowing conversion. Values outside −128..127 silently truncate. No input validation. Compare how `dim` command clamps before cast (e.g., `val < 0 ? 0 : val > 100 ? 100 : val`).
- **Action**: Add `int b = atoi(value); b = (b < -16) ? -16 : (b > 16 ? 16 : b); config.setBalance(static_cast<int8_t>(b));` at the live handler. The correct range is **-16..16**, matching: (1) the HTML slider (`min="-16" max="16"`), (2) the `options.h` compile-time `SOUND_BALANCE` validation guard (`#elif (SOUND_BALANCE < -16) || (SOUND_BALANCE > 16)`). The prior suggestion of -100..100 in this document was incorrect.

### [ ] 6.2 `brightness` command — no range clamp before `uint8_t` cast `[MEDIUM]`

- **File**: `src/core/commandhandler.cpp` line ~69
- **Code**: `config.store.brightness = static_cast<uint8_t>(atoi(value));`
- **Problem**: `atoi()` on a negative or very large string silently wraps into a garbage `uint8_t`. The nearby `dim` command at line ~46 properly clamps with a ternary to 0..100.
- **Action**: Clamp `atoi(value)` to **0..100** before the cast (matching the HTML slider `min="0" max="100"` and the `dim` handler which also clamps to 0..100). Not 0..255.

### [ ] 6.3 `contrast` command — same pattern as `brightness` `[LOW]`

- **File**: `src/core/commandhandler.cpp` — the `contrast` command
- **Code**: `config.saveValue(&config.store.contrast, static_cast<uint8_t>(atoi(value)))`
- **Problem**: Same unclamped `uint8_t` cast. Input from the WebUI is expected to be 0..100 (HTML slider `min="0" max="100"`) but no firmware guard enforces this.
- **Action**: Clamp to **0..100** before cast, consistent with the HTML slider range.

---

## [ ] 7. Logic / Correctness Bugs (from `code-summary.md` Known Issues)

### [ ] 7.1 `display.cpp` — `while(!_bootStep==0)` precedence bug `[MEDIUM]`

- **Line 113**: `while(!_bootStep==0) { delay(10); }`
- Due to C++ operator precedence, this evaluates as `(!_bootStep) == 0`. When `_bootStep = 0` (initial state), `!0 = 1`, `1 == 0 = false` → loop exits immediately without waiting. When `_bootStep = 1` or `2`, `!x = 0`, `0 == 0 = true` → loop runs indefinitely.
- Likely intent was `while(_bootStep == 0)` (wait for boot to start) or `while(_bootStep < 2)` (wait for boot to complete).
- `_bootStep` is `uint8_t` in `display.h` line ~83.

### [ ] 7.2 `netserver.cpp` — upload cleanup deletes wrong file `[HIGH]`

- Upload cleanup block: `if (SPIFFS.exists(INDEX_PATH)) SPIFFS.remove(PLAYLIST_PATH)` — should call `SPIFFS.remove(INDEX_PATH)`. The index file is never cleaned up; the playlist may be deleted instead.

### [x] 7.3 `optionschecker.h` — weather interval guard mismatch `[LOW]` (FIXED)

- Guard message says "10 to 60" but the enforced condition is "1 to 24". Message and bounds are mismatched.
- FIXED

### [ ] 7.4 `netserver.cpp` — `selectRadioBrowserServer()` `size_t` underflow `[HIGH]`

- `for (size_t i = count - 1; i > 0; --i)` runs even when `count == 0`. `size_t` is unsigned, so `0 - 1` wraps to a very large value and the loop indexes out of bounds.
- `rb_servers[count] = RADIO_BROWSER_SERVER` also writes past the array end when `count == arr_size`.

---

## [ ] 8. Unhandled or Mis-handled Web UI Commands

### [ ] 8.1 `treble`, `middle`, `bass` bypass `commandhandler` — split routing `[MEDIUM]`

- **Context**: All four EQ sliders in `player.html` have `data-command` values matching their names (`balance`, `treble`, `middle`, `bass`), all with `min="-16" max="16"`. Moving a slider sends `command=value` via WebSocket.
- **`balance`**: Handled in `commandhandler.cpp` at line ~30 (above the `//-----TODO` marker).
- **`treble`, `middle`, `bass`**: **Not present in `commandhandler.cpp` at all.** They are intercepted in `netserver.cpp` directly (lines ~614–627), *before* `cmd.exec()` is called, in the raw WebSocket message handler.
- **Split routing impact**: Commands handled in `netserver.cpp` before `cmd.exec()` cannot be triggered via MQTT (`mqtt.cpp` calls `cmd.exec()`), telnet (also routes through `cmd.exec()`), or any future command source added to `commandhandler`. Concretely: `balance` works via MQTT and telnet; `treble`/`middle`/`bass` do not.
- **Root cause**: `treble`/`middle`/`bass` were added directly to `netserver.cpp` as a shortcut while `balance` was added to `commandhandler` as part of the incomplete TODO-block refactoring (see Section 5.1). The intent was clearly for all four to be in `commandhandler`, but the work was never finished.
- **Action**: Move the `treble`, `middle`, `bass` handlers from `netserver.cpp` into `commandhandler.cpp` alongside `balance`. Use `config.setTone()` the same way those handlers already do. Add appropriate clamping (see Section 8.2).

### [ ] 8.2 All four EQ commands lack server-side range clamping `[MEDIUM]`

- **`treble`, `middle`, `bass`** handlers in `netserver.cpp`: `int8_t valb = atoi(val)` is an implicit narrowing cast with no range validation.
- **`balance`** handler in `commandhandler.cpp`: passes raw `atoi(value)` directly to `int8_t` param (see Section 6.1 for the live handler; section 6.1 recommended clamp has been corrected to -16..16 in this update).
- The valid range **-16..16** is enforced consistently in three places: (1) HTML sliders with `min="-16" max="16"`, (2) `options.h` `SOUND_BALANCE` guard `#elif (SOUND_BALANCE < -16) || (SOUND_BALANCE > 16)`, and (3) `options.h` `EQ_TREBLE`/`EQ_MIDDLE`/`EQ_BASS` guards with the same -16..16 bounds. The firmware runtime handlers are the only place that does not enforce this.
- **Action**: Each EQ command handler should clamp: `int v = atoi(val); v = (v < -16) ? -16 : (v > 16 ? 16 : v); config.setXxx((int8_t)v);`

### [ ] 8.3 `volume` command (WebUI slider) vs `vol` command — inconsistent behavior `[MEDIUM]`

- **HTML sends `volume=N`**: The volume slider uses `data-command="volume"`, so `sliderInput()` sends `volume=N` to the backend.
- **Handler for `volume=N`** (commandhandler.cpp TODO block, line ~119): `player.setVol(static_cast<uint8_t>(atoi(value)))` — queues `PR_VOL` asynchronously; `config.store.volume` is only updated when the queue processes (via `config.setVolume()` inside `PR_VOL` handler in `player.cpp`).
- **Handler for `vol=N`** (commandhandler.cpp line ~40, above TODO): Clamps value to 0..254, **synchronously** updates `config.store.volume = clamped_v`, then queues `player.setVol(v)`. This is the robust path used by MQTT, telnet, and IR.
- **Behavioral differences**:
  1. `volume` handler: no clamp before `uint8_t` cast (negative values or values > 255 silently wrap).
  2. `volume` handler: `config.store.volume` lags until `PR_VOL` processes. If `VOLUME` is broadcast between receiving the command and the queue processing, the old value is reported.
  3. `vol` handler: proper clamp, immediate synchronous config update.
- **Action**: Either consolidate both commands into one handler using the `vol` pattern (clamp + synchronous update), or fix the `volume` handler to match: clamp to 0..254 and synchronously set `config.store.volume` before calling `player.setVol()`.

### [ ] 8.4 `submitplaylistdone` intercepted in `netserver.cpp` before `cmd.exec()` `[LOW]`

- **Location**: `netserver.cpp` `onWsMessage()`, lines ~630–645 — handled **before** `cmd.exec()` is called.
- **Sent by**: `script.js` sends `websocket.send('submitplaylistdone=1')` after the server has confirmed the playlist file was saved. This triggers MQTT republish and playlist-length validation in the firmware.
- **Routing impact**: Same as 8.1 — any MQTT or telnet path that sends `submitplaylistdone` falls through `cmd.exec()` unhandled (returns `false`). Currently this only matters for testing or automation, since it's an internal JS signal.
- **Action**: Low priority. Consider moving to `commandhandler.cpp` for consistency.

### [ ] 8.5 `sleep` / `after` — HTTP GET only, no WebSocket path `[MEDIUM]`

- **Location**: `netserver.cpp` `handleIndex()` — the catch-all HTTP GET handler for `/`.
- **Code**: `if (request->hasArg("sleep")) { ... config.sleepForAfter(sford, safterd); ... }`
- **What it does**: Schedules the device to sleep for `sleep` minutes, starting `after` minutes from now. A sleep timer feature.
- **Access**: HTTP GET URL parameters only — e.g., `http://device/?sleep=30&after=5`. There is **no WebSocket equivalent** (`sleep` is absent from `commandhandler.cpp`), so MQTT, telnet, and the WebUI cannot trigger it.
- **No HTML entry point**: No HTML element in any `.html` file exposes this feature. It exists as an undocumented HTTP-only API.
- **Action**: Either add a `sleep` command to `commandhandler.cpp` (and expose it via the WebUI settings page), or document it as intentionally HTTP-only. Its absence from the WebUI means most users are unaware it exists.

### [ ] 8.6 HTTP GET `treble`+`middle`+`bass` multi-param route `[LOW]`

- **Location**: `netserver.cpp` `handleIndex()` — checked after the single-param `cmd.exec()` branch.
- **Code**: `if (request->hasArg("treble") && request->hasArg("middle") && request->hasArg("bass")) { config.setTone(...) }`
- **Analysis**: A legacy URL-parameter API that sets all three EQ bands at once: `http://device/?treble=3&middle=0&bass=-2`. Not used by any current JS code. No clamping is applied to the integer values before passing to `config.setTone(int8_t, int8_t, int8_t)`.
- **Relation to 8.1**: The WebSocket path for individual `treble`/`middle`/`bass` is in `netserver.cpp` onWsMessage. The HTTP path for all three together is here. Neither path goes through `commandhandler`.
- **Action**: Remove or consolidate. If kept, add -16..16 clamping to match the HTML slider range.

---

## [ ] 9. Commands with No HTML Entry Point

These commands exist in `commandhandler.cpp` (or elsewhere in firmware) but **cannot be triggered from any `.html` file** in the WebUI. They are reachable only via MQTT, telnet, HTTP GET URL params, or are effectively inaccessible to most users.

| Fixed | Command | Handler location | How accessible | Notes |
|---|---|---|---|---|
| [ ] | `start` | `commandhandler.cpp` | MQTT, telnet, HTTP `/?start=1` | Plays last station. No HTML button. The WebUI uses `toggle` for play/pause instead. |
| [ ] | `stop` | `commandhandler.cpp` | MQTT, telnet, HTTP `/?stop=1` | Stops playback. No HTML button. |
| [ ] | `dspon` | `commandhandler.cpp` | MQTT, telnet, HTTP `/?dspon=N` | Identical to `screenon`. Both remain in commandhandler but their HTML element is **commented out** in `options.html` line 120 with note: *"Left from yoRadio but seems to have no purpose"*. |
| [ ] | `screenon` | `commandhandler.cpp` | MQTT, telnet | Same as `dspon`. HTML element commented out. |
| [ ] | `clearspiffs` | `commandhandler.cpp` | MQTT, telnet, HTTP `/?clearspiffs=1` | Clears SPIFFS and resets play mode. No HTML button. Useful for factory cleanup but not exposed to users. |
| [ ] | `sleep` | `netserver.cpp` `handleIndex()` | HTTP `/?sleep=N&after=N` **only** | Schedules sleep timer. No WebSocket handler. No HTML. See Section 8.5. |
| [ ] | `playstation` | `commandhandler.cpp` (alias for `play`) | MQTT, telnet | The HTML uses `play=N` (via `websocket.send(\`play=${item}\`)`). `playstation` is a legacy alias; both spellings work. |

**Notes**:
- `start`, `stop`, and `dspon`/`screenon` are yoRadio leftovers that were never assigned HTML buttons in the ehRadio fork. Their presence in `commandhandler.cpp` is not harmful — they remain useful for MQTT/telnet automation — but they add dead weight to the handler if never used interactively.
- `clearspiffs` and `sleep` are subtle traps: a user configuring MQTT automations would have no way to discover these commands from the WebUI documentation or source code without reading `commandhandler.cpp` directly.

**Action items**:
- `dspon` / `screenon`: Remove the duplicate or point both to the same implementation. Decide whether to restore the HTML element or remove the command.
- `sleep`: Expose via a WebUI sleep-timer control (options page) or remove from firmware if the feature is not intended for production use.
- Document all MQTT/telnet-accessible commands in one place (currently they must be inferred by reading `commandhandler.cpp` and `telnet.cpp` separately).

---

## [ ] 10. `BUFLEN` — Multi-Purpose Magic Number

`BUFLEN = 170` is defined in `options.h` (`#define BUFLEN 170 // 170 seems safe... a lot of multipliers exist in the code...`). The comment itself is a warning sign: "a lot of multipliers exist" means 170 was already insufficient for some callers when it was written.

### 10.1 Call-site inventory

| Call site | File | Purpose | Notes |
|---|---|---|---|
| `StationInfo::name[BUFLEN]`, `::url[BUFLEN]`, `::title[BUFLEN]` | `config.h` struct | Runtime RAM fields — populated from SPIFFS playlist file | **Not NVS-stored.** Only `store.lastStation` (a `uint16_t` index) is persisted. `station.title` is from stream metadata, never saved. Changing BUFLEN just changes truncation threshold for long names/URLs. |
| `Config::_stationBuf[BUFLEN/2]` | `config.h` | Temporary CSV row parsing buffer | Consistent with playlist tab-fragment size |
| `sName[BUFLEN]`, `sUrl[BUFLEN]` | `config.cpp`, `telnet.cpp` | Stack temps matching struct field size | Consistent |
| `utf8_common.h`, `utf8Latin.cpp`, `utf8Cyrillic.cpp`, `nextion.cpp` | Display tools | Transliteration output buffer | Correct to match `title` field size |
| `audiohandlers.h` `b[BUFLEN/2]` | Audio handlers | Bitrate info string (85 bytes) | Adequate for bitrate strings |
| `audiohandlers.h` `tmp[BUFLEN]` | Audio handlers | Station title + audio info combined | Appropriate |
| `nomedia[BUFLEN]` | `sdmanager.cpp` | SD path building (`path + "/.nomedia"`) | Wrong semantic — SD paths can exceed 170 chars |
| `wsbuf[BUFLEN*2]`, `payload[BUFLEN*2]`, `buf[BUFLEN*2]`, `msgBuf[BUFLEN*2]`, `varjsbuf[BUFLEN*2]` | `netserver.cpp` | WebSocket JSON payloads, URL buffers | `*2` multiplier is a code smell — see 10.2 |
| `buf[BUFLEN]`, scratch uses | `telnet.cpp`, `netserver.cpp` | Short `snprintf` scratch buffers | Acceptable for short messages |
| `BOOTLOG` macro | `telnet.h` | Boot log buffer with bare `sprintf` | Overflow risk — cross-ref Section 11 |

### 10.2 The `*2` and `/2` multiplier smell `[MEDIUM]`

Five places in `netserver.cpp` use `BUFLEN*2` (340 bytes) because 170 was insufficient for JSON payloads. The code doubled an already-arbitrary number rather than defining an appropriately-sized constant. This conflates two unrelated constraints in one macro:

- **`wsbuf[BUFLEN*2]` with bare `sprintf`**: embeds `config.station.name` (up to 170 bytes) and `config.station.title` (up to 170 bytes) simultaneously into a 340-byte buffer with JSON framing overhead. At worst-case inputs, this is structurally too small. Already flagged in Section 11 as unsafe `sprintf`.
- The multiply/divide pattern (`*2`, `/2`) makes the actual buffer sizes invisible and means any future change to `BUFLEN` for the struct silently changes all these buffers too.

### 10.3 No NVS tie-in — RAM only `[correction]`

`station_t` (`name`, `url`, `title`) is **not stored in NVS**. `loadStation()` reads the SPIFFS playlist file at runtime and fills `station` in RAM. `station.title` is set from audio stream metadata and is never persisted. The only NVS save is `store.lastStation` — a `uint16_t` index.

Changing `BUFLEN` carries **no NVS migration risk**. The only behavioral change would be the truncation threshold for very long station names or URLs read from the playlist. Raising it does increase stack frame sizes wherever `char buf[BUFLEN]` locals are declared. The `*2` multipliers in `netserver.cpp` still exist as a sizing smell, but the cause is simpler: the JSON payload combining name + title was larger than a single BUFLEN.

### 10.4 Relationship to `RXBUFLEN` / `TXBUFLEN`

`RXBUFLEN = 50` and `TXBUFLEN = 255` are defined in `src/displays/nextion.h`. They are **completely unrelated** to `BUFLEN` — they are Nextion serial protocol frame sizes. The naming similarity is coincidental.

### 10.5 Other buffer-size constants not derived from `BUFLEN`

| Constant | Where | Value | Notes |
|---|---|---|---|
| `SET_PLAY_ERROR` buff size | `player.h` macro | `512 + 64` = 576 | Fixed literal; independent. Bare `sprintf` — see Section 11. |
| `DBGVB` buf size | `netserver.cpp` macro | `200` | Fixed literal; bare `sprintf` — see Section 11. |
| `MAX_PRINTF_LEN` | `telnet.h` | `BUFLEN + 50` = 220 | Derived from `BUFLEN`. If `BUFLEN` changes, this changes silently too. |
| `EHDPNAME_LENGTH` | `config.h` | `24` | Named purpose-specific constant — **this is the right pattern**. |

### 10.6 Recommended resolution `[LOW]`

The core problem: `BUFLEN` conflates two distinct things that happen to share one numeric value:
1. **Station field size** (`StationInfo` fields and matching transliteration buffers) — the meaningful semantic is "max station name/URL/title length".
2. **General scratch sentinel** — arbitrary "safe size" for stack temporaries.

Recommended approach: introduce `STATION_FIELD_LEN` (or similar) for category 1, making the intent explicit. Leave `BUFLEN` as-is or remove it for category 2. Replace `BUFLEN*2` and `BUFLEN/2` with purpose-named sizes or comment-justified literals. This is a **refactor, not an urgent fix** — nothing is currently broken solely because of `BUFLEN` — and unlike the previous analysis, there is **no NVS migration risk** involved.

### [ ] 10.7 Replacing `BUFLEN` Usage as a Magic Number

Each call site below should be investigated and given either a purpose-specific named constant or an inline literal with a justifying comment.

- [ ] `StationInfo::name[BUFLEN]`, `::url[BUFLEN]`, `::title[BUFLEN]` (`config.h`) — primary semantic: "max station name/URL/title length". Candidate: introduce `STATION_FIELD_LEN 170`.
- [ ] `Config::_stationBuf[BUFLEN/2]` (`config.h`) — name explicitly (e.g., `STATION_FIELD_LEN/2`) or justified inline literal.
- [ ] `sName[BUFLEN]`, `sUrl[BUFLEN]` in `config.cpp`, `telnet.cpp` — stack temps matching struct field size; update to follow `STATION_FIELD_LEN` once defined.
- [ ] Transliteration output buffers in `utf8_common.h`, `utf8Latin.cpp`, `utf8Cyrillic.cpp`, `nextion.cpp` — should match `title` field size; update to `STATION_FIELD_LEN`.
- [ ] `b[BUFLEN/2]` in `audiohandlers.h` (bitrate string, 85 bytes) — adequate size; name it or leave as explicit literal with comment.
- [ ] `tmp[BUFLEN]` in `audiohandlers.h` (title + audio info combined) — appropriate; update to `STATION_FIELD_LEN`.
- [ ] `nomedia[BUFLEN]` in `sdmanager.cpp` (SD path building) — wrong semantic; SD paths can exceed 170 chars. Replace with a purpose-specific `SD_PATH_LEN` or explicit larger literal.
- [ ] `wsbuf[BUFLEN*2]`, `payload[BUFLEN*2]`, `buf[BUFLEN*2]`, `msgBuf[BUFLEN*2]`, `varjsbuf[BUFLEN*2]` in `netserver.cpp` — the `*2` is the smell. Each should become a justified literal or purpose-named size.
- [ ] `buf[BUFLEN]` scratch uses in `telnet.cpp`, `netserver.cpp` — evaluate each; either leave with an explicit literal + comment, or retain `BUFLEN` if it remains as a general scratch sentinel.
- [ ] `BOOTLOG` macro buffer `buf[BUFLEN]` in `telnet.h` — also has bare `sprintf` overflow risk (cross-ref Section 11); address rename alongside `snprintf` fix.
- [ ] `MAX_PRINTF_LEN = BUFLEN + 50` in `telnet.h` — must not silently change if `BUFLEN` changes for other reasons. Replace with explicit `220` or `STATION_FIELD_LEN + 50` with comment.

---

## [ ] 11. Unsafe String Handling / Buffer Overflow Risks

| Fixed | Location | Issue |
|---|---|---|
| [ ] | `config.cpp` `u8fix()` | `src[strlen(src)-1]` with no empty-string guard — UB if `strlen(src) == 0`. |
| [ ] | `sdmanager.cpp` | `strrchr(filePath, '/') + 1` — if `strrchr` returns NULL, `NULL+1` is UB. |
| [ ] | `nextion.cpp` rx buffer | `rx_pos` incremented without bounds check against `RXBUFLEN` (50). Overflow on long frames. |
| [ ] | `nextion.cpp` `sscanf` | `sscanf(rxbuf, "page=%s", scanBuf)` uses `%s` without width; `scanBuf[50]` can overflow by prefix length. |
| [ ] | `commandhandler.cpp` `irclr` | `config.irindex` initialized to -1; `irVals[config.irindex][...]` is out-of-bounds if `irclr` sent before `chkid`. Also second subscript from `atoi` can be 0–255 but array dim is only 3. |
| [ ] | `netserver.cpp` `STATIONNAME`/`TITLE` | `sprintf(wsbuf, ...)` embeds ~170-byte fields into a 340-byte buffer with JSON framing. Near-limit inputs can overflow. |
| [ ] | `netserver.cpp` `DBGVB` macro | `char buf[200]; sprintf(buf, __VA_ARGS__)` — VA_ARGS controlled by callers, no overflow guard. |
| [ ] | `network.cpp` `strcpy(weatherBuf, LANG::weather_loading)` | `weatherBuf` is 254 bytes; locale string has no enforced max. Long translations overflow. |
| [ ] | `network.cpp` weather builder | Chained `sprintf` advancing pointer `p` across `weatherBuf` (254 bytes) with no remaining-length checks. |
| [ ] | `telnet.h` `BOOTLOG` macro | `sprintf(buf, __VA_ARGS__)` into `buf[BUFLEN]` (170 bytes); no VA_ARGS overflow guard. |
| [ ] | `player.h` `SET_PLAY_ERROR` macro | `sprintf(buff, __VA_ARGS__)` into `buff[576]`; caller-controlled VA_ARGS. |
| [ ] | `widgets.cpp` date string | `sprintf(_tmp, "%2d %s %d", ..., LANG::mnths[...], ...)` into `_tmp[30]`; UTF-8 month names have more bytes than display characters; 30-byte buffer can overflow with multi-byte locale encodings. |

---

## [ ] 12. WebUI / JavaScript Security Issues

| Fixed | Location | Issue |
|---|---|---|
| [ ] | `data/www/search.js` | `${station.name}` injected into `innerHTML` without escaping. Station names from Radio Browser API (external, untrusted). Script injection risk. `escapeHtml()` exists in `curated.js` but not applied here. |
| [ ] | `data/www/curated.js` | `curatedName` and `curatedLink` injected into `innerHTML` without escaping despite `escapeHtml()` being available in the same file. `curatedLink` also used as `href` with no URL scheme validation (`javascript:` scheme attack vector). |

---

## [ ] 13. Stability / Architecture Risks

Items below are **already documented in `code-summary.md`** Known Issues section. Listed here for consolidated tracking.

- `nextion.cpp`: file starts with explicit warning comment that implementation may be broken; treat as unstable until revalidated.
- `telnet.cpp`: duplicated command form list vs. `commandhandler.cpp`; new settings added to one path are easily missed in the other.
- `touchscreen.h`: enum member naming inconsistency `TDS_REQUEST` vs. `TSD_*` pattern.
- Heavy async queue and task usage — ordering/race conditions are possible (display queue, netserver queue, search/curated/update tasks).
- SPIFFS space constraints can silently break search, curated, and update workflows.

---

## [ ] 14. Dead / Redundant Includes (`netserver.cpp`) `[LOW]`

`src/core/netserver.cpp` contains duplicate `#include` directives (include guards make them a no-op at compile time, but they add noise):

| Fixed | Duplicate | Lines |
|---|---|---|
| [ ] | `#include "config.h"` | Lines 7 AND 11 — two identical includes |
| [ ] | `#include "options.h"` | Lines 1 AND 15 — two identical includes |
| [ ] | `//= #include <ESPmDNS.h>` | Line 25 — commented-out redundant copy of the active include on line 5 |

**Action**: Remove the second `#include "config.h"` (line 11), the second `#include "options.h"` (line 15), and the commented-out dead include on line 25. `[LOW]` — no runtime impact.

---

## [ ] 15. Include Path Convention Inconsistency `[TRIVIAL]`

Most `src/core/*.cpp` files include peer headers using relative names (`#include "battery.h"`), but `battery.cpp` and `rgbled.cpp` use fully-prefixed paths (`#include "core/battery.h"`, `#include "core/rgbled.h"`) even for their **own** headers. This works because PlatformIO exposes both `src/` and `src/core/` as include roots, but the mixed convention is confusing.

Notable cases:
- `battery.cpp` includes `"core/battery.h"` (self-include with prefix) and all peers with `"core/xxx.h"`
- `rgbled.cpp` includes `"core/rgbled.h"` (self-include with prefix)
- `commandhandler.cpp` includes `"core/battery.h"` but `"commandhandler.h"` without prefix

**Action**: Normalise to either all-relative (preferred for files in `src/core/`) or all-prefixed, not mixed. Low priority but makes `#include` scanning clearer. `[TRIVIAL]`

---

## 16. Dead Function Scan Result — No Orphans Found

All declared public/free functions in `src/core/*.h` were verified to have at least 3 references (declaration + definition + ≥1 call site). No dead-function candidates identified.

Notable verified-live functions that looked suspicious: `spiffsCleanup`, `deleteOldKeys`, `deleteMainwwwFile`, `purgeUnwantedFiles`, `fixPlaylistFileEnding`, `cleanStaleSearchResults`, `getRequiredFiles`, `checkNewVersionFile`, `rebootTime`, `_wwwFilesExist`, `_initHW`, `getChipId`.

---

## 99. Stuff I found

  netserver.loop(); is twice in player.cpp line 241
