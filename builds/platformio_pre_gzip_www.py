Import("env")
import gzip
import os
import shutil
from pathlib import Path

# Temp directory outside data folder
TEMP_BACKUP_DIR = Path(".pio/temp_www_backup")

def should_compress(source_file, gz_file):
    """Check if source file needs compression (newer than .gz or .gz doesn't exist)"""
    if not gz_file.exists():
        return True
    return source_file.stat().st_mtime > gz_file.stat().st_mtime

def compress_file(source_path):
    """Compress a single file with gzip"""
    gz_path = Path(str(source_path) + '.gz')
    
    if not should_compress(source_path, gz_path):
        return False
    
    try:
        with open(source_path, 'rb') as f_in:
            with gzip.open(gz_path, 'wb', compresslevel=9) as f_out:
                f_out.writelines(f_in)
        
        original_size = source_path.stat().st_size
        compressed_size = gz_path.stat().st_size
        ratio = (1 - compressed_size / original_size) * 100
        
        print(f"  + {source_path.name} -> {source_path.name}.gz ({original_size:,} -> {compressed_size:,} bytes, {ratio:.1f}% savings)")
        return True
    except Exception as e:
        print(f"  [error] compressing {source_path.name}: {e}")
        return False

def _get_selected_lang_code():
    """Return the full BCP-47 WebUI JSON code for the active language.

    The previously hard‑wired value followed L10N_LANGUAGE, but after
    adding ``L10N_WEBUI_LANGUAGE`` we must read that first and fall back
    to the normal language token.  English is treated as a special case
    because the JS layer uses built‑in defaults and does not need a file.

    Resolution order:
      1. myoptions.h  — #define L10N_WEBUI_LANGUAGE xx_XX
      2. myoptions.h  — #define L10N_LANGUAGE      xx_XX
      3. src/core/options.h — same two patterns (fallback)
      4. 'en_US' if nothing found (no JSON needed for English)
    """
    import re
    # two patterns for the two macros, search WEBUI first
    pat_webui = re.compile(r'^\s*#define\s+L10N_WEBUI_LANGUAGE\s+(\w+)', re.MULTILINE)
    pat_lang  = re.compile(r'^\s*#define\s+L10N_LANGUAGE\s+(\w+)', re.MULTILINE)

    for candidate in ("myoptions.h", "src/core/options.h"):
        p = Path(candidate)
        if not p.exists():
            continue
        text = p.read_text(encoding="utf-8", errors="ignore")
        m = pat_webui.search(text)
        if m:
            return m.group(1)
        m = pat_lang.search(text)
        if m:
            return m.group(1)

    return "en_US"  # fallback default


def deploy_locale_json(source, target, env):
    """Copy the chosen WebUI language JSON into the SPIFFS source tree.

    The language code is derived via :pyfunc:`_get_selected_lang_code`, which
    reads ``L10N_WEBUI_LANGUAGE`` if defined or falls back to
    ``L10N_LANGUAGE``.  The selected file plus ``en_US.json`` (JS fallback)
    are copied from ``src/locale/webui/`` into ``data/www/locale/``.  Any
    other JSON files already present are treated as stale and deleted.
    """
    lang_code = _get_selected_lang_code()

    locale_dst = Path("data/www/locale")
    locale_dst.mkdir(parents=True, exist_ok=True)
    locale_src = Path("src/locale/webui")

    # Determine which files we need on device
    needed = {"en_US"}  # always deploy English as JS fallback
    if not lang_code.startswith("en"):
        needed.add(lang_code)

    # Remove stale JSON files that are no longer needed
    for stale in locale_dst.glob("*.json"):
        if stale.stem not in needed:
            stale.unlink()
            print(f"  [locale] removed stale {stale.name}")

    # Deploy each needed JSON
    for code in sorted(needed):
        json_file = locale_src / f"{code}.json"
        if not json_file.exists():
            print(f"  [locale] WARNING: {json_file} not found — skipping")
            continue
        dest = locale_dst / f"{code}.json"
        if not dest.exists() or json_file.stat().st_mtime > dest.stat().st_mtime:
            shutil.copy2(str(json_file), str(dest))
            print(f"  [locale] {json_file} -> {dest}")
        else:
            print(f"  [locale] {dest} already up-to-date")


