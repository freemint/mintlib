|
| $Id$
|

|
| Initialization code; this is common to both 16 and 32 bit libraries,
| so be careful!
|
	.globl	__app		| short, declared in crtinit.c
	.globl	__base		| BASEPAGE *, declared in globals.c
	.globl	__heapbase	| void *
	.globl	__stksize	| long, declared by user or in stksiz.c
	.globl	_main		| for references

|
| externs to pull ident strings of all used libraries into the
| executable; if a library is not used, then the extern is
| satisfied by a dummy in the library

	.globl	___Ident_gnulib
	.globl	___Ident_socketlib
	.globl	___Ident_gem

|
| Assumption: basepage is passed in a0 for accessories; for programs
| a0 is always 0.

	.text
	.even
	.globl	__start
__start:
	subl	a6, a6		| clear a6 for debuggers
	cmpw	#0, a0		| test if acc or program
	jeq	__startprg	| if a program, go elsewhere
	tstl	a0@(36)		| also test parent basepage pointer
	jne	__startprg	| for accs, it must be 0
	movel	a0, __base	| acc basepage is in A0
	lea	a0@(252), sp	| use the command line as a temporary stack
	jmp	__acc_main	| function is in crtinit.c
|
| program startup code: doesn''t actually do much, other than push
| the basepage onto the stack and call _start1 in crtinit.c
|
__startprg:
	movel	sp@(4), a0	| get basepage
	movel	a0, __base	| save it
	movel	a0@(4), d0	| get _base->p_hitpa
	bclr	#0, d0		| round off
	movel	d0, sp		| set stack (temporarily)
	jmp	__crtinit	| in crtinit.c

|
| interfaces for gprof: for crt0.o, does nothing, but for gcrt0.o branches
| to the appropriate subroutines
|
	.globl 	__monstartup
	.globl	__moncontrol
	.globl 	___mcleanup

#ifdef GCRT0
	.globl	_monstartup
	.globl	_moncontrol
	.globl	__mcleanup

__monstartup:
	jmp	_monstartup
__moncontrol:
	jmp	_moncontrol
___mcleanup:
	jmp	__mcleanup
#else
__monstartup:
__moncontrol:
___mcleanup:
	rts
#endif /* GCRT0 */
