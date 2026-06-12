#include <snes.h>
#include "overworld.h"


// =========================================================
// DEFINES
// =========================================================
#define WORLD_SIZE     512      // Tamanho total do mapa em tiles
#define VIEW_SIZE      128      // Janela visivel da VRAM em tiles
#define TILE_SIZE      8        // Tamanho de cada tile em pixels
#define UPDATE_ROW     1        // Flag de atualizacao de linha no scroll
#define UPDATE_COL     2        // Flag de atualizacao de coluna no scroll
#define MAX_UPDATES    8        // Limite maximo da fila de updates por frame

// =========================================================
// REGISTERS (SNES HARDWARE)
// =========================================================
#define REG_VMADDL  (*(volatile u8*)0x2116)  // Endereco VRAM Baixo
#define REG_VMADDH  (*(volatile u8*)0x2117)  // Endereco VRAM Alto
#define REG_DMAP0   (*(volatile u8*)0x4300)  // Parametros do DMA 0
#define REG_BBAD0   (*(volatile u8*)0x4301)  // Destino do B-Bus para DMA 0
#define REG_A1T0L   (*(volatile u8*)0x4302)  // Origem do A-Bus Baixo
#define REG_A1T0H   (*(volatile u8*)0x4303)  // Origem do A-Bus Alto
#define REG_A1B0    (*(volatile u8*)0x4304)  // Banco de Origem do A-Bus
#define REG_DAS0L   (*(volatile u8*)0x4305)  // Tamanho do DMA Baixo
#define REG_DAS0H   (*(volatile u8*)0x4306)  // Tamanho do DMA Alto
#define REG_MDMAEN  (*(volatile u8*)0x420B)  // Ativacao de canais DMA

// =========================================================
// EXTERNAL DATA (ROM BINARIES)
// =========================================================
extern char ow_tiles_bin, ow_tiles_bin_end;  // Graficos brutificados do tileset
extern char ow_palette_bin;                  // Paleta de cores do overworld
extern char ow_map_chunk0,  ow_map_chunk1,  ow_map_chunk2,  ow_map_chunk3;   // Matriz de chunks do mapa
extern char ow_map_chunk4,  ow_map_chunk5,  ow_map_chunk6,  ow_map_chunk7;   // Matriz de chunks do mapa
extern char ow_map_chunk8,  ow_map_chunk9,  ow_map_chunk10, ow_map_chunk11;  // Matriz de chunks do mapa
extern char ow_map_chunk12, ow_map_chunk13, ow_map_chunk14, ow_map_chunk15;  // Matriz de chunks do mapa

extern char ow_map_chunk_t0,  ow_map_chunk_t1,  ow_map_chunk_t2,  ow_map_chunk_t3;
extern char ow_map_chunk_t4,  ow_map_chunk_t5,  ow_map_chunk_t6,  ow_map_chunk_t7;
extern char ow_map_chunk_t8,  ow_map_chunk_t9,  ow_map_chunk_t10, ow_map_chunk_t11;
extern char ow_map_chunk_t12, ow_map_chunk_t13, ow_map_chunk_t14, ow_map_chunk_t15;
// =========================================================
// MAP CHUNKS TABLE
// =========================================================
static u8* chunk_table[4][4] =
{
    { (u8*)&ow_map_chunk0,  (u8*)&ow_map_chunk1,  (u8*)&ow_map_chunk2,  (u8*)&ow_map_chunk3  },
    { (u8*)&ow_map_chunk4,  (u8*)&ow_map_chunk5,  (u8*)&ow_map_chunk6,  (u8*)&ow_map_chunk7  },
    { (u8*)&ow_map_chunk8,  (u8*)&ow_map_chunk9,  (u8*)&ow_map_chunk10, (u8*)&ow_map_chunk11 },
    { (u8*)&ow_map_chunk12, (u8*)&ow_map_chunk13, (u8*)&ow_map_chunk14, (u8*)&ow_map_chunk15 }
};


