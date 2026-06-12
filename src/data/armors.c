#include "armors.h"

/* =========================================================
   Atalhos locais para equip_mask (legibilidade)
   ========================================================= */
#define _HEAVY   EQUIP_HEAVY
#define _DOLLS   (EQUIP_CALCA|EQUIP_BRINA)
#define _ALL     EQUIP_EVERYONE
#define _NODOLL  EQUIP_NO_DOLLS

/* grupos femininos leves */
#define _FEMLIGHT (EQUIP_ROSA|EQUIP_RYDIA|EQUIP_POROM|EQUIP_LUCA|\
                   EQUIP_URSULA|EQUIP_LEONORA|EQUIP_IZAYOI|EQUIP_HARLEY)

/* magia / clerigos */
#define _MAGE_GRP (EQUIP_CECIL|EQUIP_CEODORE|EQUIP_ROSA|EQUIP_RYDIA|\
                   EQUIP_PALOM|EQUIP_POROM|EQUIP_LEONORA|EQUIP_HARLEY|\
                   EQUIP_GOLBEZ|EQUIP_CALCA|EQUIP_BRINA)

/* luvas pesadas */
#define _GLOVE_H  (EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN|EQUIP_EDGE|\
                   EQUIP_CID|EQUIP_LUCA|EQUIP_GEKKOU|EQUIP_ZANGETSU|\
                   EQUIP_IZAYOI|EQUIP_TSUKINOWA|EQUIP_GOLBEZ)

/* robes */
#define _ROBE_GRP (EQUIP_CECIL|EQUIP_CEODORE|EQUIP_ROSA|EQUIP_RYDIA|\
                   EQUIP_PALOM|EQUIP_POROM|EQUIP_LEONORA|EQUIP_HARLEY|\
                   EQUIP_GOLBEZ)

/* ninja */
#define _NINJA_G  (EQUIP_EDGE|EQUIP_ZANGETSU|EQUIP_GEKKOU|\
                   EQUIP_IZAYOI|EQUIP_TSUKINOWA)

/* =========================================================
   Atalhos para status_res comuns
   ========================================================= */
#define _SALL     SRES_ALL
#define _SELEM    0  /* sem status res, apenas elem res       */

/* =========================================================
   armor_table
   Ordem dos campos:
     name, atype, def, mdef, evd, mevd,
     elem_res, elem_absorb, flags, status_res, equip_mask,
     buy, sell
   ========================================================= */
