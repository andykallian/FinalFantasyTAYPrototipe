#ifndef WEAPONS_H
#define WEAPONS_H

#include <snes.h>

/* =========================================================
   Tipos de arma
   ========================================================= */
#define WTYPE_CLAW        0
#define WTYPE_ROD         1
#define WTYPE_STAFF       2
#define WTYPE_SWORD       3
#define WTYPE_HOLYSWORD   4
#define WTYPE_SPEAR       5
#define WTYPE_BOOMERANG   6
#define WTYPE_DAGGER      7
#define WTYPE_KATANA      8
#define WTYPE_AXE         9
#define WTYPE_HAMMER      10
#define WTYPE_HARP        11
#define WTYPE_BOW         12
#define WTYPE_ARROW       13
#define WTYPE_WHIP        14
#define WTYPE_SHURIKEN    15
#define WTYPE_FISTS       16

/* =========================================================
   Elementos
   ========================================================= */
#define ELEM_NONE         0x00
#define ELEM_FIRE         0x01
#define ELEM_ICE          0x02
#define ELEM_THUNDER      0x04
#define ELEM_HOLY         0x08
#define ELEM_DARK         0x10
#define ELEM_WIND         0x20
#define ELEM_WATER        0x40
#define ELEM_EARTH        0x80

/* =========================================================
   Flags especiais
   ========================================================= */
#define WFLAG_NONE        0x00
#define WFLAG_CASTS_SPELL 0x01
#define WFLAG_THROWABLE   0x02
#define WFLAG_TWO_HANDED  0x04
#define WFLAG_LONG_RANGE  0x08
#define WFLAG_ANTI_MAGE   0x10
#define WFLAG_ANTI_GHOST  0x20
#define WFLAG_ANTI_MECH   0x40
#define WFLAG_ANTI_GIANT  0x80
#define WFLAG_ANTI_DRAGON 0x100
#define WFLAG_ANTI_DEMON  0x200
#define WFLAG_INSTANT_KO  0x400
#define WFLAG_DMGONUSE    0x800
#define WFLAG_HP_DRAIN    0x1000

/* =========================================================
   Bitmask de quem pode equipar
   ========================================================= */
#define EQUIP_CECIL       0x00000001
#define EQUIP_CEODORE     0x00000002
#define EQUIP_KAIN        0x00000004
#define EQUIP_RYDIA       0x00000008
#define EQUIP_ROSA        0x00000010
#define EQUIP_EDGE        0x00000020
#define EQUIP_YANG        0x00000040
#define EQUIP_PALOM       0x00000080
#define EQUIP_POROM       0x00000100
#define EQUIP_EDWARD      0x00000200
#define EQUIP_GOLBEZ      0x00000400
#define EQUIP_FUSOYA      0x00000800
#define EQUIP_URSULA      0x00001000
#define EQUIP_GEKKOU      0x00002000
#define EQUIP_ZANGETSU    0x00004000
#define EQUIP_IZAYOI      0x00008000
#define EQUIP_TSUKINOWA   0x00010000
#define EQUIP_LUCA        0x00020000
#define EQUIP_LEONORA     0x00040000
#define EQUIP_HARLEY      0x00080000
#define EQUIP_CID         0x00100000
#define EQUIP_CALCA       0x00200000
#define EQUIP_BRINA       0x00400000
#define EQUIP_EVERYONE    0xFFFFFFFF

/* grupos comuns */
#define EQUIP_NINJA  (EQUIP_EDGE|EQUIP_GEKKOU|EQUIP_ZANGETSU|EQUIP_IZAYOI|EQUIP_TSUKINOWA)
#define EQUIP_MAGE   (EQUIP_RYDIA|EQUIP_PALOM|EQUIP_LEONORA|EQUIP_HARLEY|EQUIP_GOLBEZ)
#define EQUIP_CLERIC (EQUIP_ROSA|EQUIP_POROM|EQUIP_LEONORA|EQUIP_HARLEY|EQUIP_GOLBEZ)
#define EQUIP_SWORD  (EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN|EQUIP_GOLBEZ)
#define EQUIP_AXEUSERS (EQUIP_CECIL|EQUIP_KAIN|EQUIP_CID|EQUIP_LUCA|EQUIP_GEKKOU|EQUIP_GOLBEZ)
#define EQUIP_BOWUSERS (EQUIP_CECIL|EQUIP_CEODORE|EQUIP_CID|EQUIP_ROSA|EQUIP_RYDIA|\
                        EQUIP_PALOM|EQUIP_POROM|EQUIP_EDWARD|EQUIP_LUCA|EQUIP_LEONORA|\
                        EQUIP_IZAYOI|EQUIP_HARLEY)
