// #include <snes.h>

// #include "overworld.h"

// // =========================================================
// // DATA
// // =========================================================

// extern char ow_tiles_bin, ow_tiles_bin_end;
// extern char ow_palette_bin;

// extern char ow_map_chunk0,  ow_map_chunk1,  ow_map_chunk2,  ow_map_chunk3;
// extern char ow_map_chunk4,  ow_map_chunk5,  ow_map_chunk6,  ow_map_chunk7;
// extern char ow_map_chunk8,  ow_map_chunk9,  ow_map_chunk10, ow_map_chunk11;
// extern char ow_map_chunk12, ow_map_chunk13, ow_map_chunk14, ow_map_chunk15;

// // =========================================================
// // DEFINES
// // =========================================================

// #define WORLD_SIZE     512
// #define VIEW_SIZE      128
// #define TILE_SIZE      8

// #define UPDATE_ROW     1
// #define UPDATE_COL     2

// #define MAX_UPDATES    8

// // =========================================================
// // REGISTERS
// // =========================================================

// #define REG_VMADDL  (*(volatile u8*)0x2116)
// #define REG_VMADDH  (*(volatile u8*)0x2117)

// #define REG_DMAP0   (*(volatile u8*)0x4300)
// #define REG_BBAD0   (*(volatile u8*)0x4301)

// #define REG_A1T0L   (*(volatile u8*)0x4302)
// #define REG_A1T0H   (*(volatile u8*)0x4303)
// #define REG_A1B0    (*(volatile u8*)0x4304)

// #define REG_DAS0L   (*(volatile u8*)0x4305)
// #define REG_DAS0H   (*(volatile u8*)0x4306)

// #define REG_MDMAEN  (*(volatile u8*)0x420B)

// // =========================================================
// // CHUNKS
// // =========================================================

// static u8* chunk_table[4][4] =
// {
//     { (u8*)&ow_map_chunk0,  (u8*)&ow_map_chunk1,  (u8*)&ow_map_chunk2,  (u8*)&ow_map_chunk3  },
//     { (u8*)&ow_map_chunk4,  (u8*)&ow_map_chunk5,  (u8*)&ow_map_chunk6,  (u8*)&ow_map_chunk7  },
//     { (u8*)&ow_map_chunk8,  (u8*)&ow_map_chunk9,  (u8*)&ow_map_chunk10, (u8*)&ow_map_chunk11 },
//     { (u8*)&ow_map_chunk12, (u8*)&ow_map_chunk13, (u8*)&ow_map_chunk14, (u8*)&ow_map_chunk15 }
// };

// // =========================================================
// // UPDATE STRUCT
// // =========================================================

// typedef struct
// {
//     u8 type;
//     u8 addr;
//     u8* buffer;
// } MapUpdate;

// // =========================================================
// // STATE
// // =========================================================

// static s16 world_x = 0;
// static s16 world_y = 0;

// static u8 vram_left = 0;
// static u8 vram_top  = 0;

// static u16 world_zoom = 0x0100;

// // =========================================================
// // DOUBLE BUFFERS
// // =========================================================

// static u8 row_buf[2][128];
// static u8 col_buf[2][128];

// static u8 row_flip = 0;
// static u8 col_flip = 0;

// // =========================================================
// // UPDATE QUEUE
// // =========================================================

// static MapUpdate updates[MAX_UPDATES];
// static u8 update_count = 0;

// // =========================================================
// // DMA HELPER
// // =========================================================

// static inline void dmaCopyVramFast(u16 vram_addr,u8* src,u16 size,u8 mode)
// {
//     *(volatile u8*)0x2115 = mode;

//     REG_VMADDL = vram_addr & 0xFF;
//     REG_VMADDH = vram_addr >> 8;

//     REG_DMAP0 = 0x00;
//     REG_BBAD0 = 0x18;

//     REG_A1T0L = (u16)src & 0xFF;
//     REG_A1T0H = ((u16)src >> 8) & 0xFF;

//     REG_A1B0 = 0x7E;

//     REG_DAS0L = size & 0xFF;
//     REG_DAS0H = size >> 8;

//     REG_MDMAEN = 0x01;
// }

// // =========================================================
// // FAST ROW BUILDER
// // =========================================================

// static void buildRowFast(u8* dst,u16 wx,u16 wy)
// {
//     u16 remaining = 128;
//     u16 out = 0;

//     while(remaining)
//     {
//         u16 chunk_x = wx >> 7;
//         u16 chunk_y = wy >> 7;

//         u8* chunk =
//             chunk_table[chunk_y][chunk_x];

