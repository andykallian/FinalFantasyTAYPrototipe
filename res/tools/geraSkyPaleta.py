"""
make_sky2.py
============
Le sky.png, mantem os pixels (paleta 3, indices 48-63),
substitui paletas 0-2 pelos novos bytes e salva sky2.png + palette.bin
"""

from PIL import Image

BASE       = r"C:\snesdev\snes-examples\games\FinalFantasy\res\gfx\novo"
INPUT      = BASE + r"\sky.png"
OUTPUT     = BASE + r"\sky2.png"
OUTPUT_BIN = BASE + r"\palette.bin"

# Paletas 0-2 novas: 48 cores = 96 bytes
RAW_PAL012_HEX = (
    "00 00 F6 00 86 10 7F 16 D9 26 1B 2F 5D 37 54 26 "
    "9E 3B 7E 4B AE 2D 31 3A 8C 29 C6 14 B5 4A F7 52 "
    "10 3A EB 0A 2D 13 83 09 91 1F B2 3B 40 01 83 16 "
    "22 11 E4 11 25 1E C2 08 87 7A EA 7E EE 7E AD 6E "
    "72 7B 20 75 20 75 20 75 E2 7D E2 7D 24 7E 2A 7A "
    "8B 7E AC 7E 0B 62 99 7F 2A 25 5A 5F DE 73 FF 7F"
)

def bgr555_to_rgb(lo, hi):
    w = lo | (hi << 8)
    return ((w & 0x1F) << 3, ((w >> 5) & 0x1F) << 3, ((w >> 10) & 0x1F) << 3)

def rgb_to_bgr555(r, g, b):
    w = ((r >> 3) & 0x1F) | (((g >> 3) & 0x1F) << 5) | (((b >> 3) & 0x1F) << 10)
    return bytes([w & 0xFF, (w >> 8) & 0xFF])

# Parseia paletas 0-2
raw012 = bytes(int(x, 16) for x in RAW_PAL012_HEX.split())
assert len(raw012) == 96, f"Esperava 96 bytes, got {len(raw012)}"
pal012_rgb = [bgr555_to_rgb(raw012[i*2], raw012[i*2+1]) for i in range(48)]

# Le sky.png — extrai paleta 3 (indices 48-63) que sao as cores reais da imagem
img = Image.open(INPUT)
assert img.mode == "P", f"Esperava modo P, got {img.mode}"

orig_flat = img.getpalette() or []
orig_flat += [0] * (768 - len(orig_flat))

# Paleta 3: indices 48-63 da paleta original
pal3_rgb = [(orig_flat[i*3], orig_flat[i*3+1], orig_flat[i*3+2]) for i in range(48, 64)]

print("Paleta 3 extraida da sky.png original (indices 48-63):")
for i, c in enumerate(pal3_rgb):
    print(f"  [{48+i:3d}] #{c[0]:02X}{c[1]:02X}{c[2]:02X}")

# Monta paleta completa de 256 entradas
full_palette = [(0, 0, 0)] * 256
for i, c in enumerate(pal012_rgb):   # indices 0-47  = paletas 0-2 novas
    full_palette[i] = c
for i, c in enumerate(pal3_rgb):     # indices 48-63 = paleta 3 original mantida
    full_palette[48 + i] = c

flat = [ch for rgb in full_palette for ch in rgb]

# Pixels ficam iguais (ainda apontam para indices 48-63)
pixels = list(img.getdata())

# Salva sky2.png
out = Image.new("P", img.size)
out.putpalette(flat)
out.putdata(pixels)
out.save(OUTPUT)
print(f"\nsky2.png salvo: {OUTPUT}")

# Salva palette.bin: paletas 0-2 (96 bytes) + paleta 3 (32 bytes) = 128 bytes
bin_data = bytearray(raw012)
for c in pal3_rgb:
    bin_data += rgb_to_bgr555(*c)

assert len(bin_data) == 128
with open(OUTPUT_BIN, "wb") as f:
    f.write(bin_data)

print(f"palette.bin salvo: {OUTPUT_BIN}")
print(f"  bytes   0-95  = paletas 0-2 (48 cores novas)")
print(f"  bytes  96-127 = paleta  3   (16 cores da sky.png original)")