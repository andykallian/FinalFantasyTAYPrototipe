// #include <snes.h>
// #include "airship.h"
// #include "overworld.h"

// extern s16 cam_x;
// extern s16 cam_y;

// extern char sky_tiles,sky_tiles_end;
// extern char sky_map,sky_map_end;
// extern char sky_pal,sky_pal_end;

// #define SKYLINEY 31
// #define GROUNDLINES (224-SKYLINEY)


// static u8 PerspectiveA[GROUNDLINES*3+4];
// static u8 PerspectiveB[GROUNDLINES*3+4];
// static u8 PerspectiveC[GROUNDLINES*3+4];
// static u8 PerspectiveD[GROUNDLINES*3+4];

// static s16 sky_x=0;
// static s16 sky_y=0;

// static dmaMemory dma_grad;

// static dmaMemory dma_mode;
// static dmaMemory dma_bg;
// static dmaMemory dma_a;
// static dmaMemory dma_b;
// static dmaMemory dma_c;
// static dmaMemory dma_d;

// AirshipState airship_state=AIRSHIP_OFF;

// static const u8 ModeTable[5]={
//     SKYLINEY,BG_MODE3,
//     1,BG_MODE7,
//     0
// };

// const u8 BGTable[5] = {
//     SKYLINEY, 0x12, // for 80 scanlines do: 00010010 (Objects + BG 1)
//     1, 0x11,        // for 1 scanline do: 00010001 (Objects + BG 0)
//     0x00            // End transfer
// };

// static const u8 HorizonGradient[] = {
//     // linhas 0-44: antes do horizonte, sem efeito
//     28, 0xE0,

//     // linhas 45-54: gradiente da transição (10 linhas)
//     1, 0xE9,  // intensidade 0  (sem brilho ainda)
//     1, 0xE9,
//     1, 0xE9,
//     1, 0xE9,
//     1, 0xE9,
//     1, 0xE9,
//     1, 0xE9,
//     1, 0xE0,
//     0
// };

// //=========================================================
// // gera perspectiva ampulheta
// //=========================================================

// static void buildPerspective(void)
// {
//     u16 i;
//     u16 p=0;

//     // Configuração do Céu (Inalterado)
//     PerspectiveA[p]=SKYLINEY; PerspectiveA[p+1]=0; PerspectiveA[p+2]=1;
//     PerspectiveB[p]=SKYLINEY; PerspectiveB[p+1]=0; PerspectiveB[p+2]=0;
//     PerspectiveC[p]=SKYLINEY; PerspectiveC[p+1]=0; PerspectiveC[p+2]=0;
//     PerspectiveD[p]=SKYLINEY; PerspectiveD[p+1]=0; PerspectiveD[p+2]=1;

//     p=3;

//     for(i=0; i<GROUNDLINES; i++)
//     {
//         s16 scale;
//         s32 curve;
//         s16 dist_v;

//         // z (0 a 255) representa a linha vertical da tela
//         u16 z = (i << 8) / GROUNDLINES;

//         //---------------------------------------------------------
//         // CURVA PARA EFEITO CONVEXO (ANDAR SOBRE O CILINDRO)
//         //---------------------------------------------------------
//         dist_v = (s16)z - 190; 
//         curve = (s32)dist_v * dist_v;
//         curve >>= 8; // Ajuste para mais ou menos curvatura

//         // Escala base do Mode 7
//         // Somamos a curve para que as pontas (topo/base) encolham (valor maior = longe)
//         scale = 300 + (s16)curve; 
        
//         // Perspectiva leve de horizonte
//         scale += (256 - z) >> 3;

//         //---------------------------------------------------------
//         // REMOVENDO A INCLINAÇÃO (SHEAR)
//         // Para o mapa ficar reto, as matrizes B e C devem ser 0.
//         //---------------------------------------------------------
//         s16 shear = 0; 

//         // Aplicação nos buffers de HDMA
//         PerspectiveA[p] = 1;
//         PerspectiveA[p+1] = scale & 255;
//         PerspectiveA[p+2] = (scale >> 8) & 255;

