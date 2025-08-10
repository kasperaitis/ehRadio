# This script may be used by platformio to automatically replace a default Adafruit GFX Library font
# Add this to a platformio.ini env section:
# extra_scripts = pre:replace_font.py

Import("env")
import shutil
import os

env_name = env["PIOENV"]

src_font = os.path.join("glcdfont_fix", "glcdfont.c")
dst_font = os.path.join(".pio", "libdeps", env_name, "Adafruit GFX Library", "glcdfont.c")

if os.path.exists(src_font) and os.path.exists(dst_font):
    shutil.copyfile(src_font, dst_font)
    print(f"Custom glcdfont.c copied to Adafruit GFX Library for {env_name}.")
else:
    print(f"Font file or destination not found for {env_name}. Skipping replacement.")