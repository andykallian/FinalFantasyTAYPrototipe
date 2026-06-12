#include "spells.h"
#include "status.h"


const SpellDef spellTable[SPELL_COUNT] = 
{
    [SPELL_CURE] =
    {
        "Cure",
        3,
        SPELL_MENU_WHITE,
        SPELL_FX_HEAL_HP,
        100,
        0,
        TARGET_ALLY
    },

    [SPELL_CURA] =
    {
        "Cura",
        9,
        SPELL_MENU_WHITE,
        SPELL_FX_HEAL_HP,
        400,
        0,
        TARGET_ALLY
    },

    [SPELL_CURAGA] =
    {
        "Curaga",
        18,
        SPELL_MENU_WHITE,
        SPELL_FX_HEAL_HP,
        1200,
        0,
        TARGET_ALLY
    },

    [SPELL_CURAJA] =
    {
        "Curaja",
        40,
        SPELL_MENU_WHITE,
        SPELL_FX_HEAL_HP,
        9999,
        0,
        TARGET_ALLY
    },

        [SPELL_HASTE] =
    {
        "Haste",
        25,
        SPELL_MENU_WHITE,
        SPELL_FX_BUFF_STATUS,
        0,
        STATUS_HASTE,
        TARGET_ALLY
    },

    [SPELL_PROTECT] =
    {
        "Protect",
        9,
        SPELL_MENU_WHITE,
        SPELL_FX_BUFF_STATUS,
        0,
        STATUS_PROTECT,
        TARGET_ALLY
    },

    [SPELL_SHELL] =
    {
        "Shell",
        10,
        SPELL_MENU_WHITE,
        SPELL_FX_BUFF_STATUS,
        0,
        STATUS_SHELL,
        TARGET_ALLY
    },

    [SPELL_REFLECT] =
    {
        "Reflect",
        30,
        SPELL_MENU_WHITE,
        SPELL_FX_BUFF_STATUS,
        0,
        STATUS_REFLECT,
        TARGET_ALLY
    },

    [SPELL_FLOAT] =
    {
        "Float",
        8,
        SPELL_MENU_WHITE,
        SPELL_FX_BUFF_STATUS,
        0,
        STATUS_FLOAT,
        TARGET_ALLY
    },

        [SPELL_SLOW] =
    {
        "Slow",
        14,
        SPELL_MENU_WHITE,
        SPELL_FX_INFLICT_STATUS,
        0,
        STATUS_SLOW,
        TARGET_ENEMY
    },

    [SPELL_HOLD] =
    {
        "Hold",
        5,
        SPELL_MENU_WHITE,
        SPELL_FX_INFLICT_STATUS,
        0,
        STATUS_HOLD,
        TARGET_ENEMY
    },

    [SPELL_SILENCE] =
    {
        "Silence",
        6,
        SPELL_MENU_WHITE,
        SPELL_FX_INFLICT_STATUS,
        0,
        STATUS_SILENCE,
        TARGET_ENEMY
    },

    [SPELL_BERSERK] =
    {
        "Berserk",
        18,
        SPELL_MENU_WHITE,
        SPELL_FX_INFLICT_STATUS,
        0,
        STATUS_BERSERK,
        TARGET_ENEMY
    },

    [SPELL_CONFUSE] =
    {
        "Confuse",
        10,
        SPELL_MENU_WHITE,
        SPELL_FX_INFLICT_STATUS,
        0,
        STATUS_CONFUSE,
        TARGET_ENEMY
    },

    [SPELL_MINI] =
    {
        "Mini",
        6,
        SPELL_MENU_WHITE,
        SPELL_FX_INFLICT_STATUS,
        0,
        STATUS_MINI,
        TARGET_ENEMY
    },

        [SPELL_LIBRA] =
    {
        "Libra",
        1,
        SPELL_MENU_WHITE,
        SPELL_FX_SCAN,
        0,
        0,
        TARGET_ENEMY
    },

    [SPELL_SIGHT] =
    {
        "Sight",
        2,
        SPELL_MENU_WHITE,
        SPELL_FX_SIGHT,
        0,
        0,
        TARGET_SELF
    },

    [SPELL_TELEPORT] =
    {
        "Teleport",
        10,
        SPELL_MENU_WHITE,
        SPELL_FX_TELEPORT,
        0,
        0,
        TARGET_SELF
    },

        [SPELL_ESUNA] =
    {
        "Esuna",
        20,
        SPELL_MENU_WHITE,
        SPELL_FX_CURE_STATUS,
        0,

        STATUS_POISON |
        STATUS_SILENCE |
        STATUS_BLIND |
        STATUS_SLEEP |
        STATUS_CONFUSE |
        STATUS_HOLD |
        STATUS_MINI |
        STATUS_TOAD,

        TARGET_ALLY
    },

        [SPELL_RAISE] =
    {
        "Raise",
        8,
        SPELL_MENU_WHITE,
        SPELL_FX_REVIVE,
        0,
        0,
        TARGET_ALLY
    },

    [SPELL_ARISE] =
    {
        "Arise",
        52,
        SPELL_MENU_WHITE,
        SPELL_FX_FULL_REVIVE,
        0,
        0,
        TARGET_ALLY
    },

        [SPELL_HOLY] =
    {
        "Holy",
        46,
        SPELL_MENU_WHITE,
        SPELL_FX_DAMAGE_HOLY,
        2500,
        0,
        TARGET_ENEMY
    }
};