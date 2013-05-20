
;   TEST.ASM  The Free-6502 opcode test suite.
;

	    processor   6502


	    ;   --------------------------   ZERO PAGE   -------------------
	    seg.u   data
	    org     $00

TESTZ1		equ $00
TESTZ2		equ $01
TESTZ3		equ $02
TESTZ4		equ $03

IRQ_ALLOW	equ $04
IRQ_COUNT	equ $05
NMI_ALLOW	equ $06
NMI_COUNT	equ $07
IRQ_STATUS	equ $08


	    ;   --------------------------  NORMAL RAM   -------------------
	    org     $0100

TESTABS1	equ $0200
TESTABS2	equ $0201
TESTABS3	equ $0202
TESTABS4	equ $0203
TESTABS5	equ $0204
TESTABS6	equ $0205
TESTABS7	equ $0206
TESTABS8	equ $0207



RAMEND      	equ $8000
HALT		equ $8000
POSTCODE	equ $8001
LOGFILE		equ $8002
IRQ_TIMER	equ $8004
IRQ_CLEAR       equ $8005
NMI_TIMER       equ $8006
NMI_CLEAR       equ $8007

 
            ;   --------------------------     CODE      -------------------
            seg     code
            org     $F000
PROMBEG     equ     .
 
RESET       subroutine
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	; First, test some basic things that are required for the
	; rest of the tests.  This includes jumps, loads, stores, compares,
	; and branches.
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	; Test some nop's
	nop
	nop
	nop
	nop

	; Disallow interrupts
	lda #$00
	sta IRQ_ALLOW
	sta IRQ_COUNT
	sta NMI_ALLOW
	sta NMI_COUNT
	

	; Test LDA IMM and STA ABS
	lda #$00
	sta POSTCODE
	lda #$01
	sta POSTCODE

	; Test JMP
TEST_JMP
	jmp TEST_JMP1
	lda #$00
	jmp FAILURE
TEST_JMP1
	lda #$01
	sta POSTCODE


TEST_BCC
	lda #$02
	sta POSTCODE
	clc
	bcc TEST_BCC1
	lda #$01
	jmp FAILURE
TEST_BCC1
	lda #$03
	sta POSTCODE
	sec
	bcc TEST_BCC2
	jmp TEST_BCC_DONE
TEST_BCC2
	lda #$02
	jmp FAILURE
TEST_BCC_DONE


TEST_BCS
	lda #$04
	sta POSTCODE
	sec
	bcs TEST_BCS1
	lda #$01
	jmp FAILURE
TEST_BCS1
	clc
	bcs TEST_BCS2
	jmp TEST_BCS_DONE
TEST_BCS2
	lda #$02
	jmp FAILURE
TEST_BCS_DONE


TEST_CMPIMM:	; Checks cmp imm and be
	lda #$05
	sta POSTCODE
	lda #$05
	cmp #$04
	beq TEST_CMPIMM1
	cmp #$05
	beq TEST_CMPIMM2
TEST_CMPIMM1
	lda #$03
	jmp FAILURE
TEST_CMPIMM2


TEST_BNE
	lda #$06
	sta POSTCODE
	lda #$C4
	cmp #$E4
	bne TEST_BNE1
	lda #$04
	jmp FAILURE
TEST_BNE1
	cmp #$C4
	bne TEST_BNE2
	jmp TEST_BNE3
TEST_BNE2
	lda #$05
	jmp FAILURE
TEST_BNE3	

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;  Next, test some instructions with implied addressing,
	;;  or other simple instructions
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

TEST_LDXIMM
	lda #$07
	sta POSTCODE
	ldx #$42
	cpx #$32
	beq TEST_LDXIMM1
	cpx #$42
	beq TEST_LDXIMM2
TEST_LDXIMM1
	lda #$06
	jmp FAILURE
TEST_LDXIMM2


TEST_LDYIMM
	lda #$08
	sta POSTCODE
	ldy #$C3
	cpy #$D3
	beq TEST_LDYIMM1
	cpy #$C3
	beq TEST_LDYIMM2
