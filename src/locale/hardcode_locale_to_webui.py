#!/usr/bin/env python3
"""
Sync WebUI Translation Text Script
Scans HTML and JS files in data/www/ and replaces translatable text with values 
from a locale JSON file.

For HTML: Updates text in elements with data-i18n attributes
For JS: Updates default text in t('key', 'default') function calls

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
from html.parser import HTMLParser

class TranslationSyncer(HTMLParser):
    """HTML parser that tracks and updates text based on data-i18n attributes"""
    
    def __init__(self, translations):
        super().__init__()
        self.translations = translations
        self.output = []
        self.current_i18n_key = None
        self.pending_text_replacement = False
        
    def handle_starttag(self, tag, attrs):
        # Reconstruct the tag
        attrs_dict = dict(attrs)
        attrs_str = ''.join(f' {k}="{v}"' for k, v in attrs)
        
        # Check if this tag has data-i18n attribute
        if 'data-i18n' in attrs_dict:
            self.current_i18n_key = attrs_dict['data-i18n']
            self.pending_text_replacement = True
        else:
            self.current_i18n_key = None
            self.pending_text_replacement = False
            
        self.output.append(f'<{tag}{attrs_str}>')
    
    def handle_endtag(self, tag):
        self.output.append(f'</{tag}>')
        self.current_i18n_key = None
        self.pending_text_replacement = False
    
    def handle_startendtag(self, tag, attrs):
        attrs_str = ''.join(f' {k}="{v}"' for k, v in attrs)
        self.output.append(f'<{tag}{attrs_str} />')
    
    def handle_data(self, data):
        # If we're inside a tag with data-i18n, replace the text
        if self.pending_text_replacement and self.current_i18n_key:
            if self.current_i18n_key in self.translations:
                # Replace with translation value
                self.output.append(self.translations[self.current_i18n_key])
                self.pending_text_replacement = False  # Only replace once per tag
                return
        
        # Otherwise keep original data
        self.output.append(data)
    
    def handle_comment(self, data):
        self.output.append(f'<!--{data}-->')
    
    def handle_decl(self, decl):
        self.output.append(f'<!{decl}>')
    
    def get_output(self):
        return ''.join(self.output)


def load_translations(locale_code):
    """Load translations from the specified locale JSON file"""
    locale_path = Path(__file__).parent / 'webui' / f'{locale_code}.json'
    
    if not locale_path.exists():
        print(f"Error: Locale file not found: {locale_path}")
        sys.exit(1)
    
    with open(locale_path, 'r', encoding='utf-8') as f:
        # Handle potential BOM
        content = f.read()
        if content.startswith('\ufeff'):
            content = content[1:]
        return json.loads(content)


def sync_html_file(html_path, translations, dry_run=False):
    """Sync a single HTML file with translations"""
    print(f"\nProcessing: {html_path.name}")
    
    with open(html_path, 'r', encoding='utf-8') as f:
        original_content = f.read()
    
    # Use regex to find and replace text in elements with data-i18n
    # Pattern: finds opening tag with data-i18n, captures the key, then replaces inner text
    def replace_translation(match):
        i18n_key = match.group(1)
        tag_content = match.group(2)
        closing_tag = match.group(3)
        
        if i18n_key in translations:
            translation = translations[i18n_key]
            # Keep the tag structure, just replace the text
            return f'data-i18n="{i18n_key}">{translation}{closing_tag}'
        else:
            # No translation found, keep original
            return match.group(0).replace('data-i18n="', '')
    
    # Pattern explanation:
    # data-i18n="([^"]+)"  - captures the i18n key
    # >([^<]*)             - captures text content between tags (non-greedy)
    # (</)                 - captures the closing tag start
    pattern = r'data-i18n="([^"]+)">([^<]*?)(<\/)'
    
    updated_content = re.sub(pattern, replace_translation, original_content)
    
    if updated_content == original_content:
        print(f"  → No changes needed")
        return False
    
    if dry_run:
        print(f"  → Would update (dry run)")
        return True
    
    # Write updated content
    with open(html_path, 'w', encoding='utf-8') as f:
        f.write(updated_content)
    
    print(f"  → Updated!")
    return True


def sync_js_file(js_path, translations, dry_run=False):
    """Sync a single JS file with translations"""
    print(f"\nProcessing: {js_path.name}")
    
    with open(js_path, 'r', encoding='utf-8') as f:
        original_content = f.read()
    
    # Pattern to match t('key', 'Default Text') or t("key", "Default Text")
    # We need to replace the default text with the translation
    def replace_t_function(match):
        quote_char = match.group(1)  # Either ' or "
        key = match.group(2)
        default_text = match.group(4)  # Current default text
        
        if key in translations:
            translation = translations[key]
            # Escape quotes in translation to match the quote character used
            if quote_char == "'":
                translation = translation.replace("'", "\\'")
            else:
                translation = translation.replace('"', '\\"')
            return f"t({quote_char}{key}{quote_char}, {quote_char}{translation}{quote_char})"
        else:
            # No translation found, keep original
            return match.group(0)
    
    # Pattern explanation:
    # t\(                    - literal t(
    # (['"])                 - capture quote character (group 1)
    # ([^'"]+)               - capture the key (group 2)
    # \1                     - same quote character as group 1
    # ,\s*                   - comma and optional whitespace
    # (['"])                 - capture quote character for default (group 3)
    # ((?:[^'"]|\\.)*)       - capture default text, handling escaped quotes (group 4)
    # \3                     - same quote character as group 3
    # \)                     - literal )
    pattern = r"t\((['\"])([^'\"]+)\1,\s*(['\"])((?:[^'\"]|\\.)*)\3\)"
    
    updated_content = re.sub(pattern, replace_t_function, original_content)
    
    if updated_content == original_content:
        print(f"  → No changes needed")
        return False
    
    if dry_run:
        print(f"  → Would update (dry run)")
        return True
    
    # Write updated content
    with open(js_path, 'w', encoding='utf-8') as f:
        f.write(updated_content)
    
    print(f"  → Updated!")
    return True


def main():
    # Get locale code from command line or use default
    dry_run = '--dry-run' in sys.argv
    
    # Get locale code (filter out --dry-run flag)
    locale_args = [arg for arg in sys.argv[1:] if arg != '--dry-run']
    locale_code = locale_args[0] if locale_args else 'en_US'
    
    print(f"{'[DRY RUN] ' if dry_run else ''}Syncing HTML files with locale: {locale_code}")
    
    # Load translations
    translations = load_translations(locale_code)
    print(f"Loaded {len(translations)} translation keys")
    
    # Find all HTML and JS files in data/www/
    www_dir = Path(__file__).parent.parent.parent / 'data' / 'www'
    html_files = sorted(www_dir.glob('*.html'))
    js_files = sorted(www_dir.glob('*.js'))
    
    if not html_files and not js_files:
        print(f"Error: No HTML or JS files found in {www_dir}")
        sys.exit(1)
    
    print(f"Found {len(html_files)} HTML files and {len(js_files)} JS files")
    
    # Process each HTML file
    updated_count = 0
    for html_path in html_files:
        if sync_html_file(html_path, translations, dry_run):
            updated_count += 1
    
    # Process each JS file
    for js_path in js_files:
        if sync_js_file(js_path, translations, dry_run):
            updated_count += 1
    
    total_files = len(html_files) + len(js_files)
    print(f"\n{'Would update' if dry_run else 'Updated'} {updated_count} of {total_files} files")
    
    if dry_run:
        print("\nRun without --dry-run to apply changes")


if __name__ == '__main__':
    main()
