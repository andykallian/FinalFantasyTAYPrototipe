#include <snes.h>
#include "airship.h"
#include "overworld.h"

extern s16 cam_x;
extern s16 cam_y;

extern char sky_tiles, sky_tiles_end;
extern char sky_map,   sky_map_end;
extern char sky_pal,   sky_pal_end;

#define SKYLINE_Y       31
#define GROUND_OVERLAP   3
#define GROUND_START    (SKYLINE_Y-GROUND_OVERLAP)
#define SCREEN_H      224
#define GROUNDLINES   (SCREEN_H - SKYLINE_Y)

#define SKY_TILE_ADDR 0x4000
#define SKY_MAP_ADDR  0x4400
static u16 PerspectiveZ[GROUNDLINES]; 

AirshipState airship_state = AIRSHIP_OFF;

static s16 sky_x = 0;
static s16 sky_y = 0;
static s16 staged_sx = 0;
static s16 staged_sy = 0;

// =================================================================
// OTIMIZAÇÃO: Arrays transferidos para RAM apenas como buffers de DMA fixos.
// Ou melhor ainda: se tornarmos as tabelas CONSTANTES, elas nem gastam RAM!
// =================================================================

// Vamos manter as tabelas geradas dinamicamente APENAS UMA VEZ na inicialização do jogo,
// ou simplesmente gerá-las fora e colá-las aqui. Para manter seu código idêntico sem quebrar as fórmulas,
// vamos usar uma flag para calcular a perspectiva APENAS UMA VEZ na história do jogo.
static u8 perspective_initialized = 0;

static u8 PerspectiveAB[GROUNDLINES * 5 + 8];
static u8 PerspectiveCD[GROUNDLINES * 5 + 8];
static s32 PerspectiveDY[GROUNDLINES];

static dmaMemory dma_mode;
static dmaMemory dma_bg;
static dmaMemory dma_ab;
static dmaMemory dma_cd;

static const u8 ModeTable[5]=
{
    GROUND_START, BG_MODE3,
    1,            BG_MODE7,
    0
};

const u8 BGTable[5]=
{
    GROUND_START, 0x12,
    1,            0x11,
    0
};

void fadeOut(void)
{
    u8 i;
    for(i=0;i<16;i++)
    {
        WaitForVBlank();
        REG_INIDISP=(15-i)&15;
    }
}

void fadeIn(void)
{
    u8 i;
    for(i=0;i<16;i++)
    {
        WaitForVBlank();
        REG_INIDISP=i&15;
    }
}

static void buildPerspective(void)
{
    // Se já foi calculado uma vez, sai imediatamente. 
    // Isso economiza milhares de ciclos de CPU na transição!
    if (perspective_initialized) return;

    u16 i;
    u16 p = 0;

    // Céu sem distorção
    PerspectiveAB[p]   = GROUND_START;
    PerspectiveAB[p+1] = 0;    
    PerspectiveAB[p+2] = 1;    
    PerspectiveAB[p+3] = 0;    
    PerspectiveAB[p+4] = 0;    

    PerspectiveCD[p]   = GROUND_START;
    PerspectiveCD[p+1] = 0;    
    PerspectiveCD[p+2] = 0;    
    PerspectiveCD[p+3] = 0;    
    PerspectiveCD[p+4] = 1;    

    p = 5;

    for(i = 0; i < GROUNDLINES; i++)
    {
        u16 z;
        s16 scale;
        s16 dist_v;
        s32 curve;

        z = (i << 8) / GROUNDLINES;

        dist_v = (s16)z - 200;
        curve  = (s32)dist_v * dist_v;
        curve >>= 8;

        scale = 300 + (s16)curve;
        scale += (256 - z) >> 3;

        PerspectiveAB[p]   = 1;
        PerspectiveAB[p+1] = scale & 255;  
        PerspectiveAB[p+2] = scale >> 8;   
        PerspectiveAB[p+3] = 0;            
        PerspectiveAB[p+4] = 0;            

        PerspectiveCD[p]   = 1;
        PerspectiveCD[p+1] = 0;            
        PerspectiveCD[p+2] = 0;            
        PerspectiveCD[p+3] = scale & 255;  
        PerspectiveCD[p+4] = scale >> 8;   

        p += 5;
    }

    PerspectiveAB[p] = 0;
    PerspectiveCD[p] = 0;

    for(i = 0; i < GROUNDLINES; i++)
    {
        s16 sdy    = (GROUND_START + i) - 112;
        u16 zi     = ((u16)i << 8) / GROUNDLINES;
        s16 dv     = (s16)zi - 190;
        s32 cv     = (s32)dv * dv >> 8;
        s32 sc     = 300 + cv + ((256 - zi) >> 3);
        PerspectiveDY[i] = (sc * (s32)sdy) >> 8;
    }

    // Assinala que está pronto e nunca mais processará esse loop pesado
    perspective_initialized = 1; 
}