TEST_LDYIMM1
	lda #$07
	jmp FAILURE
TEST_LDYIMM2


TEST_DEX
	lda #$09
	sta POSTCODE
	ldx #$00
	dex
	cpx #$FF
	beq TEST_DEX1
	lda #$08
	jmp FAILURE
TEST_DEX1


TEST_DEY
	lda #$0A
	sta POSTCODE
	ldy #$00
	dey
	cpy #$FF
	beq TEST_DEY1
	lda #$09
	jmp FAILURE
TEST_DEY1


TEST_INX
	lda #$0B
	sta POSTCODE
	ldx #$0F
	inx
	cpx #$10
	beq TEST_INX1
	lda #$10
	jmp FAILURE
TEST_INX1


TEST_INY
	lda #$0C
	sta POSTCODE
	ldy #$7F
	iny
	cpy #$80
	beq TEST_INY1
	lda #$11
	jmp FAILURE
TEST_INY1


TEST_JSR
	lda #$0D
	sta POSTCODE
	lda #$ED
	jsr TEST_JSR1
	cmp #$42
	beq TEST_JSR2
	lda #$12
	jmp FAILURE
TEST_JSR1
	lda #$42
	rts
TEST_JSR2


TEST_TAX
	lda #$0E
	sta POSTCODE
	lda #$35
	tax
	cpx #$35
	beq TEST_TAX2
	lda #$12
	jmp FAILURE
TEST_TAX2


TEST_TAY
	lda #$0F
	sta POSTCODE
	lda #$76
	tay
	cpy #$76
	beq TEST_TAY2
	lda #$13
	jmp FAILURE
TEST_TAY2


TEST_TXA
	lda #$10
	sta POSTCODE
	ldx #$52
	txa
	cmp #$52
	beq TEST_TXA2
	lda #$14
	jmp FAILURE
TEST_TXA2


TEST_TYA
	lda #$11
	sta POSTCODE
	ldy #$52
	tya
	cmp #$52
	beq TEST_TYA2
	lda #$15
	jmp FAILURE
TEST_TYA2


	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;  Test IMM and ACC addressing instructions
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
TEST_ADCIMM
	lda #$12
	sta POSTCODE
	clc
	lda #$23
	adc #$45
	cmp #$68
	beq TEST_ADCIMM2
	lda #$16
	jmp FAILURE
TEST_ADCIMM2
	sec
	lda #$42
	adc #$63
	cmp #$A6
	beq TEST_ADCIMM3
	lda #$17
	jmp FAILURE
TEST_ADCIMM3


TEST_ANDIMM
	lda #$13
	sta POSTCODE
	lda #$36
	and #$F0
	cmp #$30
	beq TEST_ANDIMM2
	lda #$18
	jmp FAILURE
TEST_ANDIMM2


TEST_ASLACC
	lda #$14
	sta POSTCODE
	clc
	lda #$36
	asl
	cmp #$6C
	beq TEST_ASLACC2
	lda #$19
	jmp FAILURE
TEST_ASLACC2


TEST_EORIMM
	lda #$15
	sta POSTCODE
	lda #$89
	eor #$96
	cmp #$1F
	beq TEST_EORIMM2
	lda #$20
	jmp FAILURE
TEST_EORIMM2


TEST_LSRACC
	lda #$16
	sta POSTCODE
	clc
	lda #$52
	lsr
	cmp #$29
	beq TEST_LSRACC2
	lda #$21
	jmp FAILURE
TEST_LSRACC2


TEST_ORAIMM
	lda #$17
	sta POSTCODE
	lda #$B6
	ora #$4D
	cmp #$FF
	beq TEST_ORAIMM2
	lda #$22
	jmp FAILURE
TEST_ORAIMM2


TEST_ROLACC
	lda #$18
	sta POSTCODE
	clc
	lda #$23
	rol
	cmp #$46
	beq TEST_ROLACC2
	lda #$23
	jmp FAILURE