static u8* chunk_table_t[4][4] =
{
    { (u8*)&ow_map_chunk_t0,  (u8*)&ow_map_chunk_t1,  (u8*)&ow_map_chunk_t2,  (u8*)&ow_map_chunk_t3  },
    { (u8*)&ow_map_chunk_t4,  (u8*)&ow_map_chunk_t5,  (u8*)&ow_map_chunk_t6,  (u8*)&ow_map_chunk_t7  },
    { (u8*)&ow_map_chunk_t8,  (u8*)&ow_map_chunk_t9,  (u8*)&ow_map_chunk_t10, (u8*)&ow_map_chunk_t11 },
    { (u8*)&ow_map_chunk_t12, (u8*)&ow_map_chunk_t13, (u8*)&ow_map_chunk_t14, (u8*)&ow_map_chunk_t15 }
};

// =========================================================
// DATA STRUCTURES
// =========================================================
typedef struct
{
    u8 type;        // Tipo de comando (UPDATE_ROW ou UPDATE_COL)
    u8 addr;        // Index da linha ou coluna alvo na VRAM
    u8* buffer;     // Ponteiro dos dados a serem transferidos
} MapUpdate;

// =========================================================
// STATE & SCROLL GLOBAL VARIABLES
// =========================================================
static s16 world_x = 0;              // Coordenada X atual do mundo em tiles
static s16 world_y = 0;              // Coordenada Y atual do mundo em tiles
static u8 vram_left = 0;             // Ponteiro de scroll horizontal da VRAM
static u8 vram_top  = 0;             // Ponteiro de scroll vertical da VRAM
static u16 world_zoom = 0x0100;      // Fator de escala da matriz do Mode 7

// =========================================================
// RENDER DOUBLE BUFFERS
// =========================================================
static u8 row_buf[2][128];           // Buffer duplo para geracao de linhas
static u8 col_buf[2][128];           // Buffer duplo para geracao de colunas
static u8 row_flip = 0;              // Controle de alternancia do buffer de linha
static u8 col_flip = 0;              // Controle de alternancia do buffer de coluna

// =========================================================
// DMA UPDATE QUEUE
// =========================================================
static MapUpdate updates[MAX_UPDATES]; // Fila de comandos pendentes para a V-Blank
static u8 update_count = 0;            // Contador de comandos na fila de transicao
static u8 water_phase = 0;

// =========================================================
// WATER ANIMATION BUFFERS
// =========================================================
static u8 waterbuf[1088];             // Armazena os pixels dos 4 tiles de agua na RAM
u8 water_timer = 0;           // Temporizador interno do frame rate da animacao

// =========================================================
// DMA HELPERS
// =========================================================
static inline void dmaCopyVramFast(u16 vram_addr, u8* src, u16 size, u8 mode)
{
    *(volatile u8*)0x2115 = mode;       // Define incremento e passos da VRAM

    REG_VMADDL = vram_addr & 0xFF;      // Seta endereco baixo da VRAM
    REG_VMADDH = vram_addr >> 8;        // Seta endereco alto da VRAM

    REG_DMAP0 = 0x00;                   // Transferencia simples de 1 byte por passo
    REG_BBAD0 = 0x18;                   // Alvo fixo: $2118 (VMDATAL)

    REG_A1T0L = (u16)src & 0xFF;        // Endereco inicial da RAM baixo
    REG_A1T0H = ((u16)src >> 8) & 0xFF; // Endereco inicial da RAM alto
    REG_A1B0 = 0x7E;                    // Forca a leitura no banco de RAM WRAM $7E

    REG_DAS0L = size & 0xFF;            // Volume de bytes baixo
    REG_DAS0H = size >> 8;              // Volume de bytes alto

    REG_MDMAEN = 0x01;                  // Executa o canal de DMA 0 imediatamente
}

// =========================================================
// ENGINE MATH & GRAPHICS BUILDERS
// =========================================================
static void buildRowFast(u8* dst, u16 wx, u16 wy)
{
    u16 remaining = 128;
    u16 out = 0;

    while(remaining)
    {
        u16 chunk_x = wx >> 7;
        u16 chunk_y = wy >> 7;

        u8* chunk = chunk_table[chunk_y][chunk_x];

        u16 localx = wx & 127;
        u16 localy = wy & 127;
        u16 run = 128 - localx;

        if(run > remaining)
            run = remaining;

        u16 j;
        u16 src_index = (localy << 7) | localx;

        for(j = 0; j < run; j++)
        {
            dst[out + j] = chunk[src_index + j];
        }

        wx = (wx + run) & 511;
        out += run;
        remaining -= run;
    }
}