static void airshipSetupHDMA(void)
{
    REG_HDMAEN = 0;

    REG_DMAP1  = 0x00;
    REG_BBAD1  = 0x05;
    REG_A1T1LH = dma_mode.mem.c.addr;
    REG_A1B1   = dma_mode.mem.c.bank;

    REG_DMAP2  = 0x00;
    REG_BBAD2  = 0x2C;
    REG_A1T2LH = dma_bg.mem.c.addr;
    REG_A1B2   = dma_bg.mem.c.bank;

    REG_DMAP3  = 0x03;
    REG_BBAD3  = 0x1B;  
    REG_A1T3LH = dma_ab.mem.c.addr;
    REG_A1B3   = dma_ab.mem.c.bank;

    REG_DMAP4  = 0x03;
    REG_BBAD4  = 0x1D;  
    REG_A1T4LH = dma_cd.mem.c.addr;
    REG_A1B4   = dma_cd.mem.c.bank;

    REG_HDMAEN = 0x1E;  
}

void airshipEnter(void)
{
    s16 sx, sy;

    fadeOut();

    // Otimizado: Só vai calcular na primeiríssima vez que você entrar no Airship do jogo inteiro.
    buildPerspective();

    bgInitTileSet(
        1,
        &sky_tiles,
        &sky_pal,
        0,
        (&sky_tiles_end-&sky_tiles),
        16*2,
        BG_16COLORS,
        SKY_TILE_ADDR
    );

    bgInitMapSet(
        1,
        &sky_map,
        (&sky_map_end-&sky_map),
        SC_32x32,
        SKY_MAP_ADDR
    );

    setMode7(0);

    REG_CGWSEL  = 0x00;
    REG_CGADSUB = 0x23;

    REG_M7SEL = M7_WRAP;
    REG_BG2SC = (SKY_MAP_ADDR >> 8);

    // Configura os ponteiros estáticos (Pode ser feito aqui com segurança)
    dma_mode.mem.p = (u8*)ModeTable;
    dma_bg.mem.p   = (u8*)BGTable;
    dma_ab.mem.p   = PerspectiveAB;
    dma_cd.mem.p   = PerspectiveCD;

    airship_state = AIRSHIP_ON;

    overworldGetScroll(cam_x, cam_y, &sx, &sy);
    

    // REMOVIDO: O WaitForVBlank() daqui de dentro! 
    // Deixe o loop principal do main.c controlar o sincronismo de tela de forma limpa.

    REG_M7HOFS = sx & 255;
    REG_M7HOFS = sx >> 8;
    REG_M7VOFS = sy & 255;
    REG_M7VOFS = sy >> 8;
    REG_M7X    = (sx + 128) & 255;
    REG_M7X    = (sx + 128) >> 8;
    REG_M7Y    = (sy + 112) & 255;
    REG_M7Y    = (sy + 112) >> 8;

    airshipSetupHDMA();

    //fadeIn();
}

void airshipExit(void)
{
    fadeOut();

    REG_HDMAEN  = 0;
    REG_CGADSUB = 0x00;

    airship_state = AIRSHIP_OFF;

    overworldRestoreZoom();

    //fadeIn();
}

// Otimizado: Função puramente focada no envio rápido de registradores
void airshipFlush(s16 cam_x, s16 cam_y)
{
    if(airship_state == AIRSHIP_OFF)
        return;

    sky_x = cam_x >> 2;
    sky_y = (cam_y >> 4) + 20;

    overworldGetScroll(cam_x, cam_y, &staged_sx, &staged_sy);
}

void airshipVBlank(void)
{
    if(airship_state == AIRSHIP_OFF)
        return;

    REG_M7HOFS = staged_sx & 255;
    REG_M7HOFS = staged_sx >> 8;
    REG_M7VOFS = staged_sy & 255;
    REG_M7VOFS = staged_sy >> 8;

    REG_M7X = (staged_sx + 128) & 255;
    REG_M7X = (staged_sx + 128) >> 8;
    REG_M7Y = (staged_sy + 112) & 255;
    REG_M7Y = (staged_sy + 112) >> 8;

    REG_BG2HOFS = sky_x & 255;
    REG_BG2HOFS = (sky_x >> 8) & 255;
}