TEST_ROLACC2
	sec
	lda #$42
	rol
	cmp #$85
	beq TEST_ROLACC3
	lda #$24
	jmp FAILURE
TEST_ROLACC3


TEST_RORACC
	lda #$19
	sta POSTCODE
	clc
	lda #$23
	ror
	cmp #$11
	beq TEST_RORACC2
	lda #$25
	jmp FAILURE
TEST_RORACC2
	sec
	lda #$42
	ror
	cmp #$A1
	beq TEST_RORACC3
	lda #$26
	jmp FAILURE
TEST_RORACC3


TEST_SBCIMM
	lda #$20
	sta POSTCODE
	sec
	lda #$86
	sbc #$45
	cmp #$41
	beq TEST_SBCIMM2
	lda #$27
	jmp FAILURE
TEST_SBCIMM2
	clc
	lda #$89
	sbc #$23
	cmp #$65
	beq TEST_SBCIMM3
	lda #$28
	jmp FAILURE
TEST_SBCIMM3

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Test loads, stores, and ABS mode instructions
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

TEST_LDAABS
	lda #$21
	sta POSTCODE
	lda #$42
	sta TESTABS1
	lda #$9F
	sta TESTABS2
	lda TESTABS1
	cmp #$42
	beq TEST_LDAABS2
	lda #$29
	jmp FAILURE
TEST_LDAABS2
	lda TESTABS2
	cmp #$9F
	beq TEST_LDAABS3
	lda #$30
	jmp FAILURE
TEST_LDAABS3


TEST_ADCABS
	lda #$22
	sta POSTCODE
	lda #$94
	sta TESTABS2
	lda #$41
	sta TESTABS1
	lda #$53
	clc
	adc TESTABS1
	cmp TESTABS2
	beq TEST_ADCABS2
	lda #$31
	jmp FAILURE
TEST_ADCABS2
	lda #$8D
	sta TESTABS2
	lda #$98
	sta TESTABS1
	lda #$F4
	sec
	adc TESTABS1
	cmp TESTABS2
	beq TEST_ADCABS3
	lda #$32
	jmp FAILURE
TEST_ADCABS3


TEST_ANDABS
	lda #$23
	sta POSTCODE
	ldy #$84
	sty TESTABS2
	ldx #$B4
	stx TESTABS1
	lda #$86
	and TESTABS1
	cmp TESTABS2
	beq TEST_ANDABS2
	lda #$33
	jmp FAILURE
TEST_ANDABS2


TEST_ASLABS
	lda #$24
	sta POSTCODE
	ldx #$55
	stx TESTABS1
	asl TESTABS1
	lda TESTABS1
	cmp #$AA
	beq TEST_ASLABS2
	lda #$34
	jmp FAILURE
TEST_ASLABS2


TEST_CPXABS
	lda #$25
	sta POSTCODE
	lda #$53
	sta TESTABS1
	lda #$00
	ldx #$53
	cpx TESTABS1
	beq TEST_CPXABS2
	lda #$35
	jmp FAILURE
TEST_CPXABS2


TEST_CPYABS
	lda #$26
	sta POSTCODE
	lda #$45
	sta TESTABS1
	lda #$00
	ldy #$45
	cpy TESTABS1
	beq TEST_CPYABS2
	lda #$36
	jmp FAILURE
TEST_CPYABS2


TEST_DECABS
	lda #$27
	sta POSTCODE
	lda #$EF
	sta TESTABS1
	dec TESTABS1
	lda #$EE
	cmp TESTABS1
	beq TEST_DECABS2
	lda #$37
	jmp FAILURE
TEST_DECABS2
	lda #$01
	sta TESTABS1
	dec TESTABS1
	beq TEST_DECABS3  ; same as branch on zero
	lda #$38
	jmp FAILURE
TEST_DECABS3


TEST_INCABS
	lda #$28
	sta POSTCODE
	lda #$EF
	sta TESTABS1
	inc TESTABS1
	lda #$F0
	cmp TESTABS1
	beq TEST_INCABS2
	lda #$39
	jmp FAILURE
