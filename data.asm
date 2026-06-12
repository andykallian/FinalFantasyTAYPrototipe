.include "hdr.asm"

; =========================================================
; BANCO 1 - PALETAS
; =========================================================
.bank 1
.org 0
sky_pal:
.incbin "res/gfx/sky.pal"
sky_pal_end:

ceodore_pal:
.incbin "res/gfx/Ceodore.pal"
ceodore_pal_end:

enterprise_pal:
.incbin "res/gfx/Enterprise.pal"
enterprise_pal_end:

splash_pal:
.incbin "res/gfx/dream_palette.bin"
splash_pal_end:

ow_palette_bin:
.incbin "res/maps/ow_palette.bin"
ow_palette_bin_end:

; =========================================================
; BANCO 2 - TILES (overworld, sky, sprites, splash)
; =========================================================
.bank 2
.org 0x0000
ow_tiles_bin:
.incbin "res/maps/ow_tiles.bin"
ow_tiles_bin_end:

sky_tiles:
.incbin "res/gfx/sky.pic"
sky_tiles_end:

sky_map:
.incbin "res/gfx/sky.map"
sky_map_end:

splash_tiles:
.incbin "res/gfx/dream_tiles.bin"
splash_tiles_end:

splash_map:
.incbin "res/gfx/dream_map.bin"
splash_map_end:

; =========================================================
; BANCO 3 - SPRITES
; =========================================================
.bank 3
.org 0
ceodore_tiles:
.incbin "res/gfx/Ceodore.pic"
ceodore_tiles_end:

enterprise_tiles:
.incbin "res/gfx/Enterprise.pic"
enterprise_tiles_end:

shadowShip_tiles:
.incbin "res/gfx/shadowShip.pic"
shadowShip_tiles_end:

; =========================================================
; BANCOS 4-7 - CHUNKS OVERWORLD (mapa normal)
; =========================================================
.bank 4
.org 0x0000
ow_map_chunk0:
.incbin "res/maps/ow_chunk_0_0.bin"
.org 0x4000
ow_map_chunk1:
.incbin "res/maps/ow_chunk_0_1.bin"
.org 0x8000
ow_map_chunk2:
.incbin "res/maps/ow_chunk_0_2.bin"
.org 0xC000
ow_map_chunk3:
.incbin "res/maps/ow_chunk_0_3.bin"

.bank 5
.org 0x0000
ow_map_chunk4:
.incbin "res/maps/ow_chunk_1_0.bin"
.org 0x4000
ow_map_chunk5:
.incbin "res/maps/ow_chunk_1_1.bin"
.org 0x8000
ow_map_chunk6:
.incbin "res/maps/ow_chunk_1_2.bin"
.org 0xC000
ow_map_chunk7:
.incbin "res/maps/ow_chunk_1_3.bin"

.bank 6
.org 0x0000
ow_map_chunk8:
.incbin "res/maps/ow_chunk_2_0.bin"
.org 0x4000
ow_map_chunk9:
.incbin "res/maps/ow_chunk_2_1.bin"
.org 0x8000
ow_map_chunk10:
.incbin "res/maps/ow_chunk_2_2.bin"
.org 0xC000
ow_map_chunk11:
.incbin "res/maps/ow_chunk_2_3.bin"

.bank 7
.org 0x0000
ow_map_chunk12:
.incbin "res/maps/ow_chunk_3_0.bin"
.org 0x4000
ow_map_chunk13:
.incbin "res/maps/ow_chunk_3_1.bin"
.org 0x8000
ow_map_chunk14:
.incbin "res/maps/ow_chunk_3_2.bin"
.org 0xC000
ow_map_chunk15:
.incbin "res/maps/ow_chunk_3_3.bin"

; =========================================================
; BANCOS 8-11 - CHUNKS OVERWORLD (mapa _t)
; =========================================================
.bank 8
.org 0x0000
ow_map_chunk_t0:
.incbin "res/maps/ow_chunk_t_0_0.bin"
.org 0x4000
ow_map_chunk_t1:
.incbin "res/maps/ow_chunk_t_0_1.bin"
.org 0x8000
ow_map_chunk_t2:
.incbin "res/maps/ow_chunk_t_0_2.bin"
.org 0xC000
ow_map_chunk_t3:
.incbin "res/maps/ow_chunk_t_0_3.bin"

.bank 9
.org 0x0000
ow_map_chunk_t4:
.incbin "res/maps/ow_chunk_t_1_0.bin"
.org 0x4000
ow_map_chunk_t5:
.incbin "res/maps/ow_chunk_t_1_1.bin"
.org 0x8000
ow_map_chunk_t6:
.incbin "res/maps/ow_chunk_t_1_2.bin"
.org 0xC000
ow_map_chunk_t7:
.incbin "res/maps/ow_chunk_t_1_3.bin"

.bank 10
.org 0x0000
ow_map_chunk_t8:
.incbin "res/maps/ow_chunk_t_2_0.bin"
.org 0x4000
ow_map_chunk_t9:
.incbin "res/maps/ow_chunk_t_2_1.bin"
.org 0x8000
ow_map_chunk_t10:
.incbin "res/maps/ow_chunk_t_2_2.bin"
.org 0xC000
ow_map_chunk_t11:
.incbin "res/maps/ow_chunk_t_2_3.bin"

.bank 11
.org 0x0000
ow_map_chunk_t12:
.incbin "res/maps/ow_chunk_t_3_0.bin"
.org 0x4000
ow_map_chunk_t13:
.incbin "res/maps/ow_chunk_t_3_1.bin"
.org 0x8000
ow_map_chunk_t14:
.incbin "res/maps/ow_chunk_t_3_2.bin"
.org 0xC000
ow_map_chunk_t15:
.incbin "res/maps/ow_chunk_t_3_3.bin"