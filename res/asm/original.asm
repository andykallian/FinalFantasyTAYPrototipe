; ------------------------------------------------------------------------------

; [ transfer water/lava tile to vram ]

TfrWaterTiles:
@8e0e:  lda     $7f5800,x
        sta     $2119
        lda     $7f5801,x
        sta     $2119
        lda     $7f5802,x
        sta     $2119
        lda     $7f5803,x
        sta     $2119
        lda     $7f5804,x
        sta     $2119
        lda     $7f5805,x
        sta     $2119
        lda     $7f5806,x
        sta     $2119
        lda     $7f5807,x
        sta     $2119
        rts

; ------------------------------------------------------------------------------

; [ update water/lava animation ]

UpdateWaterLavaAnim:
@8e47:  lda     $1700
        bne     @8e4f                   ; branch if not overworld
        jmp     UpdateWaterAnim
@8e4f:  cmp     #$01
        bne     @8e56                   ; branch if not underground
        jmp     UpdateLavaAnim
@8e56:  rts

; ------------------------------------------------------------------------------

; [ transfer water/lava graphics to vram ]

TfrWaterLavaGfx:
@8e57:  lda     $1700
        bne     @8e5f                   ; branch if not overworld
        jmp     TfrWaterGfx
@8e5f:  cmp     #$01
        bne     @8e66                   ; branch if not underground
        jmp     TfrLavaGfx
@8e66:  rts

; ------------------------------------------------------------------------------

; [ transfer overworld water graphics to vram ]

TfrWaterGfx:
@8e67:  lda     #$80
        sta     $2115
        lda     $7c
        lsr
        and     #$0f
        tax
        lda     WaterShiftX,x
        tax
        sta     $2116
        lda     #$20
        sta     $2117
        jsr     TfrWaterTiles
        lda     $7c
        lsr
        and     #$0f
        tax
        lda     WaterShiftX,x
        clc
        adc     #$40
        tax
        sta     $2116
        lda     #$20
        sta     $2117
        jsr     TfrWaterTiles
        lda     #$80
        sta     $2115
        ldx     #$1e80
        stx     $2116
        stz     $420b
        stz     $4300
        lda     #$19
        sta     $4301
        ldx     #$5900
        stx     $4302
        lda     #$7f
        sta     $4304
        ldx     #$0100
        stx     $4305
        jsr     ExecDMA
        rts

; ------------------------------------------------------------------------------

; [ transfer underground lava graphics from vram ]

LoadLavaGfx:
@8ec4:  lda     #$80
        sta     $2115
        ldx     #$3800
        stx     $2116
        lda     $213a
        ldx     #$0000
@8ed5:  lda     $213a
        sta     $7f5800,x
        inx
        cpx     #$0100
        bne     @8ed5
        rts

; ------------------------------------------------------------------------------

; [ update underground lava animation ]

UpdateLavaAnim:
@8ee3:  lda     $7c
        and     #$01
        beq     @8eea
        rts
@8eea:  lda     $7c
        lsr
        and     #$0f
        tax
        lda     WaterShiftX,x
        ora     #$07
        tax
        lda     $7f5800,x
        sta     $06
        ldy     #$0007
@8eff:  lda     $7f57ff,x
        sta     $7f5800,x
        dex
        dey
        bne     @8eff
        txa
        and     #$f8
        clc
        adc     #$47
        tax
        lda     $7f5800,x
        sta     $7f57b9,x
        ldy     #$0007
@8f1d:  lda     $7f57ff,x
        sta     $7f5800,x
        dex
        dey
        bne     @8f1d
        txa
        and     #$f8
        tax
        lda     $06
        sta     $7f5800,x
        rts

; ------------------------------------------------------------------------------

; [ transfer underground lava graphics to vram ]

