
#ifndef _MINT_XBRA_H
# define _MINT_XBRA_H 1

#ifndef	_FEATURES_H
# include <features.h>
#endif

__BEGIN_DECLS

typedef void	(*xptr) __PROTO((void));

typedef struct __xbra
{
  long	xbra_magic;
  long	gnuc_magic;
  xptr	next;
  short	jump;
  void	(*this) __PROTO((void));
}	xbra_struct;

#define _XBRA_MAGIC	0x58425241L /* "XBRA" */
#define _GNUC_MAGIC	0x474E5543L /* "GNUC" */
#define _JMP_OPCODE	0x4EF9
#define _JSR_OPCODE	0x4EB9

#define _XBRA_VEC(x)	((void (*) __PROTO((void))) &(x.jump))

#define _XBRA_INIT(fn)	{		   \
			   _XBRA_MAGIC,    \
			   _GNUC_MAGIC,    \
			   (xptr) 0,       \
			   _JMP_OPCODE,    \
			   (void (*) __PROTO((void))) fn \
			}

#define _TRAP_VEC(n,x)	((void (*) __PROTO((void))) (((long) n << 24) | (long) &(x.jump)))

#define _TRAP_INIT(fn)	{		   \
			   _XBRA_MAGIC,    \
			   _GNUC_MAGIC,    \
			   (xptr) 0,       \
			   _JSR_OPCODE,    \
			   (void (*) __PROTO((void))) fn \
			}

__END_DECLS

#endif /* _XBRA_H */
