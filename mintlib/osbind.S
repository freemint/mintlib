|
| new osbind.c definitions for the MiNT library. With these ones, we
| are now compatible with the rest of the atari world when using 16 bit
| integers, and the 32 bit code stuff should be portable, at least
| (albeit slower than the old osbind.c)
|
#ifdef __MSHORT__
	.globl	_gemdos
	.globl	_xbios
	.globl	_bios

	.text
	.even
_gemdos:
	lea	sp@(20), a0	| 4 bytes for ret addr + 16 for parameters
	moveml	d2/a2, sp@-	| save reggies that TOS clobbers but that
				| gcc thinks functions should preserve
	movel	a0@-, sp@-	| max. of 16 bytes parameters to trap #1
	movel	a0@-, sp@-
	movel	a0@-, sp@-
	movel	a0@-, sp@-
	trap	#1		| go do the trap
	lea	sp@(16), sp	| pop parameters
	moveml	sp@+, d2/a2	| restore reggies
	rts			| return

_bios:
	lea	sp@(24), a0	| 4 bytes ret. addr. + 20 bytes parameters
	moveml	d2/a2, sp@-
	movel	a0@-, sp@-	| copy 20 bytes of trap #13 parameters
	movel	a0@-, sp@-	| looks like it only needs 14 bytes max
	movel	a0@-, sp@-
	movel	a0@-, sp@-
	movel	a0@-, sp@-
	trap	#13		| go do the trap
	lea	sp@(20), sp
	moveml	sp@+, d2/a2
	rts

_xbios:
	lea	sp@(32), a0	| 28 bytes of parameters
	moveml	d2/a2, sp@-
	movel	a0@-, sp@-	| copy 28 bytes
	movel	a0@-, sp@-	| looks like only 26 needed
	movel	a0@-, sp@-
	movel	a0@-, sp@-
	movel	a0@-, sp@-
	movel	a0@-, sp@-
	movel	a0@-, sp@-
	trap	#14		| go do the trap
	lea	sp@(28), sp
	moveml	sp@+, d2/a2
	rts

#else	/* !__MSHORT__ */
	.text
	.even
	.globl	_trap_1_w
_trap_1_w:
	moveml	d2/a2, sp@-
	movew	sp@(14), sp@-
	trap	#1
	addql	#2, sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_1_ww
_trap_1_ww:
	moveml	d2/a2, sp@-
	movew	sp@(18), sp@-
	movew	sp@(14+2), sp@-
	trap	#1
	addql	#4, sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_1_wl
_trap_1_wl:
	moveml	d2/a2, sp@-
	movel	sp@(16), sp@-
	movew	sp@(14+4), sp@-
	trap	#1
	addql	#6, sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_1_wlw
_trap_1_wlw:
	moveml	d2/a2, sp@-
	movew	sp@(22), sp@-
	movel	sp@(16+2), sp@-
	movew	sp@(14+6), sp@-
	trap	#1
	addql	#8, sp		| addq is valid for 1-8
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_1_wwl
_trap_1_wwl:
	moveml	d2/a2, sp@-
	movel	sp@(20), sp@-
	movew	sp@(18+4), sp@-
	movew	sp@(14+6), sp@-
	trap	#1
	addql	#8, sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_1_www
_trap_1_www:
	moveml	d2/a2, sp@-
	movew	sp@(22), sp@-
	movew	sp@(18+2), sp@-
	movew	sp@(14+4), sp@-
	trap	#1
	addql	#6, sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_1_wll
_trap_1_wll:
	moveml	d2/a2, sp@-
	movel	sp@(20), sp@-
	movel	sp@(16+4), sp@-
	movew	sp@(14+8), sp@-
	trap	#1
	lea	sp@(10), sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_1_wwww
_trap_1_wwww:
	moveml	d2/a1, sp@-
	movew	sp@(26), sp@-
	movew	sp@(22+2), sp@-
	movew	sp@(18+4), sp@-
	movew	sp@(14+6), sp@-
	trap	#1
	addql	#8, sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_1_wwwl
_trap_1_wwwl:
	moveml	d2/a1, sp@-
	movel	sp@(24), sp@-
	movew	sp@(22+4), sp@-
	movew	sp@(18+6), sp@-
	movew	sp@(14+8), sp@-
	trap	#1
	addw	#10, sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_1_wwll
_trap_1_wwll:
	moveml	d2/a2, sp@-
	movel	sp@(24), sp@-
	movel	sp@(20+4), sp@-
	movew	sp@(18+8), sp@-
	movew	sp@(14+10), sp@-
	trap	#1
	lea	sp@(12), sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_1_wlww
_trap_1_wlww:
	moveml	d2/a2, sp@-
	movew	sp@(26), sp@-
	movew	sp@(22+2), sp@-
	movel	sp@(16+4), sp@-
	movew	sp@(14+8), sp@-
	trap	#1
	lea	sp@(10), sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_1_wwlw
