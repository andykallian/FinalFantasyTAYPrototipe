#include "commands.h"

const CommandDef commandTable[CMD_COUNT] =
{
    { "Attack",         SUBMENU_NONE },         /* CMD_ATTACK */
    { "Items",          SUBMENU_ITEMS },         /* CMD_ITEMS */
    { "Band",           SUBMENU_BAND },         /* CMD_BAND */
    { "Defend",         SUBMENU_NONE },         /* CMD_DEFEND */
    { "Swap Rows",      SUBMENU_NONE },         /* CMD_SWAPROWS */
    { "Equip",          SUBMENU_EQUIPS },         /* CMD_EQUIP */
    { "Aim",            SUBMENU_NONE },         /* CMD_AIM */
    { "Analyze",        SUBMENU_NONE },         /* CMD_ANALYZE */
    { "Awaken",         SUBMENU_NONE },         /* CMD_AWAKEN */
    { "Bardsong",       SUBMENU_BARDSONG },     /* CMD_BARDSONG */
    { "Big Throw",      SUBMENU_NONE },         /* CMD_BIGTHROW */
    { "Black Magic",    SUBMENU_BLACK_MAGIC },  /* CMD_BLACK_MAGIC */
    { "Bluff",          SUBMENU_NONE },         /* CMD_BLUFF */
    { "Bless",          SUBMENU_NONE },         /* CMD_BLESS */
    { "Blessing",       SUBMENU_NONE },         /* CMD_BLESSING */
    { "Cease Cover",    SUBMENU_NONE },         /* CMD_CEASECOVER */
    { "Chakra",         SUBMENU_NONE },         /* CMD_CHAKRA */
    { "Cover",          SUBMENU_NONE },         /* CMD_COVER */
    { "Cover Counter",  SUBMENU_NONE },         /* CMD_COVERCOUNTER */
    { "Dance",          SUBMENU_NONE },         /* CMD_DANCE */
    { "Dualcast",       SUBMENU_NONE },         /* CMD_DUALCAST */
    { "Escape",         SUBMENU_NONE },         /* CMD_ESCAPE */
    { "Focus",          SUBMENU_NONE },         /* CMD_FOCUS */
    { "Gil Toss",       SUBMENU_NONE },         /* CMD_GILTOSS */
    { "Human Kite",     SUBMENU_NONE },         /* CMD_HUMANKITE */
    { "Illusions",      SUBMENU_NINJUTSU },     /* CMD_ILLUSIONS */
    { "Jive",           SUBMENU_NONE },         /* CMD_JIVE */
    { "Jump",           SUBMENU_NONE },         /* CMD_JUMP */
    { "Kick",           SUBMENU_NONE },         /* CMD_KICK */
    { "Mug",            SUBMENU_NONE },         /* CMD_MUG */
    { "Ninjutsu",       SUBMENU_NINJUTSU },     /* CMD_NINJUTSU */
    { "Piercing Sight", SUBMENU_NONE },         /* CMD_PIERCINGSIGHT */
    { "Pray",           SUBMENU_NONE },         /* CMD_PRAY */
    { "Pressure",       SUBMENU_NONE },         /* CMD_PRESSURE */
    { "Risk Strike",    SUBMENU_NONE },         /* CMD_RISKSTRIKE */
    { "Salve",          SUBMENU_NONE },         /* CMD_SALVE */
    { "Shuriken",       SUBMENU_NONE },         /* CMD_SHURIKEN */
    { "Steal",          SUBMENU_NONE },         /* CMD_STEAL */
    { "Summon",         SUBMENU_SUMMON },       /* CMD_SUMMON */
    { "Taunt",          SUBMENU_NONE },         /* CMD_TAUNT */
    { "Tenketsu",       SUBMENU_NONE },         /* CMD_TENKETSU */
    { "Throw",          SUBMENU_NONE },         /* CMD_THROW */
    { "White Magic",    SUBMENU_WHITE_MAGIC }   /* CMD_WHITE_MAGIC */
};