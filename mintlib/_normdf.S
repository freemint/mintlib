| mjr: not needed _normdf for -__M68881__ or the sfp004

|#######################################################################

| double floating point normalization routine
|
| written by Kai-Uwe Bloem (I5110401@dbstu1.bitnet).
| Based on a 80x86 floating point packet from comp.os.minix, written by P.Housel
|
| Revision 1.6.3 michal 05-93 (ntomczak@vm.ucs.ualberta.ca)
|  + restored and ensured future synchronization with errno codes
|  + removed bogus error when normalizing legitimate zero
|  + small mods to shave off few cycles
|
| patched by Olaf Flebbe (flebbe@tat.physik.uni-tuebingen.de)
|
| Revision 1.6.2 olaf 12-92:
|  + added support for -0.
|
| Revision 1.6.1 olaf 10-92:
|  + corrected rounding in tie case: round up, not down.
|    (needed for enquire 4.3)
|
| Revision 1.6, kub 04-90 :
| more robust handling exponent and sign handling for 32 bit integers. There
| are now overflow tests for 32 bit exponents, and bit 31 of the sign flag
| is or ed to bit 15 for later checks (i.e. both bits 31 and 15 are now sign
| bits). Take care, the upper 16 bits of rounding info are ignored for 32 bit
| integers !
|
| Revision 1.5, ++jrb 03-90:
| change __normdf interface to expect ints instead of shorts. easier
| to interface to 32 bit int code. this file is now pre-processed,
| with __MSHORT__ defined when ints are 16 bits.
|
| Revision 1.4, kub 03-90 :
| export ___normdf entry to C language. Rename the internal entry to a name
| not accessible from C to prevent crashes
|
| Revision 1.3, kub 01-90 :
| added support for denormalized numbers
|
| Revision 1.2, kub 01-90 :
| replace far shifts by swaps to gain speed
|
| Revision 1.1, kub 12-89 :
| Ported over to 68k assembler
|
| Revision 1.0:
| original 8088 code from P.S.Housel

	.text
	.even
	.globl	__infinitydf

#if !defined (__M68881__) && !defined (sfp004)
	.globl	___normdf
	.globl	___norm_df
#include "errbase.h"
# ifdef	ERROR_CHECK
LC0:
	.ascii "normdf: OVERFLOW\12\15\0"
	.even
# endif	ERROR_CHECK

	| C entry, for procs dealing with the internal representation :
	| double __normdf(long long mant, int exp, int sign, int rbits);
___normdf:
	lea	sp@(4),a0	| parameter pointer
	moveml	d2-d7,sp@-	| save working registers
	moveml	a0@+,d4-d5	| get mantissa

# ifdef __MSHORT__
	movew	a0@+,d0		| get exponent
	movew	a0@+,d2		| get sign
	movew	a0@+,d1		| rounding information
# else
	movel	a0@+,d0		| get exponent
	movel	a0@+,d2		| get sign
	jpl	0f		| or bit 31 to bit 15 for later tests
	bset	#15,d2
0:	movel	a0@+,d1		| rounding information

	movel	#0x7fff,d3
	cmpl	d3,d0		| test exponent
	jgt	oflow
	notl	d3		| #-0x8000 -> d3
	cmpl	d3,d0
	jlt	retz
# endif

	| internal entry for floating point package, saves time
	| d0=u.exp, d2=u.sign, d1=rounding bits, d4/d5=mantissa
	| registers d2-d7 must be saved on the stack !
___norm_df:
	movel	d4,d3		| rounding and u.mant == 0 ?
	orl	d5,d3
	jne	1f
	tstb	d1
	jeq	retzok
1:
	movel	d4,d3
	andl	#0xfffff000,d3	| fast shift, 16 bits ?
	jne	2f
	cmpw	#9,d0		| shift is going to far; do normal shift
	jle	2f		|  (minimize shifts here : 10l = 16l + 6r)
	swap	d4		| yes, swap register halfs
	swap	d5
	movew	d5,d4
	moveb	d1,d5		| some doubt about this one !
	lslw	#8,d5
	clrw	d1
	subw	#16,d0		| account for swap
	jra	1b
2:
	clrb	d2		| sticky byte
	movel	#0xffe00000,d6
3:	tstw	d0		| divide (shift)
	jle	0f		|  denormalized number
	movel	d4,d3
	andl	d6,d3		|  or until no bits above 53
	jeq	4f
0:	addw	#1,d0		| increment exponent
	lsrl	#1,d4
	roxrl	#1,d5
	orb	d1,d2		| set sticky
	roxrb	#1,d1		| shift into rounding bits
	jra	3b
4:
	andb	#1,d2
	orb	d2,d1		| make least sig bit sticky
	asrl	#1,d6		| #0xfff00000 -> d6
5:	movel	d4,d3		| multiply (shift) until
	andl	d6,d3		| one in implied position
	jne	6f
	subw	#1,d0		| decrement exponent
	jeq	6f		|  too small. store as denormalized number
	addb	d1,d1		| some doubt about this one *
	addxl	d5,d5
	addxl	d4,d4
	jra	5b
6:
	tstb	d1		| check rounding bits
	jge	8f		| round down - no action neccessary
	negb	d1
	jvc	7f		| round up
        movew   d5,d1           | tie case - round to even
                                | dont need rounding bits any more
        andw    #1,d1           | check if even
        jeq     8f              | mantissa is even - no action necessary
                                | fall through
7:
	clrl	d1		| zero rounding bits
	addl	#1,d5
	addxl	d1,d4
	tstw	d0
	jne	0f		| renormalize if number was denormalized
	addw	#1,d0		| correct exponent for denormalized numbers
	jra	2b
0:	movel	d4,d3		| check for rounding overflow
	asll	#1,d6		| #0xffe00000 -> d3
	andl	d6,d3
	jne	2b		| go back and renormalize
8:
	movel	d4,d3		| check if normalization caused an underflow
	orl	d5,d3
	jeq	retz
	tstw	d0		| check for exponent overflow or underflow
	jlt	retz
	cmpw	#2047,d0
	jge	oflow

	lslw	#5,d0		| re-position exponent - one bit too high
	lslw	#1,d2		| get X bit
	roxrw	#1,d0		| shift it into sign position
	swap	d0		| map to upper word
	clrw	d0
	andl	#0x0fffff,d4	| top mantissa bits
	orl	d0,d4		| insert exponent and sign
	movel	d4,d0
	movel	d5,d1
	moveml	sp@+,d2-d7
	rts

retz:
	moveq	#Erange,d0
	Emove   d0,Errno
retzok:
	moveq	#0,d0		| return zero value
	movel	d0,d1
	lslw	#1,d2		| set value of extension
	roxrl	#1,d0		| and move it to hight bit of d0
0:	moveml	sp@+,d2-d7
	rts

oflow:
#ifdef	ERROR_CHECK
	pea	pc@(LC0)
	pea	Stderr
	jbsr	_fprintf	|
	addql	#8,a7		|
	moveq	#Erange,d0
	Emove	d0,Errno
#endif	ERROR_CHECK

|	moveml	pc@(__infinitydf),d0-d1 | return infinity value
	moveml	__infinitydf,d0-d1 | return infinty value
	tstw	d2
	jpl	1f
	bset	#31,d0
1:
	moveml	sp@+,d2-d7	| should really cause trap ?!? (mjr: why?)
	rts

#endif __M68881__
