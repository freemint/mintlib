|
| vfork for MiNT. Note that the return address must be popped off the stack,
| or else it could be clobbered by the child and the parent would be left
| returning to la-la land. Also note that MiNT guarantees that register a1
| will be preserved across a vfork() system call.
|
	.globl	_vfork
	.globl	___vfork
	.globl	___mint		| MiNT version kept here
	.lcomm	L_vfsav, 128
	.text
	.even

_vfork:
___vfork:
	movel	sp@+, a1	| save return address; this is important!
#ifdef __MSHORT__
	tstw	___mint
# else
	tstl	___mint
#endif
	jeq	L_TOS		| go do the TOS thing
	movew	#0x113, sp@-	| push MiNT Pvfork() parameter
	trap	#1		| Vfork
	addql	#2, sp
	tstl	d0		| error??
	jmi	L_err
	jmp	a1@		| return
L_TOS:
#ifdef __mcoldfire__
	lea	L_vfsav, a0
	moveml	d2-d7/a1-a6, a0@	| save registers
#else
	moveml	d2-d7/a1-a6, L_vfsav	| save registers
#endif
	pea	L_vfsav
	pea	pc@(L_newprog)
	jbsr	_tfork		| tfork(L_newprog, L_vfsav)
	addql	#8, sp
#ifdef __mcoldfire__
	lea	L_vfsav, a0
	moveml	a0@, d2-d7/a1-a6	| restore reggies
#else
	moveml	L_vfsav, d2-d7/a1-a6	| restore reggies
#endif
	tstl	d0		| fork went OK??
	jmi	L_err		| no -- error
	jmp	a1@		| return to caller
L_err:
	negl	d0
#ifdef __MSHORT__
	movew	d0, _errno	| save error code in errno
# else
	movel	d0, _errno	| save error code in errno
# endif
	moveql	#-1, d0		| return -1
	jmp	a1@		| return

|
| L_newprog: here is where the child starts executing, with argument
| L_vfsav. We restore registers, zero d0, and jump back to parent
|

L_newprog:
	addql	#4, sp		| pop useless return address
	movel	sp@+, a0	| get address of save area
	moveml	a0@, d2-d7/a1-a6	| restore reggies
	clrl	d0		| child always returns 0 from vfork
	jmp	a1@		| back to caller, as child process
