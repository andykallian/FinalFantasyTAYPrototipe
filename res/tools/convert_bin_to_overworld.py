import os
from PIL import Image

# ==============================================================================
# CONFIGURAÇÕES DE CAMINHOS E DIMENSÕES
# ==============================================================================
PASTA_ORIGEM = r"C:\snesdev\snes-examples\games\FinalFantasy\res\maps"
PASTA_DESTINO = r"C:\snesdev\snes-examples\games\FinalFantasy\res\maps\A"
NOME_SAIDA = "mapa_completo.png"

# Dimensões baseadas no seu motor Mode 7
MAP_WIDTH_TILES = 512
MAP_HEIGHT_TILES = 512
TILE_SIZE = 8  # 8x8 pixels por tile

# Garante que a pasta 'A' exista
if not os.path.exists(PASTA_DESTINO):
    os.makedirs(PASTA_DESTINO)

# Definição dos caminhos dos arquivos
path_map = os.path.join(PASTA_ORIGEM, "ow_map.bin")
path_palette = os.path.join(PASTA_ORIGEM, "ow_palette.bin")
path_tiles = os.path.join(PASTA_ORIGEM, "ow_tiles.bin")
path_output = os.path.join(PASTA_DESTINO, NOME_SAIDA)

# ==============================================================================
# 1. LEITURA E CONVERSÃO DA PALETA (SNES BGR555 -> RGB888)
# ==============================================================================
print("Carregando paleta...")
with open(path_palette, "rb") as f:
    pal_data = f.read()

palette_rgb = []
# Uma paleta Mode 7 tem até 256 cores. Cada cor = 2 bytes.
num_colors = min(256, len(pal_data) // 2)

for i in range(num_colors):
    # Pega os 2 bytes da cor (Little Endian)
    b1 = pal_data[i * 2]
    b2 = pal_data[i * 2 + 1]
    color_vram = (b2 << 8) | b1
    
    # Conversão do formato SNES (BGR555) para RGB normal (0-255)
    # SNES: xbbbbbgggggrrrrr
    r = (color_vram & 0x1F) << 3
    g = ((color_vram >> 5) & 0x1F) << 3
    b = ((color_vram >> 10) & 0x1F) << 3
    
    palette_rgb.append((r, g, b))

# Preenche com preto caso a paleta tenha menos de 256 cores por algum motivo
while len(palette_rgb) < 256:
    palette_rgb.append((0, 0, 0))

# ==============================================================================
# 2. CARREGAMENTO DOS TILES E DO MAPA
# ==============================================================================
print("Carregando tiles e dados do mapa...")
with open(path_tiles, "rb") as f:
    tiles_data = f.read()

with open(path_map, "rb") as f:
    map_data = f.read()

# Cada tile Mode 7 de 8x8 ocupa exatamente 64 bytes (1 byte por pixel)
BYTES_PER_TILE = TILE_SIZE * TILE_SIZE
total_tiles_disponiveis = len(tiles_data) // BYTES_PER_TILE

# ==============================================================================
# 3. MONTAGEM DA IMAGEM PNG
# ==============================================================================
print("Renderizando o mapa em PNG...")
# Tamanho final da imagem em pixels: 512 * 8 = 4096 x 4096 pixels
img_w = MAP_WIDTH_TILES * TILE_SIZE
img_h = MAP_HEIGHT_TILES * TILE_SIZE
output_image = Image.new("RGB", (img_w, img_h))
pixels = output_image.load()

# Varre a matriz do mapa tile por tile
for tile_y in range(MAP_HEIGHT_TILES):
    for tile_x in range(MAP_WIDTH_TILES):
        
        # Encontra qual o índice do tile atual no mapa linear
        map_index = tile_y * MAP_WIDTH_TILES + tile_x
        if map_index >= len(map_data):
            break
            
        tile_id = map_data[map_index]
        
        # Segurança: se o mapa pedir um tile além do tamanho do arquivo de gráficos
        if tile_id >= total_tiles_disponiveis:
            tile_id = 0 
            
        # Endereço inicial deste tile específico no ow_tiles.bin
        tile_base_offset = tile_id * BYTES_PER_TILE
        
        # Desenha os 8x8 pixels deste tile na imagem final
        for local_y in range(TILE_SIZE):
            for local_x in range(TILE_SIZE):
                # Pixel correspondente no arquivo de tiles
                pixel_offset = tile_base_offset + (local_y * TILE_SIZE) + local_x
                palette_index = tiles_data[pixel_offset]
                
                # Pega a cor correspondente convertida da paleta
                color = palette_rgb[palette_index]
                
                # Coordenada global na imagem PNG final
                global_x = (tile_x * TILE_SIZE) + local_x
                global_y = (tile_y * TILE_SIZE) + local_y
                
                pixels[global_x, global_y] = color

# Salva o arquivo na subpasta 'A'
print(f"Salvando imagem em: {path_output}")
output_image.save(path_output)
print("Concluído com sucesso!")