#include <snes.h>
#include "splash.h"

extern char splash_tiles, splash_tiles_end;
extern char splash_map;
extern char splash_pal;

const u8 emptyTile[32] = { 0 };

#define CENTER_X1  17
#define CENTER_X2  19
#define CENTER_Y1  2
#define CENTER_Y2  9

#define WHITE_BGR  0x7FFF

u16 dreamTileMap[1024];
u16 dreamTileMapFull[1024];
u16 blankMap[1024];
u16 origPal[15];

static void setPalColor0(u16 bgr555) {
    u8 buf[2];
    buf[0] = (u8)(bgr555 & 0xFF);
    buf[1] = (u8)(bgr555 >> 8);
    WaitForVBlank();
    dmaCopyCGram(buf, 0, 2);
}

static void loadOrigPal(void) {
    u8 i;
    u16 *palSrc = (u16 *)&splash_pal;
    for (i = 0; i < 15; i++)
        origPal[i] = palSrc[i + 1];
}

static void setPalFade(u8 level, u8 maxLevel) {
    u8 buf[30];
    u8 i;
    for (i = 0; i < 15; i++) {
        u16 orig = origPal[i];
        s16 r0 = 31, g0 = 31, b0 = 31;
        s16 r1 = (s16)(orig & 0x1F);
        s16 g1 = (s16)((orig >> 5) & 0x1F);
        s16 b1 = (s16)((orig >> 10) & 0x1F);
        s16 r, g, b;
        u16 color;
        r = r0 + ((r1 - r0) * level) / maxLevel;
        g = g0 + ((g1 - g0) * level) / maxLevel;
        b = b0 + ((b1 - b0) * level) / maxLevel;
        color = ((u16)b << 10) | ((u16)g << 5) | (u16)r;
        buf[i*2]   = (u8)(color & 0xFF);
        buf[i*2+1] = (u8)(color >> 8);
    }
    WaitForVBlank();
    dmaCopyCGram(buf, 1, 30); // <-- era 2, agora 1
}

static void fadeLogoIn(u8 frames) {
    u8 i;
    for (i = 0; i <= frames; i++)
        setPalFade(i, frames);
}

static void fadeLogoOut(u8 frames) {
    u8 i;
    for (i = 0; i <= frames; i++)
        setPalFade(frames - i, frames);
}

static void buildTileMap(u16 *dst, u8 centerOnly) {
    const u8 LOGO_W = 16;
    const u8 LOGO_H = 16;
    const u8 OFF_X  = 8;
    const u8 OFF_Y  = 6;
    u16 i, tx, ty;
    u16 *mapSrc = (u16 *)&splash_map;

    for (i = 0; i < 1024; i++)
        dst[i] = 0;

    for (ty = 0; ty < LOGO_H; ty++) {
        for (tx = 0; tx < LOGO_W; tx++) {
            u16 mapX      = OFF_X + tx;
            u16 mapY      = OFF_Y + ty;
            u16 mapIdx    = mapY * 32 + mapX;
            u16 tileIdx   = ty * LOGO_W + tx;
            u16 tileEntry = (mapSrc[tileIdx] & 0x03FF) + 1;

            if (centerOnly) {
                if (mapX >= CENTER_X1 && mapX <= CENTER_X2 &&
                    mapY >= CENTER_Y1 && mapY <= CENTER_Y2)
                    dst[mapIdx] = tileEntry;
            } else {
                dst[mapIdx] = tileEntry;
            }
        }
    }
}

void initDreamsSplash(void) {
    u16 i;

    REG_INIDISP = 0x80;
    consoleInit();

    dmaCopyVram((u8 *)emptyTile,     0x2000,      32);
    dmaCopyVram((u8 *)&splash_tiles, 0x2000 + 32,
                (u32)(&splash_tiles_end - &splash_tiles));

    dmaCopyCGram((u8 *)&splash_pal, 0, 32);
    setPalColor0(WHITE_BGR);

    bgSetMapPtr(0, 0x0000, SC_32x32);
    bgSetGfxPtr(0, 0x2000);

    buildTileMap(dreamTileMap,     1);
    buildTileMap(dreamTileMapFull, 0);

    for (i = 0; i < 1024; i++)
        blankMap[i] = 0;

    WaitForVBlank();
    dmaCopyVram((u8 *)blankMap, 0x0000, 1024 * 2);

    setMode(BG_MODE1, 0);
    bgSetEnable(0);
    bgSetDisable(1);
    bgSetDisable(2);
    bgSetDisable(3);

    REG_INIDISP = 0x00;
}

static void fadeOutFrames(u8 frames) {
    u8 i;
    u8 level;
    for (i = 0; i <= frames; i++) {
        level = 15 - (u8)(((u16)i * 15) / frames);
        REG_INIDISP = level;
        WaitForVBlank();
    }
    REG_INIDISP = 0x00;
}

static void waitFrames(u8 n) {
    u8 i;
    for (i = 0; i < n; i++)
        WaitForVBlank();
}

u8 updateDreamsSplash(void) {
    loadOrigPal();

    WaitForVBlank();
    dmaCopyVram((u8 *)dreamTileMap, 0x0000, 1024 * 2);
    setPalColor0(WHITE_BGR);
    setPalFade(0, 1);
    REG_INIDISP = 0x0F;
    waitFrames(60);

    // === BATIDA: centro aparece em 2 segundos ===
    fadeLogoIn(120);

    // === some de volta ao branco em 2 segundos ===
    fadeLogoOut(120);

    // === logo completo aparece de uma vez ===
    WaitForVBlank();
    dmaCopyVram((u8 *)dreamTileMapFull, 0x0000, 1024 * 2);
    setPalFade(1, 1);
    setPalColor0(WHITE_BGR);
    REG_INIDISP = 0x0F;

    // === segura 3 segundos ===
    waitFrames(180);

    // === fade out em 1 segundo para o jogo ===
    fadeOutFrames(60);

    REG_INIDISP = 0x80;
    return 1;
}