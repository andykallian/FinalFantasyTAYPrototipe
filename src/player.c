#include <snes.h>
#include "player.h"
#include "enterprise.h"
#include "airship.h"

extern s16 cam_x;
extern s16 cam_y;

#define STEP_SIZE     8
#define STEP_SPEED    1
#define BLOCKED_COUNT (sizeof(BLOCKED_TILES))
#define LANDING_COUNT (sizeof(LANDING_TILES))

// =========================================================
// ESTADO GLOBAL
// =========================================================
PlayerState player_state      = PLAYER_STATE_WALK;
u8          player_boarding_done = 0;
u8          airship_wants_to_land = 0; // Trigger de pouso para o main.c

// =========================================================
// ESTADO INTERNO
// =========================================================
static u16 lastFrame          = 0xFFFF;
u8         playerDir          = DIR_DOWN;
u8         moveDir            = DIR_DOWN;
static u8  animFrame          = 0;
static u8  animTimer          = 0;
u8         isMoving           = 0;
u16        currentFrame       = 0;
static s16 move_rem           = 0;
u8         player_visible     = 1; // Controlado pelo main.c
static u8  wave_loop_counter  = 0;

// =========================================================
// DEFINIÇÃO ATIVA DO JOGADOR
// =========================================================
static const PlayerDef* current_player  = 0;
static const PlayerDef* previous_player = 0;

void playerSetDef(const PlayerDef* def)
{
    previous_player = current_player;
    current_player  = def;
    setPalette(def->palette, def->pal_offset, def->pal_size);
    lastFrame = 0xFFFF;
}

// =========================================================
// COLISÃO E VALIDAÇÃO DE TILES
// =========================================================
extern u8 overworldGetTileAt(s16 px, s16 py);

const u8 BLOCKED_TILES[] =
{
    0x00, 0x03,0x05, 0x06, 0x07, 0x0A, 0x0D, 0x0E, 
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 
    0x19, 0x1B, 0x1D, 0x1E, 0x1F, 0x20, 0x23, 0x28, 
    0x2B, 0x2C, 0x2D, 0x33, 0x34, 0x36, 0x37, 0x38, 
    0x3A, 0x3E, 0x40, 0x42, 0x43, 0x44, 0x46, 0x6C, 
    0x72, 0x7C, 0x7D, 0x7E, 0x95, 0x96, 0x9A, 0x9C, 
    0x9D, 0x9F, 0xA6, 0xA7
};

const u8 LANDING_TILES[] =
{
    0x0B, 0x0C, 0x0F, 0x10, 0xB7, 0xB8, 0xB9, 0xBA, 
    0xBB, 0xBC, 0xBD, 0xBE, 0xC0, 0xC1, 0xC2, 0xC3, 
    0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA
};

static u8 isSolid(s16 px, s16 py)
{
    u8 tile = overworldGetTileAt(px, py);
    u8 i;

    for(i = 0; i < BLOCKED_COUNT; i++)
    {
        if(tile == BLOCKED_TILES[i])
            return 1;
    }
    return 0;
}

static u8 canLandHere(s16 px, s16 py)
{
    u8 tile = overworldGetTileAt(px, py);
    u8 i;

    for(i = 0; i < LANDING_COUNT; i++)
    {
        if(tile == LANDING_TILES[i])
            return 1; // Tile de pouso válido encontrado
    }
    return 0;
}

// =========================================================
// DEBUG WRAM
// =========================================================
static void debugUpdateWramTiles(s16 player_x, s16 player_y)
{
    #if DEBUG_TILES
    volatile u8* wram_current = (volatile u8*)0x03AD;
    volatile u8* wram_right   = (volatile u8*)0x03AE;
    volatile u8* wram_left    = (volatile u8*)0x03AF;
    volatile u8* wram_up      = (volatile u8*)0x03B0;
    volatile u8* wram_down    = (volatile u8*)0x03B1;

    *wram_current = overworldGetTileAt(player_x,     player_y);
    *wram_right   = overworldGetTileAt(player_x + 8, player_y);
    *wram_left    = overworldGetTileAt(player_x - 8, player_y);
    *wram_up      = overworldGetTileAt(player_x,     player_y - 8);
    *wram_down    = overworldGetTileAt(player_x,     player_y + 8);
    #endif
}

