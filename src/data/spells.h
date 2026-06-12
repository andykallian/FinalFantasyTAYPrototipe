#ifndef SPELLS_H
#define SPELLS_H

#include <snes.h>

/* ===================================================== */
/* MENUS                                                 */
/* ===================================================== */

#define SPELL_MENU_WHITE   0
#define SPELL_MENU_BLACK   1
#define SPELL_MENU_SUMMON  2
#define SPELL_MENU_NINJA   3

/* ===================================================== */
/* TARGETS                                               */
/* ===================================================== */

#define TARGET_SELF            0
#define TARGET_ALLY            1
#define TARGET_ALL_ALLIES      2
#define TARGET_ENEMY           3
#define TARGET_ALL_ENEMIES     4

/* ===================================================== */
/* EFFECTS                                               */
/* ===================================================== */

#define SPELL_FX_NONE             0

#define SPELL_FX_HEAL_HP          1
#define SPELL_FX_REVIVE           2
#define SPELL_FX_FULL_REVIVE      3

#define SPELL_FX_BUFF_STATUS      4
#define SPELL_FX_INFLICT_STATUS   5
#define SPELL_FX_CURE_STATUS      6

#define SPELL_FX_SCAN             7
#define SPELL_FX_SIGHT            8
#define SPELL_FX_TELEPORT         9

#define SPELL_FX_DAMAGE_HOLY      10

#define SPELL_FX_DISPEL           11

/* ===================================================== */
/* WHITE MAGIC IDS                                       */
/* ===================================================== */

enum
{
    SPELL_CURE,
    SPELL_CURA,
    SPELL_CURAGA,
    SPELL_CURAJA,

    SPELL_HASTE,
    SPELL_SLOW,
    SPELL_BLINK,
    SPELL_FLOAT,
    SPELL_REFLECT,

    SPELL_TELEPORT,

    SPELL_ESUNA,
    SPELL_LIBRA,
    SPELL_SIGHT,

    SPELL_HOLD,
    SPELL_SILENCE,

    SPELL_PROTECT,
    SPELL_SHELL,

    SPELL_BERSERK,
    SPELL_CONFUSE,
    SPELL_MINI,

    SPELL_DISPEL,

    SPELL_RAISE,
    SPELL_ARISE,

    SPELL_HOLY,

    SPELL_COUNT
};

typedef struct
{
    const char* name;

    u8 mpCost;

    u8 menuType;

    u8 effect;

    u16 power;

    u16 statusMask;

    u8 targetType;

} SpellDef;

extern const SpellDef spellTable[SPELL_COUNT];

#endif