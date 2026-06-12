#ifndef COMMANDS_H
#define COMMANDS_H
#include <snes.h>


enum
{
    CMD_ATTACK,
    CMD_ITEMS,
    CMD_BAND,
    CMD_DEFEND,
    CMD_SWAPROWS,
    CMD_EQUIP,
    CMD_AIM,
    CMD_ANALYZE,
    CMD_AWAKEN,
    CMD_BARDSONG,
    CMD_BIGTHROW,
    CMD_BLACK_MAGIC,
    CMD_BLUFF,
    CMD_BLESS,
    CMD_BLESSING,
    CMD_CEASECOVER,
    CMD_CHAKRA,
    CMD_COVER,
    CMD_COVERCOUNTER,
    CMD_DANCE,
    CMD_DUALCAST,
    CMD_ESCAPE,
    CMD_FOCUS,
    CMD_GILTOSS,
    CMD_HUMANKITE,
    CMD_ILLUSIONS,
    CMD_JIVE,
    CMD_JUMP,
    CMD_KICK,
    CMD_MUG,
    CMD_NINJUTSU,
    CMD_PIERCINGSIGHT,
    CMD_PRAY,
    CMD_PRESSURE,
    CMD_RISKSTRIKE,
    CMD_SALVE,
    CMD_SHURIKEN,
    CMD_STEAL,
    CMD_SUMMON,
    CMD_TAUNT,
    CMD_TENKETSU,
    CMD_THROW,
    CMD_WHITE_MAGIC,

    CMD_COUNT
};

enum
{
    SUBMENU_NONE,

    SUBMENU_ITEMS,
    SUBMENU_EQUIPS,
    SUBMENU_BAND,

    SUBMENU_WHITE_MAGIC,
    SUBMENU_BLACK_MAGIC,
    SUBMENU_SUMMON,

    SUBMENU_NINJUTSU,
    SUBMENU_BARDSONG
};

typedef struct
{
    const char* name;
    u8 submenuId;
} CommandDef;

extern const CommandDef commandTable[CMD_COUNT];

#endif