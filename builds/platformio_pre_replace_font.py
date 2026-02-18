# This script may be used by platformio to automatically replace a default Adafruit GFX Library font
# Add this to a platformio.ini env section:
# extra_scripts = pre:replace_font.py

Import("env")
import shutil
import os

# Skip font replacement when building filesystem
build_targets = [str(t) for t in BUILD_TARGETS]
if "buildfs" in build_targets or "uploadfs" in build_targets:
    Return()

env_name = env["PIOENV"]

src_font = os.path.join("builds", "glcdfont_EN.c")
dst_font = os.path.join(".pio", "libdeps", env_name, "Adafruit GFX Library", "glcdfont.c")


print("\n" + "="*70)
print("FONT: Replacing font")

if os.path.exists(src_font) and os.path.exists(dst_font):
    shutil.copyfile(src_font, dst_font)
    print(f"Custom glcdfont_EN.c copied to Adafruit GFX Library for {env_name}.")
else:
    print(f"Font file or destination not found for {env_name}. Skipping replacement.")

print("="*70 + "\n")