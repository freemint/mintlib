/* Declarations for System V style searching functions.
   Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* Modified for MiNTLib by Guido Flohr <guido@freemint.de>.  */

#ifndef _SEARCH_H
#define	_SEARCH_H 1

#ifndef	_FEATURES_H
# include <features.h>
#endif

#define __need_size_t
#define __need_NULL
#include <stddef.h>

__BEGIN_DECLS

#if defined __USE_SVID || defined __USE_XOPEN_EXTENDED
/* Prototype structure for a linked-list data structure.
   This is the type used by the `insque' and `remque' functions.  */

struct qelem
  {
    struct qelem *q_forw;
    struct qelem *q_back;
    char q_data[1];
  };


/* Insert ELEM into a doubly-linked list, after PREV.  */
__EXTERN void insque __PROTO ((void *__elem, void *__prev));

/* Unlink ELEM from the doubly-linked list that it is in.  */
__EXTERN void remque __PROTO ((void *__elem));
#endif


/* For use with hsearch(3).  */
#ifndef __COMPAR_FN_T
# define __COMPAR_FN_T
typedef int (*__compar_fn_t) __PROTO ((__const void*, __const void*));

# ifdef	__USE_GNU
typedef __compar_fn_t comparison_fn_t;
# endif
#endif

/* Action which shall be performed in the call the hsearch.  */
typedef enum
  {
    FIND,
    ENTER
  }
ACTION;

typedef struct entry
  {
    char *key;
    char *data;
  }
ENTRY;

/* Opaque type for internal use.  */
struct _ENTRY;

/* Family of hash table handling functions.  The functions also
   have reentrant counterparts ending with _r.  The non-reentrant
   functions all work on a signle internal hashing table.  */

/* Search for entry matching ITEM.key in internal hash table.  If
   ACTION is `FIND' return found entry or signal error by returning
   NULL.  If ACTION is `ENTER' replace existing data (if any) with
   ITEM.data.  */
__EXTERN ENTRY *hsearch __PROTO ((ENTRY __item, ACTION __action));

/* Create a new hashing table which will at most contain NEL elements.  */
__EXTERN int hcreate __PROTO ((size_t __nel));

/* Destroy current internal hashing table.  */
__EXTERN void hdestroy __PROTO ((void));

#ifdef __USE_GNU
/* Data type for reentrant functions.  */
struct hsearch_data
  {
    struct _ENTRY *table;
    unsigned int size;
    unsigned int filled;
  };

/* Reentrant versions which can handle multiple hashing tables at the
   same time.  */
__EXTERN int hsearch_r __PROTO ((ENTRY __item, ACTION __action, 
				 ENTRY **__retval, 
				 struct hsearch_data *__htab));
__EXTERN int hcreate_r __PROTO ((size_t __nel, struct hsearch_data *htab));
__EXTERN void hdestroy_r __PROTO ((struct hsearch_data *htab));
#endif


/* The tsearch routines are very interesting. They make many
   assumptions about the compiler.  It assumes that the first field
   in node must be the "key" field, which points to the datum.
   Everything depends on that.  */
/* For tsearch */
typedef enum
{
  preorder,
  postorder,
  endorder,
  leaf
}
VISIT;

/* Search for an entry matching the given KEY in the tree pointed to
   by *ROOTP and insert a new element if not found.  */
__EXTERN void *tsearch __PROTO ((__const void *__key, void **__rootp,
			     	 __compar_fn_t compar));

/* Search for an entry matching the given KEY in the tree pointed to
   by *ROOTP.  If no matching entry is available return NULL.  */
__EXTERN void *tfind __PROTO ((__const void *__key, void *__const *__rootp,
			       __compar_fn_t compar));

/* Remove the element matching KEY from the tree pointed to by *ROOTP.  */
__EXTERN void *tdelete __PROTO ((__const void *__key, void **__rootp,
				 __compar_fn_t compar));

#ifndef __ACTION_FN_T
# define __ACTION_FN_T
typedef void (*__action_fn_t) __PROTO ((__const void *__nodep,
					VISIT __value, int __level));
#endif

/* Walk through the whole tree and call the ACTION callback for every node
   or leaf.  */
__EXTERN void twalk __PROTO ((__const void *__root, __action_fn_t action));

#ifdef __USE_GNU
/* Callback type for function to free a tree node.  If the keys are atomic
   data this function should do nothing.  */
typedef void (*__free_fn_t) __PROTO ((void *__nodep));

/* Destroy the whole tree, call FREEFCT for each node or leaf.  */
__EXTERN void tdestroy __PROTO ((void *__root, __free_fn_t freefct));
#endif


/* Perform linear search for KEY by comparing by COMPAR in an array
   [BASE,BASE+NMEMB*SIZE).  */
__EXTERN void *lfind __PROTO ((__const void *__key, __const void *__base,
			       size_t *__nmemb, size_t __size,
			       __compar_fn_t __compar));

/* Perform linear search for KEY by comparing by COMPAR function in
   array [BASE,BASE+NMEMB*SIZE) and insert entry if not found.  */
__EXTERN void *lsearch __PROTO ((__const void *__key, void *__base,
				 size_t *__nmemb, size_t __size,
				 __compar_fn_t __compar));

__END_DECLS

#endif /* search.h */
