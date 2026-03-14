#!/usr/bin/env python3
"""
Scan data/www/*.html and *.js files for translation keys and compare with locale JSON.

USAGE:
    python scan_www_check_json.py <locale> [options]
    python scan_www_check_json.py * [options]

MODES:
    (default)        Interactive mode - prompt for missing keys, ask about cleanup, ask about sort
    --fast, -f       Add all missing keys at once (one prompt), skip individual edits
    --every, -e      Prompt to review every single key (detailed proofreading)
    --diff, -d       Only prompt when HTML text differs from JSON

OPTIONS:
    --clean, -c      Auto-delete unused keys (no prompt)
    --sort, -s       Auto-sort keys hierarchically at end (no prompt)

COMBINATIONS:
    <locale> --fast --clean --sort   Batch fix all issues automatically (one prompt)
    * --fast --clean --sort          Fix all locale files in one command (one prompt per locale file)
    --every and --diff cannot be combined

EXAMPLES:
    python scan_www_check_json.py en_US
        Interactive: add missing keys, ask to delete unused, ask to sort
    
    python scan_www_check_json.py lt_LT --fast
        Add all missing keys at once, ask to delete unused, ask to sort
    
    python scan_www_check_json.py en_US --clean --sort
        Delete unused keys and sort automatically
    
    python scan_www_check_json.py * --fast --clean --sort
        Batch process all locale files: add missing, delete unused, sort
"""

import os
import sys
import json
import re
import argparse
import glob
try:
    import msvcrt  # Windows
    WINDOWS = True
except ImportError:
    import termios
    import tty
    WINDOWS = False


def get_key():
    """Get a single keypress (cross-platform)."""
    if WINDOWS:
        return msvcrt.getch()
    else:
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch


def extract_keys_from_html_js(file_path):
    """Extract translation keys and their display text from HTML/JS files."""
    keys_found = {}
    
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Pattern 1a: data-i18n="key" with text content between tags
    for match in re.finditer(r'data-i18n=["\']([^"\']+)["\'](?:[^>]*>([^<]+)<)?', content):
        key = match.group(1)
        text = match.group(2).strip() if match.group(2) else ""
        if key not in keys_found and text:
            keys_found[key] = text
    
    # Pattern 1b: data-i18n="key" with placeholder attribute (for inputs)
    for match in re.finditer(r'data-i18n=["\']([^"\']+)["\'][^>]*placeholder=["\']([^"\']+)["\']', content):
        key = match.group(1)
        text = match.group(2).strip()
        if key not in keys_found:
            keys_found[key] = text
    
    # Pattern 1c: placeholder first, then data-i18n (reversed order)
    for match in re.finditer(r'placeholder=["\']([^"\']+)["\'][^>]*data-i18n=["\']([^"\']+)["\']', content):
        key = match.group(2)
        text = match.group(1).strip()
        if key not in keys_found:
            keys_found[key] = text
    
    # Pattern 1d: data-i18n="key" with value attribute (for input buttons)
    for match in re.finditer(r'data-i18n=["\']([^"\']+)["\'][^>]*value=["\']([^"\']+)["\']', content):
        key = match.group(1)
        text = match.group(2).strip()
        if key not in keys_found:
            keys_found[key] = text
    
    # Pattern 1e: value first, then data-i18n (reversed order)
    for match in re.finditer(r'value=["\']([^"\']+)["\'][^>]*data-i18n=["\']([^"\']+)["\']', content):
        key = match.group(2)
        text = match.group(1).strip()
        if key not in keys_found:
            keys_found[key] = text
    
    # Pattern 1f: data-i18n="key" with title attribute (for tooltips)
    for match in re.finditer(r'data-i18n=["\']([^"\']+)["\'][^>]*title=["\']([^"\']+)["\']', content):
        key = match.group(1)
        text = match.group(2).strip()
        if key not in keys_found:
            keys_found[key] = text
    
    # Pattern 1g: title first, then data-i18n (reversed order)
    for match in re.finditer(r'title=["\']([^"\']+)["\'][^>]*data-i18n=["\']([^"\']+)["\']', content):
        key = match.group(2)
        text = match.group(1).strip()
        if key not in keys_found:
            keys_found[key] = text
    
    # Pattern 1h: data-i18n="key" with alt attribute (for images)
    for match in re.finditer(r'data-i18n=["\']([^"\']+)["\'][^>]*alt=["\']([^"\']+)["\']', content):
        key = match.group(1)
        text = match.group(2).strip()
        if key not in keys_found:
            keys_found[key] = text
    
    # Pattern 1i: alt first, then data-i18n (reversed order)
    for match in re.finditer(r'alt=["\']([^"\']+)["\'][^>]*data-i18n=["\']([^"\']+)["\']', content):
        key = match.group(2)
        text = match.group(1).strip()
        if key not in keys_found:
            keys_found[key] = text
    
    # Pattern 2: t('key', 'fallback text', ...) - with optional additional parameters
    for match in re.finditer(r'\bt\(["\']([^"\']+)["\'],\s*["\']([^"\']+)["\'](?:\s*,\s*[^)]+)?\)', content):
        key = match.group(1)
        text = match.group(2)
        if key not in keys_found:
            keys_found[key] = text
    
    # Pattern 3: t('key') - single argument form (skip if already found in pattern 2)
    for match in re.finditer(r'\bt\(["\']([^"\']+)["\']\)', content):
        key = match.group(1)
        if key not in keys_found:
            keys_found[key] = ""
    
    return keys_found


