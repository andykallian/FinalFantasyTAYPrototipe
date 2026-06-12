extern char ceodore_tiles, ceodore_tiles_end;
extern char ceodore_pal;

#define CEODORE_ATTR (OBJ_PAL(0) | OBJ_PRIO(2))

// --- LINHA 1 DO BMP (8 POSES) ---

const t_metasprite Ceodore_metasprite0[] = {   // frente idle
    METASPR_ITEM(0,  0,  0, CEODORE_ATTR),  // topo
    METASPR_ITEM(0, 16, 32, CEODORE_ATTR),  // corpo
    METASPR_TERM
};

const t_metasprite Ceodore_metasprite1[] = {   // frente walk
    METASPR_ITEM(0,  0,  2, CEODORE_ATTR),
    METASPR_ITEM(0, 16, 34, CEODORE_ATTR),
    METASPR_TERM
};

const t_metasprite Ceodore_metasprite2[] = {   // costas idle
    METASPR_ITEM(0,  0,  4, CEODORE_ATTR),
    METASPR_ITEM(0, 16, 36, CEODORE_ATTR),
    METASPR_TERM
};

const t_metasprite Ceodore_metasprite3[] = {   // costas walk
    METASPR_ITEM(0,  0,  6, CEODORE_ATTR),
    METASPR_ITEM(0, 16, 38, CEODORE_ATTR),
    METASPR_TERM
};

const t_metasprite Ceodore_metasprite4[] = {   // acenar 1
    METASPR_ITEM(0,  0,  8, CEODORE_ATTR),
    METASPR_ITEM(0, 16, 40, CEODORE_ATTR),
    METASPR_TERM
};

const t_metasprite Ceodore_metasprite5[] = {   // acenar 2
    METASPR_ITEM(0,  0, 10, CEODORE_ATTR),
    METASPR_ITEM(0, 16, 42, CEODORE_ATTR),
    METASPR_TERM
};

const t_metasprite Ceodore_metasprite6[] = {   // cabisbaixo
    METASPR_ITEM(0,  0, 12, CEODORE_ATTR),
    METASPR_ITEM(0, 16, 44, CEODORE_ATTR),
    METASPR_TERM
};

const t_metasprite Ceodore_metasprite7[] = {   // morto
    METASPR_ITEM(0,  0, 14, CEODORE_ATTR),
    METASPR_ITEM(0, 16, 46, CEODORE_ATTR),
    METASPR_TERM
};

// --- LINHA 2 DO BMP (6 POSES) ---

const t_metasprite Ceodore_metasprite8[] = {   // lado idle
    METASPR_ITEM(0,  0, 64, CEODORE_ATTR),
    METASPR_ITEM(0, 16, 96, CEODORE_ATTR),
    METASPR_TERM
};

const t_metasprite Ceodore_metasprite9[] = {   // lado walk 1
    METASPR_ITEM(0,  0, 66, CEODORE_ATTR),
    METASPR_ITEM(0, 16, 98, CEODORE_ATTR),
    METASPR_TERM
};

const t_metasprite Ceodore_metasprite10[] = {  // lado walk 2
    METASPR_ITEM(0,  0, 68, CEODORE_ATTR),
    METASPR_ITEM(0, 16, 100, CEODORE_ATTR),
    METASPR_TERM
};

const t_metasprite Ceodore_metasprite11[] = {  // lado walk 3
    METASPR_ITEM(0,  0, 70, CEODORE_ATTR),
    METASPR_ITEM(0, 16, 102, CEODORE_ATTR),
    METASPR_TERM
};

const t_metasprite Ceodore_metasprite12[] = {  // lado walk 4
    METASPR_ITEM(0,  0, 72, CEODORE_ATTR),
    METASPR_ITEM(0, 16, 104, CEODORE_ATTR),
    METASPR_TERM
};

const t_metasprite Ceodore_metasprite13[] = {  // lado walk 5
    METASPR_ITEM(0,  0, 74, CEODORE_ATTR),
    METASPR_ITEM(0, 16, 106, CEODORE_ATTR),
    METASPR_TERM
};

// --- ARRAY FINAL ---

const t_metasprite* Ceodore_metasprites[14] = {
    Ceodore_metasprite0,  Ceodore_metasprite1,  Ceodore_metasprite2,
    Ceodore_metasprite3,  Ceodore_metasprite4,  Ceodore_metasprite5,
    Ceodore_metasprite6,  Ceodore_metasprite7,  Ceodore_metasprite8,
    Ceodore_metasprite9,  Ceodore_metasprite10, Ceodore_metasprite11,
    Ceodore_metasprite12, Ceodore_metasprite13
};