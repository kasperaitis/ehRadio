#!/usr/bin/env python3
"""Remove weatherFmt blocks from all displayL10n files"""
import re
from pathlib import Path

# Find all displayL10n_*.h files
locale_files = list(Path('.').glob('displayL10n_*.h'))

print('Removing weatherFmt blocks from displayL10n files...\n')

for filepath in locale_files:
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    original_content = content
    
    # Remove the entire weatherFmt block including the blank line after #endif
    # More flexible pattern that handles variations in formatting and comments
    pattern = r'#if EXT_WEATHER\s*\n.*?weatherFmt.*?\n#else\s*\n.*?weatherFmt.*?\n#endif\s*\n'
    content = re.sub(pattern, '', content, flags=re.DOTALL)
    
    if content != original_content:
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(content)
        print(f'✓ {filepath.name} - Removed weatherFmt block')
    else:
        print(f'⚠ {filepath.name} - No weatherFmt block found or already removed')

print(f'\n{"="*60}')
print(f'Processed {len(locale_files)} files')
