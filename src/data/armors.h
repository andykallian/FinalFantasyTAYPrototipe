#ifndef ARMORS_H
#define ARMORS_H

#include <snes.h>
#include "weapons.h"

/* =========================================================
   Tipos de armadura
   ========================================================= */
#define ATYPE_ARMLET      0   /* pulseiras / aneis            */
#define ATYPE_ARMOR       1   /* armaduras pesadas            */
#define ATYPE_CLOTHES     2   /* roupas leves                 */
#define ATYPE_GLOVES      3   /* luvas                        */
#define ATYPE_HAT         4   /* chapeus / capacetes leves    */
#define ATYPE_HELMET      5   /* capacetes pesados            */
#define ATYPE_ROBE        6   /* roupoes magicos              */
#define ATYPE_SHIELD      7   /* escudos                      */

/* =========================================================
   Flags especiais de armadura
   ========================================================= */
#define AFLAG_NONE        0x0000
#define AFLAG_ANTI_GHOUL  0x0001   /* strong against Ghoul     */
#define AFLAG_ANTI_UNDEAD 0x0002   /* strong against Undead    */
#define AFLAG_ANTI_MAGE   0x0004   /* strong against Mage      */
#define AFLAG_ANTI_DRAGON 0x0008   /* strong against Dragon    */
#define AFLAG_ANTI_DEMON  0x0010   /* strong against Demon     */
#define AFLAG_ANTI_MECH   0x0020   /* strong against Machine   */
#define AFLAG_ANTI_GIANT  0x0040   /* strong against Giant     */
#define AFLAG_ANTI_FLAN   0x0080   /* strong against Flan      */
#define AFLAG_ABSORB_ELEM 0x0100   /* absorve elemento (ex: Fire Scarf) */
#define AFLAG_CURSED      0x0200   /* item amaldicoado         */
#define AFLAG_ALL_ABSORB  0x0400   /* resistencias viram absorcao (Hero/Cursed) */

/* =========================================================
   Resistencias de status — bitmask separado (status_res)
   ========================================================= */
#define SRES_NONE         0x00000000
#define SRES_POISON       0x00000001
#define SRES_BLIND        0x00000002
#define SRES_SILENCE      0x00000004
#define SRES_SLEEP        0x00000008
#define SRES_CONFUSE      0x00000010
#define SRES_PARALYZE     0x00000020
#define SRES_PETRIFY      0x00000040
#define SRES_GRADPETRIFY  0x00000080
#define SRES_BERSERK      0x00000100
#define SRES_CURSE        0x00000200
#define SRES_TOAD         0x00000400
#define SRES_PIG          0x00000800
#define SRES_MINI         0x00001000
#define SRES_FROG         0x00002000   /* alias Toad em alguns contextos */
#define SRES_DEATH        0x00004000
#define SRES_HOLY         0x00008000   /* resistencia elemental holy via status slot */
#define SRES_ALL          0x0000FFFF

/* =========================================================
   Grupos de equip uteis para armaduras (EQUIP_* vem de weapons.h)
   ========================================================= */
#define EQUIP_HEAVY   (EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN|EQUIP_CID|EQUIP_LUCA|EQUIP_GOLBEZ)
#define EQUIP_DOLLS   (EQUIP_CALCA|EQUIP_BRINA)
#define EQUIP_NINJA_A (EQUIP_EDGE|EQUIP_ZANGETSU|EQUIP_GEKKOU|EQUIP_IZAYOI|EQUIP_TSUKINOWA)
#define EQUIP_LIGHT   (EQUIP_EVERYONE & ~EQUIP_DOLLS)

/* =========================================================
   Grupos de equip para armaduras leves (exceto Calca/Brina)
   ========================================================= */
#define EQUIP_NO_DOLLS  (EQUIP_EVERYONE & ~(EQUIP_CALCA|EQUIP_BRINA))

/* =========================================================
   Struct principal
   ========================================================= */
