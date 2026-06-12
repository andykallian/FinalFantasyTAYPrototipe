import os
import struct
import numpy as np
from PIL import Image

MAP_W     = 512
MAP_H     = 512
TILE_SIZE = 8
BASE      = r"C:\snesdev\snes-examples\games\FinalFantasy\res\maps\novo"

path_in   = os.path.join(BASE, "ow_map.bin")
path_out  = os.path.join(BASE, "ow_map2.bin")
path_pal  = os.path.join(BASE, "ow_palette.bin")
path_tile = os.path.join(BASE, "ow_tiles.bin")
path_png  = os.path.join(BASE, "ow_map2.png")

# ─── 1. Corrige 02 02 → 02 03 ────────────────────────────────────────────────
print("[1/4] Corrigindo ow_map.bin...")
with open(path_in, "rb") as f:
    data = bytearray(f.read())

assert len(data) == MAP_W * MAP_H, f"Tamanho inesperado: {len(data)} bytes"

fixes = 0
for y in range(MAP_H):
    row_start = y * MAP_W
    x = 0
    while x < MAP_W - 1:
        i = row_start + x
        if data[i] == 0x02 and data[i + 1] == 0x02:
            data[i + 1] = 0x03
            fixes += 1
            x += 2
        else:
            x += 1

with open(path_out, "wb") as f:
    f.write(data)
print(f"      {fixes} ocorrencias corrigidas")

# ─── 2. Paleta BGR555 → RGB numpy (256, 3) ───────────────────────────────────
print("[2/4] Lendo paleta...")
pal_raw = np.frombuffer(open(path_pal, "rb").read(), dtype=np.uint16)
r = ((pal_raw & 0x001F) << 3).astype(np.uint8)
g = (((pal_raw >> 5) & 0x001F) << 3).astype(np.uint8)
b = (((pal_raw >> 10) & 0x001F) << 3).astype(np.uint8)
palette = np.stack([r, g, b], axis=1)  # (N, 3)
if len(palette) < 256:
    palette = np.vstack([palette, np.zeros((256 - len(palette), 3), dtype=np.uint8)])
print(f"      {len(palette)} cores")

# ─── 3. Tileset → (256, 8, 8, 3) ─────────────────────────────────────────────
print("[3/4] Lendo tileset...")
tiles_raw = np.frombuffer(open(path_tile, "rb").read(), dtype=np.uint8)
# cada tile: 64 bytes de índices de paleta
tile_indices = tiles_raw[:256 * 64].reshape(256, 64)       # (256, 64)
tiles_rgb = palette[tile_indices].reshape(256, 8, 8, 3)    # (256, 8, 8, 3)
print(f"      256 tiles prontos")

# ─── 4. Monta imagem 4096×4096 com numpy ─────────────────────────────────────
print("[4/4] Gerando PNG 4096x4096...")
map_array = np.frombuffer(bytes(data), dtype=np.uint8).reshape(MAP_H, MAP_W)  # (512, 512)

# Monta via block assembly:
# tiles_rgb[map_array] → (512, 512, 8, 8, 3)
# transpõe para (512, 8, 512, 8, 3) e reshape para (4096, 4096, 3)
img_np = tiles_rgb[map_array]                          # (512, 512, 8, 8, 3)
img_np = img_np.transpose(0, 2, 1, 3, 4)              # (512, 8, 512, 8, 3)
img_np = img_np.reshape(MAP_H * TILE_SIZE, MAP_W * TILE_SIZE, 3)  # (4096, 4096, 3)

Image.fromarray(img_np, "RGB").save(path_png)
print(f"\nPronto!")
print(f"  Fixes: {fixes} tiles corrigidos")
print(f"  Bin:   {path_out}")
print(f"  PNG:   {path_png}")