//         // Matriz B = 0 (Sem inclinação horizontal)
//         PerspectiveB[p] = 1;
//         PerspectiveB[p+1] = 0;
//         PerspectiveB[p+2] = 0;

//         // Matriz C = 0 (Sem inclinação vertical dos scans)
//         PerspectiveC[p] = 1;
//         PerspectiveC[p+1] = 0;
//         PerspectiveC[p+2] = 0;

//         PerspectiveD[p] = 1;
//         PerspectiveD[p+1] = scale & 255;
//         PerspectiveD[p+2] = (scale >> 8) & 255;

//         p += 3;
//     }

//     PerspectiveA[p] = 0;
//     PerspectiveB[p] = 0;
//     PerspectiveC[p] = 0;
//     PerspectiveD[p] = 0;
// }


// //=========================================================

// static void fadeOut(void)
// {
//     u8 i;

//     for(i=0;i<16;i++)
//     {
//         WaitForVBlank();
//         REG_INIDISP=(15-i)&15;
//     }
// }

// static void fadeIn(void)
// {
//     u8 i;

//     for(i=0;i<16;i++)
//     {
//         WaitForVBlank();
//         REG_INIDISP=i&15;
//     }
// }

// //=========================================================

// void airshipEnter(void)
// {
//     fadeOut();

//     buildPerspective();
    

//     //--------------------------------------------------
//     // carrega gráficos do céu
//     //--------------------------------------------------

//     // Carregue os gráficos no BG2 (4bpp / 16 cores)
//     bgInitTileSet(
//         1, 
//         &sky_tiles, 
//         &sky_pal, 
//         0, 
//         (&sky_tiles_end-&sky_tiles), 
//         16*2, 
//         BG_16COLORS, 
//         0x5000
//     );

//     bgInitMapSet( 
//         1,
//         &sky_map, 
//         (&sky_map_end-&sky_map), 
//         SC_32x32, 
//         0x6000 // Endereço do mapa );
//     );

//     //--------------------------------------------------
//     // ativa BG1
//     //--------------------------------------------------

//     setMode7(0);
//     REG_CGWSEL = 0x00;
//     REG_CGADSUB = 0x23;

//     //--------------------------------------------------
//     // mode7 wrap
//     //--------------------------------------------------

//     REG_M7SEL=M7_WRAP;
//     REG_BG2SC = (0x6000 >> 8);

//     //--------------------------------------------------
//     // HDMA
//     //--------------------------------------------------

//     dma_mode.mem.p=(u8*)ModeTable;
//     dma_bg.mem.p=(u8*)BGTable;
//     dma_grad.mem.p = (u8*)HorizonGradient;

//     dma_a.mem.p=PerspectiveA;
//     dma_b.mem.p=PerspectiveB;
//     dma_c.mem.p=PerspectiveC;
//     dma_d.mem.p=PerspectiveD;

//     airship_state=AIRSHIP_ON;

//     s16 sx, sy;

//     overworldGetScroll(cam_x, cam_y, &sx, &sy);

//     // aplica imediatamente

//     REG_M7HOFS=sx&255;
//     REG_M7HOFS=sx>>8;

//     REG_M7VOFS=sy&255;
//     REG_M7VOFS=sy>>8;

//     REG_M7X=(sx+128)&255;
//     REG_M7X=(sx+128)>>8;

//     REG_M7Y=(sy+112)&255;
//     REG_M7Y=(sy+112)>>8;

    

//     fadeIn();
// }

// //=========================================================

// void airshipExit(void)
// {
//     fadeOut();
//     REG_HDMAEN = 0;
//     airship_state = AIRSHIP_OFF;
//     overworldRestoreZoom();  // restaura zoom do overworld
//     fadeIn();
// }

// //=========================================================

// void airshipFlush(s16 cam_x,s16 cam_y)
// {
//     if(airship_state==AIRSHIP_OFF)
//         return;