TEST_INCABS2
	lda #$FF
	sta TESTABS1
	inc TESTABS1
	beq TEST_INCABS3  ; same as branch on zero
	lda #$40
	jmp FAILURE
TEST_INCABS3


TEST_EORABS
	lda #$29
	sta POSTCODE
	ldy #$32
	sty TESTABS2
	ldx #$B4
	stx TESTABS1
	lda #$86
	eor TESTABS1
	cmp TESTABS2
	beq TEST_EORABS2
	lda #$41
	jmp FAILURE
TEST_EORABS2


TEST_ORAABS
	lda #$2A
	sta POSTCODE
	ldy #$B6
	sty TESTABS2
	ldx #$B4
	stx TESTABS1
	lda #$86
	ora TESTABS1
	cmp TESTABS2
	beq TEST_ORAABS2
	lda #$42
	jmp FAILURE
TEST_ORAABS2


TEST_ROLABS
	lda #$2B
	sta POSTCODE
	clc
	ldx #$AA
	stx TESTABS1
	rol TESTABS1
	bcs TEST_ROLABS2
	lda #$43
	jmp FAILURE
TEST_ROLABS2
	lda TESTABS1
	cmp #$54
	beq TEST_ROLABS3
	lda #$44
	jmp FAILURE
TEST_ROLABS3


TEST_RORABS
	lda #$2C
	sta POSTCODE
	clc
	ldx #$55
	stx TESTABS1
	ror TESTABS1
	bcs TEST_RORABS2
	lda #$45
	jmp FAILURE
TEST_RORABS2
	lda TESTABS1
	cmp #$2A
	beq TEST_RORABS3
	lda #$46
	jmp FAILURE
TEST_RORABS3


TEST_LSRABS
	lda #$2D
	sta POSTCODE
	ldx #$96
	stx TESTABS1
	lsr TESTABS1
	lda TESTABS1
	cmp #$4B
	beq TEST_LSRABS2
	lda #$47
	jmp FAILURE
TEST_LSRABS2


TEST_LDXABS:
	lda #$2E
	sta POSTCODE
	ldx #$42
	stx TESTABS1
	ldx #$9F
	stx TESTABS2
	ldx TESTABS1
	cpx #$42
	beq TEST_LDXABS2
	lda #$48
	jmp FAILURE
TEST_LDXABS2
	ldx TESTABS2
	cpx #$9F
	beq TEST_LDXABS3
	lda #$49
	jmp FAILURE
TEST_LDXABS3


TEST_LDYABS:
	lda #$2F
	sta POSTCODE
	ldy #$34
	sty TESTABS1
	ldy #$75
	sty TESTABS2
	ldy TESTABS1
	cpy #$34
	beq TEST_LDYABS2
	lda #$4A
	jmp FAILURE
TEST_LDYABS2
	ldy TESTABS2
	cpy #$75
	beq TEST_LDYABS3
	lda #$4B
	jmp FAILURE
TEST_LDYABS3


TEST_SBCABS
	lda #$30
	sta POSTCODE
	lda #$12
	sta TESTABS2
	lda #$41
	sta TESTABS1
	lda #$53
	sec
	sbc TESTABS1
	cmp TESTABS2
	beq TEST_SBCABS2
	lda #$4C
	jmp FAILURE
TEST_SBCABS2
	lda #$5B
	sta TESTABS2
	lda #$98
	sta TESTABS1
	lda #$F4
	clc
	sbc TESTABS1
	cmp TESTABS2
	beq TEST_SBCABS3
	lda #$4D
	jmp FAILURE
TEST_SBCABS3


TEST_PHP
	lda #$31
	sta POSTCODE
	lda #$42
	pha
	lda #$ED
	pha
	lda #$BE
	pha
	lda #$00
	pla
	cmp #$BE
	bne TEST_PHP2
	pla
	cmp #$ED
	bne TEST_PHP2
	pla
	cmp #$42
	bne TEST_PHP2
	jmp TEST_PHP3
TEST_PHP2
	lda #$4E
	jmp FAILURE