typedef struct {
    const char *name;
    u8          atype;        /* ATYPE_*                      */
    u8          defense;
    u8          mag_defense;
    s8          evade;        /* % pode ser negativo          */
    s8          mag_evade;    /* % pode ser negativo          */
    u8          elem_res;     /* ELEM_* bitmask (resistencias elementais) */
    u8          elem_absorb;  /* ELEM_* bitmask (absorver, usado s/ Fire Scarf) */
    u16         flags;        /* AFLAG_* bitmask              */
    u32         status_res;   /* SRES_* bitmask               */
    u32         equip_mask;
    u16         buy;          /* 0xFFFF = nao compravel       */
    u16         sell;
} ArmorDef;

extern const ArmorDef armor_table[];
extern const u16      armor_count;

/* =========================================================
   IDs — indice direto na tabela
   ========================================================= */

/* ---- ARMLETS (0–28) ---- */
#define ARM_IRON_ARMLET       0
#define ARM_SILVER_ARMLET     1
#define ARM_DIAMOND_ARMLET    2
#define ARM_POWER_ARMLET      3
#define ARM_RUNE_ARMLET       4
#define ARM_HYPER_WRIST       5
#define ARM_TREASURE_HUNTER   6
#define ARM_TREASURE_HUNTER2  7
#define ARM_SINGLE_STAR       8
#define ARM_TALISMAN          9
#define ARM_RUBY_RING         10
#define ARM_FLAN_RING         11
#define ARM_LEVEL_BAND        12
#define ARM_LEVEL_BAND2       13
#define ARM_GIL_BAND          14
#define ARM_GIL_BAND2         15
#define ARM_RARE_BAND         16
#define ARM_RARE_BAND2        17
#define ARM_ECONOMICAL_RING   18
#define ARM_CURSED_RING       19
#define ARM_RAPID_RING        20
#define ARM_RAPID_RING2       21
#define ARM_SPRINT_RING       22
#define ARM_LIMIT_RING        23
#define ARM_TAUNT_RING        24
#define ARM_REAR_RING         25
#define ARM_TWIN_STARS        26
#define ARM_CRYSTAL_RING      27
#define ARM_PROTECT_RING      28

/* ---- ARMOR PESADA (29–48) ---- */
#define ARM_BRONZE_ARMOR      29
#define ARM_IRON_ARMOR        30
#define ARM_CHAINMAIL         31
#define ARM_HORNED_ARMOR      32
#define ARM_MYTHRIL_ARMOR     33
#define ARM_KNIGHTS_ARMOR     34
#define ARM_PLATE_ARMOR       35
#define ARM_FLAME_MAIL        36
#define ARM_ICE_MAIL          37
#define ARM_DIAMOND_ARMOR     38
#define ARM_BRONZE_BREASTPLATE 39
#define ARM_SILVER_BREASTPLATE 40
#define ARM_BONE_MAIL         41
#define ARM_GENJI_ARMOR       42
#define ARM_DRAGON_MAIL       43
#define ARM_CRYSTAL_MAIL      44
#define ARM_LUNAR_MAIL        45
#define ARM_BLUE_ARMOR        46
#define ARM_PINK_ARMOR        47
#define ARM_ADAMANT_ARMOR     48

/* ---- CLOTHES (49–72) ---- */
#define ARM_TRAINING_GARB     49
#define ARM_CLOTHING          50
#define ARM_LEATHER_CLOTHING  51
#define ARM_BOYS_CLOTHES      52
#define ARM_GIRLS_CLOTHES     53
#define ARM_ANGELS_CLOTHES    54
#define ARM_CLOWNS_CLOTHES    55
#define ARM_MAGES_CLOTHES     56
#define ARM_WARRIORS_CLOTHES  57
#define ARM_KENPO_GI          58
#define ARM_BLACK_BELT_GI     59
#define ARM_POWER_SASH        60
#define ARM_MINERVA_BUSTIER   61
#define ARM_ROSE_TWINE_DRESS  62
#define ARM_FOOT_NINJA_GEAR   63
#define ARM_SHINOBI_GEAR      64
#define ARM_MIST_WRAP         65
#define ARM_QUEENS_TIGHTS     66
#define ARM_BARDS_TUNIC       67
#define ARM_FINAL_OUTFIT      68
#define ARM_FIRE_SCARF        69
#define ARM_BRAVE_SUIT        70
#define ARM_RED_JACKET        71
#define ARM_BLACK_GARB        72
#define ARM_PHASE_BODY        73