static void buildColumnFast(u8* dst, u16 wx, u16 wy)
{
    u16 localx   = wx & 127;
    u16 chunk_x  = wx >> 7;

    u16 localy_start = wy & 127;
    u16 chunk_y      = wy >> 7;
    u16 run          = 128 - localy_start;

    u8* chunk = chunk_table_t[chunk_y][chunk_x];
    memcpy(dst, &chunk[(localx << 7) | localy_start], run);

    if(run < 128)
    {
        u16 next_wy  = (wy + run) & 511;
        u16 chunk_y2 = next_wy >> 7;
        u8* chunk2   = chunk_table_t[chunk_y2][chunk_x];

        memcpy(dst + run, &chunk2[localx << 7], 128 - run);
    }
}

static inline void queueUpdate(u8 type, u8 addr, u8* buf)
{
    if(update_count >= MAX_UPDATES)
        return;

    updates[update_count].type   = type;
    updates[update_count].addr   = addr;
    updates[update_count].buffer = buf;

    update_count++;
}

static void uploadFull(void)
{
    u16 y;

    for(y = 0; y < 128; y++)
    {
        buildRowFast(row_buf[0], world_x, (world_y + y) & 511);
        dmaCopyVramFast(y << 7, row_buf[0], 128, 0x00);
    }
}

