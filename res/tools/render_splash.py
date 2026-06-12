from PIL import Image
import numpy as np
import struct
import os

INPUT_PATH  = r"C:\snesdev\snes-examples\games\FinalFantasy\res\gfx\dreams.png"
OUTPUT_DIR  = r"C:\snesdev\snes-examples\games\FinalFantasy\res\gfx"

TILES_BIN   = os.path.join(OUTPUT_DIR, "dream_tiles.bin")
MAP_BIN     = os.path.join(OUTPUT_DIR, "dream_map.bin")
PALETTE_BIN = os.path.join(OUTPUT_DIR, "dream_palette.bin")

# --------------------------------------------------
# Carrega imagem
# --------------------------------------------------

img = Image.open(INPUT_PATH).convert("RGB")

w, h = img.size
arr = np.array(img)

# --------------------------------------------------
# Detecta fundo preto
# --------------------------------------------------

BG_THRESH = 15

is_bg = (
    (arr[:,:,0] <= BG_THRESH) &
    (arr[:,:,1] <= BG_THRESH) &
    (arr[:,:,2] <= BG_THRESH)
)

# --------------------------------------------------
# Quantiza para 15 cores do logo
# --------------------------------------------------

logo_img = Image.fromarray(arr)

img_q = logo_img.quantize(
    colors=15,
    method=Image.Quantize.FASTOCTREE,
    dither=0
)

pal = img_q.getpalette()[:15 * 3]

# --------------------------------------------------
# Monta paleta SNES
# Cor 0 = preto
# Cores 1..15 = logo
# --------------------------------------------------

final_pal_rgb = [(0,0,0)]

for i in range(15):
    r = pal[i*3 + 0]
    g = pal[i*3 + 1]
    b = pal[i*3 + 2]

    final_pal_rgb.append((r,g,b))

def rgb_to_bgr555(r,g,b):
    return ((b >> 3) << 10) | ((g >> 3) << 5) | (r >> 3)

pal_bytes = bytearray()

for r,g,b in final_pal_rgb:
    pal_bytes += struct.pack(
        "<H",
        rgb_to_bgr555(r,g,b)
    )

with open(PALETTE_BIN, "wb") as f:
    f.write(pal_bytes)

print("[OK]", PALETTE_BIN)

# --------------------------------------------------
# Remapeia pixels
# --------------------------------------------------

q_pixels = np.array(img_q)

final_pixels = q_pixels + 1

final_pixels[is_bg] = 0

# --------------------------------------------------
# Debug PNG
# --------------------------------------------------

debug_img = Image.new("P", (w,h))

debug_img.putpalette(
    [c for rgb in final_pal_rgb for c in rgb] +
    [0]*(768 - len(final_pal_rgb)*3)
)

debug_img.putdata(final_pixels.flatten())

debug_img.save(
    os.path.join(OUTPUT_DIR, "debug_quantizado.png")
)

print("[OK] debug_quantizado.png")

# --------------------------------------------------
# Conversão 4bpp SNES
# --------------------------------------------------

def tile_to_4bpp(tile):

    out = bytearray(32)

    for row in range(8):

        bp0 = 0
        bp1 = 0
        bp2 = 0
        bp3 = 0

        for col in range(8):

            c = int(tile[row,col]) & 0x0F

            bit = 7 - col

            if c & 1:
                bp0 |= (1 << bit)

            if c & 2:
                bp1 |= (1 << bit)

            if c & 4:
                bp2 |= (1 << bit)

            if c & 8:
                bp3 |= (1 << bit)

        out[row*2+0] = bp0
        out[row*2+1] = bp1

        out[16+row*2+0] = bp2
        out[16+row*2+1] = bp3

    return out

# --------------------------------------------------
# Gera tiles
# --------------------------------------------------

tiles_x = w // 8
tiles_y = h // 8

tiles_bin = bytearray()
map_bin   = bytearray()

tile_index = 1

for ty in range(tiles_y):

    for tx in range(tiles_x):

        patch = final_pixels[
            ty*8:(ty+1)*8,
            tx*8:(tx+1)*8
        ]

        tiles_bin += tile_to_4bpp(patch)

        map_bin += struct.pack(
            "<H",
            tile_index
        )

        tile_index += 1

# --------------------------------------------------
# Salva
# --------------------------------------------------

with open(TILES_BIN, "wb") as f:
    f.write(tiles_bin)

with open(MAP_BIN, "wb") as f:
    f.write(map_bin)

print()
print("Tiles:", len(tiles_bin)//32)
print("Bytes:", len(tiles_bin))
print()
print("[OK]", TILES_BIN)
print("[OK]", MAP_BIN)