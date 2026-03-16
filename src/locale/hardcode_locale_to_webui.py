#!/usr/bin/env python3
"""
Sync WebUI Translation Text Script
Scans HTML and JS files in data/www/ and replaces translatable text with values 
from a locale JSON file.

For HTML: Updates text in elements with data-i18n attributes (text content, placeholder, value, title, alt)
For JS: Updates default text in t('key', 'default', ...) function calls

Usage:
  python hardcode_locale_to_webui.py [locale_code] [--dry-run]
  
  locale_code: Optional, defaults to "en_US"
  --dry-run: Preview changes without modifying files
  
  Example: python hardcode_locale_to_webui.py lt_LT --dry-run
"""

import json
import re
import sys
from pathlib import Path


def load_translations(locale_code):
    """Load translations from the specified locale JSON file"""
    locale_path = Path(__file__).parent / 'webui' / f'{locale_code}.json'
    
    if not locale_path.exists():
        print(f"Error: Locale file not found: {locale_path}")
        sys.exit(1)
    
    with open(locale_path, 'r', encoding='utf-8') as f:
        content = f.read()
        if content.startswith('\ufeff'):  # Remove BOM if present
            content = content[1:]
        return json.loads(content)


def update_locale_h(locale_code):
    """Update HARDCODED_WEBUI_LOCALE in locale.h"""
    locale_h_path = Path(__file__).parent / 'locale.h'
    
    if not locale_h_path.exists():
        print(f"Warning: Could not find locale.h at {locale_h_path}")
        return False
    
    with open(locale_h_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Find and replace the #define HARDCODED_WEBUI_LOCALE line
    pattern = r'(#define\s+HARDCODED_WEBUI_LOCALE\s+")[^"]*(")'
    new_content = re.sub(pattern, rf'\1{locale_code}\2', content)
    
    if new_content != content:
        with open(locale_h_path, 'w', encoding='utf-8') as f:
            f.write(new_content)
        print(f"\nUpdated locale.h: HARDCODED_WEBUI_LOCALE = \"{locale_code}\"")
        return True
    else:
        print(f"\nWarning: Could not find HARDCODED_WEBUI_LOCALE in locale.h")
        return False


def sync_html_file(html_path, translations, dry_run=False):
    """Sync a single HTML file with translations"""
    with open(html_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    original_content = content
    fields_updated = 0  # Fields where text differs (actual changes)
    fields_found = 0    # All translatable fields detected
    keys_used = set()
    keys_found = set()
    
    # Pattern 1a: data-i18n="key">text</tag>
    def replace_text_content(match):
        nonlocal fields_updated, fields_found
        key = match.group(1)
        old_text = match.group(2)
        closing = match.group(3)
        
        if key in translations:
            fields_found += 1
            keys_found.add(key)
            new_text = translations[key]
            if old_text.strip() != new_text:
                fields_updated += 1
                keys_used.add(key)
                return f'data-i18n="{key}">{new_text}{closing}'
        
        return match.group(0)
    
    content = re.sub(r'data-i18n=["\']([^"\']+)["\']>([^<]*?)(<\/)', replace_text_content, content)
    
    # Pattern 1b/1c: placeholder attribute (bidirectional)
    def replace_placeholder_di18n_first(match):
        nonlocal fields_updated, fields_found
        key = match.group(1)
        old_text = match.group(2)
        
        if key in translations:
            fields_found += 1
            keys_found.add(key)
            new_text = translations[key]
            if old_text != new_text:
                fields_updated += 1
                keys_used.add(key)
                # Replace just the placeholder value, preserve everything else
                return match.group(0).replace(f'placeholder="{old_text}"', f'placeholder="{new_text}"')
        
        return match.group(0)
    
    def replace_placeholder_ph_first(match):
        nonlocal fields_updated, fields_found
        old_text = match.group(1)
        key = match.group(2)
        
        if key in translations:
            fields_found += 1
            keys_found.add(key)
            new_text = translations[key]
            if old_text != new_text:
                fields_updated += 1
                keys_used.add(key)
                return match.group(0).replace(f'placeholder="{old_text}"', f'placeholder="{new_text}"')
        
        return match.group(0)
    
    content = re.sub(r'data-i18n=["\']([^"\']+)["\'][^>]*placeholder=["\']([^"\']+)["\']', replace_placeholder_di18n_first, content)
    content = re.sub(r'placeholder=["\']([^"\']+)["\'][^>]*data-i18n=["\']([^"\']+)["\']', replace_placeholder_ph_first, content)
    
    # Pattern 1d/1e: value attribute (bidirectional)
    def replace_value_di18n_first(match):
        nonlocal fields_updated, fields_found
        key = match.group(1)
        old_text = match.group(2)
        
        if key in translations:
            fields_found += 1
            keys_found.add(key)
            new_text = translations[key]
            if old_text != new_text:
                fields_updated += 1
                keys_used.add(key)
                return match.group(0).replace(f'value="{old_text}"', f'value="{new_text}"')
        
        return match.group(0)
    
    def replace_value_val_first(match):
        nonlocal fields_updated, fields_found
        old_text = match.group(1)
        key = match.group(2)
        
        if key in translations:
            fields_found += 1
            keys_found.add(key)
            new_text = translations[key]
            if old_text != new_text:
                fields_updated += 1
                keys_used.add(key)
                return match.group(0).replace(f'value="{old_text}"', f'value="{new_text}"')
        
        return match.group(0)
    
    content = re.sub(r'data-i18n=["\']([^"\']+)["\'][^>]*value=["\']([^"\']+)["\']', replace_value_di18n_first, content)
    content = re.sub(r'value=["\']([^"\']+)["\'][^>]*data-i18n=["\']([^"\']+)["\']', replace_value_val_first, content)
    
    # Pattern 1f/1g: title attribute (bidirectional)
    def replace_title_di18n_first(match):
        nonlocal fields_updated, fields_found
        key = match.group(1)
        old_text = match.group(2)
        
        if key in translations:
            fields_found += 1
            keys_found.add(key)
            new_text = translations[key]
            if old_text != new_text:
                fields_updated += 1
                keys_used.add(key)
                return match.group(0).replace(f'title="{old_text}"', f'title="{new_text}"')
        
        return match.group(0)
    
    def replace_title_ttl_first(match):
        nonlocal fields_updated, fields_found
        old_text = match.group(1)
        key = match.group(2)
        
        if key in translations:
            fields_found += 1
            keys_found.add(key)
            new_text = translations[key]
            if old_text != new_text:
                fields_updated += 1
                keys_used.add(key)
                return match.group(0).replace(f'title="{old_text}"', f'title="{new_text}"')
        
        return match.group(0)
    
    content = re.sub(r'data-i18n=["\']([^"\']+)["\'][^>]*title=["\']([^"\']+)["\']', replace_title_di18n_first, content)
    content = re.sub(r'title=["\']([^"\']+)["\'][^>]*data-i18n=["\']([^"\']+)["\']', replace_title_ttl_first, content)
    
    # Pattern 1h/1i: alt attribute (bidirectional)
    def replace_alt_di18n_first(match):
        nonlocal fields_updated, fields_found
        key = match.group(1)
        old_text = match.group(2)
        
        if key in translations:
            fields_found += 1
            keys_found.add(key)
            new_text = translations[key]
            if old_text != new_text:
                fields_updated += 1
                keys_used.add(key)
                return match.group(0).replace(f'alt="{old_text}"', f'alt="{new_text}"')
        
        return match.group(0)
    
    def replace_alt_alt_first(match):
        nonlocal fields_updated, fields_found
        old_text = match.group(1)
        key = match.group(2)
        
        if key in translations:
            fields_found += 1
            keys_found.add(key)
            new_text = translations[key]
            if old_text != new_text:
                fields_updated += 1
                keys_used.add(key)
                return match.group(0).replace(f'alt="{old_text}"', f'alt="{new_text}"')
        
        return match.group(0)
    
    content = re.sub(r'data-i18n=["\']([^"\']+)["\'][^>]*alt=["\']([^"\']+)["\']', replace_alt_di18n_first, content)
    content = re.sub(r'alt=["\']([^"\']+)["\'][^>]*data-i18n=["\']([^"\']+)["\']', replace_alt_alt_first, content)
    
    return content, fields_found, len(keys_found), fields_updated, len(keys_used), content != original_content


def sync_js_file(js_path, translations, dry_run=False):
    """Sync a single JS file with translations"""
    with open(js_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    original_content = content
    fields_updated = 0
    fields_found = 0
    keys_used = set()
    keys_found = set()
    
    # Pattern: t('key', 'Default Text', ...) with optional additional parameters
    def replace_t_function(match):
        nonlocal fields_updated, fields_found
        quote_char = match.group(1)
        key = match.group(2)
        old_text = match.group(3)
        rest = match.group(4) or ''  # Optional additional parameters
        
        if key in translations:
            fields_found += 1
            keys_found.add(key)
            new_text = translations[key]
            # Escape quotes in translation
            if quote_char == "'":
                new_text_escaped = new_text.replace("\\", "\\\\").replace("'", "\\'")
            else:
                new_text_escaped = new_text.replace("\\", "\\\\").replace('"', '\\"')
            
            if old_text != new_text:
                fields_updated += 1
                keys_used.add(key)
                if rest:
                    return f"t({quote_char}{key}{quote_char}, {quote_char}{new_text_escaped}{quote_char}{rest})"
                else:
                    return f"t({quote_char}{key}{quote_char}, {quote_char}{new_text_escaped}{quote_char})"
        
        return match.group(0)
    
    # Pattern: t('key', 'text', optional_params)
    pattern = r"\bt\((['\"])([^'\"]+)\1,\s*(['\"])([^'\"]*)\3((?:\s*,\s*[^)]+)?\))"
    content = re.sub(pattern, replace_t_function, content)
    
    return content, fields_found, len(keys_found), fields_updated, len(keys_used), content != original_content


def main():
    # Get locale code from command line or use default
    dry_run = '--dry-run' in sys.argv
    
    # Get locale code (filter out --dry-run flag)
    locale_args = [arg for arg in sys.argv[1:] if arg != '--dry-run']
    locale_code = locale_args[0] if locale_args else 'en_US'
    
    print(f"{'[DRY RUN] ' if dry_run else ''}Syncing HTML/JS files with locale: {locale_code}")
    
    # Check for locale.h FIRST - before doing any work
    locale_h_path = Path(__file__).parent / 'locale.h'
    locale_h_exists = locale_h_path.exists()
    
    if locale_h_exists:
        print(f"✓ locale.h is ready at {locale_h_path}\n")
    elif dry_run:
        print(f"⚠ WARNING: locale.h not found at {locale_h_path}")
        print(f"  This is a dry-run, so proceeding anyway...\n")
    else:
        print(f"✗ ERROR: locale.h not found at {locale_h_path}")
        print(f"  Cannot proceed without locale.h to update HARDCODED_WEBUI_LOCALE")
        print(f"  Aborting.")
        sys.exit(1)
    
    # Load translations
    translations = load_translations(locale_code)
    print(f"Loaded {len(translations)} translation keys\n")
    
    # Find all HTML and JS files in data/www/
    www_dir = Path(__file__).parent.parent.parent / 'data' / 'www'
    html_files = sorted(www_dir.glob('*.html'))
    js_files = sorted(www_dir.glob('*.js'))
    
    if not html_files and not js_files:
        print(f"Error: No HTML or JS files found in {www_dir}")
        sys.exit(1)
    
    print(f"Found {len(html_files)} HTML files and {len(js_files)} JS files\n")
    
    # Process each HTML file
    files_with_changes = 0
    files_with_fields = 0
    total_fields_found = 0
    total_fields_updated = 0
    
    for html_path in html_files:
        print(f"Checking: {html_path.name}")
        new_content, fields_found, keys_found_count, fields_updated, keys_updated_count, has_changes = sync_html_file(html_path, translations, dry_run)
        
        if fields_found > 0:
            files_with_fields += 1
            total_fields_found += fields_found
            
            if has_changes:
                total_fields_updated += fields_updated
                if dry_run:
                    print(f"  → Found: {fields_found} field{'s' if fields_found != 1 else ''} matching {keys_found_count} key{'s' if keys_found_count != 1 else ''}. Would update {fields_updated} field{'s' if fields_updated != 1 else ''} using {keys_updated_count} key{'s' if keys_updated_count != 1 else ''}. - DRY RUN -")
                else:
                    print(f"  → Found: {fields_found} field{'s' if fields_found != 1 else ''} matching {keys_found_count} key{'s' if keys_found_count != 1 else ''}. Updated {fields_updated} field{'s' if fields_updated != 1 else ''} using {keys_updated_count} key{'s' if keys_updated_count != 1 else ''}.")
                files_with_changes += 1
                
                if not dry_run:
                    with open(html_path, 'w', encoding='utf-8') as f:
                        f.write(new_content)
            else:
                print(f"  → Found: {fields_found} field{'s' if fields_found != 1 else ''} matching {keys_found_count} key{'s' if keys_found_count != 1 else ''} (all match JSON, no updates needed)")
        else:
            print(f"  → No translatable fields found")
    
    # Process each JS file
    for js_path in js_files:
        print(f"Checking: {js_path.name}")
        new_content, fields_found, keys_found_count, fields_updated, keys_updated_count, has_changes = sync_js_file(js_path, translations, dry_run)
        
        if fields_found > 0:
            files_with_fields += 1
            total_fields_found += fields_found
            
            if has_changes:
                total_fields_updated += fields_updated
                if dry_run:
                    print(f"  → Found: {fields_found} field{'s' if fields_found != 1 else ''} matching {keys_found_count} key{'s' if keys_found_count != 1 else ''}. Would update {fields_updated} field{'s' if fields_updated != 1 else ''} using {keys_updated_count} key{'s' if keys_updated_count != 1 else ''}. - DRY RUN -")
                else:
                    print(f"  → Found: {fields_found} field{'s' if fields_found != 1 else ''} matching {keys_found_count} key{'s' if keys_found_count != 1 else ''}. Updated {fields_updated} field{'s' if fields_updated != 1 else ''} using {keys_updated_count} key{'s' if keys_updated_count != 1 else ''}.")
                files_with_changes += 1
                
                if not dry_run:
                    with open(js_path, 'w', encoding='utf-8') as f:
                        f.write(new_content)
            else:
                print(f"  → Found: {fields_found} field{'s' if fields_found != 1 else ''} matching {keys_found_count} key{'s' if keys_found_count != 1 else ''} (all match JSON, no updates needed)")
        else:
            print(f"  → No translatable fields found")
    
    total_files = len(html_files) + len(js_files)
    print(f"\n{'[DRY RUN] ' if dry_run else ''}Summary:")
    print(f"Files checked: {total_files}")
    print(f"Files with translatable fields: {files_with_fields}")
    print(f"Files {'that would be updated' if dry_run else 'updated'}: {files_with_changes}")
    print(f"Total translatable fields found: {total_fields_found}")
    print(f"Total fields {'that would be' if dry_run else ''} updated: {total_fields_updated}")
    
    if dry_run:
        print("\nRun without --dry-run to apply changes")
    else:
        # Update locale.h to reflect the hardcoded locale (only after all files processed successfully)
        if files_with_changes > 0:
            # Final safety check before updating locale.h
            locale_h_path = Path(__file__).parent / 'locale.h'
            if locale_h_path.exists():
                update_locale_h(locale_code)
            else:
                print(f"\n⚠ WARNING: locale.h disappeared! Cannot update HARDCODED_WEBUI_LOCALE")
        elif total_files > 0:
            print("\nNo files were updated, so locale.h was not modified.")


if __name__ == '__main__':
    main()
