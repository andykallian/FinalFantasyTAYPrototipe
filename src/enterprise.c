#include <snes.h>
#include "enterprise.h"
#include "airship.h"
#include "player.h"
#include "res/gfx/Enterprise_meta.inc"
#include "res/gfx/shadowShip_meta.inc"

#define SKYLINE_Y        31
#define GROUND_OVERLAP   3
#define GROUND_START    (SKYLINE_Y - GROUND_OVERLAP)
#define SCREEN_H         224
#define GROUNDLINES     (SCREEN_H - SKYLINE_Y)

extern u16 zoom;

#define ENTERPRISE_VRAM_ADDR    0x7000
#define ENTERPRISE_OAM_BASE     8
#define ENTERPRISE_PAL          1
#define ENTERPRISE_TILE_BASE    0

#define AIRSHIP_SPEED           4
#define AIRSHIP_SCREEN_Y        38

#define SHADOW_VRAM_ADDR        0x7400
#define SHADOW_TILE_BASE        64

#define SHADOW_OAM_BASE         12
#define SHADOW_PAL              1

extern u8 isMoving;
extern u8 moveDir;
extern u8 playerDir;
extern char shadowShip_tiles, shadowShip_tiles_end;

s16 ENTERPRISE_WORLD_X = 1576;
s16 ENTERPRISE_WORLD_Y = 2232;

// =========================================================
// ESTADO GLOBAL
// =========================================================
EnterpriseState enterprise_state         = ENTERPRISE_STATE_GROUND;
u8              enterprise_boarding_done = 0;
u8              enterprise_liftoff_done  = 0;
u8              enterprise_landing_done  = 0;
u8              enterprise_unboarding_done = 0;

// =========================================================
// ESTADO INTERNO
// =========================================================
static u8  enterprise_currentPose = ENTERPRISE_POSE_GROUND;
static u16 enterprise_lastFrame   = 0xFFFF;

static s16 liftoff_screen_y = 0;
static u8  liftoff_anim_timer = 0;
static u8  liftoff_anim_pose  = 0;

static u8  airship_anim_frame = 0;
static u8  airship_anim_timer = 0;
static u8  airship_moving_dir = 0;

extern s16 cam_x;
extern s16 cam_y;
static u8  shadow_loaded = 0;
static u8  shadow_current_frame = 0;
static u8  shadow_last_frame    = 0xFF;

// =========================================================
// CONFIGURAÇÃO DE EMBARQUE (DELAYS)
// =========================================================
static const u8 BOARDING_DELAYS[] =
{
    12, 12,
     8,  8,
     4,  4,
     2,  2, 2, 2,
     2,  2, 2, 2
};
#define BOARDING_STEPS (sizeof(BOARDING_DELAYS))

static u8 boarding_step  = 0;
static u8 boarding_timer = 0;
static u8 boarding_pose  = 0;

// =========================================================
// FUNÇÕES DE CONTROLE E REFRESH
// =========================================================
void enterpriseSetPose(u8 pose)
{
    enterprise_currentPose = pose;
}

static void shadowUpload(const t_metasprite *meta, u8 *sheet)
{
    u16 r0 = (u16)(meta[0].dtile) * 32;
    u16 r2 = (u16)(meta[2].dtile) * 32;

    dmaCopyVram(sheet + r0, 0x7400, 64);
    dmaCopyVram(sheet + r2, 0x7500, 64);
}

void enterpriseStartLanding(void)
{
    enterprise_state = ENTERPRISE_STATE_LANDING;
    liftoff_screen_y = -32; 
    liftoff_anim_timer = 0;
    liftoff_anim_pose  = 0;
    enterprise_landing_done = 0;
    enterprise_currentPose = ENTERPRISE_POSE_GROUND;
}

