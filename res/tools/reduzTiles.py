"""
dedupe_tiles.py
===============
Pega tilemap.png e reduz para exatamente 256 tiles únicos 8x8,
salvando tilemap2.png (imagem remontada) e tileset256.png (atlas dos 256 tiles).
"""

import sys
import numpy as np
from PIL import Image
from collections import OrderedDict, Counter

INPUT      = r"C:\snesdev\snes-examples\games\FinalFantasy\res\gfx\novo\tilemap.png"
OUTPUT     = r"C:\snesdev\snes-examples\games\FinalFantasy\res\gfx\novo\tilemap2.png"
OUT_ATLAS  = r"C:\snesdev\snes-examples\games\FinalFantasy\res\gfx\novo\tileset256.png"

TILE_SIZE  = 8
ATLAS_COLS = 16  # 16 tiles por linha → atlas 128×128

# ─────────────────────────────────────────────
def slice_tiles(img_np):
    H, W, C = img_np.shape
    assert H % TILE_SIZE == 0 and W % TILE_SIZE == 0, \
        f"Imagem {W}x{H} não é múltiplo de {TILE_SIZE}"
    tiles = []
    for ty in range(H // TILE_SIZE):
        for tx in range(W // TILE_SIZE):
            t = img_np[ty*TILE_SIZE:(ty+1)*TILE_SIZE, tx*TILE_SIZE:(tx+1)*TILE_SIZE]
            tiles.append(t)
    return tiles

def dedupe_exact(tiles):
    key_to_idx = OrderedDict()
    unique_tiles = []
    remap = []
    for tile in tiles:
        key = tile.tobytes()
        if key not in key_to_idx:
            key_to_idx[key] = len(unique_tiles)
            unique_tiles.append(tile)
        remap.append(key_to_idx[key])
    return unique_tiles, remap

def quantize_to_256(unique_tiles, remap):
    n_unique = len(unique_tiles)
    print(f"  {n_unique} tiles únicos > 256 — selecionando os 256 mais frequentes...")

    # Escolhe os 256 tiles que mais aparecem no mapa
    counts = Counter(remap)
    top256_idxs = [idx for idx, _ in counts.most_common(256)]
    top256_set  = set(top256_idxs)

    top256_tiles = [unique_tiles[i] for i in top256_idxs]
    top256_flat  = np.array(top256_tiles, dtype=np.float32).reshape(256, -1)

    # Mapeia cada tile antigo → tile mais próximo no top256
    print(f"  Calculando similaridade para {n_unique - 256} tiles excedentes...")
    old_to_new = {}
    for old_idx in range(n_unique):
        if old_idx in top256_set:
            old_to_new[old_idx] = top256_idxs.index(old_idx)
        else:
            t_flat = unique_tiles[old_idx].astype(np.float32).reshape(1, -1)
            dists  = np.sum((top256_flat - t_flat) ** 2, axis=1)
            old_to_new[old_idx] = int(np.argmin(dists))

    new_remap = [old_to_new[r] for r in remap]
    return top256_tiles, new_remap

def build_atlas(unique_tiles, C):
    size = ATLAS_COLS * TILE_SIZE  # 128
    atlas = np.zeros((size, size, C), dtype=np.uint8)
    for i, tile in enumerate(unique_tiles[:256]):
        row = i // ATLAS_COLS
        col = i % ATLAS_COLS
        atlas[row*TILE_SIZE:(row+1)*TILE_SIZE, col*TILE_SIZE:(col+1)*TILE_SIZE] = tile
    return atlas

def remap_image(remap, unique_tiles, H, W, C):
    out = np.zeros((H, W, C), dtype=np.uint8)
    tiles_w = W // TILE_SIZE
    for flat_idx, tile_idx in enumerate(remap):
        ty = flat_idx // tiles_w
        tx = flat_idx % tiles_w
        out[ty*TILE_SIZE:(ty+1)*TILE_SIZE, tx*TILE_SIZE:(tx+1)*TILE_SIZE] = unique_tiles[tile_idx]
    return out

# ─────────────────────────────────────────────
print(f"[1/5] Abrindo {INPUT}...")
img    = Image.open(INPUT).convert("RGBA")
img_np = np.array(img)
H, W, C = img_np.shape
print(f"      {W}x{H}, {C} canais — {(W//TILE_SIZE)*(H//TILE_SIZE)} tiles no total")

print(f"[2/5] Fatiando em tiles {TILE_SIZE}x{TILE_SIZE}...")
tiles = slice_tiles(img_np)

print(f"[3/5] Deduplicando...")
unique_tiles, remap = dedupe_exact(tiles)
n_unique = len(unique_tiles)
print(f"      Tiles únicos encontrados: {n_unique}")

if n_unique > 256:
    print(f"[4/5] Quantizando para 256...")
    unique_tiles, remap = quantize_to_256(unique_tiles, remap)
else:
    print(f"[4/5] {n_unique} <= 256, preenchendo restante com tiles vazios...")
    empty = np.zeros((TILE_SIZE, TILE_SIZE, C), dtype=np.uint8)
    while len(unique_tiles) < 256:
        unique_tiles.append(empty)

print(f"[5/5] Salvando...")
Image.fromarray(build_atlas(unique_tiles, C)).save(OUT_ATLAS)
print(f"      Atlas:   {OUT_ATLAS}")

Image.fromarray(remap_image(remap, unique_tiles, H, W, C)).save(OUTPUT)
print(f"      Remap:   {OUTPUT}")

print(f"\nPronto! {min(n_unique, 256)}/256 tiles usados.", end="")
if n_unique > 256:
    print(f" ({n_unique - 256} tiles substituídos pelo mais parecido)", end="")
print()