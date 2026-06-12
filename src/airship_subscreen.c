#include <snes.h>
#include "airship_subscreen.h"

//==========================================

void airshipSubInit(void)
{
    REG_TM=0x13;
    REG_TS=0x00;

    //--------------------------------
    // usa fixed color
    //--------------------------------
    REG_CGWSEL=0x00;

    //--------------------------------
    // aplica em BG2
    //--------------------------------
    REG_CGADSUB=
        0x80 |   // enable color math
        0x40 |   // half
        0x02;    // BG2

    //--------------------------------
    // azul claro
    //--------------------------------
    REG_COLDATA=0x20|8;
    REG_COLDATA=0x40|10;
    REG_COLDATA=0x80|16;
}

//==========================================

void airshipSubEnable(void)
{
    REG_CGADSUB=
        0x80|
        0x40|
        0x02;
}

//==========================================

void airshipSubDisable(void)
{
    REG_CGADSUB=0;
}

//==========================================

void airshipSubFlush(void)
{
}