# This script may be used by platformio to automatically replace a default Adafruit GFX Library font
# Add this to a platformio.ini env section:
# extra_scripts = pre:replace_font.py

Import("env")
import shutil
import os
import re
import sys

env_name = env["PIOENV"]

# Skip font replacement during clean/erase/filesystem operations
# Check sys.argv because BUILD_TARGETS may not contain the actual target names
skip_operations = ["clean", "fullclean", "erase", "buildfs", "uploadfs"]
if any(op in " ".join(sys.argv) for op in skip_operations):
    Return()

build_targets = [str(t) for t in BUILD_TARGETS]
# determine project directory (PlatformIO provides PROJECT_DIR in env) and detect codepage
project_dir = env.get("PROJECT_DIR", os.getcwd())

# Get active build flags from the environment
# CPPDEFINES contains the actual preprocessor defines that will be used
active_defines = set()

# Try CPPDEFINES first (contains actual -D flags)
cpp_defines = env.get("CPPDEFINES", [])
for item in cpp_defines:
    if isinstance(item, str):
        active_defines.add(item.split("=")[0])  # Handle KEY=VALUE format
    elif isinstance(item, tuple) and len(item) >= 1:
        active_defines.add(item[0])  # Handle (KEY, VALUE) format

# Fallback to BUILD_FLAGS
if not active_defines:
    build_flags = env.get("BUILD_FLAGS", [])
    for flag in build_flags:
        if isinstance(flag, str) and flag.startswith("-D"):
            active_defines.add(flag[2:].split("=")[0])

# Final fallback: derive from environment name (e.g., esp32_s3_kasperaitis_es3c28p -> ESP32_S3_KASPERAITIS_ES3C28P)
# This handles cases where custom build flags aren't in CPPDEFINES yet
env_flag = env_name.upper()
active_defines.add(env_flag)

print(f"replace_font: active build flags: {sorted(active_defines)}")

# Helper to find a C preprocessor #define in a file, respecting #if conditionals
def _find_define(path, macro):
    try:
        with open(path, "r", encoding="utf-8") as fh:
            in_active_block = True  # Start assuming we're in active code
            if_depth = 0            # Track nesting depth
            block_stack = []        # Stack of (depth, is_active)
            
            # Read file and handle line continuations
            lines = []
            temp_line = ""
            for raw_line in fh:
                if raw_line.rstrip().endswith('\\'):
                    temp_line += raw_line.rstrip()[:-1] + " "  # Remove \ and add space
                else:
                    lines.append(temp_line + raw_line)
                    temp_line = ""
            
            for ln in lines:
                ln_stripped = ln.strip()
                
                # Track #if defined(...) blocks (simple or OR'd)
                if re.match(r"#\s*if\s+", ln_stripped):
                    # Extract all defined(FLAG) patterns
                    flags = re.findall(r"defined\((\w+)\)", ln_stripped)
                    if flags:
                        # Block is active if ANY flag matches
                        is_active = any(flag in active_defines for flag in flags)
                        if_depth += 1
                        block_stack.append((if_depth, is_active))
                        in_active_block = is_active
                        continue
                    else:
                        # Complex #if without defined() - treat as inactive
                        if_depth += 1
                        block_stack.append((if_depth, False))
                        in_active_block = False
                        continue
                    
                # Track #ifdef
                ifdef_match = re.match(r"#\s*ifdef\s+(\w+)", ln_stripped)
                if ifdef_match:
                    flag = ifdef_match.group(1)
                    is_active = flag in active_defines
                    if_depth += 1
                    block_stack.append((if_depth, is_active))
                    in_active_block = is_active
                    continue
                
                # Track #elif defined(...)
                if re.match(r"#\s*elif\s+", ln_stripped):
                    flags = re.findall(r"defined\((\w+)\)", ln_stripped)
                    if flags and block_stack:
                        block_stack.pop()
                        if_depth = max(1, if_depth)
                        is_active = any(flag in active_defines for flag in flags)
                        block_stack.append((if_depth, is_active))
                        in_active_block = is_active
                        continue
                
                # Track #else
                if re.match(r"#\s*else", ln_stripped):
                    if block_stack:
                        old_depth, old_active = block_stack.pop()
                        is_active = not old_active
                        block_stack.append((old_depth, is_active))
                        in_active_block = is_active
                        continue
                    
                # Track #endif
                if re.match(r"#\s*endif", ln_stripped):
                    if block_stack:
                        block_stack.pop()
                        if_depth = max(0, if_depth - 1)
                        # Restore previous block state
                        in_active_block = block_stack[-1][1] if block_stack else True
                    continue
                
                # Only process #define if we're in an active block
                if in_active_block:
                    # Match quoted string: #define MACRO "value"
                    m = re.match(r'\s*#\s*define\s+' + re.escape(macro) + r'\s+"([^"]+)"', ln)
                    if m:
                        return m.group(1)
    except Exception:
        return None
    return None