//     sky_x=cam_x>>2;
//     sky_y=(cam_y>>4)+20;

//     //bgSetScroll(2,sky_x,sky_y);

//     s16 sx, sy;

//     overworldGetScroll(cam_x, cam_y, &sx, &sy);

//     REG_M7HOFS=sx&255;
//     REG_M7HOFS=sx>>8;

//     REG_M7VOFS=sy&255;
//     REG_M7VOFS=sy>>8;

//     REG_M7X=(sx+128)&255;
//     REG_M7X=(sx+128)>>8;

//     REG_M7Y=(sy+112)&255;
//     REG_M7Y=(sy+112)>>8;

//     REG_HDMAEN=0;

//     REG_DMAP1=0x00;
//     REG_BBAD1=0x05;
//     REG_A1T1LH=dma_mode.mem.c.addr;
//     REG_A1B1=dma_mode.mem.c.bank;

//     REG_DMAP2=0x00;
//     REG_BBAD2=0x2C;
//     REG_A1T2LH=dma_bg.mem.c.addr;
//     REG_A1B2=dma_bg.mem.c.bank;

//     REG_DMAP3=0x02;
//     REG_BBAD3=0x1B;
//     REG_A1T3LH=dma_a.mem.c.addr;
//     REG_A1B3=dma_a.mem.c.bank;

//     REG_DMAP4=0x02;
//     REG_BBAD4=0x1C;
//     REG_A1T4LH=dma_b.mem.c.addr;
//     REG_A1B4=dma_b.mem.c.bank;

//     REG_DMAP5=0x02;
//     REG_BBAD5=0x1D;
//     REG_A1T5LH=dma_c.mem.c.addr;
//     REG_A1B5=dma_c.mem.c.bank;

//     REG_DMAP6=0x02;
//     REG_BBAD6=0x1E;
//     REG_A1T6LH=dma_d.mem.c.addr;
//     REG_A1B6=dma_d.mem.c.bank;

//     REG_DMAP7 = 0x00;
//     REG_BBAD7 = 0x32; // COLDATA ($2132)
//     REG_A1T7LH = dma_grad.mem.c.addr;
//     REG_A1B7 = dma_grad.mem.c.bank;

//     REG_HDMAEN=0xFE;
//     REG_BG2HOFS = (sky_x & 255);
//     REG_BG2HOFS = (sky_x >> 8) & 255;
// }







////////////// aqui sem gradiente mas moderno

// #include <snes.h>
// #include "airship.h"
// #include "overworld.h"

// //=========================================================
// // EXTERNOS
// //=========================================================

// extern s16 cam_x;
// extern s16 cam_y;

// extern char sky_tiles, sky_tiles_end;
// extern char sky_map,   sky_map_end;
// extern char sky_pal,   sky_pal_end;


// //=========================================================
// // CONFIG
// //=========================================================

// #define SKYLINE_Y       31
// #define GROUND_OVERLAP   3
// #define GROUND_START    (SKYLINE_Y-GROUND_OVERLAP)
// #define SCREEN_H      224
// #define GROUNDLINES   (SCREEN_H - SKYLINE_Y)

// #define SKY_TILE_ADDR 0x4000
// #define SKY_MAP_ADDR  0x4400


// //=========================================================
// // ESTADO
// //=========================================================

// AirshipState airship_state = AIRSHIP_OFF;

// static s16 sky_x = 0;
// static s16 sky_y = 0;


// //=========================================================
// // HDMA BUFFERS
// //=========================================================

// static u8 PerspectiveA[GROUNDLINES * 3 + 4];
// static u8 PerspectiveB[GROUNDLINES * 3 + 4];
// static u8 PerspectiveC[GROUNDLINES * 3 + 4];
// static u8 PerspectiveD[GROUNDLINES * 3 + 4];

// static dmaMemory dma_mode;
// static dmaMemory dma_bg;

// static dmaMemory dma_a;
// static dmaMemory dma_b;
// static dmaMemory dma_c;
// static dmaMemory dma_d;


