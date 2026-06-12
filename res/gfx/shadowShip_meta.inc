extern char shadowShip_tiles, shadowShip_tiles_end;
extern char shadowShip_pal;

#define SHADOW_ATTR (OBJ_PAL(1) | OBJ_PRIO(2))

// ========================================
// FRAME 0
// ========================================

const t_metasprite ShadowShip_metasprite0[] =
{
    METASPR_ITEM(0, 0,  0, SHADOW_ATTR),
    METASPR_ITEM(8, 0,  1, SHADOW_ATTR),

    METASPR_ITEM(0, 8, 16, SHADOW_ATTR),
    METASPR_ITEM(8, 8, 17, SHADOW_ATTR),

    METASPR_TERM
};

// ========================================
// FRAME 1
// ========================================

const t_metasprite ShadowShip_metasprite1[] =
{
    METASPR_ITEM(0, 0,  2, SHADOW_ATTR),
    METASPR_ITEM(8, 0,  3, SHADOW_ATTR),

    METASPR_ITEM(0, 8, 18, SHADOW_ATTR),
    METASPR_ITEM(8, 8, 19, SHADOW_ATTR),

    METASPR_TERM
};

// ========================================

const t_metasprite* ShadowShip_metasprites[2] =
{
    ShadowShip_metasprite0,
    ShadowShip_metasprite1
};