#define EQUIP_HAMMERS (EQUIP_CID|EQUIP_LUCA|EQUIP_GEKKOU|EQUIP_GOLBEZ)
#define EQUIP_WHIPUSERS (EQUIP_RYDIA|EQUIP_IZAYOI|EQUIP_HARLEY)
#define EQUIP_CLAWUSERS (EQUIP_YANG|EQUIP_URSULA|EQUIP_EDGE)
#define EQUIP_DAGGERUSERS (EQUIP_CECIL|EQUIP_CEODORE|EQUIP_KAIN|EQUIP_EDGE|EQUIP_RYDIA|\
                           EQUIP_PALOM|EQUIP_EDWARD|EQUIP_GEKKOU|EQUIP_ZANGETSU|\
                           EQUIP_IZAYOI|EQUIP_TSUKINOWA|EQUIP_HARLEY|EQUIP_GOLBEZ|\
                           EQUIP_CALCA|EQUIP_BRINA)
#define EQUIP_STAFFUSERS (EQUIP_CECIL|EQUIP_CEODORE|EQUIP_ROSA|EQUIP_POROM|\
                          EQUIP_LEONORA|EQUIP_HARLEY|EQUIP_GOLBEZ)
#define EQUIP_SPEARUSERS (EQUIP_CEODORE|EQUIP_KAIN|EQUIP_ZANGETSU|EQUIP_GOLBEZ)

/* =========================================================
   Status infligidos on-hit — bitmask (inflict)
   ========================================================= */
#define SINF_NONE         0x00000000
#define SINF_POISON       0x00000001
#define SINF_BLIND        0x00000002
#define SINF_SILENCE      0x00000004
#define SINF_SLEEP        0x00000008
#define SINF_CONFUSE      0x00000010
#define SINF_PARALYZE     0x00000020
#define SINF_PETRIFY      0x00000040
#define SINF_GRADPETRIFY  0x00000080
#define SINF_BERSERK      0x00000100
#define SINF_CURSE        0x00000200
#define SINF_TOAD         0x00000400
#define SINF_PIG          0x00000800
#define SINF_MINI         0x00001000
#define SINF_DEATH        0x00002000

/* =========================================================
   Struct principal
   ========================================================= */
typedef struct {
    const char *name;
    u8          wtype;
    u8          attack;
    u8          accuracy;   /* % */
    u8          element;    /* ELEM_* bitmask */
    u16         flags;      /* WFLAG_* bitmask */
    u8          spell_id;   /* usado se WFLAG_CASTS_SPELL */
    u32         inflict;    /* SINF_* bitmask -- status infligido on-hit */
    u32         equip_mask;
    u16         buy;        /* 0xFFFF = nao compravel */
    u16         sell;
} WeaponDef;

extern const WeaponDef weapon_table[];
extern const u16       weapon_count;

/* =========================================================
   IDs — índice direto na tabela
   ========================================================= */

/* CLAWS */
#define WPN_FLAME_CLAWS       0
#define WPN_ICE_CLAWS         1
#define WPN_LIGHTNING_CLAWS   2
#define WPN_METAL_KNUCKLES    3
#define WPN_FAERIE_CLAWS      4
#define WPN_HELL_CLAWS        5
#define WPN_CAT_CLAWS         6
#define WPN_GODHAND           7
#define WPN_DRAGON_CLAWS      8
#define WPN_TIGER_FANGS       9

/* RODS */
#define WPN_ROD               10
#define WPN_ICE_ROD           11
#define WPN_FLAME_ROD         12
#define WPN_HEALING_ROD       13
#define WPN_THUNDER_ROD       14
#define WPN_LILITH_ROD        15
#define WPN_POLYMORPH_ROD     16
#define WPN_WIZARD_ROD        17
#define WPN_RECOVERY_ROD      18
#define WPN_FAERIE_ROD        19
#define WPN_STARDUST_ROD      20

/* STAVES */
#define WPN_STAFF             21
#define WPN_HEALING_STAFF     22
#define WPN_MYTHRIL_STAFF     23
#define WPN_PSYCHO_SPIRAL     24
#define WPN_PROTECT_STAFF     25
#define WPN_POWER_STAFF       26
#define WPN_AURA_STAFF        27
#define WPN_MASTERS_STAFF     28
#define WPN_SAGES_STAFF       29
#define WPN_SERAPHIM_MACE     30
#define WPN_RUNE_STAFF        31

/* SWORDS */
#define WPN_BROADSWORD        32
#define WPN_EBONY_BLADE       33
#define WPN_LONGSWORD         34
#define WPN_IRON_SWORD        35
#define WPN_ANCIENT_SWORD     36
#define WPN_CORAL_BLADE       37
#define WPN_BLOOD_SWORD       38
#define WPN_FALCHION          39
#define WPN_MYTHRIL_SWORD     40
#define WPN_SLEEP_BLADE       41
#define WPN_FLAME_SWORD       42
#define WPN_ICEBRAND          43
#define WPN_STONEBLADE        44
#define WPN_DEMON_SLAYER      45
#define WPN_ENHANCEMENT_SWORD 46
#define WPN_DEFENDER          47
#define WPN_ULTIMA_WEAPON     48