def scan_www_folder(www_path):
    """Scan all .html and .js files in www folder."""
    all_keys = {}
    
    for filename in os.listdir(www_path):
        if filename.endswith('.html') or filename.endswith('.js'):
            file_path = os.path.join(www_path, filename)
            keys = extract_keys_from_html_js(file_path)
            
            for key, text in keys.items():
                if key not in all_keys:
                    all_keys[key] = {'text': text, 'files': [filename]}
                else:
                    if filename not in all_keys[key]['files']:
                        all_keys[key]['files'].append(filename)
    
    return all_keys


def prompt_for_key(key, found_text, json_text=None, filename=None, mode='missing'):
    """Prompt user for translation text."""
    print()  # Blank line before prompt
    
    if mode == 'missing':
        print(f"[{filename}] {key}")
        print(f"[Found] {found_text}")
        print("Enter new text (ENTER to accept Found text / ESC skip adding key to JSON): ", end='', flush=True)
        
        user_input = ""
        while True:
            if WINDOWS:
                ch = msvcrt.getch()
                if ch == b'\r':  # Enter
                    result = user_input if user_input else found_text
                    if user_input:
                        print()
                    else:
                        print(f"[ENTER - using Found text: {result}]")
                    return result
                elif ch == b'\x1b':  # ESC
                    print("[ESC - skipping this key]")
                    return None  # Skip this key
                elif ch == b'\x08':  # Backspace
                    if user_input:
                        user_input = user_input[:-1]
                        print('\b \b', end='', flush=True)
                elif ch in (b'\x03', b'\x04'):  # Ctrl+C or Ctrl+D
                    print()
                    sys.exit(0)
                else:
                    try:
                        char = ch.decode('utf-8')
                        user_input += char
                        print(char, end='', flush=True)
                    except:
                        pass
            else:  # Unix/Linux
                ch = get_key()
                if ch == '\r' or ch == '\n':  # Enter
                    result = user_input if user_input else found_text
                    if user_input:
                        print()
                    else:
                        print(f"[ENTER - using Found text: {result}]")
                    return result
                elif ch == '\x1b':  # ESC
                    print("[ESC - skipping this key]")
                    return None  # Skip this key
                elif ch == '\x7f':  # Backspace
                    if user_input:
                        user_input = user_input[:-1]
                        print('\b \b', end='', flush=True)
                elif ch in ('\x03', '\x04'):  # Ctrl+C or Ctrl+D
                    print()
                    sys.exit(0)
                else:
                    user_input += ch
                    print(ch, end='', flush=True)
    
    else:  # 'all' or 'diff' mode
        print(f"[{filename}] {key}")
        print(f"[Found] {found_text}")
        if json_text is not None:
            print(f"[JSON] {json_text}")
        print("Enter new text (ENTER to accept Found text / ESC keeps JSON text): ", end='', flush=True)
        
        user_input = ""
        while True:
            if WINDOWS:
                ch = msvcrt.getch()
                if ch == b'\r':  # Enter
                    result = user_input if user_input else found_text
                    if user_input:
                        print()
                    else:
                        print(f"[ENTER - using Found text: {result}]")
                    return result
                elif ch == b'\x1b':  # ESC
                    result = json_text if json_text is not None else found_text
                    print(f"[ESC - keeping JSON text: {result}]")
                    return result
                elif ch == b'\x08':  # Backspace
                    if user_input:
                        user_input = user_input[:-1]
                        print('\b \b', end='', flush=True)
                elif ch in (b'\x03', b'\x04'):  # Ctrl+C or Ctrl+D
                    print()
                    sys.exit(0)
                else:
                    try:
                        char = ch.decode('utf-8')
                        user_input += char
                        print(char, end='', flush=True)
                    except:
                        pass
            else:  # Unix/Linux
                ch = get_key()
                if ch == '\r' or ch == '\n':  # Enter
                    result = user_input if user_input else found_text
                    if user_input:
                        print()
                    else:
                        print(f"[ENTER - using Found text: {result}]")
                    return result
                elif ch == '\x1b':  # ESC
                    result = json_text if json_text is not None else found_text
                    print(f"[ESC - keeping JSON text: {result}]")
                    return result
                elif ch == '\x7f':  # Backspace
                    if user_input:
                        user_input = user_input[:-1]
                        print('\b \b', end='', flush=True)
                elif ch in ('\x03', '\x04'):  # Ctrl+C or Ctrl+D
                    print()
                    sys.exit(0)
                else:
                    user_input += ch
                    print(ch, end='', flush=True)


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


