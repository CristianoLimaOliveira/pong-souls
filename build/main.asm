;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.1.6 #12539 (MINGW32)
;--------------------------------------------------------
	.module main
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _set_sprite_data
	.globl _Parede
	.globl _Bola
	.globl _Barra
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
_Barra::
	.ds 16
_Bola::
	.ds 16
_Parede::
	.ds 16
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;..\src\main.c:7: void main(){
;	---------------------------------
; Function main
; ---------------------------------
_main::
;..\src\main.c:11: SPRITES_8x8;
	ldh	a, (_LCDC_REG + 0)
	and	a, #0xfb
	ldh	(_LCDC_REG + 0), a
;..\src\main.c:16: set_sprite_data(0, 1, Barra);
	ld	de, #_Barra
	push	de
	xor	a, a
	inc	a
	push	af
	call	_set_sprite_data
	add	sp, #4
;C:/Users/Glenio Lobo/Desktop/Faculdade/Interface Hardware Software/pong-souls/gbdk/include/gb/gb.h:1326: shadow_OAM[nb].tile=tile;
	ld	hl, #(_shadow_OAM + 14)
	ld	(hl), #0x00
;C:/Users/Glenio Lobo/Desktop/Faculdade/Interface Hardware Software/pong-souls/gbdk/include/gb/gb.h:1399: OAM_item_t * itm = &shadow_OAM[nb];
	ld	bc, #_shadow_OAM+12
;C:/Users/Glenio Lobo/Desktop/Faculdade/Interface Hardware Software/pong-souls/gbdk/include/gb/gb.h:1400: itm->y=y, itm->x=x;
	xor	a, a
	ld	(bc), a
	inc	bc
	xor	a, a
	ld	(bc), a
;..\src\main.c:20: set_sprite_data(1, 1, Bola);
	ld	de, #_Bola
	push	de
	ld	hl, #0x101
	push	hl
	call	_set_sprite_data
	add	sp, #4
;C:/Users/Glenio Lobo/Desktop/Faculdade/Interface Hardware Software/pong-souls/gbdk/include/gb/gb.h:1326: shadow_OAM[nb].tile=tile;
	ld	hl, #(_shadow_OAM + 6)
	ld	(hl), #0x01
;C:/Users/Glenio Lobo/Desktop/Faculdade/Interface Hardware Software/pong-souls/gbdk/include/gb/gb.h:1399: OAM_item_t * itm = &shadow_OAM[nb];
	ld	hl, #(_shadow_OAM + 4)
;C:/Users/Glenio Lobo/Desktop/Faculdade/Interface Hardware Software/pong-souls/gbdk/include/gb/gb.h:1400: itm->y=y, itm->x=x;
	ld	a, #0x10
	ld	(hl+), a
	ld	(hl), #0x58
;..\src\main.c:24: set_sprite_data(2, 1, Parede);
	ld	de, #_Parede
	push	de
	ld	hl, #0x102
	push	hl
	call	_set_sprite_data
	add	sp, #4
;C:/Users/Glenio Lobo/Desktop/Faculdade/Interface Hardware Software/pong-souls/gbdk/include/gb/gb.h:1326: shadow_OAM[nb].tile=tile;
	ld	hl, #(_shadow_OAM + 10)
	ld	(hl), #0x02
;C:/Users/Glenio Lobo/Desktop/Faculdade/Interface Hardware Software/pong-souls/gbdk/include/gb/gb.h:1399: OAM_item_t * itm = &shadow_OAM[nb];
	ld	hl, #(_shadow_OAM + 8)
;C:/Users/Glenio Lobo/Desktop/Faculdade/Interface Hardware Software/pong-souls/gbdk/include/gb/gb.h:1400: itm->y=y, itm->x=x;
	ld	a, #0x98
	ld	(hl+), a
	ld	(hl), #0x50
;..\src\main.c:28: SHOW_SPRITES;
	ldh	a, (_LCDC_REG + 0)
	or	a, #0x02
	ldh	(_LCDC_REG + 0), a
;..\src\main.c:51: }
	ret
	.area _CODE
	.area _INITIALIZER
__xinit__Barra:
	.db #0x18	; 24
	.db #0x1c	; 28
	.db #0x18	; 24
	.db #0x1c	; 28
	.db #0x18	; 24
	.db #0x1c	; 28
	.db #0x18	; 24
	.db #0x1c	; 28
	.db #0x18	; 24
	.db #0x1c	; 28
	.db #0x18	; 24
	.db #0x1c	; 28
	.db #0x18	; 24
	.db #0x1c	; 28
	.db #0x18	; 24
	.db #0x1c	; 28
__xinit__Bola:
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x3c	; 60
	.db #0x3c	; 60
	.db #0x7e	; 126
	.db #0x7e	; 126
	.db #0x7e	; 126
	.db #0x7e	; 126
	.db #0x7e	; 126
	.db #0x7e	; 126
	.db #0x7e	; 126
	.db #0x7e	; 126
	.db #0x3c	; 60
	.db #0x3c	; 60
	.db #0x00	; 0
	.db #0x00	; 0
__xinit__Parede:
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0x08	; 8
	.db #0xff	; 255
	.db #0xff	; 255
	.db #0x00	; 0
	.db #0x00	; 0
	.area _CABS (ABS)
