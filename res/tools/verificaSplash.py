from PIL import Image
import struct
import os

BASE = r"C:\snesdev\snes-examples\games\FinalFantasy\res\gfx"

TILES_BIN   = os.path.join(BASE, "dream_tiles.bin")
PALETTE_BIN = os.path.join(BASE, "dream_palette.bin")
OUTPUT_PNG  = os.path.join(BASE, "teste.png")

# --------------------------------------------------
# Lê paleta BGR555
# --------------------------------------------------

palette = []

with open(PALETTE_BIN, "rb") as f:
    pal_data = f.read()

for i in range(16):
    c = struct.unpack_from("<H", pal_data, i * 2)[0]

    r = (c & 0x1F) << 3
    g = ((c >> 5) & 0x1F) << 3
    b = ((c >> 10) & 0x1F) << 3

    palette.append((r, g, b))

print("Paleta carregada:", len(palette), "cores")

# --------------------------------------------------
# Lê tiles 4bpp
# --------------------------------------------------

with open(TILES_BIN, "rb") as f:
    tile_data = f.read()

tile_count = len(tile_data) // 32

print("Tiles encontrados:", tile_count)

# --------------------------------------------------
# Layout visual:
# 16 colunas por linha
# --------------------------------------------------

tiles_per_row = 16
rows = (tile_count + tiles_per_row - 1) // tiles_per_row

img_w = tiles_per_row * 8
img_h = rows * 8

img = Image.new("RGB", (img_w, img_h))

# --------------------------------------------------
# Decodifica SNES 4bpp
# --------------------------------------------------

for tile in range(tile_count):

    base = tile * 32

    tile_x = (tile % tiles_per_row) * 8
    tile_y = (tile // tiles_per_row) * 8

    for y in range(8):

        p0 = tile_data[base + y * 2 + 0]
        p1 = tile_data[base + y * 2 + 1]

        p2 = tile_data[base + 16 + y * 2 + 0]
        p3 = tile_data[base + 16 + y * 2 + 1]

        for x in range(8):

            bit = 7 - x

            color = (
                ((p0 >> bit) & 1)
                | (((p1 >> bit) & 1) << 1)
                | (((p2 >> bit) & 1) << 2)
                | (((p3 >> bit) & 1) << 3)
            )

            img.putpixel(
                (tile_x + x, tile_y + y),
                palette[color]
            )

img.save(OUTPUT_PNG)

print()
print("PNG gerado:")
print(OUTPUT_PNG)
print()
print("Tamanho:", img_w, "x", img_h)