TEST_PHP3


	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;  Test ABS,X and ABS,Y instructions
	;;  and a couple of zero-page instructions
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
TEST_LDAABSX
	lda #$32
	sta POSTCODE
	ldx #$00
	clc
	lda #$03
	sta TESTABS1,x
	adc #$07
	inx
	sta TESTABS1,x
	adc #$07
	inx
	sta TESTABS1,x
	adc #$07
	inx
	sta TESTABS1,x
	adc #$07
	inx
	sta TESTABS1,x
	adc #$07
	inx
	sta TESTABS1,x
	adc #$07
	inx
	sta TESTABS1,x
	ldx #$00
	clc
	lda TESTABS1,x
	cmp #$03
	bne TEST_LDAABSX2
	inx
	lda TESTABS1,x
	cmp #$0A
	bne TEST_LDAABSX2
	inx
	lda TESTABS1,x
	cmp #$11
	bne TEST_LDAABSX2
	inx
	lda TESTABS1,x
	cmp #$18
	bne TEST_LDAABSX2
	inx
	lda TESTABS1,x
	cmp #$1F
	bne TEST_LDAABSX2
	inx
	lda TESTABS1,x
	cmp #$26
	bne TEST_LDAABSX2
	inx
	lda TESTABS1,x
	cmp #$2D
	bne TEST_LDAABSX2
	jmp TEST_LDAABSX3
TEST_LDAABSX2
	lda #$4F
	jmp FAILURE
TEST_LDAABSX3


TEST_LDAABSY
	lda #$33
	sta POSTCODE
	ldy #$00
	clc
	lda #$03
	sta TESTABS1,y
	adc #$07
	iny
	sta TESTABS1,y
	adc #$07
	iny
	sta TESTABS1,y
	adc #$07
	iny
	sta TESTABS1,y
	adc #$07
	iny
	sta TESTABS1,y
	adc #$07
	iny
	sta TESTABS1,y
	adc #$07
	iny
	sta TESTABS1,y
	ldy #$00
	clc
	lda TESTABS1,y
	cmp #$03
	bne TEST_LDAABSY2
	iny
	lda TESTABS1,y
	cmp #$0A
	bne TEST_LDAABSY2
	iny
	lda TESTABS1,y
	cmp #$11
	bne TEST_LDAABSY2
	iny
	lda TESTABS1,y
	cmp #$18
	bne TEST_LDAABSY2
	iny
	lda TESTABS1,y
	cmp #$1F
	bne TEST_LDAABSY2
	iny
	lda TESTABS1,y
	cmp #$26
	bne TEST_LDAABSY2
	iny
	lda TESTABS1,y
	cmp #$2D
	bne TEST_LDAABSY2
	jmp TEST_LDAABSY3
TEST_LDAABSY2
	lda #$50
	jmp FAILURE
TEST_LDAABSY3


TEST_ADCABSX
	lda #$34
	sta POSTCODE
	lda #$52
	sta TESTABS1
	lda #$24
	sta TESTABS2
	lda #$78
	sta TESTABS3
	lda #$00
	ldx #$00
	clc
	adc TESTABS1,x
	clc
	inx
	adc TESTABS1,x
	clc
	inx
	adc TESTABS1,x
	cmp #$EE
	beq TEST_ADCABSX2
	lda #$51
	jmp FAILURE
TEST_ADCABSX2


TEST_ADCABSY
	lda #$35
	sta POSTCODE
	lda #$68
	sta TESTABS1
	lda #$13
	sta TESTABS2
	lda #$95
	sta TESTABS3
	lda #$00
	ldy #$00
	clc
	adc TESTABS1,y
	clc
	iny
	adc TESTABS1,y
	clc
	iny
	adc TESTABS1,y
	cmp #$10
	beq TEST_ADCABSY2
	lda #$52
	jmp FAILURE
TEST_ADCABSY2


