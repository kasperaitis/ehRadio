# This script may be used by platformio to automatically replace a default Adafruit GFX Library font
# Add this to a platformio.ini env section:
# extra_scripts = pre:replace_font.py

Import("env")
import shutil
import os
import re

env_name = env["PIOENV"]

build_targets = [str(t) for t in BUILD_TARGETS]
# determine project directory (PlatformIO provides PROJECT_DIR in env) and detect codepage
project_dir = env.get("PROJECT_DIR", os.getcwd())


# Helper to find a C preprocessor #define in a file
def _find_define(path, macro):
    try:
        with open(path, "r", encoding="utf-8") as fh:
            for ln in fh:
                m = re.match(r"\s*#\s*define\s+" + re.escape(macro) + r"\s+(\w+)", ln)
                if m:
                    return m.group(1)
    except Exception:
        return None

# font replacement script runs on every build to copy the appropriate
# glcdfont variant into the Adafruit GFX library.  The library's default
# drawChar() implementation already reads from the static `font[]` array, so
# no runtime patching is performed.


# Look for an explicit L10N_CODEPAGE in builds/<env>/myoptions.h or project myoptions.h only.
# Do NOT search src/core/options.h — its #define L10N_CODEPAGE lines are inside #if blocks
# and cannot be read correctly without evaluating C preprocessor conditions.
codepage = None
language = None
for candidate in [
    os.path.join(project_dir, "builds", env_name, "myoptions.h"),
    os.path.join(project_dir, "myoptions.h"),
]:
    if not codepage:
        codepage = _find_define(candidate, "L10N_CODEPAGE")
    if not language:
        lang = _find_define(candidate, "L10N_LANGUAGE")
        if lang:
            language = lang
# fallback to options.h for language only
if not language:
    try:
        with open(os.path.join(project_dir, "src", "core", "options.h"), "r", encoding="utf-8") as fh:
            for ln in fh:
                m = re.match(r"\s*#\s*define\s+L10N_LANGUAGE\s+(\w+)", ln)
                if m:
                    language = m.group(1)
                    break
    except Exception:
        pass

# If codepage wasn't explicitly defined, infer from L10N_LANGUAGE
if not codepage:
    cyrillic_langs = {"ru_RU","uk_UA","be_BY","bg_BG","mk_MK","sr_RS","me_ME","uz_UZ","kk_KZ","tg_TJ","ky_KG","mn_MN"}
    codepage = "L10N_CP_CYRILLIC" if (language in cyrillic_langs) else "L10N_CP_LATIN"


# now that locale has been handled, bail early if this is only a filesystem build
if "buildfs" in build_targets or "uploadfs" in build_targets:
    Return()

use_cyrillic = (codepage == "L10N_CP_CYRILLIC")

src_font_name = 'glcdfont_Cyrillic.c' if use_cyrillic else 'glcdfont_Latin.c'
# fonts are provided under src/locale/glcdfont/ (moved from builds/ for
# consistency with other localization assets)
src_font = os.path.join("src", "locale", "glcdfont", src_font_name)

# Destination in the built Adafruit GFX library
# Note: library path can vary by platform/env; this matches previous behavior
dst_font = os.path.join(".pio", "libdeps", env_name, "Adafruit GFX Library", "glcdfont.c")

print(f"replace_font: env={env_name}, project_dir={project_dir}")
print(f"replace_font: detected L10N_CODEPAGE={codepage} (default LATIN if not set), using {src_font_name}")
print(f"replace_font: src_font={src_font}, exists={os.path.exists(src_font)}, dst_font={dst_font}, dst_parent_exists={os.path.exists(os.path.dirname(dst_font))}")

if os.path.exists(src_font) and os.path.exists(os.path.dirname(dst_font)):
    shutil.copyfile(src_font, dst_font)
    print(f"Custom {src_font_name} copied to Adafruit GFX Library for {env_name}.")
else:
    print(f"Font file or destination not found for {env_name}. Skipping replacement.")
