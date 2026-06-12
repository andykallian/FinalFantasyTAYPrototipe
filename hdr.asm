.define HIROM
.define FASTROM

.ifndef HIROM                     ;==LoRom==

.MEMORYMAP
  SLOTSIZE $8000
  DEFAULTSLOT 0
  SLOT 0 $8000
  SLOT 1 $0 $2000
  SLOT 2 $2000 $E000
  SLOT 3 $0 $10000
.ENDME

.ROMBANKSIZE $8000

.else                             ;==HiRom==

.MEMORYMAP
  SLOTSIZE $10000
  DEFAULTSLOT 0
  SLOT 0 $0000
  SLOT 1 $0 $2000
  SLOT 2 $2000 $E000
  SLOT 3 $0 $10000
  SLOT 4 $6000
.ENDME

.ROMBANKSIZE $10000

.endif

.ROMBANKS 32

.SNESHEADER
  ID "SNES"

  NAME "LIBSNES HIROM MEM MAP"
  ;    "123456789012345678901"

.ifdef FASTROM
  FASTROM
.else
  SLOWROM
.endif

.ifdef HIROM
  HIROM
.else
  LOROM
.endif

  CARTRIDGETYPE $00
  ROMSIZE $0C
  SRAMSIZE $00
  COUNTRY $01
  LICENSEECODE $00
  VERSION $00
.ENDSNES

.SNESNATIVEVECTOR
  COP EmptyHandler
  BRK EmptyHandler
  ABORT EmptyHandler
  NMI VBlank
  IRQ EmptyHandler
.ENDNATIVEVECTOR

.SNESEMUVECTOR
  COP EmptyHandler
  ABORT EmptyHandler
  NMI EmptyHandler
  RESET tcc__start
  IRQBRK EmptyHandler
.ENDEMUVECTOR

.ifdef FASTROM
  .ifdef HIROM
    .BASE $C0
  .else
    .BASE $80
  .endif
.else
  .ifdef HIROM
    .BASE $40
  .else
    .BASE $00
  .endif
.endif