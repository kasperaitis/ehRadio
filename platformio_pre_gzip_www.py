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
        
        print(f"  ✓ {source_path.name} → {source_path.name}.gz ({original_size:,} → {compressed_size:,} bytes, {ratio:.1f}% savings)")
        return True
    except Exception as e:
        print(f"  ✗ Error compressing {source_path.name}: {e}")
        return False

def compress_and_hide_originals(source, target, env):
    """Compress web files and temporarily move originals so only .gz files are in SPIFFS"""
    print("\n" + "="*70)
    print("PRE-BUILD: Compressing web files for SPIFFS...")
    print("="*70)
    
    data_dir = Path("data/www")
    if not data_dir.exists():
        print(f"Warning: {data_dir} does not exist, skipping compression")
        return
    
    # Create temp backup directory
    TEMP_BACKUP_DIR.mkdir(parents=True, exist_ok=True)
    
    # File patterns to compress
    patterns = ["*.*"]
    
    # Files to exclude from compression
    exclude = ["rb_srvrs.json"]
    
    compressed_count = 0
    skipped_count = 0
    
    # First pass: compress files
    for pattern in patterns:
        for file_path in sorted(data_dir.glob(pattern)):
            if file_path.name in exclude:
                print(f"  ⊘ Skipping {file_path.name} (excluded)")
                continue
            
            if compress_file(file_path):
                compressed_count += 1
            else:
                skipped_count += 1
    
    print("-"*70)
    print(f"Compressed: {compressed_count} files | Skipped: {skipped_count} files (already up-to-date)")
    print("="*70)
    
    # Second pass: move originals outside data directory
    print("\nMoving original files out of data/www (only .gz will be in SPIFFS)...")
    hidden_count = 0
    for pattern in patterns:
        for file_path in sorted(data_dir.glob(pattern)):
            if file_path.name in exclude:
                continue
            
            gz_path = Path(str(file_path) + '.gz')
            if gz_path.exists():
                backup_path = TEMP_BACKUP_DIR / file_path.name
                if backup_path.exists():
                    backup_path.unlink()
                shutil.move(str(file_path), str(backup_path))
                hidden_count += 1
                print(f"  → {file_path.name} moved to backup")
    
    print(f"\nMoved: {hidden_count} original files to {TEMP_BACKUP_DIR}")
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
    print("\n" + "="*70)
    print("INIT: Running compression now (before build starts)")
    print("="*70 + "\n")
    compress_and_hide_originals(None, None, env)

# Note: NOT using AddPreAction here because we run compression at init time instead
# This ensures compression always runs for filesystem operations
