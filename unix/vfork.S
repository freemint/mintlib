|
| vfork for MiNT. Note that the return address must be popped off the stack,
| or else it could be clobbered by the child and the parent would be left
| returning to la-la land. Also note that MiNT guarantees that register a1
| will be preserved across a vfork() system call.
|

#include "libc-symbols.h"

	.globl	C_SYMBOL_NAME(vfork)
	.globl	C_SYMBOL_NAME(__vfork)
	.globl	C_SYMBOL_NAME(__mint)		| MiNT version kept here
	.lcomm	L_vfsav, 128
	.text
	.even

C_SYMBOL_NAME(vfork):
C_SYMBOL_NAME(__vfork):
	movel	(%sp)+, %a1	| save return address; this is important!
#ifdef __MSHORT__
	tstw	C_SYMBOL_NAME(__mint)
# else
	tstl	C_SYMBOL_NAME(__mint)
#endif
	jeq	L_TOS		| go do the TOS thing
	movew	#0x113, -(%sp)	| push MiNT Pvfork() parameter
	trap	#1		| Vfork
	addql	#2, %sp
	tstl	%d0		| error??
	jmi	L_err
	jmp	(%a1)		| return; note: assumes that a1 was not clobbered by vfork call
L_TOS:
	lea	L_vfsav, %a0
	moveml	%d2-%d7/%a1-%a6, (%a0)	| save registers
#ifdef __FASTCALL__
	movel	%a0,%d0
	lea	L_newprog(%pc),%a0
	jbsr	C_SYMBOL_NAME(tfork)		| tfork(L_newprog, L_vfsav)
#else
	pea	(%a0)
	pea	L_newprog(%pc)
	jbsr	C_SYMBOL_NAME(tfork)		| tfork(L_newprog, L_vfsav)
	addql	#8, %sp
#endif
	lea	L_vfsav, %a0
	moveml	(%a0), %d2-%d7/%a1-%a6	| restore reggies
	tstl	%d0		| fork went OK??
	jmi	L_err		| no -- error
	jmp	(%a1)		| return to caller
L_err:
	negl	%d0
#ifdef __MSHORT__
	movew	%d0, C_SYMBOL_NAME(errno)	| save error code in errno
# else
	movel	%d0, C_SYMBOL_NAME(errno)	| save error code in errno
# endif
	moveql	#-1, %d0		| return -1
	jmp	(%a1)		| return

|
| L_newprog: here is where the child starts executing, with argument
| L_vfsav. We restore registers, zero d0, and jump back to parent
|

L_newprog:
	addql	#4, %sp		| pop useless return address
#ifdef __FASTCALL__
	movel	%d0, %a0	| get address of save area
#else
	movel	%sp@+, %a0	| get address of save area
#endif
	moveml	%a0@, %d2-%d7/%a1-%a6	| restore reggies
	clrl	%d0		| child always returns 0 from vfork
	jmp	%a1@		| back to caller, as child process

#include "elfattr.S"