TEST_ANDABSY
	lda #$36
	sta POSTCODE
	lda #$34
	sta TESTABS1
	lda #$54
	sta TESTABS2
	lda #$97
	sta TESTABS3
	lda #$FF
	ldy #$00
	and TESTABS1,y
	iny
	and TESTABS1,y
	iny
	and TESTABS1,y
	cmp #$14
	beq TEST_ANDABSY2
	lda #$53
	jmp FAILURE
TEST_ANDABSY2


TEST_ANDABSX
	lda #$37
	sta POSTCODE
	lda #$34
	sta TESTABS1
	lda #$54
	sta TESTABS2
	lda #$97
	sta TESTABS3
	lda #$FF
	ldx #$00
	and TESTABS1,x
	inx
	and TESTABS1,x
	inx
	and TESTABS1,x
	cmp #$14
	beq TEST_ANDABSX2
	lda #$54
	jmp FAILURE
TEST_ANDABSX2


TEST_ADCZ
	lda #$38
	sta POSTCODE
	lda #$64
	sta TESTZ1
	lda #$39
	clc
	adc TESTZ1
	cmp #$9D
	beq TEST_ADCZ2
	lda #$55
	jmp FAILURE
TEST_ADCZ2


TEST_ADCZX
	lda #$39
	sta POSTCODE
	lda #$95
	sta TESTZ1
	lda #$76
	sta TESTZ2
	lda #$45
	sta TESTZ3
	ldx #$00
	lda #$00
	clc
	adc TESTZ1,x
	inx
	clc
	adc TESTZ1,x
	inx
	clc
	adc TESTZ1,x
	cmp #$50
	beq TEST_ADCZX2
	lda #$56
	jmp FAILURE
TEST_ADCZX2


TEST_ANDZ
	lda #$3A
	sta POSTCODE
	lda #$64
	sta TESTZ1
	lda #$39
	and TESTZ1
	cmp #$20
	beq TEST_ANDZ2
	lda #$57
	jmp FAILURE
TEST_ANDZ2


TEST_ANDZX
	lda #$3B
	sta POSTCODE
	lda #$95
	sta TESTZ1
	lda #$76
	sta TESTZ2
	lda #$45
	sta TESTZ3
	ldx #$00
	lda #$FF
	and TESTZ1,x
	inx
	and TESTZ1,x
	inx
	and TESTZ1,x
	cmp #$04
	beq TEST_ANDZX2
	lda #$58
	jmp FAILURE
TEST_ANDZX2


TEST_CMPABSX
	lda #$3C
	sta POSTCODE
	lda #$97
	sta TESTABS1
	lda #$78
	sta TESTABS2
	lda #$45
	sta TESTABS3
	ldx #$00
	lda #$97
	cmp TESTABS1,x
	bne TEST_CMPABSX2
	lda #$78
	inx
	cmp TESTABS1,x
	bne TEST_CMPABSX2
	lda #$45
	inx
	cmp TESTABS1,x
	bne TEST_CMPABSX2
	jmp TEST_CMPABSX3
TEST_CMPABSX2
	lda #$59
	jmp FAILURE
TEST_CMPABSX3


TEST_CMPABSY
	lda #$3D
	sta POSTCODE
	lda #$97
	sta TESTABS1
	lda #$78
	sta TESTABS2
	lda #$45
	sta TESTABS3
	ldy #$00
	lda #$97
	cmp TESTABS1,y
	bne TEST_CMPABSY2
	lda #$78
	iny
	cmp TESTABS1,y
	bne TEST_CMPABSY2
	lda #$45
	iny
	cmp TESTABS1,y
	bne TEST_CMPABSY2
	jmp TEST_CMPABSY3
TEST_CMPABSY2
	lda #$5A
	jmp FAILURE
TEST_CMPABSY3


TEST_CMPZX
	lda #$3E
	sta POSTCODE
	lda #$97
	sta TESTABS1
	lda #$78
	sta TESTABS2
	lda #$45
	sta TESTABS3
	ldx #$00
	lda #$97
	cmp TESTABS1,x
	bne TEST_CMPZX2
	lda #$78
	inx
	cmp TESTABS1,x
	bne TEST_CMPZX2
	lda #$45
	inx
	cmp TESTABS1,x
	bne TEST_CMPZX2
	jmp TEST_CMPZX3