def sort_json_data(data):
    """Sort JSON data dict by hierarchical key ordering."""
    sorted_keys = sorted(data.keys(), key=get_sort_priority)
    return {key: data[key] for key in sorted_keys}


def process_locale_file(locale_code, www_path, json_path, mode, auto_clean, auto_sort):
    """Process a single locale file."""
    print(f"\n{'='*60}")
    print(f"Processing: {locale_code}.json")
    print(f"{'='*60}")
    
    if not os.path.exists(json_path):
        print(f"Error: JSON file not found at {json_path}")
        return False
    
    # Load JSON
    with open(json_path, 'r', encoding='utf-8') as f:
        locale_data = json.load(f)
    
    # Scan www files
    print(f"Scanning {www_path} for translation keys...")
    found_keys = scan_www_folder(www_path)
    print(f"Found {len(found_keys)} unique keys in HTML/JS files")
    print(f"Loaded {len(locale_data)} keys from {locale_code}.json")
    
    # Count excluded locale* keys
    excluded_keys = [k for k in locale_data.keys() if k in ('locale_code', 'locale', 'locale_en')]
    if excluded_keys:
        print(f"Ignoring {len(excluded_keys)} locale* metadata key(s)")
    
    # Show missing keys summary if in missing or fast mode
    if mode in ('missing', 'fast'):
        missing_keys = [(key, data) for key, data in found_keys.items() if locale_data.get(key) is None]
        if missing_keys:
            print("\n" + "="*60)
            print("Keys in HTML/JS files not found in JSON:")
            print("="*60)
            for key, data in sorted(missing_keys):
                print(f"  {key} = {data['text']}")
            print(f"\nTotal: {len(missing_keys)} missing key(s)")
            print("=" * 60)
    
    # Process keys
    updates = {}
    processed_count = 0
    
    if mode == 'fast':
        # Fast mode: add all missing keys at once
        missing_keys = [(key, data) for key, data in found_keys.items() if locale_data.get(key) is None]
        if missing_keys:
            print(f"\nAdd all {len(missing_keys)} missing keys? [y/n]: ", end='', flush=True)
            response = input().strip().lower()
            if response == 'y':
                for key, data in missing_keys:
                    updates[key] = data['text']
                    processed_count += 1
    
    elif mode in ('missing', 'every', 'diff'):
        # Interactive modes
        for key, data in sorted(found_keys.items()):
            found_text = data['text']
            filename = data['files'][0] if data['files'] else 'unknown'
            json_text = locale_data.get(key)
            
            if mode == 'missing':
                if json_text is None:
                    new_text = prompt_for_key(key, found_text, None, filename, mode='missing')
                    if new_text is not None:  # Only add if not skipped (ESC)
                        updates[key] = new_text
                        processed_count += 1
            
            elif mode == 'every':
                new_text = prompt_for_key(key, found_text, json_text, filename, mode='all')
                if new_text != json_text:
                    updates[key] = new_text
                    processed_count += 1
            
            elif mode == 'diff':
                if json_text is None or (found_text and json_text != found_text):
                    new_text = prompt_for_key(key, found_text, json_text, filename, mode='diff')
                    if new_text != json_text:
                        updates[key] = new_text
                        processed_count += 1
    
    # Update JSON if changes were made
    if updates:
        print(f"\n{len(updates)} key(s) updated")
        locale_data.update(updates)
    else:
        print("\nNo changes made")
    
    # Handle unused keys
    unused = []
    for key in sorted(locale_data.keys()):
        if key not in found_keys and key not in ('locale_code', 'locale', 'locale_en'):
            unused.append(key)
    
    # Show unused keys
    print("\n" + "="*60)
    print("Keys in JSON not found in HTML/JS files:")
    print("="*60)
    
    if unused:
        for key in unused:
            print(f"  {key} = {locale_data[key]}")
        print(f"\nTotal: {len(unused)} unused key(s)")
        
        # Delete unused keys
        if auto_clean:
            for key in unused:
                del locale_data[key]
            print(f"✓ Auto-deleted {len(unused)} unused key(s)")
        else:
            print("\nWould you like to delete these keys from the JSON? [y/n]: ", end='', flush=True)
            response = input().strip().lower()
            if response == 'y':
                for key in unused:
                    del locale_data[key]
                print(f"✓ Deleted {len(unused)} unused key(s)")
            else:
                print("No keys deleted")
    else:
        print("  (none)")
    
    # Sort JSON
    if auto_sort:
        locale_data = sort_json_data(locale_data)
        print("\n✓ Auto-sorted keys hierarchically")
    elif (updates or unused) and mode != 'fast':  # Only ask if something changed
        print("\nWould you like to sort the keys in the JSON? [y/n]: ", end='', flush=True)
        response = input().strip().lower()
        if response == 'y':
            locale_data = sort_json_data(locale_data)
            print("✓ Sorted keys hierarchically")
    
    # Write updated JSON
    temp_path = json_path + '.tmp'
    with open(temp_path, 'w', encoding='utf-8') as f:
        json.dump(locale_data, f, ensure_ascii=False, indent=2)
    
    # Replace original
    os.replace(temp_path, json_path)
    print(f"\n✓ Saved {json_path}")
    
    return True


