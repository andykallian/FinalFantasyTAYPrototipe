from PIL import Image
import struct
import glob
import sys
import os

MAPS_DIR = sys.argv[1] if len(sys.argv) > 1 else "C:\\snesdev\\snes-examples\\games\\FinalFantasy\\res\\maps"
TILES    = os.path.join(MAPS_DIR, "ow_tiles.bin")
PAL      = os.path.join(MAPS_DIR, "ow_palette.bin")

# --- paleta ------------------------------------------------------------------
with open(PAL, "rb") as f:
    pal_data = f.read()

palette = []
for i in range(len(pal_data) // 2):
    color = struct.unpack_from("<H", pal_data, i * 2)[0]
    r = (color & 0x1F) << 3
    g = ((color >> 5)  & 0x1F) << 3
    b = ((color >> 10) & 0x1F) << 3
    palette.append((r, g, b))

# --- tiles -------------------------------------------------------------------
with open(TILES, "rb") as f:
    tiles_data = f.read()

# --- chunks ------------------------------------------------------------------
chunks = sorted(glob.glob(os.path.join(MAPS_DIR, "ow_chunk_*.bin")))

if not chunks:
    print(f"Nenhum chunk encontrado em {MAPS_DIR}")
    sys.exit(1)

for chunk_path in chunks:
    with open(chunk_path, "rb") as f:
        chunk_data = f.read()

    img    = Image.new("RGB", (1024, 1024))
    pixels = img.load()

    for ty in range(128):
        for tx in range(128):
            tile_idx  = chunk_data[ty * 128 + tx]
            tile      = tiles_data[tile_idx * 64:(tile_idx + 1) * 64]
            for y in range(8):
                for x in range(8):
                    pixel_idx = tile[y * 8 + x]
                    color     = palette[pixel_idx] if pixel_idx < len(palette) else (0, 0, 0)
                    pixels[tx * 8 + x, ty * 8 + y] = color

    out = chunk_path.replace(".bin", "_preview.png")
    img.save(out)
    print(f"Salvo: {out}")

print(f"\n{len(chunks)} chunk(s) processado(s).")