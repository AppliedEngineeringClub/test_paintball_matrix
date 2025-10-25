#!/usr/bin/env python3
"""
get_dimensions.py

Loads the image at hard-coded path 'image/image.png',
then writes its width and height in pixels to the file
'pythonoutput.txt' (so the C++ code can read from it).
"""

from PIL import Image  # Requires Pillow library
import sys

image_path = " ~/image/image.png"  # hard-coded path of input image

try:
    img = Image.open(image_path)
    width, height = img.size  # width = number of columns, height = number of rows
except Exception as e:
    # If error (file not found, wrong format), write error to stderr and exit
    print(f"Error opening image '{image_path}': {e}", file=sys.stderr)
    sys.exit(1)

# Write the dimensions to the file
with open("pythonoutput.txt", "w") as f:
  f.write(f"{width} {height}")