// =========================================================
// WATER ANIMATION SYSTEM
// =========================================================
void overworldAnimateWaterTick(void)
{
    water_timer++;
    if(water_timer < 8)
        return;
    water_timer = 0;

    u16 tile, row, col;
    u8 temp;

    switch(water_phase & 3)
    {
        // =====================================================
        // FASE 0: Tiles 0~3 (horizontal completo) +
        //         Tiles 0x98/0x99 (metade superior horizontal)
        // =====================================================
        case 0:
            for(tile = 0; tile < 4; tile++)
            {
                u16 base = tile << 6;
                for(row = 0; row < 8; row++)
                {
                    u16 p = base + (row << 3);
                    temp         = waterbuf[p + 7];
                    waterbuf[p + 7] = waterbuf[p + 6];
                    waterbuf[p + 6] = waterbuf[p + 5];
                    waterbuf[p + 5] = waterbuf[p + 4];
                    waterbuf[p + 4] = waterbuf[p + 3];
                    waterbuf[p + 3] = waterbuf[p + 2];
                    waterbuf[p + 2] = waterbuf[p + 1];
                    waterbuf[p + 1] = waterbuf[p + 0];
                    waterbuf[p]     = temp;
                }
            }

            for(tile = 4; tile < 6; tile++)
            {
                u16 base = tile << 6;
                for(row = 0; row < 4; row++)
                {
                    u16 p = base + (row << 3);
                    temp         = waterbuf[p + 7];
                    waterbuf[p + 7] = waterbuf[p + 6];
                    waterbuf[p + 6] = waterbuf[p + 5];
                    waterbuf[p + 5] = waterbuf[p + 4];
                    waterbuf[p + 4] = waterbuf[p + 3];
                    waterbuf[p + 3] = waterbuf[p + 2];
                    waterbuf[p + 2] = waterbuf[p + 1];
                    waterbuf[p + 1] = waterbuf[p + 0];
                    waterbuf[p]     = temp;
                }
            }
            break;

        // =====================================================
        // FASE 1: Tiles 0x90/0x91 (metade inferior horizontal) +
        //         Tiles 0xDB~0xDE (vertical completo)
        // =====================================================
        case 1:
            for(tile = 6; tile < 8; tile++)
            {
                u16 base = tile << 6;
                for(row = 4; row < 8; row++)
                {
                    u16 p = base + (row << 3);
                    temp         = waterbuf[p + 7];
                    waterbuf[p + 7] = waterbuf[p + 6];
                    waterbuf[p + 6] = waterbuf[p + 5];
                    waterbuf[p + 5] = waterbuf[p + 4];
                    waterbuf[p + 4] = waterbuf[p + 3];
                    waterbuf[p + 3] = waterbuf[p + 2];
                    waterbuf[p + 2] = waterbuf[p + 1];
                    waterbuf[p + 1] = waterbuf[p + 0];
                    waterbuf[p]     = temp;
                }
            }

            for(tile = 8; tile < 12; tile++)
            {
                u16 base = tile << 6;
                for(col = 0; col < 8; col++)
                {
                    temp = waterbuf[base + (7 << 3) + col];
                    waterbuf[base + (7 << 3) + col] = waterbuf[base + (6 << 3) + col];
                    waterbuf[base + (6 << 3) + col] = waterbuf[base + (5 << 3) + col];
                    waterbuf[base + (5 << 3) + col] = waterbuf[base + (4 << 3) + col];
                    waterbuf[base + (4 << 3) + col] = waterbuf[base + (3 << 3) + col];
                    waterbuf[base + (3 << 3) + col] = waterbuf[base + (2 << 3) + col];
                    waterbuf[base + (2 << 3) + col] = waterbuf[base + (1 << 3) + col];
                    waterbuf[base + (1 << 3) + col] = waterbuf[base + (0 << 3) + col];
                    waterbuf[base + (0 << 3) + col] = temp;
                }
            }
            break;

        // =====================================================
        // FASE 2: Tile 0xD6 (vertical completo) +
        //         Tiles 0x9A e 0xA6 (vertical, colunas 4-7)
        // =====================================================
        case 2:
        {
            u16 base_D6 = 12 << 6;
            for(col = 0; col < 8; col++)
            {
                temp = waterbuf[base_D6 + (7 << 3) + col];
                waterbuf[base_D6 + (7 << 3) + col] = waterbuf[base_D6 + (6 << 3) + col];
                waterbuf[base_D6 + (6 << 3) + col] = waterbuf[base_D6 + (5 << 3) + col];
                waterbuf[base_D6 + (5 << 3) + col] = waterbuf[base_D6 + (4 << 3) + col];
                waterbuf[base_D6 + (4 << 3) + col] = waterbuf[base_D6 + (3 << 3) + col];
                waterbuf[base_D6 + (3 << 3) + col] = waterbuf[base_D6 + (2 << 3) + col];
                waterbuf[base_D6 + (2 << 3) + col] = waterbuf[base_D6 + (1 << 3) + col];
                waterbuf[base_D6 + (1 << 3) + col] = waterbuf[base_D6 + (0 << 3) + col];
                waterbuf[base_D6 + (0 << 3) + col] = temp;
            }

            u16 bases_6[2] = { 13 << 6, 14 << 6 };
            u16 b;
            for(b = 0; b < 2; b++)
            {
                u16 base = bases_6[b];
                for(col = 4; col < 8; col++)
                {
                    temp = waterbuf[base + (7 << 3) + col];
                    waterbuf[base + (7 << 3) + col] = waterbuf[base + (6 << 3) + col];
                    waterbuf[base + (6 << 3) + col] = waterbuf[base + (5 << 3) + col];
                    waterbuf[base + (5 << 3) + col] = waterbuf[base + (4 << 3) + col];
                    waterbuf[base + (4 << 3) + col] = waterbuf[base + (3 << 3) + col];
                    waterbuf[base + (3 << 3) + col] = waterbuf[base + (2 << 3) + col];
                    waterbuf[base + (2 << 3) + col] = waterbuf[base + (1 << 3) + col];
                    waterbuf[base + (1 << 3) + col] = waterbuf[base + (0 << 3) + col];
                    waterbuf[base + (0 << 3) + col] = temp;
                }
            }
            break;
        }

        // =====================================================
        // FASE 3: Tiles 0x9F e 0xA7 (vertical, colunas 0-3)
        // =====================================================
        case 3:
        {
            u16 bases_7[2] = { 15 << 6, 16 << 6 };
            u16 b;
            for(b = 0; b < 2; b++)
            {
                u16 base = bases_7[b];
                for(col = 0; col < 4; col++)
                {
                    temp = waterbuf[base + (7 << 3) + col];
                    waterbuf[base + (7 << 3) + col] = waterbuf[base + (6 << 3) + col];
                    waterbuf[base + (6 << 3) + col] = waterbuf[base + (5 << 3) + col];
                    waterbuf[base + (5 << 3) + col] = waterbuf[base + (4 << 3) + col];
                    waterbuf[base + (4 << 3) + col] = waterbuf[base + (3 << 3) + col];
                    waterbuf[base + (3 << 3) + col] = waterbuf[base + (2 << 3) + col];
                    waterbuf[base + (2 << 3) + col] = waterbuf[base + (1 << 3) + col];
                    waterbuf[base + (1 << 3) + col] = waterbuf[base + (0 << 3) + col];
                    waterbuf[base + (0 << 3) + col] = temp;
                }
            }
            break;
        }
    }

    water_phase++;
}