// //=========================================================
// // HDMA TABLES
// //=========================================================

// // Troca BG mode no horizonte
// static const u8 ModeTable[5]=
// {
//     GROUND_START, BG_MODE3,
//     1,            BG_MODE7,
//     0
// };

// // Ativa BG do céu e depois Mode7
// const u8 BGTable[5]=
// {
//     GROUND_START,0x12,
//     1,0x11,
//     0
// };


// //=========================================================
// // FADE
// //=========================================================

// static void fadeOut(void)
// {
//     u8 i;

//     for(i=0;i<16;i++)
//     {
//         WaitForVBlank();
//         REG_INIDISP=(15-i)&15;
//     }
// }

// static void fadeIn(void)
// {
//     u8 i;

//     for(i=0;i<16;i++)
//     {
//         WaitForVBlank();
//         REG_INIDISP=i&15;
//     }
// }


// //=========================================================
// // GERA PERSPECTIVA
// //=========================================================

// static void buildPerspective(void)
// {
//     u16 i;
//     u16 p=0;

//     // céu sem distorção
//     PerspectiveA[p]=GROUND_START;
//     PerspectiveA[p+1]=0;
//     PerspectiveA[p+2]=1;

//     PerspectiveB[p]=GROUND_START;
//     PerspectiveB[p+1]=0;
//     PerspectiveB[p+2]=0;

//     PerspectiveC[p]=GROUND_START;
//     PerspectiveC[p+1]=0;
//     PerspectiveC[p+2]=0;

//     PerspectiveD[p]=GROUND_START;
//     PerspectiveD[p+1]=0;
//     PerspectiveD[p+2]=1;

//     p=3;

//     for(i=0;i<GROUNDLINES;i++)
//     {
//         u16 z;
//         s16 scale;

//         s16 dist_v;
//         s32 curve;

//         z=(i<<8)/GROUNDLINES;

//         // curva "cilíndrica"
//         dist_v=(s16)z-190;

//         curve=(s32)dist_v*dist_v;
//         curve>>=8;

//         scale=300+(s16)curve;

//         // horizonte suave
//         scale+=(256-z)>>3;

//         PerspectiveA[p]=1;
//         PerspectiveA[p+1]=scale&255;
//         PerspectiveA[p+2]=scale>>8;

//         // sem shear
//         PerspectiveB[p]=1;
//         PerspectiveB[p+1]=0;
//         PerspectiveB[p+2]=0;

//         PerspectiveC[p]=1;
//         PerspectiveC[p+1]=0;
//         PerspectiveC[p+2]=0;

//         PerspectiveD[p]=1;
//         PerspectiveD[p+1]=scale&255;
//         PerspectiveD[p+2]=scale>>8;

//         p+=3;
//     }

//     // fim tabelas
//     PerspectiveA[p]=0;
//     PerspectiveB[p]=0;
//     PerspectiveC[p]=0;
//     PerspectiveD[p]=0;
// }


// //=========================================================
// // CONFIGURA HDMA
// //=========================================================

// static void airshipSetupHDMA(void)
// {
//     REG_HDMAEN=0;

//     // modo
//     REG_DMAP1=0x00;
//     REG_BBAD1=0x05;
//     REG_A1T1LH=dma_mode.mem.c.addr;
//     REG_A1B1=dma_mode.mem.c.bank;

//     // bg
//     REG_DMAP2=0x00;
//     REG_BBAD2=0x2C;
//     REG_A1T2LH=dma_bg.mem.c.addr;
//     REG_A1B2=dma_bg.mem.c.bank;

//     // matrix A
//     REG_DMAP3=0x02;
//     REG_BBAD3=0x1B;
//     REG_A1T3LH=dma_a.mem.c.addr;
//     REG_A1B3=dma_a.mem.c.bank;

//     // matrix B
//     REG_DMAP4=0x02;
//     REG_BBAD4=0x1C;
//     REG_A1T4LH=dma_b.mem.c.addr;
//     REG_A1B4=dma_b.mem.c.bank;