const ArmorDef armor_table[ARMOR_COUNT] = {

    /* =======================================================
       ARMLETS
       ======================================================= */

    /* 0 - Iron Armlet */
    { "Iron Armlet",
      ATYPE_ARMLET, 2, 1, 0, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_ROSA|EQUIP_RYDIA|EQUIP_EDGE|EQUIP_YANG|EQUIP_PALOM|EQUIP_POROM|
      EQUIP_EDWARD|EQUIP_URSULA|EQUIP_LEONORA|EQUIP_GEKKOU|EQUIP_ZANGETSU|
      EQUIP_IZAYOI|EQUIP_TSUKINOWA|EQUIP_HARLEY|EQUIP_GOLBEZ|EQUIP_CALCA|EQUIP_BRINA,
      100, 50 },

    /* 1 - Silver Armlet */
    { "Silver Armlet",
      ATYPE_ARMLET, 4, 4, 0, 4,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_GHOUL, SRES_NONE,
      EQUIP_ROSA|EQUIP_RYDIA|EQUIP_EDGE|EQUIP_YANG|EQUIP_PALOM|EQUIP_POROM|
      EQUIP_EDWARD|EQUIP_URSULA|EQUIP_LEONORA|EQUIP_GEKKOU|EQUIP_ZANGETSU|
      EQUIP_IZAYOI|EQUIP_TSUKINOWA|EQUIP_HARLEY|EQUIP_GOLBEZ|EQUIP_CALCA|EQUIP_BRINA,
      650, 325 },

    /* 2 - Diamond Armlet */
    { "Diamond Armlet",
      ATYPE_ARMLET, 6, 8, 0, 6,
      ELEM_THUNDER, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_ROSA|EQUIP_RYDIA|EQUIP_EDGE|EQUIP_YANG|EQUIP_PALOM|EQUIP_POROM|
      EQUIP_EDWARD|EQUIP_URSULA|EQUIP_LEONORA|EQUIP_GEKKOU|EQUIP_ZANGETSU|
      EQUIP_IZAYOI|EQUIP_TSUKINOWA|EQUIP_HARLEY|EQUIP_GOLBEZ|EQUIP_CALCA|EQUIP_BRINA,
      0xFFFF, 0 },

    /* 3 - Power Armlet */
    { "Power Armlet",
      ATYPE_ARMLET, 2, 2, 0, 2,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN|EQUIP_RYDIA|EQUIP_EDGE|EQUIP_CID|
      EQUIP_YANG|EQUIP_LUCA|EQUIP_URSULA|EQUIP_GEKKOU|EQUIP_ZANGETSU|
      EQUIP_IZAYOI|EQUIP_TSUKINOWA|EQUIP_GOLBEZ,
      0xFFFF, 0 },

    /* 4 - Rune Armlet */
    { "Rune Armlet",
      ATYPE_ARMLET, 5, 8, 0, 8,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_SILENCE,
      EQUIP_ROSA|EQUIP_RYDIA|EQUIP_EDGE|EQUIP_YANG|EQUIP_PALOM|EQUIP_POROM|
      EQUIP_EDWARD|EQUIP_URSULA|EQUIP_LEONORA|EQUIP_GEKKOU|EQUIP_ZANGETSU|
      EQUIP_IZAYOI|EQUIP_TSUKINOWA|EQUIP_HARLEY|EQUIP_GOLBEZ|EQUIP_CALCA|EQUIP_BRINA,
      2000, 1000 },

    /* 5 - Hyper Wrist */
    { "Hyper Wrist",
      ATYPE_ARMLET, 4, 3, 0, 3,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN|EQUIP_RYDIA|EQUIP_EDGE|EQUIP_CID|
      EQUIP_YANG|EQUIP_LUCA|EQUIP_URSULA|EQUIP_GEKKOU|EQUIP_ZANGETSU|
      EQUIP_IZAYOI|EQUIP_TSUKINOWA|EQUIP_GOLBEZ,
      0xFFFF, 0 },

    /* 6 - Treasure Hunter */
    { "Treasure Hunter",
      ATYPE_ARMLET, 2, 1, 0, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 7 - Treasure Hunter V2 */
    { "Treasure Hunter V2",
      ATYPE_ARMLET, 3, 2, 3, 2,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 8 - Single Star */
    { "Single Star",
      ATYPE_ARMLET, 3, 5, -5, 5,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 9 - Talisman */
    { "Talisman",
      ATYPE_ARMLET, 2, 12, -5, 13,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_ROSA|EQUIP_RYDIA|EQUIP_EDGE|EQUIP_YANG|EQUIP_PALOM|EQUIP_POROM|
      EQUIP_EDWARD|EQUIP_URSULA|EQUIP_LEONORA|EQUIP_GEKKOU|EQUIP_ZANGETSU|
      EQUIP_IZAYOI|EQUIP_TSUKINOWA|EQUIP_HARLEY|EQUIP_GOLBEZ|EQUIP_CALCA|EQUIP_BRINA,
      0xFFFF, 0 },

    /* 10 - Ruby Ring */
    { "Ruby Ring",
      ATYPE_ARMLET, 0, 3, 0, 2,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_PIG,
      _ALL, 1000, 500 },

    /* 11 - Flan Ring */
    { "Flan Ring",
      ATYPE_ARMLET, 7, 0, 2, -10,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_FLAN, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 12 - Level Band */
    { "Level Band",
      ATYPE_ARMLET, 1, 0, -10, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 13 - Level Band V2 */
    { "Level Band V2",
      ATYPE_ARMLET, 3, 2, -7, 2,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 14 - Gil Band */
    { "Gil Band",
      ATYPE_ARMLET, 4, 1, -6, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 15 - Gil Band V2 */
    { "Gil Band V2",
      ATYPE_ARMLET, 5, 5, -5, 5,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 16 - Rare Band */
    { "Rare Band",
      ATYPE_ARMLET, 3, 1, -1, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 17 - Rare Band V2 */
    { "Rare Band V2",
      ATYPE_ARMLET, 5, 3, 0, 3,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 18 - Economical Ring */
    { "Economical Ring",
      ATYPE_ARMLET, 2, 2, -5, 2,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 19 - Cursed Ring */
    { "Cursed Ring",
      ATYPE_ARMLET, 0, 0, -10, -5,
      ELEM_NONE, ELEM_NONE, AFLAG_CURSED|AFLAG_ALL_ABSORB, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 20 - Rapid Ring */
    { "Rapid Ring",
      ATYPE_ARMLET, 4, 4, -5, 4,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 21 - Rapid Ring V2 */
    { "Rapid Ring V2",
      ATYPE_ARMLET, 5, 5, 0, 10,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 22 - Sprint Ring */
    { "Sprint Ring",
      ATYPE_ARMLET, 1, 5, 5, 15,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 23 - Limit Ring */
    { "Limit Ring",
      ATYPE_ARMLET, 3, 2, -7, 2,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 24 - Taunt Ring */
    { "Taunt Ring",
      ATYPE_ARMLET, 5, 5, -5, 5,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 25 - Rear Ring */
    { "Rear Ring",
      ATYPE_ARMLET, 2, 2, -8, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 26 - Twin Stars */
    { "Twin Stars",
      ATYPE_ARMLET, 4, 6, -5, 6,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 27 - Crystal Ring */
    { "Crystal Ring",
      ATYPE_ARMLET, 20, 12, 5, 10,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_DRAGON, SRES_CONFUSE|SRES_SLEEP,
      _ALL, 0xFFFF, 0 },

    /* 28 - Protect Ring */
    { "Protect Ring",
      ATYPE_ARMLET, 10, 12, 5, 10,
      ELEM_FIRE|ELEM_ICE|ELEM_THUNDER|ELEM_HOLY|ELEM_DARK|ELEM_WIND|ELEM_WATER|ELEM_EARTH,
      ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* =======================================================
       ARMOR PESADA
       ======================================================= */

    /* 29 - Bronze Armor */
    { "Bronze Armor",
      ATYPE_ARMOR, 4, 1, -10, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 600, 300 },

    /* 30 - Iron Armor */
    { "Iron Armor",
      ATYPE_ARMOR, 7, 2, -10, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 1000, 500 },

    /* 31 - Chainmail */
    { "Chainmail",
      ATYPE_ARMOR, 10, 3, -10, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 2200, 1100 },

    /* 32 - Horned Armor */
    { "Horned Armor",
      ATYPE_ARMOR, 12, 2, -10, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 0xFFFF, 0 },

    /* 33 - Mythril Armor */
    { "Mythril Armor",
      ATYPE_ARMOR, 13, 4, -10, 2,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_GHOUL, SRES_NONE,
      _HEAVY, 17000, 8500 },

    /* 34 - Knight's Armor */
    { "Knight's Armor",
      ATYPE_ARMOR, 11, 3, -10, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_UNDEAD, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN,
      0xFFFF, 0 },

    /* 35 - Plate Armor */
    { "Plate Armor",
      ATYPE_ARMOR, 15, 2, -20, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 5000, 2500 },

    /* 36 - Flame Mail */
    { "Flame Mail",
      ATYPE_ARMOR, 15, 4, -10, 2,
      ELEM_ICE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 0xFFFF, 0 },

    /* 37 - Ice Mail */
    { "Ice Mail",
      ATYPE_ARMOR, 17, 4, -10, 2,
      ELEM_FIRE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 0xFFFF, 0 },

    /* 38 - Diamond Armor */
    { "Diamond Armor",
      ATYPE_ARMOR, 19, 4, -10, 2,
      ELEM_THUNDER, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 0xFFFF, 0 },

    /* 39 - Bronze Breastplate */
    { "Bronze Breastplate",
      ATYPE_ARMOR, 4, 2, 5, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _NODOLL, 450, 225 },

    /* 40 - Silver Breastplate */
    { "Silver Breastplate",
      ATYPE_ARMOR, 7, 4, 5, 2,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_GHOUL, SRES_NONE,
      _NODOLL, 2000, 1000 },

    /* 41 - Bone Mail */
    { "Bone Mail",
      ATYPE_ARMOR, 18, 2, -10, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_UNDEAD, SRES_POISON,
      _HEAVY, 37500, 18750 },

    /* 42 - Genji Armor */
    { "Genji Armor",
      ATYPE_ARMOR, 21, 7, -10, 4,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN|EQUIP_EDGE|EQUIP_CID|EQUIP_LUCA|
      EQUIP_ZANGETSU|EQUIP_GEKKOU|EQUIP_IZAYOI|EQUIP_TSUKINOWA|EQUIP_GOLBEZ,
      0xFFFF, 0 },

    /* 43 - Dragon Mail */
    { "Dragon Mail",
      ATYPE_ARMOR, 23, 8, -10, 5,
      ELEM_FIRE|ELEM_ICE|ELEM_THUNDER|ELEM_HOLY|ELEM_DARK|ELEM_WIND|ELEM_WATER|ELEM_EARTH,
      ELEM_NONE, AFLAG_ANTI_DRAGON, SRES_NONE,
      _HEAVY, 0xFFFF, 0 },

    /* 44 - Crystal Mail */
    { "Crystal Mail",
      ATYPE_ARMOR, 25, 10, -10, 5,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_UNDEAD,
      SRES_PIG|SRES_MINI|SRES_TOAD|SRES_BERSERK,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN|EQUIP_GOLBEZ,
      0xFFFF, 0 },

    /* 45 - Lunar Mail */
    { "Lunar Mail",
      ATYPE_ARMOR, 30, 12, -10, 8,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE,
      SRES_POISON|SRES_SLEEP|SRES_CONFUSE|SRES_PETRIFY|SRES_DEATH,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_GOLBEZ,
      0xFFFF, 0 },

    /* 46 - Blue Armor */
    { "Blue Armor",
      ATYPE_ARMOR, 45, 25, -10, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_DRAGON|AFLAG_ANTI_MECH|AFLAG_ANTI_GIANT, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN|EQUIP_EDGE|EQUIP_CID|EQUIP_YANG|
      EQUIP_PALOM|EQUIP_EDWARD|EQUIP_ZANGETSU|EQUIP_GEKKOU|EQUIP_TSUKINOWA|EQUIP_GOLBEZ,
      0xFFFF, 0 },

    /* 47 - Pink Armor */
    { "Pink Armor",
      ATYPE_ARMOR, 25, 10, 99, 30,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, _SALL,
      _FEMLIGHT, 0xFFFF, 0 },

    /* 48 - Adamant Armor */
    { "Adamant Armor",
      ATYPE_ARMOR, 50, 20, -10, 13,
      ELEM_FIRE, ELEM_NONE, AFLAG_NONE,
      SRES_PETRIFY|SRES_PIG|SRES_POISON,
      _NODOLL, 0xFFFF, 0 },

    /* =======================================================
       CLOTHES
       ======================================================= */

    /* 49 - Training Garb */
    { "Training Garb",
      ATYPE_CLOTHES, 9, 2, -5, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_KAIN, 0xFFFF, 0 },

    /* 50 - Clothing */
    { "Clothing",
      ATYPE_CLOTHES, 1, 0, 0, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _NODOLL, 0, 0 },

    /* 51 - Leather Clothing */
    { "Leather Clothing",
      ATYPE_CLOTHES, 2, 1, 0, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _NODOLL, 200, 100 },

    /* 52 - Boy's Clothes */
    { "Boy's Clothes",
      ATYPE_CLOTHES, 3, 3, 0, 4,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE,
      SRES_PIG|SRES_MINI|SRES_TOAD,
      EQUIP_CALCA, 0xFFFF, 0 },

    /* 53 - Girl's Clothes */
    { "Girl's Clothes",
      ATYPE_CLOTHES, 3, 3, 0, 4,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE,
      SRES_PIG|SRES_MINI|SRES_TOAD,
      EQUIP_BRINA, 0xFFFF, 0 },

    /* 54 - Angel's Clothes */
    { "Angel's Clothes",
      ATYPE_CLOTHES, 5, 5, 5, 5,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE,
      SRES_PIG|SRES_TOAD|SRES_MINI,
      _DOLLS, 0xFFFF, 0 },

    /* 55 - Clown's Clothes */
    { "Clown's Clothes",
      ATYPE_CLOTHES, 3, 3, 20, 3,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE,
      SRES_PIG|SRES_TOAD|SRES_MINI,
      _DOLLS, 0xFFFF, 0 },

    /* 56 - Mage's Clothes */
    { "Mage's Clothes",
      ATYPE_CLOTHES, 5, 5, 5, 5,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _DOLLS, 0xFFFF, 0 },

    /* 57 - Warrior's Clothes */
    { "Warrior's Clothes",
      ATYPE_CLOTHES, 10, 0, -5, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE,
      SRES_PIG|SRES_TOAD|SRES_MINI,
      _DOLLS, 0xFFFF, 0 },

    /* 58 - Kenpo Gi */
    { "Kenpo Gi",
      ATYPE_CLOTHES, 5, 2, 10, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _NODOLL, 4000, 2000 },

    /* 59 - Black Belt Gi */
    { "Black Belt Gi",
      ATYPE_CLOTHES, 10, 4, 20, 2,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _NODOLL, 0xFFFF, 0 },

    /* 60 - Power Sash */
    { "Power Sash",
      ATYPE_CLOTHES, 15, 0, 0, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _NODOLL, 0xFFFF, 0 },

    /* 61 - Minerva Bustier */
    { "Minerva Bustier",
      ATYPE_CLOTHES, 20, 5, 30, 5,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_PARALYZE,
      _FEMLIGHT, 0xFFFF, 0 },

    /* 62 - Rose Twine Dress */
    { "Rose Twine Dress",
      ATYPE_CLOTHES, 9, 5, 25, 5,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _FEMLIGHT, 0xFFFF, 0 },

    /* 63 - Foot Ninja Gear */
    { "Foot Ninja Gear",
      ATYPE_CLOTHES, 2, 2, 10, 2,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _NODOLL, 480, 240 },

    /* 64 - Shinobi Gear */
    { "Shinobi Gear",
      ATYPE_CLOTHES, 4, 3, 50, 3,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _NODOLL, 3500, 1750 },

    /* 65 - Mist Wrap */
    { "Mist Wrap",
      ATYPE_CLOTHES, 8, 8, 35, 10,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_POISON,
      _NODOLL, 0xFFFF, 0 },

    /* 66 - Queen's Tights */
    { "Queen's Tights",
      ATYPE_CLOTHES, 5, 5, 15, 5,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE,
      SRES_PIG|SRES_PARALYZE|SRES_CONFUSE,
      EQUIP_ROSA|EQUIP_RYDIA|EQUIP_POROM|EQUIP_URSULA|EQUIP_LEONORA|
      EQUIP_IZAYOI|EQUIP_HARLEY,
      8800, 4400 },

    /* 67 - Bard's Tunic */
    { "Bard's Tunic",
      ATYPE_CLOTHES, 2, 1, 0, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_SILENCE,
      _NODOLL, 70, 35 },

    /* 68 - Final Outfit */
    { "Final Outfit",
      ATYPE_CLOTHES, 30, 15, 30, 15,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE,
      SRES_MINI|SRES_PIG|SRES_TOAD,
      _DOLLS, 0xFFFF, 0 },

    /* 69 - Fire Scarf */
    { "Fire Scarf",
      ATYPE_CLOTHES, 20, 10, 50, 10,
      ELEM_NONE, ELEM_FIRE, AFLAG_ABSORB_ELEM, SRES_NONE,
      _NINJA_G, 0xFFFF, 0 },

    /* 70 - Brave Suit */
    { "Brave Suit",
      ATYPE_CLOTHES, 22, 8, 25, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_CURSE,
      EQUIP_EDGE|EQUIP_YANG|EQUIP_EDWARD|EQUIP_URSULA|EQUIP_ZANGETSU|
      EQUIP_GEKKOU|EQUIP_IZAYOI|EQUIP_TSUKINOWA|EQUIP_HARLEY,
      0xFFFF, 0 },

    /* 71 - Red Jacket */
    { "Red Jacket",
      ATYPE_CLOTHES, 21, 12, 20, 4,
      ELEM_FIRE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_EDGE|EQUIP_YANG|EQUIP_EDWARD|EQUIP_URSULA|EQUIP_ZANGETSU|
      EQUIP_GEKKOU|EQUIP_IZAYOI|EQUIP_TSUKINOWA|EQUIP_HARLEY,
      0xFFFF, 0 },

    /* 72 - Black Garb */
    { "Black Garb",
      ATYPE_CLOTHES, 34, 15, 60, 7,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _NINJA_G, 0xFFFF, 0 },

    /* 73 - Phase Body */
    { "Phase Body",
      ATYPE_CLOTHES, 60, 30, 30, 15,
      ELEM_FIRE, ELEM_NONE, AFLAG_ANTI_MECH|AFLAG_ANTI_GIANT,
      SRES_POISON|SRES_PIG|SRES_MINI|SRES_FROG|SRES_PETRIFY,
      _DOLLS, 0xFFFF, 0 },

    /* =======================================================
       GLOVES
       ======================================================= */

    /* 74 - Iron Gloves */
    { "Iron Gloves",
      ATYPE_GLOVES, 2, 0, -10, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _GLOVE_H, 130, 65 },

    /* 75 - Mythril Gloves */
    { "Mythril Gloves",
      ATYPE_GLOVES, 6, 2, -10, 2,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_GHOUL, SRES_NONE,
      _GLOVE_H, 2000, 1000 },

    /* 76 - Bone Wrist */
    { "Bone Wrist",
      ATYPE_GLOVES, 7, 1, -10, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_UNDEAD, SRES_POISON,
      _GLOVE_H, 3800, 1900 },

    /* 77 - Gauntlets */
    { "Gauntlets",
      ATYPE_GLOVES, 5, 1, -10, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_UNDEAD, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN,
      0xFFFF, 0 },

    /* 78 - Diamond Gloves */
    { "Diamond Gloves",
      ATYPE_GLOVES, 7, 3, -10, 3,
      ELEM_THUNDER, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN|EQUIP_CID|EQUIP_LUCA|EQUIP_GOLBEZ,
      0xFFFF, 0 },

    /* 79 - Giant's Gloves */
    { "Giant's Gloves",
      ATYPE_GLOVES, 10, 0, -10, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_GIANT, SRES_MINI,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN|EQUIP_EDGE|EQUIP_CID|EQUIP_YANG|
      EQUIP_LUCA|EQUIP_URSULA|EQUIP_GEKKOU|EQUIP_ZANGETSU|EQUIP_IZAYOI|
      EQUIP_TSUKINOWA|EQUIP_GOLBEZ,
      0xFFFF, 0 },

    /* 80 - Queen's Gloves */
    { "Queen's Gloves",
      ATYPE_GLOVES, 2, 2, 0, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE,
      SRES_POISON|SRES_TOAD|SRES_PETRIFY,
      EQUIP_ROSA|EQUIP_RYDIA|EQUIP_POROM|EQUIP_LUCA|EQUIP_URSULA|
      EQUIP_LEONORA|EQUIP_IZAYOI|EQUIP_HARLEY,
      5800, 2900 },

    /* 81 - Genji Gloves */
    { "Genji Gloves",
      ATYPE_GLOVES, 8, 5, -10, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _GLOVE_H, 0xFFFF, 0 },

    /* 82 - Dragon Gloves */
    { "Dragon Gloves",
      ATYPE_GLOVES, 9, 6, -10, 3,
      ELEM_FIRE|ELEM_ICE|ELEM_THUNDER|ELEM_HOLY|ELEM_DARK|ELEM_WIND|ELEM_WATER|ELEM_EARTH,
      ELEM_NONE, AFLAG_ANTI_DRAGON, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN|EQUIP_CID|EQUIP_LUCA|EQUIP_GOLBEZ,
      0xFFFF, 0 },

    /* 83 - Crystal Gloves */
    { "Crystal Gloves",
      ATYPE_GLOVES, 10, 7, -10, 5,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_UNDEAD, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN|EQUIP_GOLBEZ,
      0xFFFF, 0 },

    /* 84 - Lunar Gloves */
    { "Lunar Gloves",
      ATYPE_GLOVES, 12, 9, -10, 5,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_GOLBEZ,
      0xFFFF, 0 },

    /* 85 - Phase Knuckle */
    { "Phase Knuckle",
      ATYPE_GLOVES, 20, 10, 0, 10,
      ELEM_THUNDER, ELEM_NONE, AFLAG_ANTI_MECH|AFLAG_ANTI_GIANT,
      SRES_PIG|SRES_MINI|SRES_FROG|SRES_BERSERK|SRES_SLEEP,
      _DOLLS, 0xFFFF, 0 },

    /* 86 - Adamant Gloves */
    { "Adamant Gloves",
      ATYPE_GLOVES, 20, 10, 10, 11,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE,
      SRES_SLEEP|SRES_PARALYZE|SRES_BERSERK,
      _NODOLL, 0xFFFF, 0 },

    /* =======================================================
       HATS
       ======================================================= */

    /* 87 - Turban */
    { "Turban",
      ATYPE_HAT, 6, 0, -10, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_KAIN, 0xFFFF, 0 },

    /* 88 - Leather Cap */
    { "Leather Cap",
      ATYPE_HAT, 1, 1, -5, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 100, 50 },

    /* 89 - Feathered Cap */
    { "Feathered Cap",
      ATYPE_HAT, 2, 3, -4, 3,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 330, 165 },

    /* 90 - Wizard's Hat */
    { "Wizard's Hat",
      ATYPE_HAT, 3, 5, -3, 5,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _MAGE_GRP, 700, 350 },

    /* 91 - Sage's Miter */
    { "Sage's Miter",
      ATYPE_HAT, 5, 7, -2, 7,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_UNDEAD, SRES_NONE,
      _MAGE_GRP, 2000, 1000 },

    /* 92 - Gold Hairpin */
    { "Gold Hairpin",
      ATYPE_HAT, 8, 10, 0, 9,
      ELEM_THUNDER, ELEM_NONE, AFLAG_ANTI_DRAGON, SRES_NONE,
      EQUIP_ROSA|EQUIP_RYDIA|EQUIP_POROM|EQUIP_LUCA|EQUIP_URSULA|
      EQUIP_LEONORA|EQUIP_IZAYOI|EQUIP_HARLEY|EQUIP_BRINA,
      0xFFFF, 0 },

    /* 93 - Headband */
    { "Headband",
      ATYPE_HAT, 2, 3, 0, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_CONFUSE,
      _ALL, 450, 225 },

    /* 94 - Circlet */
    { "Circlet",
      ATYPE_HAT, 4, 7, 0, 7,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _MAGE_GRP, 1500, 750 },

    /* 95 - Mystic Veil */
    { "Mystic Veil",
      ATYPE_HAT, 8, 8, -2, 8,
      ELEM_HOLY, ELEM_NONE, AFLAG_NONE, SRES_CURSE,
      EQUIP_ROSA|EQUIP_RYDIA|EQUIP_LUCA|EQUIP_URSULA|EQUIP_POROM|
      EQUIP_LEONORA|EQUIP_IZAYOI|EQUIP_HARLEY|EQUIP_BRINA,
      0xFFFF, 0 },

    /* 96 - Beret */
    { "Beret",
      ATYPE_HAT, 5, 4, 0, 4,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 1200, 600 },

    /* 97 - Green Beret */
    { "Green Beret",
      ATYPE_HAT, 3, 1, 2, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 98 - Black Cowl */
    { "Black Cowl",
      ATYPE_HAT, 7, 1, 4, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_SLEEP,
      _ALL, 0xFFFF, 0 },

    /* 99 - Goblin Mask */
    { "Goblin Mask",
      ATYPE_HAT, 7, 5, 0, 5,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_BLIND,
      _ALL, 0xFFFF, 0 },

    /* 100 - Queen's Mask */
    { "Queen's Mask",
      ATYPE_HAT, 1, 1, -5, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE,
      SRES_SILENCE|SRES_BLIND|SRES_MINI|SRES_BERSERK,
      EQUIP_ROSA|EQUIP_RYDIA|EQUIP_LUCA|EQUIP_URSULA|EQUIP_POROM|
      EQUIP_LEONORA|EQUIP_IZAYOI|EQUIP_HARLEY|EQUIP_BRINA,
      3500, 1750 },

    /* 101 - Officer's Hat */
    { "Officer's Hat",
      ATYPE_HAT, 7, 7, -3, 7,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* 102 - Red Cap */
    { "Red Cap",
      ATYPE_HAT, 10, 12, 2, 12,
      ELEM_FIRE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_EDGE|EQUIP_YANG|EQUIP_EDWARD|EQUIP_URSULA|EQUIP_ZANGETSU|
      EQUIP_GEKKOU|EQUIP_IZAYOI|EQUIP_TSUKINOWA|EQUIP_HARLEY,
      0xFFFF, 0 },

    /* 103 - White Tiger Mask */
    { "White Tiger Mask",
      ATYPE_HAT, 8, 3, 6, 3,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_EDGE|EQUIP_YANG|EQUIP_EDWARD|EQUIP_URSULA|EQUIP_ZANGETSU|
      EQUIP_GEKKOU|EQUIP_IZAYOI|EQUIP_TSUKINOWA|EQUIP_HARLEY,
      0xFFFF, 0 },

    /* 104 - Cat-Ear Hood */
    { "Cat-Ear Hood",
      ATYPE_HAT, 7, 18, 7, 16,
      ELEM_ICE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _MAGE_GRP, 0xFFFF, 0 },

    /* 105 - Hypno Crown */
    { "Hypno Crown",
      ATYPE_HAT, 7, 16, 6, 17,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE,
      SRES_PIG|SRES_MINI|SRES_TOAD,
      _MAGE_GRP, 0xFFFF, 0 },

    /* 106 - Chakra Band */
    { "Chakra Band",
      ATYPE_HAT, 5, 5, 0, 5,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE,
      SRES_POISON|SRES_BLIND|SRES_SILENCE|SRES_SLEEP,
      _ALL, 0xFFFF, 0 },

    /* 107 - Ribbon */
    { "Ribbon",
      ATYPE_HAT, 9, 12, 2, 12,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_MAGE, _SALL,
      _ALL, 0xFFFF, 0 },

    /* 108 - Glass Mask */
    { "Glass Mask",
      ATYPE_HAT, 30, 0, -10, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 0xFFFF, 0 },

    /* =======================================================
       HELMETS
       ======================================================= */

    /* 109 - Bronze Helm */
    { "Bronze Helm",
      ATYPE_HELMET, 3, 0, -10, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 150, 75 },

    /* 110 - Iron Helm */
    { "Iron Helm",
      ATYPE_HELMET, 5, 1, -10, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 800, 400 },

    /* 111 - Steel Helm */
    { "Steel Helm",
      ATYPE_HELMET, 7, 1, -10, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 2000, 1000 },

    /* 112 - Mythril Helm */
    { "Mythril Helm",
      ATYPE_HELMET, 8, 2, -10, 2,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_GHOUL, SRES_NONE,
      _HEAVY, 3000, 1500 },

    /* 113 - Horned Helmet */
    { "Horned Helmet",
      ATYPE_HELMET, 8, 1, -10, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 0xFFFF, 0 },

    /* 114 - Cross Helm */
    { "Cross Helm",
      ATYPE_HELMET, 9, 1, -10, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_BLIND,
      _HEAVY, 4200, 2100 },

    /* 115 - Diamond Helm */
    { "Diamond Helm",
      ATYPE_HELMET, 9, 2, -10, 2,
      ELEM_THUNDER, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 0xFFFF, 0 },

    /* 116 - Steel Headplate */
    { "Steel Headplate",
      ATYPE_HELMET, 4, 1, 0, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ALL, 750, 375 },

    /* 117 - Lustrous Helm */
    { "Lustrous Helm",
      ATYPE_HELMET, 7, 2, -10, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_UNDEAD, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN,
      0xFFFF, 0 },

    /* 118 - Genji Helm */
    { "Genji Helm",
      ATYPE_HELMET, 10, 8, -10, 3,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN|EQUIP_CID|EQUIP_EDGE|EQUIP_LUCA|
      EQUIP_ZANGETSU|EQUIP_GEKKOU|EQUIP_IZAYOI|EQUIP_TSUKINOWA|EQUIP_GOLBEZ,
      0xFFFF, 0 },

    /* 119 - Dragon Helm */
    { "Dragon Helm",
      ATYPE_HELMET, 11, 7, -10, 4,
      ELEM_FIRE|ELEM_ICE|ELEM_THUNDER|ELEM_HOLY|ELEM_DARK|ELEM_WIND|ELEM_WATER|ELEM_EARTH,
      ELEM_NONE, AFLAG_ANTI_DRAGON, SRES_NONE,
      _HEAVY, 0xFFFF, 0 },

    /* 120 - Crystal Helm */
    { "Crystal Helm",
      ATYPE_HELMET, 12, 8, -10, 5,
      ELEM_FIRE|ELEM_ICE|ELEM_THUNDER|ELEM_HOLY|ELEM_DARK|ELEM_WIND|ELEM_WATER|ELEM_EARTH,
      ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN|EQUIP_GOLBEZ,
      0xFFFF, 0 },

    /* 121 - Lunar Helm */
    { "Lunar Helm",
      ATYPE_HELMET, 14, 10, -10, 16,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_GOLBEZ,
      0xFFFF, 0 },

    /* 122 - Phase Helm */
    { "Phase Helm",
      ATYPE_HELMET, 25, 10, 10, 0,
      ELEM_ICE, ELEM_NONE, AFLAG_ANTI_MECH|AFLAG_ANTI_GIANT,
      SRES_BLIND|SRES_PIG|SRES_MINI|SRES_FROG|SRES_DEATH,
      _DOLLS, 0xFFFF, 0 },

    /* 123 - Adamant Helm */
    { "Adamant Helm",
      ATYPE_HELMET, 25, 10, 10, 11,
      ELEM_THUNDER, ELEM_NONE, AFLAG_NONE,
      SRES_BLIND|SRES_TOAD|SRES_DEATH,
      _NODOLL, 0xFFFF, 0 },

    /* =======================================================
       ROBES
       ======================================================= */

    /* 124 - Gaia Gear */
    { "Gaia Gear",
      ATYPE_ROBE, 3, 3, 0, 3,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_GRADPETRIFY,
      _ROBE_GRP, 500, 250 },

    /* 125 - Sage's Surplice */
    { "Sage's Surplice",
      ATYPE_ROBE, 5, 5, 0, 5,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _ROBE_GRP, 1200, 600 },

    /* 126 - Luminous Robe */
    { "Luminous Robe",
      ATYPE_ROBE, 12, 9, 0, 10,
      ELEM_THUNDER, ELEM_NONE, AFLAG_ANTI_UNDEAD, SRES_NONE,
      _ROBE_GRP, 0xFFFF, 0 },

    /* 127 - Mage's Robe */
    { "Mage's Robe",
      ATYPE_ROBE, 6, 5, 0, 5,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_RYDIA|EQUIP_PALOM|EQUIP_HARLEY|EQUIP_GOLBEZ,
      2000, 1000 },

    /* 128 - Black Robe */
    { "Black Robe",
      ATYPE_ROBE, 8, 7, 0, 7,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_RYDIA|EQUIP_PALOM|EQUIP_HARLEY|EQUIP_GOLBEZ,
      0xFFFF, 0 },

    /* 129 - Red Robe */
    { "Red Robe",
      ATYPE_ROBE, 11, 9, 0, 7,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_ROSA|EQUIP_RYDIA|EQUIP_PALOM|EQUIP_POROM|EQUIP_LEONORA|
      EQUIP_HARLEY|EQUIP_GOLBEZ,
      0xFFFF, 0 },

    /* 130 - White Robe */
    { "White Robe",
      ATYPE_ROBE, 18, 10, 0, 5,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_GHOUL|AFLAG_ANTI_UNDEAD, SRES_BLIND,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_ROSA|EQUIP_POROM|EQUIP_LEONORA,
      0xFFFF, 0 },

    /* 131 - Professor's Robe */
    { "Professor's Robe",
      ATYPE_ROBE, 10, 5, 5, 5,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _NODOLL, 0xFFFF, 0 },

    /* 132 - Exorcist Gown */
    { "Exorcist Gown",
      ATYPE_ROBE, 11, 6, 0, 6,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_DEMON, SRES_NONE,
      _NODOLL, 0xFFFF, 0 },

    /* 133 - Ebony Robe */
    { "Ebony Robe",
      ATYPE_ROBE, 11, 9, 1, 10,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_UNDEAD, SRES_NONE,
      EQUIP_GOLBEZ, 0xFFFF, 0 },

    /* 134 - Sage's Robe */
    { "Sage's Robe",
      ATYPE_ROBE, 19, 15, 14, 18,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_MAGE, SRES_SILENCE,
      _ROBE_GRP, 0xFFFF, 0 },

    /* 135 - Robe of Lords */
    { "Robe of Lords",
      ATYPE_ROBE, 19, 18, 5, 15,
      ELEM_FIRE|ELEM_ICE|ELEM_THUNDER|ELEM_HOLY|ELEM_DARK|ELEM_WIND|ELEM_WATER|ELEM_EARTH,
      ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_ROSA|EQUIP_POROM|EQUIP_LEONORA,
      0xFFFF, 0 },

    /* =======================================================
       SHIELDS
       ======================================================= */

    /* 136 - Bronze Shield */
    { "Bronze Shield",
      ATYPE_SHIELD, 1, 0, 20, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 100, 50 },

    /* 137 - Large Shield */
    { "Large Shield",
      ATYPE_SHIELD, 4, 0, 20, 0,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 0xFFFF, 0 },

    /* 138 - Iron Shield */
    { "Iron Shield",
      ATYPE_SHIELD, 2, 1, 22, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 600, 300 },

    /* 139 - Mythril Shield */
    { "Mythril Shield",
      ATYPE_SHIELD, 3, 2, 26, 2,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_GHOUL, SRES_NONE,
      _HEAVY, 1000, 500 },

    /* 140 - Flame Shield */
    { "Flame Shield",
      ATYPE_SHIELD, 3, 2, 28, 2,
      ELEM_ICE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 0xFFFF, 0 },

    /* 141 - Ice Shield */
    { "Ice Shield",
      ATYPE_SHIELD, 3, 2, 30, 2,
      ELEM_FIRE, ELEM_NONE, AFLAG_ANTI_DEMON, SRES_NONE,
      _HEAVY, 0xFFFF, 0 },

    /* 142 - Diamond Shield */
    { "Diamond Shield",
      ATYPE_SHIELD, 4, 2, 32, 3,
      ELEM_THUNDER, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 0xFFFF, 0 },

    /* 143 - Lustrous Shield */
    { "Lustrous Shield",
      ATYPE_SHIELD, 2, 1, 24, 1,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_UNDEAD, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN,
      0xFFFF, 0 },

    /* 144 - Aegis Shield */
    { "Aegis Shield",
      ATYPE_SHIELD, 4, 5, 34, 4,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_MAGE, SRES_PETRIFY,
      _HEAVY, 0xFFFF, 0 },

    /* 145 - Genji Shield */
    { "Genji Shield",
      ATYPE_SHIELD, 5, 3, 36, 4,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      _HEAVY, 0xFFFF, 0 },

    /* 146 - Dragon Shield */
    { "Dragon Shield",
      ATYPE_SHIELD, 6, 3, 38, 5,
      ELEM_FIRE|ELEM_ICE|ELEM_THUNDER|ELEM_HOLY|ELEM_DARK|ELEM_WIND|ELEM_WATER|ELEM_EARTH,
      ELEM_NONE, AFLAG_ANTI_DRAGON, SRES_NONE,
      _HEAVY, 0xFFFF, 0 },

    /* 147 - Crystal Shield */
    { "Crystal Shield",
      ATYPE_SHIELD, 7, 4, 40, 6,
      ELEM_NONE, ELEM_NONE, AFLAG_ANTI_UNDEAD, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN|EQUIP_GOLBEZ,
      0xFFFF, 0 },

    /* 148 - Lunar Shield */
    { "Lunar Shield",
      ATYPE_SHIELD, 9, 5, 45, 9,
      ELEM_NONE, ELEM_NONE, AFLAG_NONE, SRES_NONE,
      EQUIP_CECIL|EQUIP_CEODORE|EQUIP_GOLBEZ,
      0xFFFF, 0 },

    /* 149 - Hero's Shield */
    { "Hero's Shield",
      ATYPE_SHIELD, 10, 10, 45, 10,
      ELEM_NONE, ELEM_NONE, AFLAG_ALL_ABSORB, SRES_NONE,
      _HEAVY, 0xFFFF, 0 },

    /* 150 - Phase Shield */
    { "Phase Shield",
      ATYPE_SHIELD, 15, 14, 40, 20,
      ELEM_HOLY, ELEM_NONE, AFLAG_ANTI_MECH|AFLAG_ANTI_GIANT,
      SRES_SILENCE|SRES_PIG|SRES_MINI|SRES_FROG|SRES_CONFUSE|SRES_CURSE,
      _DOLLS, 0xFFFF, 0 },

    /* 151 - Adamant Shield */
    { "Adamant Shield",
      ATYPE_SHIELD, 15, 15, 50, 15,
      ELEM_ICE, ELEM_NONE, AFLAG_NONE,
      SRES_SILENCE|SRES_MINI|SRES_CONFUSE|SRES_CURSE,
      _NODOLL, 0xFFFF, 0 },
};

const u16 armor_count = ARMOR_COUNT;