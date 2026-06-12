#ifndef ITEMS_H
#define ITEMS_H

#include <snes.h>
#include "status.h"

// Categorias
#define ITEM_CAT_CONSUMABLE  0
#define ITEM_CAT_BATTLE      1
#define ITEM_CAT_KEY         2
#define ITEM_CAT_STAT        3
#define ITEM_CAT_SUMMON      4

// Efeitos
#define ITEM_FX_NONE         0
#define ITEM_FX_HEAL_HP      1
#define ITEM_FX_HEAL_MP      2
#define ITEM_FX_HEAL_FULL    3
#define ITEM_FX_REVIVE       4
#define ITEM_FX_CURE_STATUS  5
#define ITEM_FX_CURE_ALL     6
#define ITEM_FX_PARTY_HP     7
#define ITEM_FX_PARTY_FULL   8
#define ITEM_FX_RAISE_MAX_HP 9
#define ITEM_FX_RAISE_MAX_MP 10
#define ITEM_FX_CAST_SPELL   11
#define ITEM_FX_INSTANT_KO   12
#define ITEM_FX_SIGHT        13
#define ITEM_FX_EXIT         14
#define ITEM_FX_VIEW_ENEMY   15
#define ITEM_FX_TEACH_SUMMON 16

#define ITEM_FX_INFLICT_STATUS 17
#define ITEM_FX_BUFF_STATUS    18
#define ITEM_FX_SELF_DAMAGE    19

// Status flags (bitmask para ITEM_FX_CURE_STATUS)

typedef struct {
    const char *name;
    u16 cost;
    u8  category;
    u8  effect;
    u16 power;
    u32 status_mask;
    u8  target_flags;
} ItemDef;

extern const ItemDef item_table[];
extern const u16     item_count;

// IDs — índice direto na tabela
#define ITEM_POTION          0
#define ITEM_HI_POTION       1
#define ITEM_X_POTION        2
#define ITEM_ETHER           3
#define ITEM_DRY_ETHER       4
#define ITEM_ELIXIR          5
#define ITEM_MEGALIXIR       6
#define ITEM_PHOENIX_DOWN    7
#define ITEM_GOLD_NEEDLE     8
#define ITEM_MAIDENS_KISS    9
#define ITEM_MALLET          10
#define ITEM_DIET_RATION     11
#define ITEM_CROSS           12
#define ITEM_ECHO_HERBS      13
#define ITEM_EYE_DROPS       14
#define ITEM_ANTIDOTE        15
#define ITEM_REMEDY          16
#define ITEM_SMALL_TALE      17
#define ITEM_DISCOVERY_BOOK  18
#define ITEM_GOLDEN_APPLE    19
#define ITEM_SILVER_APPLE    20
#define ITEM_SOMA_DROP       21
#define ITEM_TENT            22
#define ITEM_COTTAGE         23
#define ITEM_GNOMISH_BREAD   24
#define ITEM_EMERGENCY_EXIT  25
#define ITEM_GOBLIN          26
#define ITEM_BOMB            27
#define ITEM_COCKATRICE      28
#define ITEM_MINDFLAYER      29
#define ITEM_CHOCOBO         30
// battle items
#define ITEM_BOMB_FRAGMENT   31
#define ITEM_BOMB_CRANK      32
#define ITEM_ANTARCTIC_WIND  33
#define ITEM_ARCTIC_WIND     34
#define ITEM_ZEUS_WRATH      35
#define ITEM_HEAVENLY_WRATH  36
#define ITEM_STARDUST        37
#define ITEM_LILITHS_KISS    38
#define ITEM_VAMPIRE_FANG    39
#define ITEM_BACCHUS_WINE    40
#define ITEM_HERMES_SANDALS  41
#define ITEM_BRONZE_HOURGLASS 42
#define ITEM_SILVER_HOURGLASS 43
#define ITEM_GOLD_HOURGLASS  44
#define ITEM_SPIDERS_SILK    45
#define ITEM_DECOY           46
#define ITEM_RED_FANG        47
#define ITEM_WHITE_FANG      48
#define ITEM_BLUE_FANG       49
#define ITEM_LIGHT_CURTAIN   50
#define ITEM_BOMB_CORE       51
#define ITEM_LUNAR_CURTAIN   52
#define ITEM_SILENT_BELL     53
#define ITEM_GAIA_DRUM       54
#define ITEM_COEURL_WHISKER  55
#define ITEM_BESTIARY        56
#define ITEM_ALARM_CLOCK     57
#define ITEM_UNICORN_HORN    58
// key items
#define ITEM_ADAMANTITE         59
#define ITEM_ADAMANTINE_PIG     60
#define ITEM_AGARTITE           61
#define ITEM_BARDS_LYRE         62
#define ITEM_BARON_KEY          63
#define ITEM_BLACK_TAIL         64
#define ITEM_BLUE_TAIL          65
#define ITEM_BOUQUET            66
#define ITEM_BRONZE_TAIL        67
#define ITEM_CRYSTAL            68
#define ITEM_DAMCYAN_FLOWERS    69
#define ITEM_DARK_CRYSTAL       70
#define ITEM_EBONY_TAIL         71
#define ITEM_FRYING_PAN         72
#define ITEM_GIL_BIRD_EGG       73
#define ITEM_GOLD_TAIL          74
#define ITEM_GREEN_TAIL         75
#define ITEM_GREY_TAIL          76
#define ITEM_KOKKOL_ORE         77
#define ITEM_LADLE              78
#define ITEM_LUSTFUL_LALIHO     79
#define ITEM_MEMBERS_CARD       80
#define ITEM_MEMBERS_WRIT       81
#define ITEM_MYTHRIL_BOLT       82
#define ITEM_MYTHRIL_NUT        83
#define ITEM_MYTHRIL_SPRING     84
#define ITEM_PINK_TAIL          85
#define ITEM_POETS_NOTEBOOK     86
#define ITEM_PROOF_OF_COURAGE   87
#define ITEM_PURPLE_TAIL        88
#define ITEM_RAINBOW_TAIL       89
#define ITEM_RED_TAIL           90
#define ITEM_SAND_PEARL         91
#define ITEM_SILVER_TAIL        92
#define ITEM_SMALL_TAIL         93
#define ITEM_VIP_CARD           94
#define ITEM_WHISPERWEED_SEED   95
#define ITEM_WHITE_TAIL         96

#define ITEM_COUNT             97


#endif