//     // matrix C
//     REG_DMAP5=0x02;
//     REG_BBAD5=0x1D;
//     REG_A1T5LH=dma_c.mem.c.addr;
//     REG_A1B5=dma_c.mem.c.bank;

//     // matrix D
//     REG_DMAP6=0x02;
//     REG_BBAD6=0x1E;
//     REG_A1T6LH=dma_d.mem.c.addr;
//     REG_A1B6=dma_d.mem.c.bank;

//     REG_HDMAEN=0x7E;
// }


// //=========================================================
// // ENTRA AIRSHIP
// //=========================================================

// void airshipEnter(void)
// {
//     s16 sx,sy;

//     fadeOut();

//     // gera perspectiva
//     buildPerspective();

//     // carrega céu
//     bgInitTileSet(
//         1,
//         &sky_tiles,
//         &sky_pal,
//         0,
//         (&sky_tiles_end-&sky_tiles),
//         16*2,
//         BG_16COLORS,
//         SKY_TILE_ADDR
//     );

//     bgInitMapSet(
//         1,
//         &sky_map,
//         (&sky_map_end-&sky_map),
//         SC_32x32,
//         SKY_MAP_ADDR
//     );

//     // ativa mode7
//     setMode7(0);

//     REG_CGWSEL=0x00;
//     REG_CGADSUB=0x23;

//     REG_M7SEL=M7_WRAP;

//     REG_BG2SC=(SKY_MAP_ADDR>>8);

//     // ponteiros HDMA
//     dma_mode.mem.p=(u8*)ModeTable;
//     dma_bg.mem.p=(u8*)BGTable;

//     dma_a.mem.p=(u8*)PerspectiveA;
//     dma_b.mem.p=(u8*)PerspectiveB;
//     dma_c.mem.p=(u8*)PerspectiveC;
//     dma_d.mem.p=(u8*)PerspectiveD;

//     airship_state=AIRSHIP_ON;
    

//     overworldGetScroll(
//         cam_x,
//         cam_y,
//         &sx,
//         &sy
//     );

//     WaitForVBlank();

//     // aplica posição correta antes da tela ligar
//     REG_M7HOFS=sx&255;
//     REG_M7HOFS=sx>>8;

//     REG_M7VOFS=sy&255;
//     REG_M7VOFS=sy>>8;

//     REG_M7X=(sx+128)&255;
//     REG_M7X=(sx+128)>>8;

//     REG_M7Y=(sy+112)&255;
//     REG_M7Y=(sy+112)>>8;

//     airshipSetupHDMA();

//     fadeIn();
// }


// //=========================================================
// // SAI AIRSHIP
// //=========================================================

// void airshipExit(void)
// {
//     fadeOut();

//     REG_HDMAEN=0;

//     airship_state=AIRSHIP_OFF;

//     // volta zoom original
//     overworldRestoreZoom();

//     fadeIn();
// }


// //=========================================================
// // UPDATE FRAME
// //=========================================================

// void airshipFlush(s16 cam_x,s16 cam_y)
// {
//     s16 sx,sy;

//     if(airship_state==AIRSHIP_OFF)
//         return;

//     // scroll lento do céu
//     sky_x=cam_x>>2;
//     sky_y=(cam_y>>4)+20;

//     overworldGetScroll(
//         cam_x,
//         cam_y,
//         &sx,
//         &sy
//     );

//     // câmera mode7
//     REG_M7HOFS=sx&255;
//     REG_M7HOFS=sx>>8;

//     REG_M7VOFS=sy&255;
//     REG_M7VOFS=sy>>8;

//     REG_M7X=(sx+128)&255;
//     REG_M7X=(sx+128)>>8;

//     REG_M7Y=(sy+112)&255;
//     REG_M7Y=(sy+112)>>8;

//     // scroll do céu
//     REG_BG2HOFS=(sky_x&255);
//     REG_BG2HOFS=(sky_x>>8)&255;
// }