static void landingUpdate(void)
{
    liftoff_screen_y += 2; 
    airship_anim_timer++;

    if(airship_anim_timer >= 8)
    {
        airship_anim_timer = 0;
        airship_anim_frame ^= 1;
    }

    liftoff_anim_timer++;
    if(liftoff_anim_timer >= 6)
    {
        liftoff_anim_timer = 0;
        liftoff_anim_pose ^= 1;
        enterprise_currentPose = liftoff_anim_pose ? ENTERPRISE_POSE_FLY_ALT : ENTERPRISE_POSE_GROUND;
    }

    if(liftoff_screen_y >= (112 - 16))
    {
        liftoff_screen_y = 112 - 16;
        ENTERPRISE_WORLD_X = cam_x;
        ENTERPRISE_WORLD_Y = cam_y;
        enterprise_landing_done = 1; 
    }
}

void enterpriseStartUnboarding(void)
{
    enterprise_state = ENTERPRISE_STATE_UNBOARDING;
    boarding_step     = 0;
    boarding_timer    = 0;
    boarding_pose     = 0;
    enterprise_currentPose = ENTERPRISE_POSE_GROUND;
    enterprise_unboarding_done = 0;
}

static void unboardingUpdate(void)
{
    boarding_timer++;
    u8 reverse_step = (BOARDING_STEPS - 1) - boarding_step;

    if(boarding_timer >= BOARDING_DELAYS[reverse_step])
    {
        boarding_timer = 0;
        boarding_pose ^= 1;
        enterprise_currentPose = boarding_pose;
        boarding_step++;

        if(boarding_step >= BOARDING_STEPS)
        {
            enterprise_state = ENTERPRISE_STATE_GROUND;
            enterprise_currentPose = ENTERPRISE_POSE_GROUND; 
            enterprise_unboarding_done = 1; 
        }
    }
}

void enterpriseStartBoarding(void)
{
    enterprise_state  = ENTERPRISE_STATE_BOARDING;
    boarding_step     = 0;
    boarding_timer    = 0;
    boarding_pose     = 0;
    enterprise_currentPose = ENTERPRISE_POSE_GROUND;
}

void enterpriseStartLiftoff(void)
{
    enterprise_state       = ENTERPRISE_STATE_LIFTOFF;
    liftoff_screen_y       = 112 - 16;
    liftoff_anim_timer     = 0;
    liftoff_anim_pose      = 0;
    enterprise_currentPose = ENTERPRISE_POSE_GROUND;
    airship_moving_dir     = DIR_LEFT;
    airship_anim_frame     = 0;
    airship_anim_timer     = 0;
}

static void boardingUpdate(void)
{
    boarding_timer++;

    if(boarding_timer >= BOARDING_DELAYS[boarding_step])
    {
        boarding_timer = 0;
        boarding_pose ^= 1;
        enterprise_currentPose = boarding_pose;
        boarding_step++;

        if(boarding_step >= BOARDING_STEPS)
        {
            enterprise_boarding_done = 1;
            boarding_step  = 0;
            boarding_timer = 0;
            boarding_pose  = 0;
        }
    }
}

static void liftoffUpdate(void)
{
    liftoff_screen_y -= 2;
    airship_anim_timer++;

    if(airship_anim_timer >= 8)
    {
        airship_anim_timer = 0;
        airship_anim_frame ^= 1;
    }

    liftoff_anim_timer++;
    if(liftoff_anim_timer >= 6)
    {
        liftoff_anim_timer = 0;
        liftoff_anim_pose ^= 1;
        enterprise_currentPose = liftoff_anim_pose ? ENTERPRISE_POSE_FLY_ALT : ENTERPRISE_POSE_GROUND;
    }

    if(liftoff_screen_y < 35)
    {
        enterprise_state        = ENTERPRISE_STATE_GROUND;
        enterprise_liftoff_done = 1;
        isMoving  = 0;
        moveDir   = DIR_LEFT;
        playerDir = DIR_LEFT;
    }
}