void overworldAnimateWaterFlush(void)
{
    *(volatile u8*)0x2115 = 0x80;
    REG_DMAP0 = 0x00;
    REG_BBAD0 = 0x19;
    REG_A1B0  = 0x7E;

    switch((water_phase - 1) & 3)
    {
        case 0:
            // Tiles 0~3 -> VRAM 0x0000
            REG_VMADDL = 0x00; REG_VMADDH = 0x00;
            REG_A1T0L = (u16)&waterbuf[0] & 255;
            REG_A1T0H = ((u16)&waterbuf[0] >> 8) & 255;
            REG_DAS0L = 256 & 0xFF; REG_DAS0H = 256 >> 8;
            REG_MDMAEN = 1;

            // Tiles 0x98/0x99 -> VRAM 0x2700
            REG_VMADDL = 0x00; REG_VMADDH = 0x27;
            REG_A1T0L = (u16)&waterbuf[256] & 255;
            REG_A1T0H = ((u16)&waterbuf[256] >> 8) & 255;
            REG_DAS0L = 128 & 0xFF; REG_DAS0H = 128 >> 8;
            REG_MDMAEN = 1;
            break;

        case 1:
            // Tiles 0x90/0x91 -> VRAM 0x2540
            REG_VMADDL = 0x40; REG_VMADDH = 0x25;
            REG_A1T0L = (u16)&waterbuf[384] & 255;
            REG_A1T0H = ((u16)&waterbuf[384] >> 8) & 255;
            REG_DAS0L = 128 & 0xFF; REG_DAS0H = 128 >> 8;
            REG_MDMAEN = 1;

            // Tiles 0xDB~0xDE -> VRAM 0x3340
            REG_VMADDL = 0x00; REG_VMADDH = 0x33;
            REG_A1T0L = (u16)&waterbuf[512] & 255;
            REG_A1T0H = ((u16)&waterbuf[512] >> 8) & 255;
            REG_DAS0L = 256 & 0xFF; REG_DAS0H = 256 >> 8;
            REG_MDMAEN = 1;
            break;

        case 2:
            // Tile 0xD6 -> VRAM 0x2780
            REG_VMADDL = 0x80; REG_VMADDH = 0x27;
            REG_A1T0L = (u16)&waterbuf[768] & 255;
            REG_A1T0H = ((u16)&waterbuf[768] >> 8) & 255;
            REG_DAS0L = 64 & 0xFF; REG_DAS0H = 64 >> 8;
            REG_MDMAEN = 1;

            // Tile 0x9A -> VRAM 0x2680
            REG_VMADDL = 0x80; REG_VMADDH = 0x26;
            REG_A1T0L = (u16)&waterbuf[832] & 255;
            REG_A1T0H = ((u16)&waterbuf[832] >> 8) & 255;
            REG_DAS0L = 64 & 0xFF; REG_DAS0H = 64 >> 8;
            REG_MDMAEN = 1;

            // Tile 0xA6 -> VRAM 0x2980
            REG_VMADDL = 0x80; REG_VMADDH = 0x29;
            REG_A1T0L = (u16)&waterbuf[896] & 255;
            REG_A1T0H = ((u16)&waterbuf[896] >> 8) & 255;
            REG_DAS0L = 64 & 0xFF; REG_DAS0H = 64 >> 8;
            REG_MDMAEN = 1;
            break;

        case 3:
            // Tile 0x9F -> VRAM 0x27C0
            REG_VMADDL = 0xC0; REG_VMADDH = 0x27;
            REG_A1T0L = (u16)&waterbuf[960] & 255;
            REG_A1T0H = ((u16)&waterbuf[960] >> 8) & 255;
            REG_DAS0L = 64 & 0xFF; REG_DAS0H = 64 >> 8;
            REG_MDMAEN = 1;

            // Tile 0xA7 -> VRAM 0x29C0
            REG_VMADDL = 0xC0; REG_VMADDH = 0x29;
            REG_A1T0L = (u16)&waterbuf[1024] & 255;
            REG_A1T0H = ((u16)&waterbuf[1024] >> 8) & 255;
            REG_DAS0L = 64 & 0xFF; REG_DAS0H = 64 >> 8;
            REG_MDMAEN = 1;
            break;
    }
}