/* HOLY SWORDS */
#define WPN_EXCALIPOOR        49
#define WPN_KINGSWORD         50
#define WPN_LUSTROUS_SWORD    51
#define WPN_EXCALIBUR         52
#define WPN_RAGNAROK          53

/* SPEARS */
#define WPN_SPEAR             54
#define WPN_JAVELIN           55
#define WPN_TRIDENT           56
#define WPN_PARTISAN          57
#define WPN_WIND_SPEAR        58
#define WPN_FLAME_LANCE       59
#define WPN_DRAGOON_LANCE     60
#define WPN_OBELISK           61
#define WPN_BLOOD_LANCE       62
#define WPN_GUNGNIR           63
#define WPN_WYVERN_LANCE      64
#define WPN_HOLY_LANCE        65

/* BOOMERANGS */
#define WPN_BOOMERANG         66
#define WPN_METAL_BOOMERANG   67
#define WPN_CHAKRAM           68
#define WPN_WING_EDGE         69
#define WPN_MOONRING_BLADE    70
#define WPN_RISING_SUN        71

/* DAGGERS */
#define WPN_KNIFE             72
#define WPN_DAGGER            73
#define WPN_MYTHRIL_KNIFE     74
#define WPN_DANCING_DAGGER    75
#define WPN_MAGE_MASHER       76
#define WPN_TRITON_DAGGER     77
#define WPN_ASSASSIN_DAGGER   78
#define WPN_PHASE_CUTTER      79

/* KATANAS */
#define WPN_KUNAI             80
#define WPN_KODACHI           81
#define WPN_KOGARASU          82
#define WPN_CRIMSON_CHERRY    83
#define WPN_ASHURA            84
#define WPN_BOLTSLICER        85
#define WPN_KOTETSU           86
#define WPN_KIKU_ICHIMONJI    87
#define WPN_MURASAME          88
#define WPN_MASAMUNE          89
#define WPN_MUTSUNOKAMI       90

/* AXES */
#define WPN_CRESCENT_AXE      91
#define WPN_BATTLE_AXE        92
#define WPN_TOMAHAWK          93
#define WPN_DWARVEN_AXE       94
#define WPN_OGREKILLER        95
#define WPN_POISON_AXE        96
#define WPN_RUNE_AXE          97
#define WPN_GIGANT_AXE        98

/* HAMMERS */
#define WPN_HAMMER            99
#define WPN_WOODEN_HAMMER     100
#define WPN_MYTHRIL_HAMMER    101
#define WPN_GAIA_HAMMER       102
#define WPN_SLEDGEHAMMER      103
#define WPN_THOR_HAMMER       104

/* HARPS */
#define WPN_DREAM_HARP        105
#define WPN_SILVER_HARP       106
#define WPN_LAMIA_HARP        107
#define WPN_DARK_HARP         108
#define WPN_MUSE_HARP         109
#define WPN_APOLLOS_HARP      110
#define WPN_LOKIS_HARP        111

/* BOWS */
#define WPN_BOW               112
#define WPN_CROSSBOW          113
#define WPN_GREAT_BOW         114
#define WPN_KILLER_BOW        115
#define WPN_ELFIN_BOW         116
#define WPN_YOICHI_BOW        117
#define WPN_ARTEMIS_BOW       118
#define WPN_PERSEUS_BOW       119

/* ARROWS */
#define WPN_MEDUSA_ARROWS     120
#define WPN_IRON_ARROWS       121
#define WPN_HOLY_ARROWS       122
#define WPN_FIRE_ARROWS       123
#define WPN_ICE_ARROWS        124
#define WPN_LIGHTNING_ARROWS  125
#define WPN_BLINDING_ARROWS   126
#define WPN_POISON_ARROWS     127
#define WPN_SILENCING_ARROWS  128
#define WPN_ANGEL_ARROWS      129
#define WPN_YOICHI_ARROWS     130
#define WPN_ARTEMIS_ARROWS    131
#define WPN_PERSEUS_ARROWS    132

/* WHIPS */
#define WPN_QUEENS_WHIP       133
#define WPN_WHIP              134
#define WPN_THORN_WHIP        135
#define WPN_CHAIN_WHIP        136
#define WPN_ICE_WHIP          137
#define WPN_BLITZ_WHIP        138
#define WPN_FLAME_WHIP        139
#define WPN_DRAGON_WHISKER    140
#define WPN_MYSTIC_WHIP       141

/* SHURIKEN */
#define WPN_SHURIKEN          142
#define WPN_MANJI_SHURIKEN    143
#define WPN_FUMA_SHURIKEN     144

/* FISTS */
#define WPN_UNARMED           145

#define WEAPON_COUNT          146

#endif /* WEAPONS_H */