TEST_CMPZX2
	lda #$5B
	jmp FAILURE
TEST_CMPZX3


TEST_CMPZ
	lda #$3F
	sta POSTCODE
	lda #$95
	sta TESTZ3
	lda #$00
	lda #$95
	cmp TESTZ3
	beq TEST_CMPZ2
	lda #$5C
	jmp FAILURE
TEST_CMPZ2
	lda #$75
	sta TESTZ3
	lda #$67
	cmp TESTZ3
	bne TEST_CMPZ3
	lda #$5D
	jmp FAILURE
TEST_CMPZ3


TEST_CPXZ
	lda #$40
	sta POSTCODE
	lda #$36
	sta TESTZ3
	lda #$00
	ldx #$36
	cpx TESTZ3
	beq TEST_CPXZ2
	lda #$5E
	jmp FAILURE
TEST_CPXZ2
	lda #$57
	sta TESTZ3
	ldx #$39
	cpx TESTZ3
	bne TEST_CPXZ3
	lda #$5F
	jmp FAILURE
TEST_CPXZ3


TEST_CPYZ
	lda #$41
	sta POSTCODE
	lda #$75
	sta TESTZ3
	lda #$00
	ldy #$75
	cpy TESTZ3
	beq TEST_CPYZ2
	lda #$60
	jmp FAILURE
TEST_CPYZ2
	lda #$43
	sta TESTZ3
	ldy #$24
	cpy TESTZ3
	bne TEST_CPYZ3
	lda #$61
	jmp FAILURE
TEST_CPYZ3

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Let's test some interrupts!
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
TEST_IRQ
	lda #$42
	sta POSTCODE
	cli
	lda #$00
	sta IRQ_COUNT
	lda #$01
	sta IRQ_ALLOW
	lda #$10
	sta IRQ_CLEAR
	sta IRQ_TIMER
	ldx #$00
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	cpx #$10
	beq TEST_IRQ1
	lda #$62
	jmp FAILURE
TEST_IRQ1
	lda IRQ_COUNT
	cmp #$01
	beq TEST_IRQ2
	lda #$63
	jmp FAILURE
TEST_IRQ2
	sei
	lda #$00
	sta IRQ_COUNT
	lda #$01
	sta IRQ_ALLOW
	lda #$10
	sta IRQ_CLEAR
	sta IRQ_TIMER
	ldx #$00
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	cpx #$10
	beq TEST_IRQ3
	lda #$62
	jmp FAILURE
TEST_IRQ3
	lda IRQ_COUNT
	cmp #$00
	beq TEST_IRQ4
	lda #$63
	jmp FAILURE
TEST_IRQ4
	lda #$00
	sta IRQ_ALLOW
	sta IRQ_CLEAR


TEST_NMI
	lda #$43
	sta POSTCODE
	lda #$00
	sta NMI_COUNT
	lda #$01
	sta NMI_ALLOW
	lda #$10
	sta NMI_CLEAR
	sta NMI_TIMER
	ldx #$00
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	inx
	cpx #$10
	beq TEST_NMI1
	lda #$64
	jmp FAILURE
TEST_NMI1
	lda NMI_COUNT
	cmp #$01
	beq TEST_NMI2
	lda #$65
	jmp FAILURE
TEST_NMI2
	lda #$00
	sta NMI_ALLOW
	sta NMI_CLEAR


	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;  Test for some bugs found in v0.3
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
TEST_BCCNEG
	lda #$44
	sta POSTCODE
	jmp TEST_BCCNEG1	
TEST_BCCNEG2
	jmp TEST_BCCNEG3
TEST_BCCNEG1
	sec
	bcs TEST_BCCNEG2
	; To make this totally robust there should be 256 nop's here
	nop
	nop
	nop
	lda #$66
	jmp FAILURE
TEST_BCCNEG3