_trap_1_wwlw:
	moveml	d2/a2, sp@-
	movew	sp@(26), sp@-
	movel	sp@(20+2), sp@-
	movew	sp@(18+6), sp@-
	movew	sp@(14+8), sp@-
	trap	#1
	lea	sp@(10), sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_1_wwlll
_trap_1_wwlll:
	moveml	d2/a2, sp@-
	movel	sp@(28), sp@-
	movel	sp@(24+4), sp@-
	movel	sp@(20+8), sp@-
	movew	sp@(18+12), sp@-
	movew	sp@(14+14), sp@-
	trap	#1
	lea	sp@(16), sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_1_wwwll
_trap_1_wwwll:
	moveml	d2/a2, sp@-
	movel	sp@(28), sp@-
	movel	sp@(24+4), sp@-
	movew	sp@(22+8), sp@-
	movew	sp@(18+10), sp@-
	movew	sp@(14+12), sp@-
	trap	#1
	lea	sp@(14), sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_1_wwllll
_trap_1_wwllll:
	moveml	d2/a2,sp@-
	movel	sp@(32),sp@-
	movel	sp@(28+4),sp@-
	movel	sp@(24+8),sp@-
	movel	sp@(20+12),sp@-
	movew	sp@(18+16),sp@-
	movew	sp@(14+18),sp@-
	trap	#1
	lea	sp@(20),sp
	moveml	sp@+,d2/a2
	rts

	.globl	_trap_13_w
_trap_13_w:
	moveml	d2/a2, sp@-
	movew	sp@(14), sp@-
	trap	#13
	addql	#2, sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_13_ww
_trap_13_ww:
	moveml	d2/a2, sp@-
	movew	sp@(18), sp@-
	movew	sp@(14+2), sp@-
	trap	#13
	addql	#4, sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_13_wl
_trap_13_wl:
	moveml	d2/a2, sp@-
	movel	sp@(16), sp@-
	movew	sp@(14+4), sp@-
	trap	#13
	addql	#6, sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_13_www
_trap_13_www:
	moveml	d2/a2, sp@-
	movew	sp@(22), sp@-
	movew	sp@(18+2), sp@-
	movew	sp@(14+4), sp@-
	trap	#13
	addql	#6, sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_13_wwl
_trap_13_wwl:
	moveml	d2/a2, sp@-
	movel	sp@(20), sp@-
	movew	sp@(18+4), sp@-
	movew	sp@(14+6), sp@-
	trap	#13
	addql	#8, sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_13_wwlwww
_trap_13_wwlwww:
	moveml	d2/a2, sp@-
	movew	sp@(34), sp@-
	movew	sp@(30+2), sp@-
	movew	sp@(26+4), sp@-
	movel	sp@(20+6), sp@-
	movew	sp@(18+10), sp@-
	movew	sp@(14+12), sp@-
	trap	#13
	lea	sp@(14), sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_14_w
_trap_14_w:
	moveml	d2/a2, sp@-
	movew	sp@(14), sp@-
	trap	#14
	addql	#2, sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_14_ww
_trap_14_ww:
	moveml	d2/a2, sp@-
	movew	sp@(18), sp@-
	movew	sp@(14+2), sp@-
	trap	#14
	addql	#4, sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_14_wl
_trap_14_wl:
	moveml	d2/a2, sp@-
	movel	sp@(16), sp@-
	movew	sp@(14+4), sp@-
	trap	#14
	addql	#6, sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_14_www
_trap_14_www:
	moveml	d2/a2, sp@-
	movew	sp@(22), sp@-
	movew	sp@(18+2), sp@-
	movew	sp@(14+4), sp@-
	trap	#14
	addql	#6, sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_14_wwl
_trap_14_wwl:
	moveml	d2/a2, sp@-
	movel	sp@(20), sp@-
	movew	sp@(18+4), sp@-
	movew	sp@(14+6), sp@-
	trap	#14
	addql	#8, sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_14_wwll
_trap_14_wwll:
	moveml	d2/a2, sp@-
	movel	sp@(24), sp@-
	movel	sp@(20+4), sp@-
	movew	sp@(18+8), sp@-
	movew	sp@(14+10), sp@-
	trap	#14
	lea	sp@(12), sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_14_wllw
_trap_14_wllw:
	moveml	d2/a2, sp@-
	movew	sp@(26), sp@-
	movel	sp@(20+2), sp@-
	movel	sp@(16+6), sp@-
	movew	sp@(14+10), sp@-
	trap	#14
	lea	sp@(12), sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_14_wlll
_trap_14_wlll:
	moveml	d2/a2, sp@-
	movel	sp@(24), sp@-
	movel	sp@(20+4), sp@-
	movel	sp@(16+8), sp@-
	movew	sp@(14+12), sp@-
	trap	#14
	lea	sp@(14), sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_14_wwwl
