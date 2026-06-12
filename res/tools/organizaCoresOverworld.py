"""
reduce_palette.py
-----------------
Le res\maps\tiled.png e gera res\maps\novomundo.png com exatamente 48 cores,
agrupadas por matiz (HSV), eliminando tons muito similares.
"""

import sys, os
import numpy as np
from PIL import Image

# Fix encoding no terminal Windows
sys.stdout.reconfigure(encoding='utf-8', errors='replace')

TARGET = 48

BASE   = r"C:\snesdev\snes-examples\games\FinalFantasy\res\maps"
INPUT  = os.path.join(BASE, "tiled.png")
OUTPUT = os.path.join(BASE, "novomundo.png")


def rgb_to_hsv_arr(rgb):
    r, g, b = rgb[:, 0] / 255.0, rgb[:, 1] / 255.0, rgb[:, 2] / 255.0
    mx = np.maximum(np.maximum(r, g), b)
    mn = np.minimum(np.minimum(r, g), b)
    df = mx - mn
    h = np.zeros(len(r))
    mask_r = (mx == r) & (df > 0)
    mask_g = (mx == g) & (df > 0)
    mask_b = (mx == b) & (df > 0)
    h[mask_r] = (60 * ((g[mask_r] - b[mask_r]) / df[mask_r])) % 360
    h[mask_g] = (60 * ((b[mask_g] - r[mask_g]) / df[mask_g]) + 120) % 360
    h[mask_b] = (60 * ((r[mask_b] - g[mask_b]) / df[mask_b]) + 240) % 360
    s = np.where(mx == 0, 0.0, df / mx)
    return np.stack([h, s, mx], axis=1)


def hue_sort_key(row):
    h, s, v = row
    if s < 0.12:
        return (10, 0, v)
    return (int(h / 30), -s, -v)


def weighted_kmeans(pixels, weights, k, n_init=3, max_iter=80):
    N = len(pixels)
    rng = np.random.default_rng(42)
    best_inertia = float('inf')
    best_centers = None

    for _ in range(n_init):
        idx = rng.choice(N, p=weights / weights.sum())
        centers = [pixels[idx]]
        for _ in range(k - 1):
            dists = np.min(
                np.stack([((pixels - c) ** 2).sum(1) for c in centers], axis=1),
                axis=1
            )
            prob = dists * weights
            prob /= prob.sum()
            centers.append(pixels[rng.choice(N, p=prob)])
        centers = np.array(centers, dtype=np.float32)

        for _ in range(max_iter):
            diff = pixels[:, None, :] - centers[None, :, :]
            labels = (diff ** 2).sum(2).argmin(1)
            new_centers = np.zeros_like(centers)
            for j in range(k):
                mask = labels == j
                if mask.any():
                    w = weights[mask]
                    new_centers[j] = (pixels[mask] * w[:, None]).sum(0) / w.sum()
                else:
                    new_centers[j] = centers[j]
            if np.allclose(centers, new_centers, atol=0.5):
                centers = new_centers
                break
            centers = new_centers

        diff = pixels[:, None, :] - centers[None, :, :]
        inertia = ((diff ** 2).sum(2).min(1) * weights).sum()
        if inertia < best_inertia:
            best_inertia = inertia
            best_centers = centers.copy()

    return best_centers


def main():
    print(f"[1/5] Carregando: {INPUT}")
    img = Image.open(INPUT).convert('RGB')
    print(f"      Tamanho: {img.size}")

    print("[2/5] Contando frequencias de cor...")
    pixels_raw = np.array(img, dtype=np.uint8).reshape(-1, 3)
    pv = pixels_raw.view(np.dtype((np.void, 3)))
    uniq_void, counts = np.unique(pv, return_counts=True)
    uniq = uniq_void.view(np.uint8).reshape(-1, 3)
    print(f"      Cores unicas: {len(uniq)}")

    if len(uniq) <= TARGET:
        print(f"      Imagem ja tem {len(uniq)} cores (<= {TARGET}), apenas ordenando paleta...")
        palette = uniq.copy()
    else:
        print(f"[3/5] K-Means ponderado -> {TARGET} clusters...")
        centers = weighted_kmeans(uniq.astype(np.float32), counts.astype(np.float32), TARGET)
        palette = np.clip(np.round(centers), 0, 255).astype(np.uint8)
        palette = np.unique(palette, axis=0)
        while len(palette) < TARGET:
            extra = palette[0].copy()
            extra[0] = min(extra[0] + 1, 255)
            palette = np.vstack([palette, extra[None]])
            palette = np.unique(palette, axis=0)

    print(f"[4/5] Ordenando paleta por matiz (HSV)...")
    hsv = rgb_to_hsv_arr(palette)
    order = sorted(range(len(palette)), key=lambda i: hue_sort_key(hsv[i]))
    palette = palette[order]

    print(f"      Paleta final ({len(palette)} cores):")
    for i, c in enumerate(palette):
        h, s, v = rgb_to_hsv_arr(c[None])[0]
        label = "acromatico" if s < 0.12 else f"H={h:.0f}graus"
        print(f"        [{i:02d}] RGB({c[0]:3d},{c[1]:3d},{c[2]:3d})  {label}")

    print("[5/5] Remapeando pixels e salvando...")
    CHUNK = 65536
    N = len(pixels_raw)
    labels = np.empty(N, dtype=np.uint8)
    pal32 = palette.astype(np.int32)
    for start in range(0, N, CHUNK):
        chunk = pixels_raw[start:start + CHUNK].astype(np.int32)
        diff = chunk[:, None, :] - pal32[None, :, :]
        labels[start:start + CHUNK] = (diff ** 2).sum(2).argmin(1).astype(np.uint8)

    H, W = img.size[1], img.size[0]
    out = Image.fromarray(labels.reshape(H, W), mode='P')
    flat_pal = palette.flatten().tolist() + [0] * (768 - len(palette) * 3)
    out.putpalette(flat_pal)
    out.save(OUTPUT, optimize=True)

    print(f"")
    print(f"OK! Salvo em: {OUTPUT}")
    print(f"   {len(palette)} cores ordenadas por matiz.")


if __name__ == "__main__":
    main()