# Helper to find DSP_LANGUAGE flag pattern: #define DSP_LANGUAGE_lt_LT
def _find_language_flag(path):
    try:
        with open(path, "r", encoding="utf-8") as fh:
            in_active_block = True
            if_depth = 0
            block_stack = []
            
            # Read file and handle line continuations
            lines = []
            temp_line = ""
            for raw_line in fh:
                if raw_line.rstrip().endswith('\\'):
                    temp_line += raw_line.rstrip()[:-1] + " "  # Remove \ and add space
                else:
                    lines.append(temp_line + raw_line)
                    temp_line = ""
            
            for ln in lines:
                ln_stripped = ln.strip()
                
                # Track #if defined(...) blocks (simple or OR'd)
                if re.match(r"#\s*if\s+", ln_stripped):
                    # Extract all defined(FLAG) patterns
                    flags = re.findall(r"defined\((\w+)\)", ln_stripped)
                    if flags:
                        # Block is active if ANY flag matches
                        is_active = any(flag in active_defines for flag in flags)
                        if_depth += 1
                        block_stack.append((if_depth, is_active))
                        in_active_block = is_active
                        continue
                    else:
                        # Complex #if without defined() - treat as inactive
                        if_depth += 1
                        block_stack.append((if_depth, False))
                        in_active_block = False
                        continue
                    
                # Track #ifdef
                ifdef_match = re.match(r"#\s*ifdef\s+(\w+)", ln_stripped)
                if ifdef_match:
                    flag = ifdef_match.group(1)
                    is_active = flag in active_defines
                    if_depth += 1
                    block_stack.append((if_depth, is_active))
                    in_active_block = is_active
                    continue
                
                # Track #elif defined(...)
                if re.match(r"#\s*elif\s+", ln_stripped):
                    flags = re.findall(r"defined\((\w+)\)", ln_stripped)
                    if flags and block_stack:
                        block_stack.pop()
                        if_depth = max(1, if_depth)
                        is_active = any(flag in active_defines for flag in flags)
                        block_stack.append((if_depth, is_active))
                        in_active_block = is_active
                        continue
                
                # Track #else
                if re.match(r"#\s*else", ln_stripped):
                    if block_stack:
                        old_depth, old_active = block_stack.pop()
                        is_active = not old_active
                        block_stack.append((old_depth, is_active))
                        in_active_block = is_active
                        continue
                    
                # Track #endif
                if re.match(r"#\s*endif", ln_stripped):
                    if block_stack:
                        block_stack.pop()
                        if_depth = max(0, if_depth - 1)
                        in_active_block = block_stack[-1][1] if block_stack else True
                    continue
                
                # Look for DSP_LANGUAGE_xx_XX pattern
                if in_active_block:
                    m = re.match(r'\s*#\s*define\s+DSP_LANGUAGE_([a-zA-Z]{2}_[a-zA-Z]{2})', ln)
                    if m:
                        return m.group(1)
    except Exception:
        return None
    return None

# Helper to check if a codepage flag is defined: #define L10N_CP_LATIN or #define L10N_CP_CYRILLIC
def _check_codepage_flag(path, flag_name):
    try:
        with open(path, "r", encoding="utf-8") as fh:
            in_active_block = True
            if_depth = 0
            block_stack = []
            
            # Read file and handle line continuations
            lines = []
            temp_line = ""
            for raw_line in fh:
                if raw_line.rstrip().endswith('\\'):
                    temp_line += raw_line.rstrip()[:-1] + " "  # Remove \ and add space
                else:
                    lines.append(temp_line + raw_line)
                    temp_line = ""
            
            for ln in lines:
                ln_stripped = ln.strip()
                
                # Track #if defined(...) blocks (simple or OR'd)
                if re.match(r"#\s*if\s+", ln_stripped):
                    # Extract all defined(FLAG) patterns
                    flags = re.findall(r"defined\((\w+)\)", ln_stripped)
                    if flags:
                        # Block is active if ANY flag matches
                        is_active = any(flag in active_defines for flag in flags)
                        if_depth += 1
                        block_stack.append((if_depth, is_active))
                        in_active_block = is_active
                        continue
                    else:
                        # Complex #if without defined() - treat as inactive
                        if_depth += 1
                        block_stack.append((if_depth, False))
                        in_active_block = False
                        continue
                    
                # Track #ifdef
                ifdef_match = re.match(r"#\s*ifdef\s+(\w+)", ln_stripped)
                if ifdef_match:
                    flag = ifdef_match.group(1)
                    is_active = flag in active_defines
                    if_depth += 1
                    block_stack.append((if_depth, is_active))
                    in_active_block = is_active
                    continue
                
                # Track #elif defined(...)
                if re.match(r"#\s*elif\s+", ln_stripped):
                    flags = re.findall(r"defined\((\w+)\)", ln_stripped)
                    if flags and block_stack:
                        block_stack.pop()
                        if_depth = max(1, if_depth)
                        is_active = any(flag in active_defines for flag in flags)
                        block_stack.append((if_depth, is_active))
                        in_active_block = is_active
                        continue
                
                # Track #else
                if re.match(r"#\s*else", ln_stripped):
                    if block_stack:
                        old_depth, old_active = block_stack.pop()
                        is_active = not old_active
                        block_stack.append((old_depth, is_active))
                        in_active_block = is_active
                        continue
                    
                # Track #endif
                if re.match(r"#\s*endif", ln_stripped):
                    if block_stack:
                        block_stack.pop()
                        if_depth = max(0, if_depth - 1)
                        in_active_block = block_stack[-1][1] if block_stack else True
                    continue
                
                # Look for #define L10N_CP_xxx pattern
                if in_active_block:
                    m = re.match(r'\s*#\s*define\s+' + re.escape(flag_name) + r'(?:\s|$)', ln)
                    if m:
                        return True
    except Exception:
        return False
    return False

