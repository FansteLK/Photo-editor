#!/usr/bin/env python3
"""Generate a colourful 32-bit BGRA BMP test image (the format the engine reads; no dependencies).

    python3 scripts/make_sample.py samples/sample.bmp [width] [height]
"""

import math
import struct
import sys


def pixel(x, y, w, h):
    # Diagonal hue gradient with a few circles and stripes, so every operation has something to change.
    t = (x + y) / (w + h)
    r = int(255 * (0.5 + 0.5 * math.sin(2 * math.pi * t)))
    g = int(255 * (0.5 + 0.5 * math.sin(2 * math.pi * t + 2.1)))
    b = int(255 * (0.5 + 0.5 * math.sin(2 * math.pi * t + 4.2)))
    for cx, cy, rad, col in ((0.3, 0.35, 0.18, (250, 250, 250)), (0.7, 0.6, 0.22, (20, 20, 30))):
        if (x / w - cx) ** 2 + (y / h - cy) ** 2 < rad**2:
            r, g, b = col
    if (y // 12) % 2 == 0 and x > w * 0.82:
        r, g, b = 255 - r, 255 - g, 255 - b
    return r, g, b


def main():
    path = sys.argv[1]
    w = int(sys.argv[2]) if len(sys.argv) > 2 else 320
    h = int(sys.argv[3]) if len(sys.argv) > 3 else 200
    size = 54 + w * 4 * h
    with open(path, "wb") as f:
        f.write(b"BM" + struct.pack("<IHHI", size, 0, 0, 54))
        f.write(struct.pack("<IiiHHIIiiII", 40, w, h, 1, 32, 0, size - 54, 2835, 2835, 0, 0))
        for y in range(h - 1, -1, -1):  # BMP rows are stored bottom-up
            for x in range(w):
                r, g, b = pixel(x, y, w, h)
                f.write(bytes((b, g, r, 255)))


if __name__ == "__main__":
    main()