static void enterprise_uploadTiles(const t_metasprite *meta, u8 *sheet)
{
    u16 r0 = (u16)(meta[ 0].dtile) * 32;
    u16 r1 = (u16)(meta[ 4].dtile) * 32;
    u16 r2 = (u16)(meta[ 8].dtile) * 32;
    u16 r3 = (u16)(meta[12].dtile) * 32;

    dmaCopyVram(sheet + r0,      0x7000, 128);
    dmaCopyVram(sheet + r1,      0x7100, 128);
    dmaCopyVram(sheet + r2,      0x7200, 128);
    dmaCopyVram(sheet + r3,      0x7300, 128);
}

static void enterpriseSetOAM(u8 slot, u8 size, u8 hide, s16 x, s16 y)
{
    u16 ext_index = 512 + (slot >> 2);
    u8  ext_shift = (slot & 3) << 1;

    oamMemory[ext_index] &= ~(3 << ext_shift);

    if(hide == OBJ_HIDE)
    {
        oamMemory[slot * 4 + 1] = 240;
        return;
    }

    u8 mask = 0;
    if(size == OBJ_LARGE)  mask |= 2;
    if(x < 0 || x > 255)   mask |= 1;

    oamMemory[ext_index] |= (mask << ext_shift);
}

static void shadowDraw(s16 x, s16 y)
{
    u16 id = SHADOW_OAM_BASE * 4;

    oamSet(id, x, y, 2, 0, 0, 256 + SHADOW_TILE_BASE, SHADOW_PAL);
    enterpriseSetOAM(SHADOW_OAM_BASE, OBJ_SMALL, OBJ_SHOW, x, y);
}

static void shadowHide(void)
{
    u16 id = SHADOW_OAM_BASE * 4;

    oamSet(id, 0, 240, 0, 0, 0, 0, 0);
    enterpriseSetOAM(SHADOW_OAM_BASE, OBJ_SMALL, OBJ_HIDE, 0, 240);
}

// =========================================================
// INITIALIZE
// =========================================================
void enterpriseInit(void)
{
    setPalette((u8*)&enterprise_pal, 144, 32);

    enterprise_state         = ENTERPRISE_STATE_GROUND;
    enterprise_boarding_done = 0;
    enterprise_liftoff_done  = 0;
    enterprise_landing_done  = 0;

    enterprise_currentPose   = ENTERPRISE_POSE_GROUND;
    enterprise_lastFrame     = 0xFFFF;
    shadow_last_frame        = 0xFF;

    shadowUpload(ShadowShip_metasprites[0], (u8*)&shadowShip_tiles);
    enterprise_uploadTiles(Enterprise_metasprites[ENTERPRISE_POSE_GROUND], (u8*)&enterprise_tiles);
    enterprise_lastFrame = ENTERPRISE_POSE_GROUND;
}

// =========================================================
// MÁQUINA DE ESTADOS E ANIMAÇÃO DA AIRSHIP
// =========================================================
void enterpriseUpdate(void)
{
    switch(enterprise_state)
    {
        case ENTERPRISE_STATE_GROUND:      enterprise_currentPose = ENTERPRISE_POSE_GROUND; break;
        case ENTERPRISE_STATE_BOARDING:    boardingUpdate();   break;
        case ENTERPRISE_STATE_LIFTOFF:     liftoffUpdate();    break;
        case ENTERPRISE_STATE_LANDING:     landingUpdate();    break;
        case ENTERPRISE_STATE_UNBOARDING:  unboardingUpdate(); break;
    }

    if(airship_state == AIRSHIP_ON)
    {
        airship_anim_timer++;
        if(airship_anim_timer >= 8)
        {
            airship_anim_timer = 0;
            airship_anim_frame ^= 1;
        }

        airship_moving_dir = isMoving ? moveDir : playerDir;

        switch(airship_moving_dir)
        {
            case DIR_LEFT:
            case DIR_RIGHT:
                enterprise_currentPose = airship_anim_frame ? ENTERPRISE_POSE_FLY_ALT : ENTERPRISE_POSE_GROUND;
                break;
            case DIR_UP:
                enterprise_currentPose = airship_anim_frame ? ENTERPRISE_POSE_UP_B : ENTERPRISE_POSE_UP_A;
                break;
            case DIR_DOWN:
                enterprise_currentPose = airship_anim_frame ? ENTERPRISE_POSE_DOWN_B : ENTERPRISE_POSE_DOWN_A;
                break;
        }
    }
}