// =========================================================
// ANIMAÇÃO
// =========================================================
static void playerUpdateAnim(void)
{
    if (player_state == PLAYER_STATE_WAVING) return;
    u8 visualDir = isMoving ? moveDir : playerDir;

    if(!isMoving)
    {
        switch(visualDir)
        {
            case DIR_DOWN:  currentFrame = FRAME_FRONT_IDLE;      break;
            case DIR_UP:    currentFrame = FRAME_BACK_IDLE;       break;
            case DIR_LEFT:  currentFrame = FRAME_SIDE_IDLE_LEFT;  break;
            case DIR_RIGHT: currentFrame = FRAME_SIDE_IDLE_RIGHT; break;
        }
        return;
    }

    animTimer++;
    if(animTimer > 10)
    {
        animTimer = 0;
        animFrame ^= 1;
    }

    switch(visualDir)
    {
        case DIR_DOWN:  currentFrame = animFrame ? FRAME_FRONT_WALK : FRAME_FRONT_IDLE;       break;
        case DIR_UP:    currentFrame = animFrame ? FRAME_BACK_WALK : FRAME_BACK_IDLE;         break;
        case DIR_LEFT:  currentFrame = animFrame ? FRAME_SIDE_WALK1_LEFT : FRAME_SIDE_WALK2_LEFT;  break;
        case DIR_RIGHT: currentFrame = animFrame ? FRAME_SIDE_WALK1_RIGHT : FRAME_SIDE_WALK2_RIGHT; break;
    }
}

// =========================================================
// INICIALIZAÇÃO
// =========================================================
void playerInit(s16 startX, s16 startY, const PlayerDef* def)
{
    cam_x = startX;
    cam_y = startY;

    playerDir            = DIR_DOWN;
    moveDir              = DIR_DOWN;
    animFrame            = 0;
    animTimer            = 0;
    isMoving             = 0;
    currentFrame         = FRAME_FRONT_IDLE;
    lastFrame            = 0xFFFF;
    player_visible       = 1;
    player_state         = PLAYER_STATE_WALK;
    player_boarding_done = 0;

    playerSetDef(def);

    const t_metasprite* meta = current_player->metasprites[FRAME_FRONT_IDLE];
    u8* sheet = current_player->tiles;

    u16 headTop = (u16)(meta[0].dtile) * 32;
    u16 headBot = headTop + (16 * 32);
    u16 bodyTop = (u16)(meta[1].dtile) * 32;
    u16 bodyBot = bodyTop + (16 * 32);

    dmaCopyVram(sheet + headTop, 0x6000, 64);
    dmaCopyVram(sheet + headBot, 0x6100, 64);
    dmaCopyVram(sheet + bodyTop, 0x6200, 64);
    dmaCopyVram(sheet + bodyBot, 0x6300, 64);

    lastFrame = FRAME_FRONT_IDLE;
}

// =========================================================
// PRIORIDADE DE INPUT D-PAD
// =========================================================
static void playerUpdateDirection(u16 held, u16 press)
{
    if      (press & KEY_UP)    playerDir = DIR_UP;
    else if (press & KEY_DOWN)  playerDir = DIR_DOWN;
    else if (press & KEY_LEFT)  playerDir = DIR_LEFT;
    else if (press & KEY_RIGHT) playerDir = DIR_RIGHT;

    switch(playerDir)
    {
        case DIR_UP:
            if      (!(held & KEY_UP)    && (held & KEY_DOWN))  playerDir = DIR_DOWN;
            else if (!(held & KEY_UP)    && (held & KEY_LEFT))  playerDir = DIR_LEFT;
            else if (!(held & KEY_UP)    && (held & KEY_RIGHT)) playerDir = DIR_RIGHT;
            break;
        case DIR_DOWN:
            if      (!(held & KEY_DOWN)  && (held & KEY_UP))    playerDir = DIR_UP;
            else if (!(held & KEY_DOWN)  && (held & KEY_LEFT))  playerDir = DIR_LEFT;
            else if (!(held & KEY_DOWN)  && (held & KEY_RIGHT)) playerDir = DIR_RIGHT;
            break;
        case DIR_LEFT:
            if      (!(held & KEY_LEFT)  && (held & KEY_UP))    playerDir = DIR_UP;
            else if (!(held & KEY_LEFT)  && (held & KEY_DOWN))  playerDir = DIR_DOWN;
            else if (!(held & KEY_LEFT)  && (held & KEY_RIGHT)) playerDir = DIR_RIGHT;
            break;
        case DIR_RIGHT:
            if      (!(held & KEY_RIGHT) && (held & KEY_UP))    playerDir = DIR_UP;
            else if (!(held & KEY_RIGHT) && (held & KEY_DOWN))  playerDir = DIR_DOWN;
            else if (!(held & KEY_RIGHT) && (held & KEY_LEFT))  playerDir = DIR_LEFT;
            break;
    }
}

