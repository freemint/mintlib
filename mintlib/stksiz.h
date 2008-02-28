#ifndef _STKSIZ_H
#define _STKSIZ_H

/* definitions needed in mintlib/crtinit.c and mintlib/stksize.c */

#define MINFREE	(8L * 1024L)		/* free at least this much mem on top */
#define MINKEEP (64L * 1024L)		/* keep at least this much mem on stack */

#endif /* _STKSIZ_H */
