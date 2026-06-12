BASE       = r"C:\snesdev\snes-examples\games\FinalFantasy\res\maps"
MAP_W      = 512
MAP_H      = 512
CHUNK_SIZE = 128

import os

with open(os.path.join(BASE, "ow_map.bin"), "rb") as f:
    data = f.read()

map_grid = []
for y in range(MAP_H):
    row = []
    for x in range(MAP_W):
        row.append(data[y * MAP_W + x])
    map_grid.append(row)

for chunk_row in range(4):
    for chunk_col in range(4):

        # Row-major: para buildRowFast
        chunk_rm = bytearray()
        for y in range(CHUNK_SIZE):
            for x in range(CHUNK_SIZE):
                tile_x = chunk_col * CHUNK_SIZE + x
                tile_y = chunk_row * CHUNK_SIZE + y
                chunk_rm.append(map_grid[tile_y][tile_x])
        with open(os.path.join(BASE, f"ow_chunk_{chunk_row}_{chunk_col}.bin"), "wb") as f:
            f.write(chunk_rm)

        # Column-major: para buildColumnFast
        chunk_cm = bytearray()
        for x in range(CHUNK_SIZE):
            for y in range(CHUNK_SIZE):
                tile_x = chunk_col * CHUNK_SIZE + x
                tile_y = chunk_row * CHUNK_SIZE + y
                chunk_cm.append(map_grid[tile_y][tile_x])
        with open(os.path.join(BASE, f"ow_chunk_t_{chunk_row}_{chunk_col}.bin"), "wb") as f:
            f.write(chunk_cm)

        print(f"chunk_{chunk_row}_{chunk_col} + chunk_t_{chunk_row}_{chunk_col} gerados")

print("Pronto!")