// =========================================================
// HELPER DE PROXIMIDADE
// =========================================================
static u8 isNearEnterprise(void)
{
    s16 dx = cam_x - ENTERPRISE_WORLD_X;
    s16 dy = cam_y - ENTERPRISE_WORLD_Y;

    if(dx < 0) dx = -dx;
    if(dy < 0) dy = -dy;

    return (dx < 16 && dy < 16);
}

// =========================================================
// LOOP DE ATUALIZAÇÃO PRINCIPAL
// =========================================================
void playerUpdate(void)
{
    u16 held  = padsCurrent(0);
    u16 press = padsDown(0);
    u8  steps_this_frame;
    u8  p;

    isMoving = 0;

    // Processa tentativa de pouso da nave ao apertar B
    if((press & KEY_B) && (airship_state != AIRSHIP_OFF)) {
        s16 px = (cam_x + 128) & 4095;
        s16 py = (cam_y + 128) & 4095;

        if(canLandHere(px, py)) {
            airship_wants_to_land = 1;
            return; // Bloqueia inputs porque iniciou a descida
        }           
    }

    if(enterprise_state == ENTERPRISE_STATE_UNBOARDING) return;
    if(enterprise_state == ENTERPRISE_STATE_LANDING)    return; 

    // Bloqueia movimentação se estiver decolando ou embarcando
    if(enterprise_state == ENTERPRISE_STATE_BOARDING || enterprise_state == ENTERPRISE_STATE_LIFTOFF)
    {
        if(enterprise_boarding_done)
        {
            enterprise_boarding_done = 0;
            enterpriseStartLiftoff();
        }
        return;
    }

    // Gerencia o gatilho de embarque na Enterprise
    if(airship_state == AIRSHIP_OFF)
    {
        if((press & KEY_A) && isNearEnterprise())
        {
            player_visible = 0;
            enterpriseStartBoarding();
            return;
        }
    }

    // Atualiza lógica da animação de aceno (Waving)
    if (player_state == PLAYER_STATE_WAVING)
    {
        if (press & (KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT))
        {
            player_state = PLAYER_STATE_WALK; // Cancela aceno se mover
        }
        else
        {
            animTimer++;
            if (animTimer > 12) 
            {
                animTimer = 0;
                animFrame ^= 1;
                wave_loop_counter++;
                currentFrame = animFrame ? 5 : 4;

                if (wave_loop_counter >= 6)
                {
                    player_state = PLAYER_STATE_WALK;
                    currentFrame = FRAME_FRONT_IDLE; 
                }
            }
            return; // Bloqueia motor de passos durante o aceno animado
        }
    }

    // Ativa o estado de aceno pelo botão R
    if (airship_state == AIRSHIP_OFF && move_rem == 0)
    {
        if (press & KEY_R) 
        {
            player_state = PLAYER_STATE_WAVING;
            animTimer = 0;
            animFrame = 0;
            wave_loop_counter = 0;
            currentFrame = 4; 
            return;
        }
    }

    playerUpdateDirection(held, press);

    // Motor de passos multi-substep (4x velocidade para nave)
    steps_this_frame = (airship_state != AIRSHIP_OFF) ? 4 : 1;

    for (p = 0; p < steps_this_frame; p++)
    {
        if(move_rem > 0)
        {
            isMoving = 1;
            switch(moveDir)
            {
                case DIR_UP:    cam_y -= STEP_SPEED; break;
                case DIR_DOWN:  cam_y += STEP_SPEED; break;
                case DIR_LEFT:  cam_x -= STEP_SPEED; break;
                case DIR_RIGHT: cam_x += STEP_SPEED; break;
            }
            move_rem -= STEP_SPEED;
        }
        else if(held & (KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT))
        {
            moveDir = playerDir;
            u8 is_blocked = 0;
            
            // Só executa colisão física contra cenário se estiver a pé
            if (airship_state == AIRSHIP_OFF) 
            {
                s16 px = (cam_x + 128) & 4095;
                s16 py = (cam_y + 128) & 4095;
                s16 nx = px;
                s16 ny = py;

                switch(moveDir)
                {
                    case DIR_UP:    ny = (py - STEP_SIZE) & 4095; break;
                    case DIR_DOWN:  ny = (py + STEP_SIZE) & 4095; break;
                    case DIR_LEFT:  nx = (px - STEP_SIZE) & 4095; break;
                    case DIR_RIGHT: nx = (px + STEP_SIZE) & 4095; break;
                }

                switch(moveDir)
                {
                    case DIR_UP:    is_blocked = isSolid((nx-4)&4095, (ny-4)&4095) || isSolid((nx+3)&4095, (ny-4)&4095); break;
                    case DIR_DOWN:  is_blocked = isSolid((nx-4)&4095, (ny+3)&4095) || isSolid((nx+3)&4095, (ny+3)&4095); break;
                    case DIR_LEFT:  is_blocked = isSolid((nx-4)&4095, (ny-4)&4095) || isSolid((nx-4)&4095, (ny+3)&4095); break;
                    case DIR_RIGHT: is_blocked = isSolid((nx+3)&4095, (ny-4)&4095) || isSolid((nx+3)&4095, (ny+3)&4095); break;
                }
            }

            if(!is_blocked)
            {
                isMoving = 1;
                move_rem = STEP_SIZE - STEP_SPEED;

                switch(moveDir)
                {
                    case DIR_UP:    cam_y -= STEP_SPEED; break;
                    case DIR_DOWN:  cam_y += STEP_SPEED; break;
                    case DIR_LEFT:  cam_x -= STEP_SPEED; break;
                    case DIR_RIGHT: cam_x += STEP_SPEED; break;
                }
            }
            else
            {
                break;
            }
        }
    }

    // Wrap das coordenadas do mapa toroidal (4096 x 4096)
    while(cam_x < 0)     cam_x += 4096;
    while(cam_x >= 4096) cam_x -= 4096;
    while(cam_y < 0)     cam_y += 4096;
    while(cam_y >= 4096) cam_y -= 4096;

    if(player_visible)
    {
        playerUpdateAnim();
        s16 player_x = (cam_x + 128) & 4095;
        s16 player_y = (cam_y + 128) & 4095;
        debugUpdateWramTiles(player_x, player_y);
    }
}

