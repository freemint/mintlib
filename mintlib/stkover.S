#include "libc-symbols.h"

	.globl C_SYMBOL_NAME(_StkOver)
	.globl C_SYMBOL_NAME(_StkLim)

	.text

overflow: .dc.b 13,10
	.ascii "Stack overflow"
	.dc.b 0
	.even

	.text

C_SYMBOL_NAME(_StkOver):
	movea.l    C_SYMBOL_NAME(_StkLim),%a7
	pea.l      overflow(%pc)
	move.w     #9,-(%a7) /* Cconws */
	trap       #1
	move.w     #0x7FFF,(%a7)
	move.w     #76,-(%a7) /* Pterm */
	trap       #1

#include "elfattr.S"
