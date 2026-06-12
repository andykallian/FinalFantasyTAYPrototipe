from PIL import Image
import struct
import os
import time

BASE = r"C:\snesdev\snes-examples\games\FinalFantasy\res\maps"

IMG_PATH  = os.path.join(BASE, "overworld.png")
OUT_TILES = os.path.join(BASE, "ow_tiles.bin")
OUT_MAP   = os.path.join(BASE, "ow_map.bin")
OUT_PAL   = os.path.join(BASE, "ow_palette.bin")

TILE_SIZE = 8
MAP_W = 512
MAP_H = 512

print("=" * 50)
print("  SNES Mode 7 Overworld Converter")
print("=" * 50)

# =========================================
# CARREGAR IMAGEM
# =========================================
print(f"\n[1/5] Carregando imagem: {IMG_PATH}")
t = time.time()
img = Image.open(IMG_PATH).convert("RGB")
print(f"      Resolucao: {img.width}x{img.height} pixels")
print(f"      Tempo: {time.time()-t:.2f}s")
assert img.width == 4096 and img.height == 4096, "Imagem deve ser 4096x4096"

# =========================================
# PALETA
# =========================================
print(f"\n[2/5] Extraindo paleta...")
t = time.time()
color_set = set()
for y in range(img.height):
    for x in range(img.width):
        color_set.add(img.getpixel((x, y)))

print(f"      Cores originais encontradas: {len(color_set)}")

if len(color_set) > 255:
    print(f"      AVISO: mais de 255 cores, reduzindo com quantize...")
    img_p = img.quantize(colors=255, method=Image.Quantize.MEDIANCUT)
    img = img_p.convert("RGB")
    color_set = set()
    for y in range(img.height):
        for x in range(img.width):
            color_set.add(img.getpixel((x, y)))
    print(f"      Cores apos quantize: {len(color_set)}")

colors = list(color_set)
def hue_sort_key(rgb):
    r, g, b = rgb[0]/255.0, rgb[1]/255.0, rgb[2]/255.0
    mx = max(r, g, b); mn = min(r, g, b); df = mx - mn
    if mx == mn:   h = 0.0
    elif mx == r:  h = (60 * ((g - b) / df)) % 360
    elif mx == g:  h = (60 * ((b - r) / df) + 120) % 360
    else:          h = (60 * ((r - g) / df) + 240) % 360
    s = 0.0 if mx == 0 else df / mx
    if s < 0.12:   return (10, 0, mx)
    return (int(h / 30), -s, -mx)

palette = [(0, 0, 0)] + sorted([c for c in colors if c != (0, 0, 0)], key=hue_sort_key)
palette = palette[:256]
color_to_idx = {c: i for i, c in enumerate(palette)}
print(f"      Paleta final: {len(palette)} cores")
print(f"      Cor 0 (backdrop): {palette[0]}")
print(f"      Cor 1: {palette[1]}")
print(f"      Cor 255: {palette[-1]}")
print(f"      Tempo: {time.time()-t:.2f}s")

# =========================================
# TILES
# =========================================
print(f"\n[3/5] Extraindo tiles ({MAP_W}x{MAP_H} = {MAP_W*MAP_H} total)...")
t = time.time()
tile_map = {}
tiles_list = []
map_data = []
overflow_count = 0

for ty in range(MAP_H):
    if ty % 64 == 0:
        print(f"      Processando linha {ty}/{MAP_H}...")
    for tx in range(MAP_W):
        px = tx * TILE_SIZE
        py = ty * TILE_SIZE
        tile_pixels = []
        for y in range(TILE_SIZE):
            for x in range(TILE_SIZE):
                rgb = img.getpixel((px + x, py + y))
                idx = color_to_idx.get(rgb, 0)
                tile_pixels.append(idx)
        tile_bytes = bytes(tile_pixels)
        if tile_bytes not in tile_map:
            tile_map[tile_bytes] = len(tiles_list)
            tiles_list.append(tile_bytes)
        tidx = tile_map[tile_bytes]
        if tidx > 255:
            overflow_count += 1
        map_data.append(tidx)

print(f"      Tiles unicos encontrados: {len(tiles_list)}")
print(f"      Tiles que cabem na VRAM (<=256): {min(len(tiles_list), 256)}")
if overflow_count > 0:
    print(f"      AVISO: {overflow_count} referencias de mapa apontam para tiles >255 (serao truncadas)")
else:
    print(f"      OK: todos os tiles cabem em 256 indices")
print(f"      Tempo: {time.time()-t:.2f}s")

# =========================================
# SALVAR TILES
# =========================================
print(f"\n[4/5] Salvando arquivos em {BASE}...")
t = time.time()

tiles_bin = bytearray()
for tile in tiles_list[:256]:
    tiles_bin += tile
while len(tiles_bin) < 256 * 64:
    tiles_bin += bytes(64)

with open(OUT_TILES, "wb") as f:
    f.write(tiles_bin)
print(f"      ow_tiles.bin: {len(tiles_bin)} bytes ({len(tiles_bin)//64} tiles)")

with open(OUT_MAP, "wb") as f:
    for idx in map_data:
        f.write(bytes([idx % 256]))
print(f"      ow_map.bin: {len(map_data)} bytes ({MAP_W}x{MAP_H} tiles)")

pal_bin = bytearray()
for r, g, b in palette:
    r5 = r >> 3
    g5 = g >> 3
    b5 = b >> 3
    color = (b5 << 10) | (g5 << 5) | r5
    pal_bin += struct.pack("<H", color)

with open(OUT_PAL, "wb") as f:
    f.write(pal_bin)
print(f"      ow_palette.bin: {len(pal_bin)} bytes ({len(pal_bin)//2} cores)")
print(f"      Tempo: {time.time()-t:.2f}s")

# =========================================
# RESUMO
# =========================================
print(f"\n[5/5] Resumo final:")
print(f"      Mapa total:     {MAP_W*TILE_SIZE}x{MAP_H*TILE_SIZE} pixels")
print(f"      Tiles unicos:   {len(tiles_list)}")
print(f"      Cores na paleta:{len(palette)}")
print(f"      Chunks 128x128: {(MAP_W//128)*(MAP_H//128)} chunks ({MAP_W//128}x{MAP_H//128} grid)")
print(f"      VRAM por chunk: 16384 bytes mapa + 16384 bytes tiles = 32KB")
if len(tiles_list) > 256:
    print(f"\n      !! ATENCAO: {len(tiles_list)} tiles unicos encontrados.")
    print(f"         O SNES Mode 7 suporta apenas 256.")
    print(f"         Sera necessario streaming de tileset por chunk.")
else:
    print(f"\n      Tileset cabe inteiro na VRAM.")
print("\n" + "=" * 50)
print("  Conversao concluida!")
print("=" * 50)