def compress_and_hide_originals(source, target, env):
    """Compress web files and temporarily move originals so only .gz files are in SPIFFS"""
    print("\n" + "="*70)
    print("PRE-BUILD: Compressing web files for SPIFFS...")
    print("="*70)

    # Stage locale JSON files before compression pass
    print("\nDeploying locale JSON files:")
    deploy_locale_json(source, target, env)
    
    data_dir = Path("data/www")
    if not data_dir.exists():
        print(f"Warning: {data_dir} does not exist, skipping compression")
        return
    
    # Create temp backup directory
    TEMP_BACKUP_DIR.mkdir(parents=True, exist_ok=True)
    
    # Files to exclude from compression (by filename, any directory)
    exclude = ["rb_srvrs.json"]
    # Subdirectories to exclude from compression — files are kept as plain files in SPIFFS
    # (avoids ESPAsyncWebServer gzip+subdirectory edge cases for small files)
    exclude_dirs = ["locale"]
    
    compressed_count = 0
    skipped_count = 0
    
    # First pass: compress all files recursively
    for file_path in sorted(data_dir.rglob("*")):
        if not file_path.is_file():
            continue
        rel = file_path.relative_to(data_dir)
        # Exclude files in excluded subdirectories
        if any(part in exclude_dirs for part in rel.parts[:-1]):
            print(f"  [skip] {rel} (excluded dir)")
            continue
        if file_path.name in exclude:
            print(f"  [skip] {rel} (excluded)")
            continue

        # Skip files that are already gzipped (avoid creating .gz.gz entries)
        if file_path.name.endswith('.gz'):
            print(f"  [skip] {file_path.relative_to(data_dir)} (already gzipped)")
            skipped_count += 1
            continue
        
        if compress_file(file_path):
            compressed_count += 1
        else:
            skipped_count += 1
    
    print("-"*70)
    print(f"Compressed: {compressed_count} files | Skipped: {skipped_count} files (already up-to-date)")
    print("="*70)
    
    # Second pass: move originals outside data directory (preserve relative subpath in backup)
    print("\nMoving original files out of data/www (only .gz and excluded files will be in SPIFFS):")
    hidden_count = 0
    moved_names = []
    for file_path in sorted(data_dir.rglob("*")):
        if not file_path.is_file():
            continue
        rel = file_path.relative_to(data_dir)
        if any(part in exclude_dirs for part in rel.parts[:-1]):
            continue
        if file_path.name in exclude:
            continue
        if file_path.name.endswith('.gz'):
            continue
        
        gz_path = Path(str(file_path) + '.gz')
        if gz_path.exists():
            rel = file_path.relative_to(data_dir)
            backup_path = TEMP_BACKUP_DIR / rel
            backup_path.parent.mkdir(parents=True, exist_ok=True)
            if backup_path.exists():
                backup_path.unlink()
            shutil.move(str(file_path), str(backup_path))
            hidden_count += 1
            moved_names.append(f"-> {rel}")
    
    print(" ".join(moved_names))
    print(f"Moved {hidden_count} original files to {TEMP_BACKUP_DIR}")
    print(f"SPIFFS will contain ONLY .gz files (and excluded files)")
    print("="*70 + "\n")

# Detect if we're doing a filesystem operation
import sys
any_fs_target = any(t in sys.argv for t in ["uploadfs", "buildfs", "--target"])

if any_fs_target:
    # Delete cached spiffs.bin to force rebuild
    spiffs_bin = Path(env.subst("$BUILD_DIR")) / "spiffs.bin"
    if spiffs_bin.exists():
        print("\n" + "="*70)
        print("INIT: Deleting cached spiffs.bin")
        print("="*70)
        spiffs_bin.unlink()
        print("  → Deleted spiffs.bin - will rebuild with compression")
        print("="*70 + "\n")
    
    # Run compression now at init time
    compress_and_hide_originals(None, None, env)

# Note: NOT using AddPreAction here because we run compression at init time instead
# This ensures compression always runs for filesystem operations