# font replacement script runs on every build to copy the appropriate
# glcdfont variant into the Adafruit GFX library.  The library's default
# drawChar() implementation already reads from the static `font[]` array, so
# no runtime patching is performed.


# Look for DSP_LANGUAGE_xx_XX flag and actual L10N_CP_xxx codepage flags in myoptions.h or l10n.h
codepage = None
language = None
lang_source = None
for candidate in [
    os.path.join(project_dir, "builds", env_name, "myoptions.h"),
    os.path.join(project_dir, "myoptions.h"),
]:
    if not language:
        lang = _find_language_flag(candidate)
        if lang:
            language = lang
            lang_source = candidate

# Check for actual L10N_CP_xxx flags defined by locale.h
for candidate in [
    os.path.join(project_dir, "src", "core", "locale.h"),
]:
    if not codepage:
        if _check_codepage_flag(candidate, "L10N_CP_CYRILLIC"):
            codepage = "L10N_CP_CYRILLIC"
        elif _check_codepage_flag(candidate, "L10N_CP_LATIN"):
            codepage = "L10N_CP_LATIN"

# Debug output for language detection
if language:
    source_name = os.path.basename(lang_source) if lang_source else "unknown"
    print(f"  [font] Detected DSP_LANGUAGE_{language} from {source_name}")
else:
    print(f"  [font] No DSP_LANGUAGE flag found, using default English")
    language = "en_US"

# If codepage wasn't found in locale.h, fall back to inferring from language
if not codepage:
    cyrillic_langs = {"ru_RU","uk_UA","be_BY","bg_BG","mk_MK","sr_RS","me_ME","uz_UZ","kk_KZ","tg_TJ","ky_KG","mn_MN"}
    codepage = "L10N_CP_CYRILLIC" if (language in cyrillic_langs) else "L10N_CP_LATIN"
    print(f"  [font] Inferred codepage={codepage} from language (locale.h not parsed - if inference is wrong, this script needs fixing)")
else:
    print(f"  [font] Detected codepage={codepage} from locale.h")

use_cyrillic = (codepage == "L10N_CP_CYRILLIC")

src_font_name = 'glcdfont_Cyrillic.c' if use_cyrillic else 'glcdfont_Latin.c'
# fonts are provided under src/locale/glcdfont/ (moved from builds/ for
# consistency with other localization assets)
src_font = os.path.join("src", "locale", "glcdfont", src_font_name)

# Destination in the built Adafruit GFX library
# Note: library path can vary by platform/env; this matches previous behavior
dst_font = os.path.join(".pio", "libdeps", env_name, "Adafruit GFX Library", "glcdfont.c")

if os.path.exists(src_font) and os.path.exists(os.path.dirname(dst_font)):
    shutil.copyfile(src_font, dst_font)
    print(f"  [font] {src_font} -> {dst_font}")
    print(f"  [font] Custom {src_font_name} installed for {env_name}")
else:
    if not os.path.exists(src_font):
        print(f"  [font] ✗ Source font not found: {src_font}")
    if not os.path.exists(os.path.dirname(dst_font)):
        print(f"  [font] ✗ Destination library not found: {os.path.dirname(dst_font)}")
    print(f"  [font] Skipping font replacement for {env_name}")
