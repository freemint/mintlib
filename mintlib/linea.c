/*
 * function form of linea bindings
 *	++jrb
 */

#define __NO_INLINE__
#include <mint/linea.h>

void linea0()                                                   
{
        register __LINEA *__xaline __asm__ ("a0");
        register __FONT **__xfonts __asm__ ("a1");
        register short (**__xfuncs) (void) __asm__ ("a2");

        __asm__ volatile
        (
		ASM_LINEA(0x0)
        : "=g"(__xaline), "=g"(__xfonts), "=g"(__xfuncs)  /* outputs */
        :                                                 /* inputs  */
        : __CLOBBER_RETURN("a0") __CLOBBER_RETURN("a1") __CLOBBER_RETURN("a2") "d0", "d1", "d2"       /* clobbered regs */
	  AND_MEMORY
        );

        __aline = __xaline;
        __fonts = __xfonts;
        __funcs = __xfuncs;
}

void linea1() 							
{									
	__asm__ volatile
	(
		ASM_LINEA(0x1)
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	  AND_MEMORY
	);								
}

int linea2() 							
{									
	register long retvalue __asm__("d0");

	__asm__ volatile						
	(
		ASM_LINEA(0x2)
	: "=r"(retvalue)				  /* outputs */	
	: 						  /* inputs  */	
	: __CLOBBER_RETURN("d0") "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	  AND_MEMORY
	);								

	return (int) retvalue;
}

void linea3() 							
{									
	__asm__ volatile						
	(
		ASM_LINEA(0x3)
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	  AND_MEMORY
	);								
}

void linea4() 							
{									
	__asm__ volatile						
	(
		ASM_LINEA(0x4)
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	  AND_MEMORY
	);								
}

void linea5() 							
{									
	__asm__ volatile						
	(
		ASM_LINEA(0x5)
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	  AND_MEMORY
	);								
}

void linea6() 							
{									
	__asm__ volatile						
	(
		ASM_LINEA(0x6)
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	  AND_MEMORY
	);								
}

void linea7(BBPB *P) 							
{									
	__asm__ volatile						
	(
		PUSH_SP("d2/a2/a6", 12)
 		"movl	%0,a6\n\t"
		ASM_LINEA(0x7) "\n\t"
		POP_SP("d2/a2/a6", 12)
	: 						  /* outputs */	
	: "r"(P)					  /* inputs  */	
	: "d0", "d1", "a0", "a1"		   /* clobbered regs */
	  AND_MEMORY
	);								
}

void linea8() 							
{									
	__asm__ volatile						
	(
		ASM_LINEA(0x8)
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	  AND_MEMORY
	);								
}

void linea9() 							
{									
	__asm__ volatile						
	(
		ASM_LINEA(0x9)
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	  AND_MEMORY
	);								
}

void lineaa() 							
{
	__asm__ volatile						
	(
		ASM_LINEA(0xa)
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	  AND_MEMORY
	);								
}

void lineab() 							
{									
	__asm__ volatile						
	(
		ASM_LINEA(0xb)
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	  AND_MEMORY
	);								
}

void lineac(void *P) 							
{									
	__asm__ volatile						
	(
 		"movl	%0,a2\n\t"
		ASM_LINEA(0xc)
	: 						  /* outputs */	
	: "r"(P)					  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"              /* clobbered regs */	
	  AND_MEMORY
	);								
}

void linead(int x, int y,  SFORM * sd, void *ss)
{									
	__asm__ volatile						
	(
 		"movw	%0,d0\n\t"
 		"movw	%1,d1\n\t"
 		"movl	%2,a0\n\t"
 		"movl	%3,a2\n\t"
		ASM_LINEA(0xd)
	: 						  /* outputs */	
	: "r"((short)x), "r"((short)y), "r"(sd), "r"(ss)  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"              /* clobbered regs */	
	  AND_MEMORY
	);								
}

void lineae() 							
{									
	__asm__ volatile						
	(
		ASM_LINEA(0xe)
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	  AND_MEMORY
	);								
}

void lineaf() 							
{									
	__asm__ volatile						
	(
		ASM_LINEA(0xf)
	: 						  /* outputs */	
	: 						  /* inputs  */	
	: "d0", "d1", "d2", "a0", "a1", "a2"       /* clobbered regs */	
	  AND_MEMORY
	);								
}