// =========================================================
// SYSTEM CONTROL & SCROLL CORE
// =========================================================
void overworldInit(s16 cam_x, s16 cam_y, u16 zoom)
{
    bgInitMapTileSet7(
        &ow_tiles_bin,
        &ow_map_chunk0,
        &ow_palette_bin,
        (&ow_tiles_bin_end - &ow_tiles_bin),
        0x0000
    );

    setMode7(0);
    REG_M7SEL = M7_WRAP;

    world_x = ((cam_x >> 3) - 64) & 511;
    world_y = ((cam_y >> 3) - 64) & 511;

    vram_left = 0;
    vram_top  = 0;

    uploadFull();
    
    char* rom_src = (char*)&ow_tiles_bin;

    // Grupo 1: Tiles 0, 1, 2, 3 -> Começa no byte 0
    memcpy(&waterbuf[0], rom_src, 256);
    
    // Grupo 2: Tiles 0x9C e 0x9D (era 0x98/0x99)
    memcpy(&waterbuf[256], (rom_src + 0x9C*64), 128);

    // Grupo 3: Tiles 0x95 e 0x96 (era 0x90/0x91)
    memcpy(&waterbuf[384], (rom_src + 0x95*64), 128);

    // Grupo 4: Tiles 0xCC, 0xCD, 0xCE, 0xCF
    memcpy(&waterbuf[512], (rom_src + 0xCC*64), 256);

    // Grupo 5: Tile 0x9E (era 0xD6)
    memcpy(&waterbuf[768], (rom_src + 0x9E*64), 64);

        // Grupo 6: Tile 0x9A -> buffer[832]
    memcpy(&waterbuf[832],  (rom_src + 0x9A*64), 64);

    // Grupo 7: Tile 0xA6 -> buffer[896]
    memcpy(&waterbuf[896],  (rom_src + 0xA6*64), 64);

    // Grupo 8: Tile 0x9F -> buffer[960]
    memcpy(&waterbuf[960],  (rom_src + 0x9F*64), 64);

    // Grupo 9: Tile 0xA7 -> buffer[1024]
    memcpy(&waterbuf[1024], (rom_src + 0xA7*64), 64);

    world_zoom = zoom;

    REG_M7A = zoom & 0xFF;
    REG_M7A = zoom >> 8;
    REG_M7D = zoom & 0xFF;
    REG_M7D = zoom >> 8;
}

void overworldRestoreZoom(void)
{
    REG_M7A = world_zoom & 0xFF;
    REG_M7A = world_zoom >> 8;
    REG_M7D = world_zoom & 0xFF;
    REG_M7D = world_zoom >> 8;
}

void overworldScroll(s16 cam_x, s16 cam_y)
{
    s16 lx = (vram_left << 3) + (cam_x - (world_x << 3));
    s16 ly = (vram_top << 3) + (cam_y - (world_y << 3));

    REG_M7HOFS = lx & 0xFF;
    REG_M7HOFS = lx >> 8;
    REG_M7VOFS = ly & 0xFF;
    REG_M7VOFS = ly >> 8;
}