//         u16 localx = wx & 127;
//         u16 localy = wy & 127;

//         u16 run = 128 - localx;

//         if(run > remaining)
//             run = remaining;

//         u16 j;

//         u16 src_index =
//             (localy << 7) | localx;

//         for(j = 0; j < run; j++)
//         {
//             dst[out + j] =
//                 chunk[src_index + j];
//         }

//         wx = (wx + run) & 511;

//         out += run;
//         remaining -= run;
//     }
// }

// // =========================================================
// // FAST COLUMN BUILDER
// // =========================================================

// static void buildColumnFast(u8* dst,u16 wx,u16 wy)
// {
//     u16 i;

//     u16 localx = wx & 127;

//     u16 chunk_x = wx >> 7;

//     for(i=0;i<128;i++)
//     {
//         u16 y = (wy + i) & 511;

//         u16 chunk_y = y >> 7;

//         u8* chunk =
//             chunk_table[chunk_y][chunk_x];

//         u16 localy = y & 127;

//         dst[i] =
//             chunk[(localy << 7) | localx];
//     }
// }

// // =========================================================
// // QUEUE
// // =========================================================

// static inline void queueUpdate(u8 type,u8 addr,u8* buf)
// {
//     if(update_count >= MAX_UPDATES)
//         return;

//     updates[update_count].type   = type;
//     updates[update_count].addr   = addr;
//     updates[update_count].buffer = buf;

//     update_count++;
// }

// // =========================================================
// // FULL MAP UPLOAD
// // =========================================================

// static void uploadFull(void)
// {
//     u16 y;

//     for(y=0;y<128;y++)
//     {
//         buildRowFast(
//             row_buf[0],
//             world_x,
//             (world_y + y) & 511
//         );

//         dmaCopyVramFast(
//             y << 7,
//             row_buf[0],
//             128,
//             0x00
//         );
//     }
// }

// // =========================================================
// // INIT
// // =========================================================

// void overworldInit(s16 cam_x,s16 cam_y,u16 zoom)
// {
//     bgInitMapTileSet7(
//         &ow_tiles_bin,
//         &ow_map_chunk0,
//         &ow_palette_bin,
//         (&ow_tiles_bin_end - &ow_tiles_bin),
//         0x0000
//     );

//     setMode7(0);

//     REG_M7SEL = M7_WRAP;

//     world_x =
//         ((cam_x >> 3) - 64) & 511;

//     world_y =
//         ((cam_y >> 3) - 64) & 511;

//     vram_left = 0;
//     vram_top  = 0;

//     uploadFull();

//     world_zoom = zoom;

//     REG_M7A = zoom & 0xFF;
//     REG_M7A = zoom >> 8;

//     REG_M7D = zoom & 0xFF;
//     REG_M7D = zoom >> 8;
// }

// // =========================================================
// // RESTORE ZOOM
// // =========================================================

// void overworldRestoreZoom(void)
// {
//     REG_M7A = world_zoom & 0xFF;
//     REG_M7A = world_zoom >> 8;

//     REG_M7D = world_zoom & 0xFF;
//     REG_M7D = world_zoom >> 8;
// }

// // =========================================================
// // SCROLL
// // =========================================================

// void overworldScroll(s16 cam_x,s16 cam_y)
// {
//     s16 lx =
//         (vram_left << 3)
//         + (cam_x - (world_x << 3));

//     s16 ly =
//         (vram_top << 3)
//         + (cam_y - (world_y << 3));

//     REG_M7HOFS = lx & 0xFF;
//     REG_M7HOFS = lx >> 8;

//     REG_M7VOFS = ly & 0xFF;
//     REG_M7VOFS = ly >> 8;
// }

// // =========================================================
// // PREPARE
// // =========================================================

// void overworldPrepare(s16 cam_x,s16 cam_y)
// {
//     s16 target_x =
//         ((cam_x >> 3) - 64) & 511;

//     s16 target_y =
//         ((cam_y >> 3) - 64) & 511;

//     s16 dx =
//         (target_x - world_x) & 511;

//     s16 dy =
//         (target_y - world_y) & 511;

//     if(dx > 255) dx -= 512;
//     if(dy > 255) dy -= 512;

//     update_count = 0;

//     // =====================================================
//     // RIGHT
//     // =====================================================

//     while(dx > 0)
//     {
//         u8* buf = col_buf[col_flip];

//         world_x =
//             (world_x + 1) & 511;

//         u8 write_col = vram_left;

//         vram_left =
//             (vram_left + 1) & 127;

