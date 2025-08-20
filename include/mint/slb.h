/*  
 * Copyright (C) 2000 Konrad Kokoszkiewicz <draco@atari.org.pl>
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 * 
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, see
 * <https://www.gnu.org/licenses/>.
 */

# ifndef _MINT_SLB_H
# define _MINT_SLB_H 1

#ifndef _FEATURES_H
# include <features.h>
#endif

__BEGIN_DECLS

typedef void *SLB_HANDLE;
typedef long __CDECL (*SLB_EXEC)(SLB_HANDLE sl, long fn, short nargs, ...);

typedef struct {
	SLB_HANDLE	handle;
	SLB_EXEC	exec;
} SLB;

long _slbopen (char *fname, char *path, long ver, void *hnd, void *exec);


__END_DECLS

# endif /* mint/slb.h */
