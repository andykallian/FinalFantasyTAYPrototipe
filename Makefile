ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please create an environment variable PVSNESLIB_HOME")
endif

HIROM=1
FASTROM=1

include ${PVSNESLIB_HOME}/devkitsnes/snes_rules

.PHONY: all

export ROMNAME := finalfantasy

SOURCES := src/main.c data.asm hdr.asm

#------------------------------------------------
# SPRITE CEODORE
#------------------------------------------------
res/gfx/Ceodore.pic: res/gfx/Ceodore.bmp
	$(GFXCONV) -s 16 -o 16 -u 16 -X 16 -Y 32 -P 2 -t bmp -i $<

res/gfx/Enterprise.pic: res/gfx/Enterprise.bmp
	$(GFXCONV) -s 16 -o 16 -u 16 -X 24 -Y 24 -P 2 -t bmp -i $<

res/gfx/shadowShip.pic: res/gfx/shadowShip.bmp
	$(GFXCONV) -s 16 -o 16 -u 16 -X 16 -Y 16 -P 2 -t bmp -i $<

res/gfx/sky.pic: res/gfx/sky.png
	$(GFXCONV) -s 8 -o 16 -u 16 -m -p -i $<

#------------------------------------------------
all: res/gfx/sky.pic $(ROMNAME).sfc

clean: cleanBuildRes cleanRom cleanGfx