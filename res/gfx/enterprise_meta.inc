extern char enterprise_tiles, enterprise_tiles_end;
extern char enterprise_pal;

#define ENTERPRISE_ATTR (OBJ_PAL(1) | OBJ_PRIO(0))

// =========================================================
// POSE 0 — parada
// =========================================================
const t_metasprite Enterprise_metasprite0[] = {
    METASPR_ITEM(0,  0,  0, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  0,  1, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 0,  2, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 0,  3, ENTERPRISE_ATTR),

    METASPR_ITEM(0,  8, 16, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  8, 17, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 8, 18, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 8, 19, ENTERPRISE_ATTR),

    METASPR_ITEM(0,  16, 32, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  16, 33, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 16, 34, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 16, 35, ENTERPRISE_ATTR),

    METASPR_ITEM(0,  24, 48, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  24, 49, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 24, 50, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 24, 51, ENTERPRISE_ATTR),
    METASPR_TERM
};

// =========================================================
// POSE 1 — horizontal
// =========================================================
const t_metasprite Enterprise_metasprite1[] = {
    METASPR_ITEM(0,  0,  4, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  0,  5, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 0,  6, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 0,  7, ENTERPRISE_ATTR),

    METASPR_ITEM(0,  8, 20, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  8, 21, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 8, 22, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 8, 23, ENTERPRISE_ATTR),

    METASPR_ITEM(0,  16, 36, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  16, 37, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 16, 38, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 16, 39, ENTERPRISE_ATTR),

    METASPR_ITEM(0,  24, 52, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  24, 53, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 24, 54, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 24, 55, ENTERPRISE_ATTR),
    METASPR_TERM
};

// =========================================================
// POSE 2 — subindo A
// =========================================================
const t_metasprite Enterprise_metasprite2[] = {
    METASPR_ITEM(0,  0,  8, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  0,  9, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 0, 10, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 0, 11, ENTERPRISE_ATTR),

    METASPR_ITEM(0,  8, 24, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  8, 25, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 8, 26, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 8, 27, ENTERPRISE_ATTR),

    METASPR_ITEM(0,  16, 40, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  16, 41, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 16, 42, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 16, 43, ENTERPRISE_ATTR),

    METASPR_ITEM(0,  24, 56, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  24, 57, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 24, 58, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 24, 59, ENTERPRISE_ATTR),
    METASPR_TERM
};

// =========================================================
// POSE 3 — subindo B
// =========================================================
const t_metasprite Enterprise_metasprite3[] = {
    METASPR_ITEM(0,  0, 12, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  0, 13, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 0, 14, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 0, 15, ENTERPRISE_ATTR),

    METASPR_ITEM(0,  8, 28, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  8, 29, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 8, 30, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 8, 31, ENTERPRISE_ATTR),

    METASPR_ITEM(0,  16, 44, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  16, 45, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 16, 46, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 16, 47, ENTERPRISE_ATTR),

    METASPR_ITEM(0,  24, 60, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  24, 61, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 24, 62, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 24, 63, ENTERPRISE_ATTR),
    METASPR_TERM
};

// =========================================================
// POSE 4 — descendo A
// =========================================================
const t_metasprite Enterprise_metasprite4[] = {
    METASPR_ITEM(0,  0, 64, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  0, 65, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 0, 66, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 0, 67, ENTERPRISE_ATTR),

    METASPR_ITEM(0,  8, 80, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  8, 81, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 8, 82, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 8, 83, ENTERPRISE_ATTR),

    METASPR_ITEM(0,  16, 96, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  16, 97, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 16, 98, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 16, 99, ENTERPRISE_ATTR),

    METASPR_ITEM(0,  24, 112, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  24, 113, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 24, 114, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 24, 115, ENTERPRISE_ATTR),
    METASPR_TERM
};

// =========================================================
// POSE 5 — descendo B
// =========================================================
const t_metasprite Enterprise_metasprite5[] = {
    METASPR_ITEM(0,  0, 68, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  0, 69, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 0, 70, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 0, 71, ENTERPRISE_ATTR),

    METASPR_ITEM(0,  8, 84, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  8, 85, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 8, 86, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 8, 87, ENTERPRISE_ATTR),

    METASPR_ITEM(0,  16, 100, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  16, 101, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 16, 102, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 16, 103, ENTERPRISE_ATTR),

    METASPR_ITEM(0,  24, 116, ENTERPRISE_ATTR),
    METASPR_ITEM(8,  24, 117, ENTERPRISE_ATTR),
    METASPR_ITEM(16, 24, 118, ENTERPRISE_ATTR),
    METASPR_ITEM(24, 24, 119, ENTERPRISE_ATTR),
    METASPR_TERM
};

// =========================================================
// ARRAY FINAL
// =========================================================
const t_metasprite* const Enterprise_metasprites[] = {
    Enterprise_metasprite0,
    Enterprise_metasprite1,
    Enterprise_metasprite2,
    Enterprise_metasprite3,
    Enterprise_metasprite4,
    Enterprise_metasprite5
};