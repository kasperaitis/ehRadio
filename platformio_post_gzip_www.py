Import("env")
import shutil
from pathlib import Path

# Temp directory where originals were backed up
TEMP_BACKUP_DIR = Path(".pio/temp_www_backup")

def restore_and_cleanup(source, target, env):
    """Restore original files and delete all .gz files after SPIFFS build"""
    print("\n" + "="*70)
    print("POST-BUILD: Restoring original files and cleaning up...")
    print("="*70)
    
    data_dir = Path("data/www")
    
    # Restore original files from backup
    restored_count = 0
    if TEMP_BACKUP_DIR.exists():
        print("\nRestoring original files to data/www...")
        for backup_file in sorted(TEMP_BACKUP_DIR.glob("*")):
            dest_path = data_dir / backup_file.name
            shutil.move(str(backup_file), str(dest_path))
            restored_count += 1
            print(f"  ← {backup_file.name} restored")
        
        # Remove temp backup directory
        try:
            TEMP_BACKUP_DIR.rmdir()
            print(f"\nRemoved temporary backup directory: {TEMP_BACKUP_DIR}")
        except:
            pass
    else:
        print(f"No backup directory found at {TEMP_BACKUP_DIR}")
    
    # Delete all .gz files from data/www
    print("\nDeleting all .gz files from data/www...")
    deleted_count = 0
    for gz_file in sorted(data_dir.glob("*.gz")):
        gz_file.unlink()
        deleted_count += 1
        print(f"  ✗ {gz_file.name} deleted")
    
    print("-"*70)
    print(f"Restored: {restored_count} files | Deleted: {deleted_count} .gz files")
    print(f"data/www now contains only original source files for editing")
    print("="*70 + "\n")

# Register the post-build action
env.AddPostAction("$BUILD_DIR/spiffs.bin", restore_and_cleanup)
