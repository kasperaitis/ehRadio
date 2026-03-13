# ehRadio — Languages, Fonts & Codepages

This document explains the full localization pipeline: how a language selection flows from a single define in `myoptions.h` all the way to characters appearing on the display.

---

## Table of Contents

1. [Overview](#overview)
2. [Configuration Cascade](#configuration-cascade)
3. [Picking a Language — `DSP_LANGUAGE`](#picking-a-language--DSP_LANGUAGE)
4. [Codepages — `L10N_CODEPAGE`](#codepages--l10n_codepage)
5. [Locale Files (`displayL10n_*.h`)](#locale-files-displayl10n_h)
6. [The Include Chain (`l10n.h`)](#the-include-chain-l10nh)
7. [Custom Locale Override](#custom-locale-override)
8. [UTF-8 Text Processing Pipeline](#utf-8-text-processing-pipeline)
9. [GLCD Font & Glyph System](#glcd-font--glyph-system)
10. [How to Add a New Glyph](#how-to-add-a-new-glyph)
11. [Weather Language (`weatherLang`)](#weather-language-weatherlang)
12. [How to Add a New Language](#how-to-add-a-new-language)
13. [WebUI i18n](#webui-i18n)
14. [Developer Tools](#developer-tools)

---

## Overview

The display on an ESP32 radio uses a **bitmap GLCD font** (Adafruit GFX style). This font has a fixed set of glyphs — it cannot render arbitrary Unicode on the fly. The localization system solves this in two ways:

- For **ASCII + a small set of extended characters** that are baked into the active font file, strings are passed straight to the display renderer.
- For everything else (accented Latin letters, Cyrillic letters not in the font, etc.), a **UTF-8 → transliteration / normalization** pass converts the string to displayable characters before rendering.

The active language also controls UI strings (day names, month names, wind directions, etc.) and the language code sent to the OpenWeather API.

Separately, the **WebUI** (served from the device over Wi-Fi) has its own runtime i18n layer: translated strings are loaded from a small JSON file on the device filesystem, so the settings and player pages can be displayed in the local language without any firmware recompile.

---

## Configuration Cascade

Settings are applied in this order — later entries override earlier ones:

```
src/core/options.h          ← built-in system defaults (DO NOT EDIT)
         ↓
myoptions.h                 ← your hardware & locale overrides
         ↓
mytheme.h                   ← colour / UI overrides (optional)
```

All language and codepage configuration belongs in **`myoptions.h`**.

Language selection is **compile‑time only**.

---

## Picking a Language — `DSP_LANGUAGE`

In `myoptions.h`, set:

```cpp
#define DSP_LANGUAGE ru_RU
```

If `DSP_LANGUAGE` is not defined, it defaults to `en_US`.

---

## Codepages — `L10N_CODEPAGE`

The codepage controls **which extended character set is baked into the GLCD font** and therefore which characters can be rendered natively without transliteration.

| Constant | Value | Meaning |
|---|:---:|---|
| `L10N_CP_LATIN` | 1 | Latin extended glyphs (accented Latin letters: à, é, ü, ø, etc.) |
| `L10N_CP_CYRILLIC` | 2 | Cyrillic glyphs (А–Я, plus language-specific extras like Є, Ї, Ґ, Ё, І) |

### Auto-detection

You do **not** need to set `L10N_CODEPAGE` manually. The preprocessor in `options.h` automatically selects the correct codepage based on `DSP_LANGUAGE`:

- Cyrillic is automatically selected for: `ru_RU`, `uk_UA`, `be_BY`, `bg_BG`, `mk_MK`, `sr_RS`, `me_ME`, `uz_UZ`, `kk_KZ`, `tg_TJ`, `ky_KG`, `mn_MN`
- All other languages default to `L10N_CP_LATIN`

### Forcing a codepage

To override the auto-detected codepage, add to `myoptions.h`:

```cpp
#define L10N_CODEPAGE L10N_CP_CYRILLIC   // or L10N_CP_LATIN
```

### Effect on rendering

The active codepage affects three things:

1. **Which GLCD font file is linked** — `glcdfont_Latin.c` or `glcdfont_Cyrillic.c` (selected by `builds/platformio_pre_replace_font.py` during the build). Display drivers use the static `font[]` array provided by the Adafruit GFX library; no runtime pointer or switching is involved.
2. **Which characters `shouldPreserveChar()` passes through** — preserved characters are written as raw UTF-8 bytes directly to the display buffer; non-preserved characters are transliterated.
3. **Case handling** — both font variants carry **uppercase glyphs only**. In both codepages, lowercase extended characters are accepted and rendered using the uppercase glyph. The mechanism differs:
   - **Cyrillic:** lowercase codepoints U+0430–U+044F fall inside the preserve range and are explicitly remapped to their uppercase equivalents U+0410–U+042F before being written to the output buffer.
   - **Latin:** both the uppercase and lowercase codepoint for each accented letter are listed in `LATIN_PRESERVE[]`, and `utf8Latin.cpp` maps both to the same (uppercase) glyph slot — e.g. `à` (C3 A0) and `À` (C3 80) both write glyph index `0x80`, which holds the uppercase `À` bitmap.

---

## Locale Files (`displayL10n_*.h`)

Each locale file lives in `src/locale/` and is named using the full IETF BCP 47 format:

```
src/locale/displayL10n_en_US.h
src/locale/displayL10n_ru_RU.h
src/locale/displayL10n_uk_UA.h
...
```

Every locale file defines the same set of `PROGMEM` string constants placed in the `LANG` namespace:

| Constant group | Example values |
|---|---|
| Short day names | `mon`, `tue`, `wed`, `thu`, `fri`, `sat`, `sun` |
| Full day names | `monday`, `tuesday`, `wednesday`, … |
| Month names | `jan`, `feb`, `mar`, … `dec` |
| Wind direction strings | `wn_N`, `wn_NE`, `wn_E`, … `wn_NNW` |
| Weather condition labels | `wc_thunder`, `wc_rain`, `wc_snow`, `wc_clear`, etc. |
| OpenWeather language code | `weatherLang[]` — the API lang parameter sent to OpenWeather |

All strings are stored in flash (`PROGMEM`) to conserve RAM on the ESP32.

---

## The Include Chain (`l10n.h`)

`src/displays/tools/l10n.h` is the single include point for locale strings. It:

1. Checks `DSP_LANGUAGE` with an `#if / #elif` ladder and sets `L10N_PATH` to the matching locale file path.
2. Checks whether `src/locale/displayL10n_custom.h` exists — if so, it is included **instead** of the auto-selected locale file (see [Custom Locale Override](#custom-locale-override)).
3. Wraps everything inside `namespace LANG { ... }` so locale strings don't pollute the global namespace.

All display code that needs localized strings includes `l10n.h` and accesses strings as `LANG::mon`, `LANG::weatherLang`, etc.

---

## Custom Locale Override

If you need to modify UI strings without touching the built-in locale files, create:

```
src/locale/displayL10n_custom.h
```

This file, if present, completely replaces the auto-selected locale — the compiler will not include the standard `displayL10n_*.h` at all. Copy the locale you want to base yours on and edit from there.

Add it to your `.gitignore` so it will persist across project updates.

---

## UTF-8 Text Processing Pipeline

Station metadata (song titles, station names) arrives as UTF-8 strings. These strings may contain characters that the GLCD font cannot display directly. The processing pipeline decides what to do with each character.

### Modules

| File | Role |
|---|---|
| `utf8To.cpp/.h` | **Entry point.** `utf8To(str, uppercase)` — calls `canRenderNative()` first; if the string is fully renderable, returns it unchanged. Otherwise calls `utf8ToAscii()`. |
| `utf8_common.h/.cpp` | Shared tables and inline logic: `shouldPreserveChar()`, `canRenderNative()`, `utf8ToAscii()`, `transliterateCyrillic()`. Contains both the Latin mapping table (`LATIN_MAP`) and the Cyrillic transliteration table (`CYRILLIC_MAP`). |
| `utf8Cyrillic.cpp/.h` | Cyrillic-specific processing (used by the Cyrillic codepage path). |
| `utf8Latin.cpp/.h` | Latin extended normalization (used by the Latin codepage path). |

### Decision flow

```
utf8To(str)
    │
    ├─ canRenderNative(str)?
    │       │
    │       YES → return str unchanged (font can display it directly)
    │       │
    │       NO  → utf8ToAscii(str)
    │                   │
    │                   ├─ ASCII byte (< 0x80) → keep as-is
    │                   │
    │                   ├─ 2-byte sequence (0xC2–0xDF)
    │                   │       ├─ shouldPreserveChar()? → write both bytes (native glyph)
    │                   │       ├─ Cyrillic (0xD0/0xD1)? → transliterateCyrillic() → ASCII letter
    │                   │       └─ Latin extended? → LATIN_MAP lookup → ASCII equivalent(s)
    │                   │
    │                   ├─ 3-byte: ellipsis (U+2026) → "..."
    │                   ├─ 3-byte: trademark (U+2122) → "TM"
    │                   └─ other → space
    │
    └─ return processed string
```

### `shouldPreserveChar()` and codepage

`shouldPreserveChar()` checks whether a two-byte UTF-8 sequence maps to a glyph slot in the **currently compiled font**:

- **Latin codepage:** looks up the codepoint in `LATIN_PRESERVE[]` — a list of accented Latin codepoints that the `glcdfont_Latin.c` font provides.
- **Cyrillic codepage:** preserves the main Cyrillic block U+0410–U+044F (А–я) plus additional entries from `CYRILLIC_PRESERVE[]`. Latin accented letters are **not** preserved on the Cyrillic codepage — they are transliterated to plain ASCII instead.

---

## GLCD Font & Glyph System

The project uses a modified **Adafruit GFX GLCD** bitmap font stored in `src/locale/glcdfont/` (previously under `builds/`). Two variants are maintained:

| File | Purpose |
|---|---|
| `glcdfont-lib.c` | Original Adafruit font (reference only, not linked directly) |
| `glcdfont_Latin.c` | Latin variant — slots 0x80–0xFF filled with accented Latin glyphs |
| `glcdfont_Latin.md` | Latin glyph map and documentation |
| `glcdfont_Cyrillic.c` | Cyrillic variant — slots 0x80–0xFF filled with Cyrillic glyphs |
| `glcdfont_Cyrillic.md` | Cyrillic glyph map and documentation |

The build script `builds/platformio_pre_replace_font.py` copies the appropriate `.c` variant into the Adafruit GFX library directory before compilation, based on `L10N_CODEPAGE`.

### Cyrillic glyph layout

The Cyrillic font uses the upper half of the 256-glyph table (slots 0x80–0xFF):

- **0x80–0x9F** (slots 128–159): Main Cyrillic uppercase block U+0410–U+042F (А–Я)
- **0xA0–0xAF** (slots 160–175): Language-specific extras — Є (Ukrainian IE), Ґ, Ї, І, Ё (Russian IO), etc.
- **0xB0–0xFF**: Available for additional glyphs or left as unused

Because only uppercase Cyrillic is stored, the UTF-8 processing layer automatically converts any preserved lowercase Cyrillic character (U+0430–U+044F) to its uppercase equivalent (U+0410–U+042F) before storing it in the output buffer.

### Latin glyph layout

The Latin font fills slots 0x80–0xC8 with **uppercase** accented Latin and Greek characters needed by Western European languages: À, Á, Â, Ã, Ä, Å, Æ, Ç, È, É, Í, Î, Ð, Ñ, Ó, Ô, Õ, Ö, Ø, Ú, Ü, Ý, Þ, and extended Latin letters for Czech, Slovak, Polish, Baltic, Romanian, Hungarian, Croatian, and Greek scripts. Lowercase accented variants have no separate glyph slots — `LATIN_PRESERVE[]` lists both the uppercase and lowercase codepoint for each character, and `utf8Latin.cpp` maps both to the same uppercase glyph index. The result is that `à`, `á`, etc. are displayed identically to `À`, `Á`.

---

## How to Add a New Glyph

This covers the full process of adding a brand-new character to the GLCD font and wiring it into the UTF-8 processing pipeline so it renders natively on the display instead of being transliterated.

There are two independent codepaths — one for the **Latin** codepage and one for the **Cyrillic** codepage. Identify which font variant you are modifying and follow that path.

---

### Latin codepage (`glcdfont_Latin.c` + `utf8Latin.cpp`)

**Step 1 — Find a free glyph slot**

Open `src/locale/glcdfont/glcdfont_Latin.c`. The used range is currently 0x80–0xC8. The next free slot is **0xC9**. Pick the lowest unused index.

**Step 2 — Draw the glyph**

Use `scripts/glyph_creator_gui.py` to edit `src/locale/glcdfont/glcdfont_Latin.c`. Design the glyph bitmap for the **uppercase** form of the character (the font carries uppercase only; both cases will be directed to this slot).

**Step 3 — Update the glyph map documentation**

Add a row to `src/locale/glcdfont/glcdfont_Latin.md` for the new slot, following the existing column format (`dec`, `hex`, `U+`, `char`, Unicode name, Languages).

**Step 4 — Register the codepoints in `LATIN_PRESERVE[]`** (`utf8_common.cpp`)

`LATIN_PRESERVE[]` lists every codepoint that has a native glyph. Add **both** the uppercase and lowercase codepoint as a pair (uppercase first):

```cpp
// utf8_common.cpp — inside LATIN_PRESERVE[]
0x0XYZ, 0x0xyz,   // Ẋ / ẋ  (example)
```

This tells `shouldPreserveChar()` and `canRenderNative()` that these codepoints are renderable and must not be transliterated.

**Step 5 — Add the byte mapping in `utf8Latin.cpp`**

`utf8Latin.cpp` maps raw UTF-8 byte pairs to glyph slot indices via `switch` statements grouped by the first byte. Find the `switch` block matching the first UTF-8 byte of your character (e.g. `0xC4` for Latin Extended-A U+0100–U+017F, `0xC5` for U+0180–U+024F, `0xCE`/`0xCF` for Greek) and add a `case` for both the uppercase and lowercase second byte, both resolving to your new slot:

```cpp
// Example: adding Ẋ (C4 AB) / ẋ (C4 AC) at slot 0xC9
case 0xAB: case 0xAC: code = 0xC9; break; // Ẋ / ẋ -> 0xC9
```

If no `switch` block exists for the first byte yet, add a new `if (b1 == 0xXX && str[r+1]) { ... }` block following the same pattern as the existing ones.

---

### Cyrillic codepage (`glcdfont_Cyrillic.c` + `utf8Cyrillic.cpp`)

**Step 1 — Find a free glyph slot**

Open `src/locale/glcdfont/glcdfont_Cyrillic.c`. Used slots:
- 0x80–0x9F: main Cyrillic А–Я (fixed, do not touch)
- 0xA0–0xB7: language-specific extras

The next free slot is **0xB8**. Pick the lowest unused index above 0xB7.

**Step 2 — Draw the glyph**

Use `scripts/glyph_creator_gui.py` to add the glyph bitmap at your chosen slot. Draw the uppercase form; lowercase will be mapped to the same slot by the converter.

**Step 3 — Update the glyph map documentation**

Add a row to `src/locale/glcdfont/glcdfont_Cyrillic.md`.

**Step 4 — Register the codepoint in `CYRILLIC_PRESERVE[]`** (`utf8_common.cpp`)

Add the **uppercase** codepoint to `CYRILLIC_PRESERVE[]`. Only the uppercase is needed here because the main Cyrillic block (U+0410–U+044F) is already handled by a range check; `CYRILLIC_PRESERVE[]` covers the extras outside that range:

```cpp
// utf8_common.cpp — inside CYRILLIC_PRESERVE[]
0x04XY,   // new letter (uppercase)
```

**Step 5 — Add the codepoint mapping in `utf8Cyrillic.cpp`**

In `map_cyrillic_cp_to_glyph()`, add a `case` for both the uppercase and lowercase codepoints, returning your new slot index:

```cpp
// utf8Cyrillic.cpp — inside map_cyrillic_cp_to_glyph()
case 0x04XY: case 0x04Xy: return 0xB8; // Ӿ / ӿ
```

---

### Alternative: transliteration only (no new glyph)

If you just want an unfamiliar character to fall back to an ASCII approximation rather than a blank/space **without** adding a font glyph, add an entry to `LATIN_MAP[]` in `utf8_common.cpp` (do **not** add it to `LATIN_PRESERVE[]`):

```cpp
// utf8_common.cpp — inside LATIN_MAP[]
{0xC4, 0xBF, "L"},  // example: Ŀ -> "L"
```

This is sufficient for characters whose script is already covered by the font script (e.g. an obscure Latin letter that should just render as its base letter).

---

## Weather Language (`weatherLang`)

Each locale file defines a `weatherLang[]` string constant. This is the language code sent as the `lang=` parameter in OpenWeather API requests, allowing weather condition descriptions to be returned in the local language.

```cpp
// Example from displayL10n_ru_RU.h
const char weatherLang[] PROGMEM = "ru";
```

If OpenWeather does not support a particular language, the locale falls back to `"en"`. See `src/locale/l10n.md` for the full table.

---

## How to Add a New Language

1. **Copy an existing locale file** as a starting point:
   ```
   src/locale/displayL10n_en_US.h  →  src/locale/displayL10n_xx_XX.h
   ```

2. **Translate all string constants** in the new file (day names, month names, weather labels, wind directions).

3. **Set `weatherLang[]`** to the appropriate OpenWeather API language code.

4. **Register the language token** in `src/core/options.h` — add a `#define` line in the language list block and assign it the next available numeric index.

5. **Add an `#elif` branch** in `src/displays/tools/l10n.h` to map the new token to the new file path.

6. **Determine codepage.** If the language uses a Cyrillic script, add it to the auto-detect `#if` condition in `options.h`. If it uses an unusual script not covered by either existing codepage, a new codepage and corresponding font would be needed.

7. **Update `src/locale/l10n.md`** with the new entry in the languages table.

8. **Add a WebUI locale JSON file** in `src/locale/webui/`. Copy `src/locale/webui/en_US.json` as a template, rename it to `{code}.json`, and translate all values. The build script (`platformio_pre_gzip_www.py`) always deploys **both the selected language’s JSON and `en_US.json`** into `data/www/locale/` during the SPIFFS build, removing any stale files from previous builds. See [WebUI i18n](#webui-i18n) for the key reference.

9. **Set `DSP_LANGUAGE`** in `myoptions.h` and build.
   *Optionally* also define `WEBUI_LANGUAGE` if you want the
   WebUI to use a different locale than the display firmware.  If this
   macro is omitted the web interface simply inherits `DSP_LANGUAGE`.
---

## WebUI i18n

The WebUI served over Wi-Fi has its own runtime translation layer that operates independently of the compile-time firmware locale.

### How it works

1. **Language detection** — `variables.js` (injected by the firmware) exposes `uiLang` as the same integer index used by `DSP_LANGUAGE`. On page load, `script.js` maps this to a full BCP-47 code via `_langCodes[]` and fetches `/locale/{code}.json` from the device filesystem. For English (`uiLang == 0` or `en_US`) the fetch is skipped and built-in defaults are used.

    > **Note:** the WebUI language is only controllable at compile time.
> The firmware injects an integer (`uiLang`) that determines which JSON
> file the browser attempts to load. Historically this value was equal to
> `DSP_LANGUAGE`, but it can now be overridden by defining
> `WEBUI_LANGUAGE` in `myoptions.h`. Omitting the override keeps the
> old behaviour. Regardless of the setting, any new WebUI language still
> requires a corresponding JSON file in `src/locale/webui/` and a rebuild
> of the filesystem image.

2. **`t(key, ...args)` helper** — looks up `key` in the loaded `i18n` object and returns the translated string. Positional placeholders `{0}`, `{1}` are substituted with extra arguments.

3. **`applyI18n()` DOM walker** — called after the JSON is loaded; it queries every `[data-i18n]` element and replaces its text content (or `value` / `placeholder` for inputs) with `t(key)`.

4. **`data-i18n` attributes** — every translatable label in `options.html`, `player.html`, `search.html`, `curated.html`, and `updform.html` carries a `data-i18n="key"` attribute with the fallback English text left as the element's default content.

5. **Dynamic strings** — JS-generated text (OTA progress messages, update-available button, redirect notice, battery status) calls `t()` directly in the event handler.

6. **Battery status** — the firmware sends battery info as an English string (`volt: Xmv, percentage: X%, status: Idle`). `script.js` parses this and rebuilds it using `t('lbl_batt_volt')`, `t('lbl_batt_percentage')`, `t('lbl_batt_status')`, and `t('st_batt_{state}')` keys, so the display language matches the rest of the UI without any firmware change.

7. **CSS knob labels** — the toggle switch on/off text is translated via CSS custom properties `--knob-off` and `--knob-on`, set from `t('lbl_off')` / `t('lbl_on')`.

### JSON locale files

WebUI locale JSONs now live in `src/locale/webui/` (co‑located with the
firmware locale headers in the parent directory). The build script
(`platformio_pre_gzip_www.py`) automatically copies all non‑English JSONs
from that `webui` folder into `data/www/locale/` before the SPIFFS image is
built. `en_US.json` is always copied alongside the chosen locale so the JS fallback fetch can succeed; other files are cleaned out.
are baked into `script.js` as the runtime fallback.

Locale JSON files in `src/locale/` are now named using just the
BCP‑47 language code (e.g. `en_US.json`, `ru_RU.json`). The build script
copies the selected file directly to `data/www/locale/<code>.json` when
building the filesystem image. The loader in `script.js` requests the
short name; legacy images still using the old prefix will no longer be
served.

| File | Purpose |
|---|---|
| `src/locale/webui/en_US.json` | Master key reference — all keys with English values (not deployed to device) |
| `src/locale/webui/lt_LV.json` | Latvian translation (example of a complete translation) |

To add a new language, copy `src/locale/webui/en_US.json`, rename it to
`<code>.json` (matching the BCP‑47 code in `_langCodes[]` in `script.js`),
translate all values, and run a filesystem build. Untranslated keys fall
back to displaying the raw key name.

### Key categories

| Prefix | Examples | Covers |
|---|---|---|
| `ttl_` | `ttl_settings`, `ttl_playlist_editor` | Page titles |
| `nav_` | `nav_system`, `nav_wifi` | Navigation tab labels |
| `title_` | `title_battery`, `title_weather` | Section headings |
| `lbl_` | `lbl_flip_screen`, `lbl_volume` | Input / toggle labels |
| `ph_` | `ph_battref` | Input placeholders |
| `btn_` | `btn_save`, `btn_reset` | Button labels |
| `msg_` | `msg_ota_complete`, `msg_no_update` | Dynamic status messages |
| `st_batt_` | `st_batt_idle`, `st_batt_charging` | Battery state strings |
| `lbl_off` / `lbl_on` | — | Toggle knob labels |

---
## Two Python GUI tools in `scripts/` assist with font glyph work:

| Tool | Purpose |
|---|---|
| `scripts/glyph_creator_gui.py` | Create and edit individual glyph bitmaps in the Adafruit GLCD format. Supports importing and exporting `.c` font files. |
| `scripts/glyph_compare_gui.py` | Visually compare two glyph sets side-by-side. Useful for auditing differences between `glcdfont_Latin.c` and `glcdfont_Cyrillic.c`. |

See `scripts/scripts.md` for usage instructions.
