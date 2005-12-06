/*  alloca.h -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifndef	_ALLOCA_H

#ifndef _FEATURES_H
# include <features.h>
#endif

#ifndef STDDEF_H
# define __need_size_t
# include <stddef.h>
#endif

__BEGIN_DECLS

#undef alloca

extern void *__alloca (size_t);
extern void *alloca (size_t);

#ifdef __GNUC__
# define __alloca(X) __builtin_alloca (X)
# define alloca(X) __builtin_alloca (X)
#endif

__END_DECLS

#endif /* _ALLOCA_H */
