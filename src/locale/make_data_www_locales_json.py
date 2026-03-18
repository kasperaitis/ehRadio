#!/usr/bin/env python3
"""
make_data_www_locales_json.py

Scans the webui folder for locale JSON files and creates a compact locales.json
index file for web browsers/JavaScript.

Output format (compact, one locale per line):
{
"be_BY": "беларуская мова",
"bg_BG": "български език",
...
}
"""

import json
import os
from pathlib import Path

def main():
    # Get paths: src/locale -> repo root -> data/www
    script_dir = Path(__file__).parent
    repo_root = script_dir.parent.parent
    webui_dir = script_dir / "webui"
    output_file = repo_root / "data" / "www" / "locales.json"
    
    if not webui_dir.exists():
        print(f"Error: webui directory not found at {webui_dir}")
        return 1
    
    # Dictionary to store all locales (locale_code: native_name)
    locales = {}
    
    # Scan all .json files in webui directory
    json_files = sorted(webui_dir.glob("*.json"))
    
    if not json_files:
        print(f"Warning: No JSON files found in {webui_dir}")
        return 1
    
    print(f"Found {len(json_files)} locale files in webui/")
    
    # Process each JSON file
    for json_file in json_files:
        # Skip the output file itself if it exists
        if json_file.name == "locales.json":
            continue
        
        # Extract locale code from filename (e.g., "be_BY" from "be_BY.json")
        locale_code = json_file.stem
        
        try:
            # Read the JSON file (handle UTF-8 BOM)
            with open(json_file, 'r', encoding='utf-8-sig') as f:
                data = json.load(f)
            
            # Extract locale field (native name only)
            native_name = data.get("locale", "")
            
            if not native_name:
                print(f"Warning: {json_file.name} missing 'locale' field")
                continue
            
            # Add to locales dictionary (simple key: value)
            locales[locale_code] = native_name
            
            print(f"  ✓ {locale_code}: {native_name}")
            
        except json.JSONDecodeError as e:
            print(f"Error: Failed to parse {json_file.name}: {e}")
            continue
        except Exception as e:
            print(f"Error: Failed to process {json_file.name}: {e}")
            continue
    
    if not locales:
        print("Error: No valid locale data found")
        return 1
    
    # Write compact locales.json (no indentation, one locale per line)
    try:
        # Ensure output directory exists
        output_file.parent.mkdir(parents=True, exist_ok=True)
        
        # Manually format for compact output with one locale per line
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write('{\n')
            sorted_items = sorted(locales.items())
            for i, (code, name) in enumerate(sorted_items):
                # Escape double quotes in name if present
                escaped_name = name.replace('"', '\\"')
                comma = ',' if i < len(sorted_items) - 1 else ''
                f.write(f'"{code}": "{escaped_name}"{comma}\n')
            f.write('}\n')
        
        print(f"\n✓ Successfully created {output_file}")
        print(f"  Total locales: {len(locales)}")
        return 0
        
    except Exception as e:
        print(f"Error: Failed to write {output_file}: {e}")
        return 1

if __name__ == "__main__":
    exit(main())
