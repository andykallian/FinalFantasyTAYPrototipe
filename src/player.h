#ifndef PLAYER_H
#define PLAYER_H

#include <snes.h>

#define DIR_DOWN  0
#define DIR_UP    1
#define DIR_LEFT  2
#define DIR_RIGHT 3

#define FRAME_FRONT_IDLE       0
#define FRAME_FRONT_WALK       1
#define FRAME_BACK_IDLE        2
#define FRAME_BACK_WALK        3
#define FRAME_SIDE_IDLE_LEFT   8
#define FRAME_SIDE_WALK1_LEFT  9
#define FRAME_SIDE_WALK2_LEFT  10
#define FRAME_SIDE_IDLE_RIGHT  8
#define FRAME_SIDE_WALK1_RIGHT 9
#define FRAME_SIDE_WALK2_RIGHT 10

typedef enum
{
    PLAYER_STATE_WALK,
    PLAYER_STATE_AIRSHIP,
    PLAYER_STATE_WAVING
} PlayerState;

extern PlayerState player_state;
extern u8          player_boarding_done;

typedef struct
{
    const t_metasprite** metasprites;
    u8* tiles;
    u8* palette;
    u8                   pal_offset;
    u8                   pal_size;
} PlayerDef;

void playerInit(s16 startX, s16 startY, const PlayerDef* def);
void playerSetDef(const PlayerDef* def);
void playerUpdate(void);
void playerDraw(void);
void playerFlush(void);

#endif