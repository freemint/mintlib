
#ifndef _IFLINK_H
#define _IFLINK_H 1

#ifndef _FEATURES_H
# include <features.h>
#endif

__EXTERN int	if_link		__PROTO ((char*, char*));
__EXTERN int	if_getlnkflags	__PROTO ((char*, short*));
__EXTERN int	if_setlnkflags	__PROTO ((char*, short));
__EXTERN int	if_getifflags	__PROTO ((char*, short*));
__EXTERN int	if_setifflags	__PROTO ((char*, short));

#endif /* mint/iflink.h */
