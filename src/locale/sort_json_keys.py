#!/usr/bin/env python3
"""
Sort keys in a locale JSON file with hierarchy.
Usage: python sort_json_keys.py <json_file_or_directory>
Example: python sort_json_keys.py webui/en_US.json
Example: python sort_json_keys.py webui
"""

import os
import sys
import json
import glob


def get_sort_priority(key):
    """
    Return a tuple for sorting priority:
    - First element: category priority (lower = earlier)
    - Second element: the key itself for alphabetical sorting within category
    """
    prefixes = [
        'locale_',   # 0
        'title_',    # 1
        'nav_',      # 2
        'ttl_',      # 3
        'lbl_',      # 4
        'btn_',      # 5
        'msg_',      # 6
        'ph_',       # 7
        'st_',       # 8
        'sort_',     # 9
        'unit_',     # 10
    ]
    
    for i, prefix in enumerate(prefixes):
        if key.startswith(prefix):
            return (i, key)
    
    # Default: alphabetical at the end
    return (999, key)


def sort_json_file(json_path):
    """Sort a JSON file with hierarchical key ordering."""
    if not os.path.exists(json_path):
        print(f"Error: File not found: {json_path}")
        return False
    
    # Load JSON
    with open(json_path, 'r', encoding='utf-8') as f:
        data = json.load(f)
    
    if not isinstance(data, dict):
        print(f"Error: JSON file must contain an object at root level")
        return False
    
    print(f"Loaded {len(data)} keys from {json_path}")
    
    # Sort keys
    sorted_keys = sorted(data.keys(), key=get_sort_priority)
    sorted_data = {key: data[key] for key in sorted_keys}
    
    # Write to temp file
    temp_path = json_path + '.tmp'
    with open(temp_path, 'w', encoding='utf-8') as f:
        json.dump(sorted_data, f, ensure_ascii=False, indent=2)
    
    # Replace original
    os.replace(temp_path, json_path)
    print(f"Sorted and saved {json_path}")
    
    # Show grouping summary
    print("\nKey grouping:")
    current_prefix = None
    count = 0
    
    for key in sorted_keys:
        # Determine prefix
        prefix = None
        for p in ['locale_', 'title_', 'nav_', 'ttl_', 'lbl_', 'btn_', 'msg_', 'ph_', 'st_', 'sort_', 'unit_']:
            if key.startswith(p):
                prefix = p.rstrip('_')
                break
        
        if prefix != current_prefix:
            if current_prefix is not None:
                print(f"  {current_prefix}: {count} key(s)")
            current_prefix = prefix if prefix else 'other'
            count = 1
        else:
            count += 1
    
    # Print last group
    if current_prefix is not None:
        print(f"  {current_prefix}: {count} key(s)")
    
    return True


def main():
    if len(sys.argv) < 2:
        print("Usage: python sort_json_keys.py <json_file_or_directory>")
        print("Example: python sort_json_keys.py webui/en_US.json")
        print("Example: python sort_json_keys.py webui")
        sys.exit(1)
    
    target = sys.argv[1]
    
    # Handle relative paths from script directory
    if not os.path.isabs(target):
        script_dir = os.path.dirname(os.path.abspath(__file__))
        target = os.path.join(script_dir, target)
    
    # Check if target is a directory or file
    if os.path.isdir(target):
        # Sort all JSON files in directory
        json_files = glob.glob(os.path.join(target, '*.json'))
        if not json_files:
            print(f"No JSON files found in {target}")
            sys.exit(1)
        
        print(f"Found {len(json_files)} JSON file(s) in {target}\n")
        success_count = 0
        
        for json_file in sorted(json_files):
            print(f"\n{'='*60}")
            print(f"Processing: {os.path.basename(json_file)}")
            print('='*60)
            if sort_json_file(json_file):
                success_count += 1
        
        print(f"\n{'='*60}")
        print(f"Successfully sorted {success_count}/{len(json_files)} file(s)")
        print('='*60)
        sys.exit(0 if success_count == len(json_files) else 1)
    
    elif os.path.isfile(target):
        # Sort single file
        if sort_json_file(target):
            sys.exit(0)
        else:
            sys.exit(1)
    
    else:
        print(f"Error: {target} is neither a file nor a directory")
        sys.exit(1)


if __name__ == '__main__':
    main()
