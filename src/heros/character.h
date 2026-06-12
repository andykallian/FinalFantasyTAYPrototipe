#ifndef CHARACTER_H
#define CHARACTER_H

#include <snes.h>
#include "../player.h"

#define MAX_SPELLS 32

typedef struct
{
    u16 hp;
    u16 mp;

    u8 strength;
    u8 speed;
    u8 stamina;
    u8 intelligence;
    u8 spirit;

} Stats;

typedef struct
{
    u8 level;

    u16 hp;
    u16 mp;

    u8 strength;
    u8 speed;
    u8 stamina;
    u8 intelligence;
    u8 spirit;

} GrowthEntry;

typedef struct
{
    u8  level;
    u16 spellId;
} LearnSpell;

typedef struct
{
    const PlayerDef* def;

    u8  level;
    u32 exp;

    Stats stats;

    u16 currentHp;
    u16 currentMp;

    u16 rightHand;
    u16 leftHand;

    u16 head;
    u16 body;
    u16 arms;

    u16 command1;
    u16 command2;
    u16 command3;

    u8  spellCount;
    u16 spells[MAX_SPELLS];

} Character;

void characterSetLevel(
    Character* character,
    const GrowthEntry* growthTable,
    u16 growthCount,
    u8 level
);

#endif