TfrLavaGfx:
@8f34:  lda     #$80
        sta     $2115
        lda     $7c
        lsr
        and     #$0f
        tax
        lda     WaterShiftX,x
        tax
        sta     $2116
        lda     #$38
        sta     $2117
        jsr     TfrWaterTiles
        lda     $7c
        lsr
        and     #$0f
        tax
        lda     WaterShiftX,x
        clc
        adc     #$40
        tax
        sta     $2116
        lda     #$38
        sta     $2117
        jsr     TfrWaterTiles
        inc     $7c
        rts

; ------------------------------------------------------------------------------

; [ transfer overworld water graphics from vram ]

LoadWaterGfx:
@8f69:  lda     #$80
        sta     $2115
        ldx     #$2000
        stx     $2116
        lda     $213a
        ldx     #$0000
@8f7a:  lda     $213a
        sta     $7f5800,x
        inx
        cpx     #$0100
        bne     @8f7a
        ldx     #$1e80
        stx     $2116
        lda     $213a
        ldx     #$0000
@8f93:  lda     $213a
        sta     $7f5900,x
        inx
        cpx     #$0100
        bne     @8f93
        rts

; ------------------------------------------------------------------------------

; [ update overworld water animation ]

UpdateWaterAnim:
@8fa1:  lda     $7c
        and     #$01
        beq     @8faa
        jmp     @8ff3
@8faa:  lda     $7c
        lsr
        and     #$0f
        tax
        lda     WaterShiftX,x
        ora     #$07
        tax
        lda     $7f5800,x
        sta     $06
        ldy     #$0007
@8fbf:  lda     $7f57ff,x
        sta     $7f5800,x
        dex
        dey
        bne     @8fbf
        txa
        and     #$f8
        clc
        adc     #$47
        tax
        lda     $7f5800,x
        sta     $7f57b9,x
        ldy     #$0007
@8fdd:  lda     $7f57ff,x
        sta     $7f5800,x
        dex
        dey
        bne     @8fdd
        txa
        and     #$f8
        tax
        lda     $06
        sta     $7f5800,x
@8ff3:  lda     $7c
        and     #$0f
        tax
        lda     WaterShiftY,x
        clc
        adc     #$38
        tax
        lda     $7f5900,x
        sta     $06
        ldy     #$0007
@9008:  lda     $7f58f8,x
        sta     $7f5900,x
        txa
        sec
        sbc     #$08
        tax
        dey
        bne     @9008
        lda     $7c
        and     #$0f
        tax
        lda     WaterShiftY,x
        clc
        adc     #$b8
        tax
        lda     $7f5900,x
        sta     $7f5848,x
        ldy     #$0007
@902f:  lda     $7f58f8,x
        sta     $7f5900,x
        txa
        sec
        sbc     #$08
        tax
        dey
        bne     @902f
        lda     $06
        sta     $7f5900,x
        lda     $7c
        and     #$0f
        tax
        lda     WaterShiftY,x
        clc
        adc     #$38
        tax
        lda     $7f5900,x
        sta     $06
        ldy     #$0007
@905a:  lda     $7f58f8,x
        sta     $7f5900,x
        txa
        sec
        sbc     #$08
        tax
        dey
        bne     @905a
        lda     $7c
        and     #$0f
        tax
        lda     WaterShiftY,x
        clc
        adc     #$b8
        tax
        lda     $7f5900,x
        sta     $7f5848,x
        ldy     #$0007
@9081:  lda     $7f58f8,x
        sta     $7f5900,x
        txa
        sec
        sbc     #$08
        tax
        dey
        bne     @9081
        lda     $06
        sta     $7f5900,x
        inc     $7c
        rts

; ------------------------------------------------------------------------------

; overworld water data (offset of row to shift each frame)
; 0, 9, 2, 11, 4, 13, 6, 15, 8, 1, 10, 3, 12, 5, 14, 7

WaterShiftY:
@909a:  .byte   $00,$41,$02,$43,$04,$45,$06,$47,$40,$01,$42,$03,$44,$05,$46,$07
WaterShiftX:
@90aa:  .byte   $00,$88,$10,$98,$20,$a8,$30,$b8,$80,$08,$90,$18,$a0,$28,$b0,$38