TEST_SBCIMMFLAGS
	lda #$45
	sta POSTCODE	
	sec
	lda #$34
	sbc #$75
	bcc TEST_SBCIMMFLAGS2
	lda #$67
	jmp FAILURE	
TEST_SBCIMMFLAGS2


TEST_STACK
	lda #$46
	sta POSTCODE
	tsx
	stx TESTZ1
	lda #$42
	pha
	lda #$00  ; zero out acc
	tsx
	inx
	lda $0100,x
	cmp #$42
	beq TEST_STACK1
	lda #$68
	jmp FAILURE
TEST_STACK1
	lda #$69
	sta $0112
	lda #$00
	ldx #$11
	txs
	pla
	cmp #$69
	beq TEST_STACK2
	lda #$69
	jmp FAILURE
TEST_STACK2
	ldx TESTZ1
	txs
TEST_STACK3	

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
TEST_BRK
	lda #$47
	sta POSTCODE
	lda #$00
	pha
	plp
	stx IRQ_STATUS
	lda #$00
	sta IRQ_COUNT
	lda #$01
	sta IRQ_ALLOW
	ldx #$59
	brk
	inx ; Note:  This instruction should be skipped by the CPU
	lda #$00
	sta IRQ_ALLOW
	lda IRQ_COUNT
	cmp #$01
	beq TEST_BRK2
	lda #$70
	jmp FAILURE
TEST_BRK2
	lda IRQ_STATUS
	and #$10
	bne TEST_BRK3
	lda #$71
	jmp FAILURE
TEST_BRK3
	cpx #$59
	beq TEST_BRK4
	lda #$72
	jmp FAILURE
TEST_BRK4

	; Test for proper wrap around in Zero-Page,X addressing modes
	; We use fixed (hard-coded address for this, yick!)
TEST_ZPX
	lda #$48
	sta POSTCODE
	lda #$53
	sta $30
	lda #$00
	ldx #$40
	lda $F0,x
	cmp #$53
	beq TEST_ZPX2
	lda #$73
	jmp FAILURE
TEST_ZPX2

	; Test for proper generation of the C and V flags
TEST_CFLAG
	lda #$49
	sta POSTCODE	
        clc
        lda #$ff
        adc #$01
        bcs TEST_CFLAG1
        lda #$74
        jmp FAILURE
TEST_CFLAG1


TEST_VFLAG
	lda #$4A
	sta POSTCODE
        sec
        lda #$7f                
        sbc #$7e ; 7f - 7e - ~c = 01
        bvc TEST_VFLAG1
        lda #$75
        jmp FAILURE
TEST_VFLAG1        


	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
SUCCESS
	sei
	lda #$FF
	sta POSTCODE
	sta HALT
	jmp SUCCESS

FAILURE
        sei
	sta HALT
	jmp FAILURE


	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Our interrupt handlers
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
IRQ_ISR
	pha	; Save the registers
	txa
	pha
	tya
	pha

	tsx	; Take the status register and save it
	inx
	inx
	inx
	inx
	lda $0100,x
	sta IRQ_STATUS
	
	
	lda IRQ_ALLOW
	cmp #$00
	bne IRQ_ALLOWED
	lda #$E0
	jmp FAILURE
IRQ_ALLOWED
        sta IRQ_CLEAR
        inc IRQ_COUNT

        pla	; Restore the registers
        tay
        pla
        tax
        pla
        rti


NMI_ISR
	pha	; Save the registers
	txa
	pha
	tya
	pha
	
	lda NMI_ALLOW
	cmp #$00
	bne NMI_ALLOWED
	lda #$E0
	jmp FAILURE
NMI_ALLOWED
        sta NMI_CLEAR
        inc NMI_COUNT
        
        pla	; Restore the registers
        tay
        pla
        tax
        pla
        rti

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


IRQ	    jmp     IRQ_ISR
NMI	    jmp     NMI_ISR

            ;   VECTOR  ------------------------------------------------
 
            seg     vector
            org     $FFFA
            dc.w    NMI
            dc.w    RESET
            dc.w    IRQ
 
PROMEND     equ     .
 