// =========================================================
// VBLANK DMA FLUSH (INTERLEAVED)
// =========================================================
void enterpriseFlush(void)
{
    u8 enterprise_needs_update = (enterprise_currentPose != enterprise_lastFrame);
    
    if (enterprise_needs_update)
    {
        enterprise_lastFrame = enterprise_currentPose;
        enterprise_uploadTiles(Enterprise_metasprites[enterprise_currentPose], (u8*)&enterprise_tiles);
        return; // Adia a sombra para o próximo frame para evitar sobrecarga no VBlank
    }

    if (enterprise_state == ENTERPRISE_STATE_LIFTOFF ||
        enterprise_state == ENTERPRISE_STATE_LANDING ||
        airship_state == AIRSHIP_ON)
    {
        if (airship_anim_frame != shadow_last_frame)
        {
            shadow_last_frame = airship_anim_frame;
            shadowUpload(ShadowShip_metasprites[airship_anim_frame], (u8*)&shadowShip_tiles);
        }
    }
}

// =========================================================
// DRAW OAM (SPRITES)
// =========================================================
void enterpriseDraw(s16 cam_x, s16 cam_y)
{
    s16 screen_x, screen_y;
    u16 id  = ENTERPRISE_OAM_BASE * 4;
    u8  flipH = 0;

    if(enterprise_state == ENTERPRISE_STATE_LIFTOFF || enterprise_state == ENTERPRISE_STATE_LANDING)
    {
        s16 ship_x = 128 - 16;
        s16 ship_y = liftoff_screen_y;
        s16 shadow_x = 128 - 8;
        s16 shadow_y = 112;

        shadowDraw(shadow_x, shadow_y);
        oamSet(id, ship_x, ship_y, 3, 0, 0, 256 + ENTERPRISE_TILE_BASE, ENTERPRISE_PAL);
        enterpriseSetOAM(ENTERPRISE_OAM_BASE, OBJ_LARGE, OBJ_SHOW, ship_x, ship_y);
        return;
    }

    if(airship_state == AIRSHIP_ON)
    {
        flipH = (airship_moving_dir == DIR_RIGHT) ? 1 : 0;

        shadowDraw(128 - 8, (112 - 16) + 16);
        oamSet(id, 128 - 16, AIRSHIP_SCREEN_Y, 3, flipH, 0, 256 + ENTERPRISE_TILE_BASE, ENTERPRISE_PAL);
        enterpriseSetOAM(ENTERPRISE_OAM_BASE, OBJ_LARGE, OBJ_SHOW, 128 - 16, AIRSHIP_SCREEN_Y);
        return;
    }

    shadowHide();

    screen_x = (s16)((s32)ENTERPRISE_WORLD_X - cam_x) + 128 - 16;
    screen_y = (s16)((s32)ENTERPRISE_WORLD_Y - cam_y) + 112 - 16;

    if(screen_x < -32 || screen_x > 256 || screen_y < -32 || screen_y > 224)
    {
        oamSet(id, 0, 240, 0, 0, 0, 0, 0);
        enterpriseSetOAM(ENTERPRISE_OAM_BASE, OBJ_LARGE, OBJ_HIDE, screen_x, screen_y);
        return;
    }

    oamSet(id, screen_x, screen_y, 3, 0, 0, 256 + ENTERPRISE_TILE_BASE, ENTERPRISE_PAL);
    enterpriseSetOAM(ENTERPRISE_OAM_BASE, OBJ_LARGE, OBJ_SHOW, screen_x, screen_y);
}