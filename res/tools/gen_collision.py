"""
gen_collision.py
Gera collision_map.h a partir do worldMap.tmj
Uso: python gen_collision.py

Tiles com attribute "FF00" no Tiled serao marcados como solidos (1).
Todos os outros serao livres (0).
"""

import json
import os

TMJ_PATH   = "res/maps/worldMap.tmj"
OUTPUT_H   = "src/collision_map.h"
OUTPUT_C   = "src/collision_map.c"

SOLID_ATTR = "FF00"   # valor que voce setar no Tiled para tiles solidos

def main():
    with open(TMJ_PATH, "r") as f:
        tmj = json.load(f)

    width  = tmj["width"]   # 128
    height = tmj["height"]  # 128

    # --- monta set de tile IDs solidos ---
    solid_ids = set()
    for ts in tmj.get("tilesets", []):
        firstgid = ts["firstgid"]
        for tile in ts.get("tiles", []):
            for prop in tile.get("properties", []):
                if prop["name"] == "attribute" and prop["value"].upper() == SOLID_ATTR:
                    solid_ids.add(firstgid + tile["id"])

    print(f"Tiles solidos encontrados (GIDs): {sorted(solid_ids)}")

    # --- pega layer BG1 ---
    layer_data = None
    for layer in tmj["layers"]:
        if layer["type"] == "tilelayer":
            layer_data = layer["data"]
            break

    if layer_data is None:
        print("ERRO: nenhuma tilelayer encontrada!")
        return

    # --- gera array de colisao ---
    cmap = []
    for tile_gid in layer_data:
        cmap.append(1 if tile_gid in solid_ids else 0)

    # --- escreve collision_map.h ---
    os.makedirs("src", exist_ok=True)
    with open(OUTPUT_H, "w") as f:
        f.write("#ifndef COLLISION_MAP_H\n")
        f.write("#define COLLISION_MAP_H\n\n")
        f.write("#include <snes.h>\n\n")
        f.write(f"#define CMAP_WIDTH  {width}\n")
        f.write(f"#define CMAP_HEIGHT {height}\n")
        f.write(f"#define CMAP_TILE_SIZE 8\n\n")
        f.write("extern const u8 collision_map[CMAP_HEIGHT * CMAP_WIDTH];\n\n")
        f.write("#endif // COLLISION_MAP_H\n")

    # --- escreve collision_map.c ---
    with open(OUTPUT_C, "w") as f:
        f.write('#include "collision_map.h"\n\n')
        f.write("const u8 collision_map[CMAP_HEIGHT * CMAP_WIDTH] = {\n")
        for row in range(height):
            row_data = cmap[row * width : row * width + width]
            f.write("    " + ", ".join(str(v) for v in row_data) + ",\n")
        f.write("};\n")

    print(f"Gerado: {OUTPUT_H}")
    print(f"Gerado: {OUTPUT_C}")
    solid_count = sum(cmap)
    print(f"Tiles solidos no mapa: {solid_count} / {width*height}")

if __name__ == "__main__":
    main()