//         buildColumnFast(
//             buf,
//             (world_x + 127) & 511,
//             world_y
//         );

//         queueUpdate(
//             UPDATE_COL,
//             write_col,
//             buf
//         );

//         col_flip ^= 1;

//         dx--;
//     }

//     // =====================================================
//     // LEFT
//     // =====================================================

//     while(dx < 0)
//     {
//         u8* buf = col_buf[col_flip];

//         world_x =
//             (world_x - 1) & 511;

//         vram_left =
//             (vram_left - 1) & 127;

//         buildColumnFast(
//             buf,
//             world_x,
//             world_y
//         );

//         queueUpdate(
//             UPDATE_COL,
//             vram_left,
//             buf
//         );

//         col_flip ^= 1;

//         dx++;
//     }

//     // =====================================================
//     // DOWN
//     // =====================================================

//     while(dy > 0)
//     {
//         u8* buf = row_buf[row_flip];

//         world_y =
//             (world_y + 1) & 511;

//         u8 write_row = vram_top;

//         vram_top =
//             (vram_top + 1) & 127;

//         buildRowFast(
//             buf,
//             world_x,
//             (world_y + 127) & 511
//         );

//         queueUpdate(
//             UPDATE_ROW,
//             write_row,
//             buf
//         );

//         row_flip ^= 1;

//         dy--;
//     }

//     // =====================================================
//     // UP
//     // =====================================================

//     while(dy < 0)
//     {
//         u8* buf = row_buf[row_flip];

//         world_y =
//             (world_y - 1) & 511;

//         vram_top =
//             (vram_top - 1) & 127;

//         buildRowFast(
//             buf,
//             world_x,
//             world_y
//         );

//         queueUpdate(
//             UPDATE_ROW,
//             vram_top,
//             buf
//         );

//         row_flip ^= 1;

//         dy++;
//     }
// }

// // =========================================================
// // FLUSH
// // =========================================================

// void overworldFlush(void)
// {
//     u8 i;

//     for(i=0;i<update_count;i++)
//     {
//         MapUpdate* u = &updates[i];

//         // =================================================
//         // ROW
//         // =================================================

//         if(u->type == UPDATE_ROW)
//         {
//             u8 part1 =
//                 128 - vram_left;

//             u8 part2 =
//                 vram_left;

//             dmaCopyVramFast(
//                 ((u16)u->addr << 7) + vram_left,
//                 u->buffer,
//                 part1,
//                 0x00
//             );

//             if(part2)
//             {
//                 dmaCopyVramFast(
//                     ((u16)u->addr << 7),
//                     u->buffer + part1,
//                     part2,
//                     0x00
//                 );
//             }
//         }

//         // =================================================
//         // COLUMN
//         // =================================================

//         else
//         {
//             u8 part1 =
//                 128 - vram_top;

//             u8 part2 =
//                 vram_top;

//             dmaCopyVramFast(
//                 (((u16)vram_top << 7) + u->addr),
//                 u->buffer,
//                 part1,
//                 0x02
//             );

//             if(part2)
//             {
//                 dmaCopyVramFast(
//                     u->addr,
//                     u->buffer + part1,
//                     part2,
//                     0x02
//                 );
//             }
//         }
//     }

//     *(volatile u8*)0x2115 = 0x80;

//     update_count = 0;
// }

// // Coloque isso no FINAL do seu arquivo overworld.c DEBUGANDO, para que a função tenha acesso à tabela de chunks. Se você colocar isso em player.c, não vai compilar porque player.c não tem acesso à chunk_table (ela é definida em overworld.c). Mas aqui, dentro de overworld.c, funciona perfeitamente!

// u8 overworldGetTileAt(s16 px, s16 py) 
// {
//     // Garante o wrap-around correto do mapa dentro do limite de 4096 pixels
//     u16 world_x = (u16)px & 4095;
//     u16 world_y = (u16)py & 4095;

//     // Converte de pixels para coordenadas de tiles (divisão por 8)
//     u16 tile_x = world_x >> 3;
//     u16 tile_y = world_y >> 3;

//     // Encontra o chunk correspondente (chunk_table está definida aqui neste arquivo, então funciona perfeitamente!)
//     u16 chunk_x = tile_x >> 7;
//     u16 chunk_y = tile_y >> 7;

//     u8* chunk = chunk_table[chunk_y][chunk_x];

//     // Encontra a posição local (offset) do tile de 0 a 127 dentro do chunk
//     u16 local_x = tile_x & 127;
//     u16 local_y = tile_y & 127;

//     return chunk[(local_y << 7) | local_x] & 0xFF;
// }