void overworldGetScroll(s16 cam_x,s16 cam_y,s16 *sx,s16 *sy)
{
    *sx = (vram_left << 3) + (cam_x - (world_x << 3));
    *sy = (vram_top  << 3) + (cam_y - (world_y << 3));
}

void overworldPrepare(s16 cam_x, s16 cam_y)
{
    s16 target_x = ((cam_x >> 3) - 64) & 511;
    s16 target_y = ((cam_y >> 3) - 64) & 511;

    s16 dx = (target_x - world_x) & 511;
    s16 dy = (target_y - world_y) & 511;

    if(dx > 255) dx -= 512;
    if(dy > 255) dy -= 512;

    update_count = 0;

    // =====================================================
    // SCROLL DIRECTION LOOPS
    // =====================================================
    while(dx > 0)
    {
        u8* buf = col_buf[col_flip];
        world_x = (world_x + 1) & 511;
        u8 write_col = vram_left;
        vram_left = (vram_left + 1) & 127;

        buildColumnFast(buf, (world_x + 127) & 511, world_y);
        queueUpdate(UPDATE_COL, write_col, buf);

        col_flip ^= 1;
        dx--;
    }

    while(dx < 0)
    {
        u8* buf = col_buf[col_flip];
        world_x = (world_x - 1) & 511;
        vram_left = (vram_left - 1) & 127;

        buildColumnFast(buf, world_x, world_y);
        queueUpdate(UPDATE_COL, vram_left, buf);

        col_flip ^= 1;
        dx++;
    }

    while(dy > 0)
    {
        u8* buf = row_buf[row_flip];
        world_y = (world_y + 1) & 511;
        u8 write_row = vram_top;
        vram_top = (vram_top + 1) & 127;

        buildRowFast(buf, world_x, (world_y + 127) & 511);
        queueUpdate(UPDATE_ROW, write_row, buf);

        row_flip ^= 1;
        dy--;
    }

    while(dy < 0)
    {
        u8* buf = row_buf[row_flip];
        world_y = (world_y - 1) & 511;
        vram_top = (vram_top - 1) & 127;

        buildRowFast(buf, world_x, world_y);
        queueUpdate(UPDATE_ROW, vram_top, buf);

        row_flip ^= 1;
        dy++;
    }
}

void overworldFlush(void)
{
    u8 i;

    for(i = 0; i < update_count; i++)
    {
        MapUpdate* u = &updates[i];

        if(u->type == UPDATE_ROW)
        {
            u8 part1 = 128 - vram_left;
            u8 part2 = vram_left;

            dmaCopyVramFast(((u16)u->addr << 7) + vram_left, u->buffer, part1, 0x00);

            if(part2)
            {
                dmaCopyVramFast(((u16)u->addr << 7), u->buffer + part1, part2, 0x00);
            }
        }
        else
        {
            u8 part1 = 128 - vram_top;
            u8 part2 = vram_top;

            dmaCopyVramFast((((u16)vram_top << 7) + u->addr), u->buffer, part1, 0x02);

            if(part2)
            {
                dmaCopyVramFast(u->addr, u->buffer + part1, part2, 0x02);
            }
        }
    }

    *(volatile u8*)0x2115 = 0x80;
    update_count = 0;
}

// =========================================================
// COLLISION & DEBUG DETECTION
// =========================================================
u8 overworldGetTileAt(s16 px, s16 py) 
{
    u16 world_x = (u16)px & 4095;        // Enquadra posicao X no limite do mapa
    u16 world_y = (u16)py & 4095;        // Enquadra posicao Y no limite do mapa

    u16 tile_x = world_x >> 3;           // Divide pixel por 8 para achar coluna
    u16 tile_y = world_y >> 3;           // Divide pixel por 8 para achar linha

    u16 chunk_x = tile_x >> 7;           // Mapeia quadrante X do chunk
    u16 chunk_y = tile_y >> 7;           // Mapeia quadrante Y do chunk

    u8* chunk = chunk_table[chunk_y][chunk_x];

    u16 local_x = tile_x & 127;          // Descobre coordenada X interna
    u16 local_y = tile_y & 127;          // Descobre coordenada Y interna

    return chunk[(local_y << 7) | local_x] & 0xFF; // Retorna ID puro do tile
}