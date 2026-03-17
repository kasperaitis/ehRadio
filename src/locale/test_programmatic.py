#!/usr/bin/env python3
"""Test programmatic calling of scan_trans_deepl.py (no shell interference)."""
import subprocess
import sys

# Test cases with special characters
test_cases = [
    '"Hello"',           # Text with quotes
    "It's great",        # Apostrophe
    'He said "Hi"',      # Embedded quotes
    'C:\\path\\file',    # Backslashes (Windows path)
]

for text in test_cases:
    result = subprocess.run(
        [sys.executable, 'scan_trans_deepl.py', 'en_US', 'de_DE', text],
        capture_output=True,
        text=True,
        encoding='utf-8'
    )
    
    if result.returncode == 0:
        output = result.stdout.strip()
        print(f"✓ Input:  {repr(text)}")
        print(f"  Output: {repr(output)}")
        print()
    else:
        print(f"✗ Failed: {repr(text)}")
        print(f"  Error: {result.stderr.strip()}")
        print()
