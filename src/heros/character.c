#include "character.h"

void characterSetLevel(
    Character* character,
    const GrowthEntry* growthTable,
    u16 growthCount,
    u8 level
)
{
    const GrowthEntry* g;
    u16 i;

    if(level > 99)
        level = 99;

    /* começa usando a primeira entrada da tabela */
    g = &growthTable[0];

    /* procura o maior marco <= level */
    for(i = 0; i < growthCount; i++)
    {
        if(growthTable[i].level <= level)
            g = &growthTable[i];
        else
            break;
    }

    character->level = level;

    character->stats.hp = g->hp;
    character->stats.mp = g->mp;

    character->stats.strength     = g->strength;
    character->stats.speed        = g->speed;
    character->stats.stamina      = g->stamina;
    character->stats.intelligence = g->intelligence;
    character->stats.spirit       = g->spirit;

    character->currentHp = g->hp;
    character->currentMp = g->mp;
}