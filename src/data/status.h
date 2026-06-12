#ifndef STATUS_H
#define STATUS_H

#include <snes.h>

/* =========================================================
   STATUS FLAGS
   ========================================================= */

#define STATUS_NONE        0x00000000UL

/* negativos */

#define STATUS_POISON      0x00000001UL
#define STATUS_SLEEP       0x00000002UL
#define STATUS_SILENCE     0x00000004UL
#define STATUS_BLIND       0x00000008UL
#define STATUS_CONFUSE     0x00000010UL
#define STATUS_HOLD        0x00000020UL
#define STATUS_BERSERK     0x00000040UL
#define STATUS_PIG         0x00000080UL

#define STATUS_TOAD        0x00000100UL
#define STATUS_MINI        0x00000200UL
#define STATUS_PETRIFY     0x00000400UL
#define STATUS_CURSE       0x00000800UL
#define STATUS_STOP        0x00001000UL
#define STATUS_SLOW        0x00002000UL
#define STATUS_DOOM        0x00004000UL
#define STATUS_ZOMBIE      0x00008000UL

/* positivos */

#define STATUS_HASTE       0x00010000UL
#define STATUS_FLOAT       0x00020000UL
#define STATUS_BLINK       0x00040000UL
#define STATUS_REFLECT     0x00080000UL
#define STATUS_PROTECT     0x00100000UL
#define STATUS_SHELL       0x00200000UL
#define STATUS_REGEN       0x00400000UL
#define STATUS_BARRIER     0x00800000UL

#define STATUS_RERAISE     0x01000000UL
#define STATUS_LIBRA       0x02000000UL

/* grupos úteis */

#define STATUS_NEGATIVE \
( \
    STATUS_POISON   | \
    STATUS_SLEEP    | \
    STATUS_SILENCE  | \
    STATUS_BLIND    | \
    STATUS_CONFUSE  | \
    STATUS_HOLD     | \
    STATUS_BERSERK  | \
    STATUS_PIG      | \
    STATUS_TOAD     | \
    STATUS_MINI     | \
    STATUS_PETRIFY  | \
    STATUS_CURSE    | \
    STATUS_STOP     | \
    STATUS_SLOW     | \
    STATUS_DOOM     | \
    STATUS_ZOMBIE \
)

#define STATUS_POSITIVE \
( \
    STATUS_HASTE    | \
    STATUS_FLOAT    | \
    STATUS_BLINK    | \
    STATUS_REFLECT  | \
    STATUS_PROTECT  | \
    STATUS_SHELL    | \
    STATUS_REGEN    | \
    STATUS_BARRIER  | \
    STATUS_RERAISE  | \
    STATUS_LIBRA \
)

#endif