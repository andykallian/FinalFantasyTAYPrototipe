# palette.py
palette = bytearray()

palette += (0).to_bytes(2, 'little')

for i in range(1, 256):
    r = (i * 3) & 0x1F
    g = (i * 7) & 0x1F
    b = (i * 11) & 0x1F
    color = (b << 10) | (g << 5) | r
    palette += color.to_bytes(2, 'little')

with open("../maps/palette.bin", "wb") as f:
    f.write(palette)

print(f"palette.bin gerado: {len(palette)} bytes")
print(f"cor 0: {palette[0]:02X} {palette[1]:02X} (deve ser 00 00)")
print(f"cor 1: {palette[2]:02X} {palette[3]:02X}")
print(f"cor 255: {palette[510]:02X} {palette[511]:02X}")