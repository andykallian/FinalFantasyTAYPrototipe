import struct, sys

def read_bmp(path):
    with open(path, 'rb') as f:
        data = f.read()
    
    pixel_offset = struct.unpack_from('<I', data, 10)[0]
    w = struct.unpack_from('<I', data, 18)[0]
    h = struct.unpack_from('<I', data, 22)[0]
    bpp = struct.unpack_from('<H', data, 28)[0]
    
    print(f"Imagem: {w}x{h} pixels, {bpp}bpp")
    print(f"Tiles grid: {w//8}x{h//8} = {(w//8)*(h//8)} tiles total")
    
    # BMP é armazenado de baixo para cima
    row_size = ((w * bpp // 8) + 3) & ~3  # alinha a 4 bytes
    pixels = []
    for y in range(h):
        row_start = pixel_offset + (h - 1 - y) * row_size
        row = data[row_start:row_start + w]
        pixels.append(list(row))
    
    # Extrai cada tile 8x8 e verifica unicidade
    unique_tiles = set()
    tile_count = 0
    
    for ty in range(h // 8):
        for tx in range(w // 8):
            tile = []
            for py in range(8):
                for px in range(8):
                    tile.append(pixels[ty*8 + py][tx*8 + px])
            unique_tiles.add(tuple(tile))
            tile_count += 1
    
    print(f"\nTiles únicos encontrados: {len(unique_tiles)}")
    print(f"Limite do Mode 7: 256")
    
    if len(unique_tiles) <= 256:
        print("✓ OK! Dentro do limite do Mode 7.")
    else:
        excesso = len(unique_tiles) - 256
        print(f"✗ EXCESSO: {excesso} tiles acima do limite.")
        print(f"\nPara resolver, você precisa simplificar o mapa")
        print(f"para que tiles similares usem exatamente os mesmos pixels.")

if __name__ == '__main__':
    path = sys.argv[1] if len(sys.argv) > 1 else 'res/maps/worldmap.bmp'
    read_bmp(path)