def main():
    # Show help if no arguments provided
    if len(sys.argv) == 1:
        print(__doc__)
        sys.exit(0)
    
    parser = argparse.ArgumentParser(
        description='Scan www files for translation keys and manage locale JSON files',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )
    parser.add_argument('locale', help='Locale code (e.g., en_US) or * to process all locales')
    parser.add_argument('--fast', '-f', action='store_true', help='Add all missing keys at once (one prompt)')
    parser.add_argument('--every', '-e', action='store_true', help='Prompt to review every single key')
    parser.add_argument('--diff', '-d', action='store_true', help='Only prompt when text differs')
    parser.add_argument('--clean', '-c', action='store_true', help='Auto-delete unused keys (no prompt)')
    parser.add_argument('--sort', '-s', action='store_true', help='Auto-sort keys hierarchically (no prompt)')
    args = parser.parse_args()
    
    # Validate argument combinations
    if args.every and args.diff:
        print("Error: --every and --diff cannot be combined")
        sys.exit(1)
    
    if args.locale == '*' and (args.every or args.diff):
        print("Error: * (all locales) cannot be combined with --every or --diff")
        sys.exit(1)
    
    # Determine mode
    if args.fast:
        mode = 'fast'
    elif args.every:
        mode = 'every'
    elif args.diff:
        mode = 'diff'
    else:
        mode = 'missing'
    
    # Paths
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.abspath(os.path.join(script_dir, '..', '..'))
    www_path = os.path.join(project_root, 'data', 'www')
    
    if not os.path.exists(www_path):
        print(f"Error: www folder not found at {www_path}")
        sys.exit(1)
    
    # Process file(s)
    if args.locale == '*':
        # Process all locale files
        webui_path = os.path.join(script_dir, 'webui')
        json_files = glob.glob(os.path.join(webui_path, '*.json'))
        
        if not json_files:
            print(f"Error: No JSON files found in {webui_path}")
            sys.exit(1)
        
        print(f"Found {len(json_files)} locale file(s) to process")
        
        success_count = 0
        for json_path in sorted(json_files):
            locale_code = os.path.splitext(os.path.basename(json_path))[0]
            if process_locale_file(locale_code, www_path, json_path, mode, args.clean, args.sort):
                success_count += 1
        
        print(f"\n{'='*60}")
        print(f"Processed {success_count}/{len(json_files)} locale file(s) successfully")
        print(f"{'='*60}")
    
    else:
        # Process single locale file
        json_path = os.path.join(script_dir, 'webui', f'{args.locale}.json')
        process_locale_file(args.locale, www_path, json_path, mode, args.clean, args.sort)


if __name__ == '__main__':
    main()
