#!/usr/bin/env python3
"""
Generate firmware.txt and releases.md from myoptions.h
Operates on files in the same folder as the script.
"""

import re
import os
from pathlib import Path

def parse_myoptions_h(myoptions_path):
    """
    Parse myoptions.h to extract firmware metadata.
    
    Format expected in myoptions.h:
    #define FIRMWARE "filename.bin" // "board_env", "chip_family", "contributor"
    #define FIRMWARE_NAME "Friendly Name" // "optional_url"
    
    Returns tuple: (firmwares_list, url_map)
    - firmwares_list: List of tuples (board_env, chip_family, fw_env, friendly_name)
    - url_map: Dict mapping fw_env to URL
    """
    firmwares = []
    url_map = {}
    
    with open(myoptions_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Find all FIRMWARE definitions with their metadata
    firmware_pattern = r'#define\s+FIRMWARE\s+"([^"]+)"\s*//\s*"([^"]+)",\s*"([^"]+)",\s*"([^"]+)"'
    firmware_matches = re.finditer(firmware_pattern, content)
    
    for match in firmware_matches:
        filename = match.group(1)  # "esp32_s3_trip5_es3c28p.bin"
        board_env = match.group(2)  # "board_esp32_s3_n16r8"
        chip_family = match.group(3)  # "ESP32-S3"
        contributor = match.group(4)  # "Trip5" or "Kasperaitis"
        
        # Skip board_ entries (bare boards without full config)
        if filename.startswith('board_'):
            continue
        
        # Remove .bin extension to get fw_env
        fw_env = filename.replace('.bin', '')
        
        # Find corresponding FIRMWARE_NAME on the next line
        # Search for FIRMWARE_NAME within 500 chars after this FIRMWARE definition (handles long URLs)
        pos = match.end()
        next_section = content[pos:pos+500]
        name_pattern = r'#define\s+FIRMWARE_NAME\s+"([^"]+)"\s*//\s*"([^"]*?)"'
        name_match = re.search(name_pattern, next_section)
        
        if name_match:
            friendly_name = name_match.group(1)
            url = name_match.group(2)
            if url:  # Store URL if it exists
                url_map[fw_env] = url
        else:
            # Fallback to using the filename if no FIRMWARE_NAME found
            friendly_name = fw_env
        
        # Include contributor name in friendly_name for firmware.txt
        full_friendly_name = f"{contributor} {friendly_name}"
        
        firmwares.append((board_env, chip_family, fw_env, full_friendly_name))
    
    return firmwares, url_map

def generate_firmware_txt(firmwares, output_path):
    """
    Generate firmware.txt from firmware metadata.
    
    Format: board_env|chip_family|fw_env|friendly_name
    """
    with open(output_path, 'w', encoding='utf-8') as f:
        for board_env, chip_family, fw_env, friendly_name in firmwares:
            f.write(f"{board_env}|{chip_family}|{fw_env}|{friendly_name}\n")
    
    print(f"✅ Generated {output_path} with {len(firmwares)} firmware entries")

def get_version_from_options_h():
    """
    Extract version from src/core/options.h
    """
    options_h = Path(__file__).parent.parent.parent / "src" / "core" / "options.h"
    if options_h.exists():
        with open(options_h, 'r', encoding='utf-8') as f:
            for line in f:
                if '#define RADIOVERSION' in line:
                    match = re.search(r'"([^"]+)"', line)
                    if match:
                        return match.group(1)
    return ""

def generate_releases_md(firmwares, url_map, output_path):
    """
    Patch releases.md with firmware listings.
    Preserves existing content and only updates firmware lists under ### <Contributor> Firmware sections.
    
    Args:
        firmwares: List of tuples (board_env, chip_family, fw_env, friendly_name)
        url_map: Dict mapping fw_env to URL
        output_path: Path to releases.md file
    """
    # Group firmwares by contributor
    by_contributor = {}
    for board_env, chip_family, fw_env, friendly_name in firmwares:
        # Extract contributor from fw_env (e.g., "trip5" from "esp32_s3_trip5_...")
        parts = fw_env.split('_')
        if len(parts) >= 3:
            contributor = parts[2]  # Usually the third part
        else:
            contributor = "Other"
        
        if contributor not in by_contributor:
            by_contributor[contributor] = []
        by_contributor[contributor].append((board_env, chip_family, fw_env, friendly_name))
    
    # Read existing releases.md
    if output_path.exists():
        with open(output_path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
    else:
        lines = []
    
    # Process releases.md - patch firmware sections
    new_lines = []
    i = 0
    while i < len(lines):
        line = lines[i]
        
        # Check for ### <Contributor> Firmware pattern
        match = re.match(r'^###\s+(\w+)\s+Firmware\s*$', line)
        if match:
            contributor = match.group(1).lower()
            new_lines.append(line)  # Keep the header
            i += 1
            
            # Skip existing firmware entries (lines starting with "  - ")
            while i < len(lines) and lines[i].strip().startswith('- '):
                i += 1
            
            # Add new firmware entries if we have them for this contributor
            if contributor in by_contributor:
                for board_env, chip_family, fw_env, friendly_name in by_contributor[contributor]:
                    filename = f"{fw_env}.bin"
                    if fw_env in url_map:
                        # With URL - create link
                        entry_line = f"  - [`{filename}`]({url_map[fw_env]})\n"
                    else:
                        # Without URL - just the filename in code format
                        entry_line = f"  - `{filename}`\n"
                    new_lines.append(entry_line)
                print(f"✅ Updated {contributor} section with {len(by_contributor[contributor])} entries")
            else:
                print(f"⚠️  No firmware found for {contributor}")
            
            continue
        
        new_lines.append(line)
        i += 1
    
    # Write updated releases.md
    with open(output_path, 'w', encoding='utf-8') as f:
        f.writelines(new_lines)
    
    print(f"✅ Patched {output_path}")

def generate_esp_web_tools_manifests(firmwares, output_dir, version=""):
    """
    Generate ESP Web Tools manifest JSON files for each firmware.
    
    Args:
        firmwares: List of tuples (board_env, chip_family, fw_env, friendly_name)
        output_dir: Path to output directory for web_assets
        version: Version string (optional, will be read from options.h if not provided)
    """
    import json
    from datetime import datetime
    
    if not version:
        version = get_version_from_options_h()
    
    # Create manifests directory
    manifests_dir = output_dir / "manifests"
    manifests_dir.mkdir(parents=True, exist_ok=True)
    
    manifest_count = 0
    for board_env, chip_family, fw_env, friendly_name in firmwares:
        
        # Determine bootloader offset based on chip family
        bl_offset = 0 if chip_family in ["ESP32-S3", "ESP32-C3"] else 4096
        
        # Create manifest
        manifest = {
            "name": f"ehRadio - {friendly_name}",
            "version": version,
            "funding_url": "https://github.com/sponsors/trip5",
            "builds": [
                {
                    "chipFamily": chip_family,
                    "parts": [
                        {
                            "path": f"../firmware/{board_env}_bootloader.bin",
                            "offset": bl_offset
                        },
                        {
                            "path": f"../firmware/{board_env}_partitions.bin",
                            "offset": 32768
                        },
                        {
                            "path": f"../firmware/{fw_env}.bin",
                            "offset": 65536
                        }
                    ]
                }
            ]
        }
        
        # Write manifest file
        manifest_file = manifests_dir / f"{fw_env}-manifest.json"
        with open(manifest_file, 'w', encoding='utf-8', newline='\n') as f:
            json.dump(manifest, f, indent=2)
            f.write('\n')  # Ensure trailing newline
        
        manifest_count += 1
    
    print(f"✅ Generated {manifest_count} ESP Web Tools manifests in {manifests_dir}")
    return manifest_count

def generate_firmware_info_json(firmwares, output_path, version=""):
    """
    Generate firmware-info.json with summary of all firmware variants.
    
    Args:
        firmwares: List of tuples (board_env, chip_family, fw_env, friendly_name)
        output_path: Path to output firmware-info.json file
        version: Version string (optional, will be read from options.h if not provided)
    """
    import json
    
    if not version:
        version = get_version_from_options_h()
    
    variants = []
    for board_env, chip_family, fw_env, friendly_name in firmwares:
        
        variants.append({
            "name": friendly_name,
            "manifest": f"manifests/{fw_env}-manifest.json",
            "description": f"ehRadio - {fw_env}"
        })
    
    # Create firmware-info structure
    firmware_info = {
        "project": "ehRadio",
        "version": version,
        "variants": variants
    }
    
    # Write firmware-info.json
    output_path.parent.mkdir(parents=True, exist_ok=True)
    with open(output_path, 'w', encoding='utf-8', newline='\n') as f:
        json.dump(firmware_info, f, indent=2)
        f.write('\n')  # Ensure trailing newline
    
    print(f"✅ Generated {output_path} with {len(variants)} firmware variants")

def main():
    # Operate on files in the same folder as this script
    script_dir = Path(__file__).parent
    
    myoptions_path = script_dir / "myoptions.h"
    firmware_txt_path = script_dir / "firmware.txt"
    releases_md_path = script_dir / "releases.md"
    
    if not myoptions_path.exists():
        print(f"❌ Error: {myoptions_path} not found")
        print("   Make sure myoptions.h exists in the same folder as this script")
        return 1
    
    print(f"📖 Parsing {myoptions_path}...")
    firmwares, url_map = parse_myoptions_h(myoptions_path)
    
    if not firmwares:
        print("⚠️  Warning: No firmware definitions found in myoptions.h")
        print("   Expected format:")
        print('   #define FIRMWARE "name.bin" // "board_env", "chip_family", "contributor"')
        print('   #define FIRMWARE_NAME "Friendly Name"')
        return 1
    
    print(f"✅ Found {len(firmwares)} firmware definitions")
    
    # Generate firmware.txt
    generate_firmware_txt(firmwares, firmware_txt_path)
    
    # Patch releases.md
    generate_releases_md(firmwares, url_map, releases_md_path)
    
    # Generate ESP Web Tools manifests
    web_assets_dir = script_dir / "web_assets"
    generate_esp_web_tools_manifests(firmwares, web_assets_dir)
    
    # Generate firmware-info.json
    firmware_info_path = web_assets_dir / "firmware-info.json"
    generate_firmware_info_json(firmwares, firmware_info_path)
    
    print("\n📋 Summary:")
    for board_env, chip_family, fw_env, friendly_name in firmwares:
        print(f"  • {friendly_name:30} ({fw_env})")
    
    return 0

if __name__ == "__main__":
    exit(main())
