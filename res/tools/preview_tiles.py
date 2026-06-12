from PIL import Image
import struct
import os
import sys

MAPS_DIR = sys.argv[1] if len(sys.argv) > 1 else "C:\\snesdev\\snes-examples\\games\\FinalFantasy\\res\\maps"
    
TILES = os.path.join(MAPS_DIR, "ow_tiles.bin")
PAL   = os.path.join(MAPS_DIR, "ow_palette.bin")

# -------------------------------------------------------------------
# Paleta
# -------------------------------------------------------------------

with open(PAL, "rb") as f:
    pal_data = f.read()

palette = []

for i in range(len(pal_data) // 2):
    color = struct.unpack_from("<H", pal_data, i * 2)[0]

    r = (color & 0x1F) << 3
    g = ((color >> 5) & 0x1F) << 3
    b = ((color >> 10) & 0x1F) << 3

    palette.append((r, g, b))

# -------------------------------------------------------------------
# Tiles
# -------------------------------------------------------------------

with open(TILES, "rb") as f:
    tiles_data = f.read()

tile_count = len(tiles_data) // 64

print(f"{tile_count} tiles encontrados")

# -------------------------------------------------------------------
# Layout do tileset preview
# -------------------------------------------------------------------

TILES_PER_ROW = 16

rows = (tile_count + TILES_PER_ROW - 1) // TILES_PER_ROW

img = Image.new(
    "RGB",
    (TILES_PER_ROW * 8, rows * 8)
)

pixels = img.load()

# -------------------------------------------------------------------
# Desenha tiles
# -------------------------------------------------------------------

for tile_id in range(tile_count):

    tile = tiles_data[tile_id * 64:(tile_id + 1) * 64]

    tx = tile_id % TILES_PER_ROW
    ty = tile_id // TILES_PER_ROW

    base_x = tx * 8
    base_y = ty * 8

    for y in range(8):
        for x in range(8):

            pixel_idx = tile[y * 8 + x]

            color = (
                palette[pixel_idx]
                if pixel_idx < len(palette)
                else (255, 0, 255)
            )

            pixels[base_x + x, base_y + y] = color

# -------------------------------------------------------------------
# Salva
# -------------------------------------------------------------------

out = os.path.join(MAPS_DIR, "ow_tiles_preview.png")

img.save(out)

print(f"Salvo: {out}")