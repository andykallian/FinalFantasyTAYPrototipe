# gen_chunks_col.py
# Gera chunks reorganizados por coluna para DMA eficiente no SNES Mode 7
# Input:  ../maps/ow_map.bin  (512x512 tiles, linha por linha)
# Output: ../maps/ow_chunk_R_C_col.bin  (128x128 tiles, coluna por coluna)

import os

MAP_W      = 512
MAP_H      = 512
CHUNK_SIZE = 128

IN_MAP  = "../maps/ow_map.bin"
OUT_DIR = "../maps"

print("Carregando ow_map.bin...")
with open(IN_MAP, "rb") as f:
    data = f.read()

assert len(data) == MAP_W * MAP_H, f"Tamanho inesperado: {len(data)} bytes"

# monta grid 2D
map_grid = []
for y in range(MAP_H):
    map_grid.append(list(data[y * MAP_W : y * MAP_W + MAP_W]))

for chunk_row in range(4):
    for chunk_col in range(4):

        # origem do chunk no mapa global
        base_x = chunk_col * CHUNK_SIZE
        base_y = chunk_row * CHUNK_SIZE

        # organiza por coluna: col0_linha0, col0_linha1 ... col0_linha127,
        #                       col1_linha0, col1_linha1 ... col127_linha127
        chunk = bytearray()
        for col in range(CHUNK_SIZE):
            for row in range(CHUNK_SIZE):
                chunk.append(map_grid[base_y + row][base_x + col])

        filename = os.path.join(OUT_DIR, f"ow_chunk_{chunk_row}_{chunk_col}_col.bin")
        with open(filename, "wb") as f:
            f.write(chunk)

        print(f"  {os.path.basename(filename)}  ({len(chunk)} bytes)")

print("Pronto!")