// =========================================================
// FLUSH VRAM
// =========================================================
void playerFlush(void)
{
    if(!player_visible) return;
    if(currentFrame == lastFrame) return;

    lastFrame = currentFrame;

    const t_metasprite* meta = current_player->metasprites[currentFrame];
    u8* sheet = current_player->tiles;

    u16 headTop = (u16)(meta[0].dtile) * 32;
    u16 headBot = headTop + (16 * 32);
    u16 bodyTop = (u16)(meta[1].dtile) * 32;
    u16 bodyBot = bodyTop + (16 * 32);

    dmaCopyVram(sheet + headTop, 0x6000, 64);
    dmaCopyVram(sheet + headBot, 0x6100, 64);
    dmaCopyVram(sheet + bodyTop, 0x6200, 64);
    dmaCopyVram(sheet + bodyBot, 0x6300, 64);
}

// =========================================================
// OAM DRAW
// =========================================================
void playerDraw(void)
{
    if(!player_visible)
    {
        oamSetEx(0, OBJ_SMALL, OBJ_HIDE);
        oamSetEx(4, OBJ_SMALL, OBJ_HIDE);
        return;
    }

    u8 screenX = 128 - 8;
    u8 screenY = 112 - 16;

    u8 visualDir = isMoving ? moveDir : playerDir;
    u8 flipH = (visualDir == DIR_RIGHT) ? 1 : 0;

    if (player_state == PLAYER_STATE_WAVING)
    {
        flipH = 0; // Trava sprite olhando para frente ao acenar
    }

    oamSet(0, screenX, screenY,      2, flipH, 0, 0,  8);
    oamSetEx(0, OBJ_SMALL, OBJ_SHOW);

    oamSet(4, screenX, screenY + 16, 2, flipH, 0, 32, 8);
    oamSetEx(4, OBJ_SMALL, OBJ_SHOW);
}