_trap_14_wwwl:
	moveml	d2/a2, sp@-
	movel	sp@(24), sp@-
	movew	sp@(22+4), sp@-
	movew	sp@(18+6), sp@-
	movew	sp@(14+8), sp@-
	trap	#14
	lea	sp@(10), sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_14_wwwwl
_trap_14_wwwwl:
	moveml	d2/a2, sp@-
	movel	sp@(28), sp@-
	movew	sp@(26+4), sp@-
	movew	sp@(22+6), sp@-
	movew	sp@(18+8), sp@-
	movew	sp@(14+10), sp@-
	trap	#14
	lea	sp@(12), sp
	moveml	sp@+, d2/a2
	rts
	
	.globl	_trap_14_wllww
_trap_14_wllww:
	moveml	d2/a2, sp@-
	movew	sp@(30), sp@-
	movew	sp@(26+2), sp@-
	movel	sp@(20+4), sp@-
	movel	sp@(16+8), sp@-
	movew	sp@(14+12), sp@-
	trap	#14
	lea	sp@(14), sp
	moveml	sp@+, d2/a2
	rts
	
	.globl	_trap_14_wlwlw
_trap_14_wlwlw:
	moveml	d2/a2, sp@-
	movew	sp@(30), sp@-
	movel	sp@(24+2), sp@-
	movew	sp@(22+6), sp@-
	movel	sp@(16+8), sp@-
	movew	sp@(14+12), sp@-
	trap	#14
	lea	sp@(14), sp
	moveml	sp@+, d2/a2
	rts
	
	.globl	_trap_14_wllll
_trap_14_wllll:
	moveml	d2/a2,sp@-
	movel	sp@(28),sp@-
	movel	sp@(24+4),sp@-
	movel	sp@(20+8),sp@-
	movel	sp@(16+12),sp@-
	movew	sp@(14+16),sp@-
	trap	#14
	lea	sp@(18),sp
	moveml	sp@+,d2/a2
	rts

	.globl	_trap_14_wwwwww
_trap_14_wwwwww:
	moveml	d2/a2, sp@-
	movew	sp@(34), sp@-
	movew	sp@(30+2), sp@-
	movew	sp@(26+4), sp@-
	movew	sp@(22+6), sp@-
	movew	sp@(18+8), sp@-
	movew	sp@(14+10), sp@-
	trap	#14
	lea	sp@(12), sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_14_wllllll
_trap_14_wllllll:
	moveml	d2/a2,sp@-
	movel	sp@(36),sp@-
	movel	sp@(32+4),sp@-
	movel	sp@(28+8),sp@-
	movel	sp@(24+12),sp@-
	movel	sp@(20+16),sp@-
	movel	sp@(16+20),sp@-
	movew	sp@(14+24),sp@-
	trap	#14
	lea	sp@(26),sp
	moveml	sp@+,d2/a2
	rts

	.globl	_trap_14_wwwwwww
_trap_14_wwwwwww:
	moveml	d2/a2, sp@-
	movew	sp@(38), sp@-
	movew	sp@(34+2), sp@-
	movew	sp@(30+4), sp@-
	movew	sp@(26+6), sp@-
	movew	sp@(22+8), sp@-
	movew	sp@(18+10), sp@-
	movew	sp@(14+12), sp@-
	trap	#14
	lea	sp@(14), sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_14_wllwwwww
_trap_14_wllwwwww:
	moveml	d2/a2, sp@-
	movew	sp@(42), sp@-
	movew	sp@(38+2), sp@-
	movew	sp@(34+4), sp@-
	movew	sp@(30+6), sp@-
	movew	sp@(26+8), sp@-
	movel	sp@(20+10), sp@-
	movel	sp@(16+14), sp@-
	movew	sp@(14+18), sp@-
	trap	#14
	lea	sp@(20), sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_14_wllwwwwlw
_trap_14_wllwwwwlw:
	moveml	d2/a2, sp@-
	movew	sp@(46), sp@-
	movel	sp@(40+2), sp@-
	movew	sp@(38+6), sp@-
	movew	sp@(34+8), sp@-
	movew	sp@(30+10), sp@-
	movew	sp@(26+12), sp@-
	movel	sp@(20+14), sp@-
	movel	sp@(16+18), sp@-
	movew	sp@(14+22), sp@-
	trap	#14
	lea	sp@(24), sp
	moveml	sp@+, d2/a2
	rts

	.globl	_trap_14_wllwwwwwlw
_trap_14_wllwwwwwlw:
	moveml	d2/a2, sp@-
	movew	sp@(50), sp@-
	movel	sp@(44+2), sp@-
	movew	sp@(42+6), sp@-
	movew	sp@(38+8), sp@-
	movew	sp@(34+10), sp@-
	movew	sp@(30+12), sp@-
	movew	sp@(26+14), sp@-
	movel	sp@(20+16), sp@-
	movel	sp@(16+20), sp@-
	movew	sp@(14+24), sp@-
	trap	#14
	lea	sp@(26), sp
	moveml	sp@+, d2/a2
	rts
#endif