/* ---- GLOVES (74–86) ---- */
#define ARM_IRON_GLOVES       74
#define ARM_MYTHRIL_GLOVES    75
#define ARM_BONE_WRIST        76
#define ARM_GAUNTLETS         77
#define ARM_DIAMOND_GLOVES    78
#define ARM_GIANTS_GLOVES     79
#define ARM_QUEENS_GLOVES     80
#define ARM_GENJI_GLOVES      81
#define ARM_DRAGON_GLOVES     82
#define ARM_CRYSTAL_GLOVES    83
#define ARM_LUNAR_GLOVES      84
#define ARM_PHASE_KNUCKLE     85
#define ARM_ADAMANT_GLOVES    86

/* ---- HATS (87–108) ---- */
#define ARM_TURBAN            87
#define ARM_LEATHER_CAP       88
#define ARM_FEATHERED_CAP     89
#define ARM_WIZARDS_HAT       90
#define ARM_SAGES_MITER       91
#define ARM_GOLD_HAIRPIN      92
#define ARM_HEADBAND          93
#define ARM_CIRCLET           94
#define ARM_MYSTIC_VEIL       95
#define ARM_BERET             96
#define ARM_GREEN_BERET       97
#define ARM_BLACK_COWL        98
#define ARM_GOBLIN_MASK       99
#define ARM_QUEENS_MASK       100
#define ARM_OFFICERS_HAT      101
#define ARM_RED_CAP           102
#define ARM_WHITE_TIGER_MASK  103
#define ARM_CAT_EAR_HOOD      104
#define ARM_HYPNO_CROWN       105
#define ARM_CHAKRA_BAND       106
#define ARM_RIBBON            107
#define ARM_GLASS_MASK        108

/* ---- HELMETS (109–124) ---- */
#define ARM_BRONZE_HELM       109
#define ARM_IRON_HELM         110
#define ARM_STEEL_HELM        111
#define ARM_MYTHRIL_HELM      112
#define ARM_HORNED_HELMET     113
#define ARM_CROSS_HELM        114
#define ARM_DIAMOND_HELM      115
#define ARM_STEEL_HEADPLATE   116
#define ARM_LUSTROUS_HELM     117
#define ARM_GENJI_HELM        118
#define ARM_DRAGON_HELM       119
#define ARM_CRYSTAL_HELM      120
#define ARM_LUNAR_HELM        121
#define ARM_PHASE_HELM        122
#define ARM_ADAMANT_HELM      123

/* ---- ROBES (124–135) ---- */
#define ARM_GAIA_GEAR         124
#define ARM_SAGES_SURPLICE    125
#define ARM_LUMINOUS_ROBE     126
#define ARM_MAGES_ROBE        127
#define ARM_BLACK_ROBE        128
#define ARM_RED_ROBE          129
#define ARM_WHITE_ROBE        130
#define ARM_PROFESSORS_ROBE   131
#define ARM_EXORCIST_GOWN     132
#define ARM_EBONY_ROBE        133
#define ARM_SAGES_ROBE        134
#define ARM_ROBE_OF_LORDS     135

/* ---- SHIELDS (136–150) ---- */
#define ARM_BRONZE_SHIELD     136
#define ARM_LARGE_SHIELD      137
#define ARM_IRON_SHIELD       138
#define ARM_MYTHRIL_SHIELD    139
#define ARM_FLAME_SHIELD      140
#define ARM_ICE_SHIELD        141
#define ARM_DIAMOND_SHIELD    142
#define ARM_LUSTROUS_SHIELD   143
#define ARM_AEGIS_SHIELD      144
#define ARM_GENJI_SHIELD      145
#define ARM_DRAGON_SHIELD     146
#define ARM_CRYSTAL_SHIELD    147
#define ARM_LUNAR_SHIELD      148
#define ARM_HEROS_SHIELD      149
#define ARM_PHASE_SHIELD      150
#define ARM_ADAMANT_SHIELD    151

#define ARMOR_COUNT           152

#endif /* ARMORS_H */