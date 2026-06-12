#include <snes.h>
#include "../player.h"
#include "res/gfx/Ceodore_meta.inc"

const PlayerDef PLAYER_CEODORE =
{
    Ceodore_metasprites,
    (u8*)&ceodore_tiles,
    (u8*)&ceodore_pal,
    128,
    32
};