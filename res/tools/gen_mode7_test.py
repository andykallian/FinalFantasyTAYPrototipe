# gen_mode7_test.py
import struct

TILE_SIZE = 8
NUM_TILES = 256
MAP_SIZE = 128

tiles = bytearray()
for t in range(NUM_TILES):
    for y in range(TILE_SIZE):
        for x in range(TILE_SIZE):
            tiles.append(t)

with open("../maps/tiles.bin", "wb") as f:
    f.write(tiles)

map_data = bytearray()
for y in range(MAP_SIZE):
    for x in range(MAP_SIZE):
        map_data.append((x + y) % 256)

with open("../maps/map.bin", "wb") as f:
    f.write(map_data)

print(f"tiles.bin gerado: {len(tiles)} bytes ({NUM_TILES} tiles de {TILE_SIZE}x{TILE_SIZE})")
print(f"map.bin gerado: {len(map_data)} bytes ({MAP_SIZE}x{MAP_SIZE})")
print(f"tile 0 primeiros pixels: {list(tiles[:8])}")
print(f"tile 1 primeiros pixels: {list(tiles[64:72])}")
print(f"mapa [0,0]={map_data[0]} [1,0]={map_data[1]} [0,1]={map_data[128]}")