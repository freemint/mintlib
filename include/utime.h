#ifndef _U_TIME_H
#define _U_TIME_H

#ifndef _FEATURES_H
#include <features.h>
#endif

#define __need_time_t
#include <time.h>

struct utimbuf {			/* type for times() call */
	time_t	actime;
	time_t	modtime;
};

__EXTERN int utime __PROTO((const char *path, const struct utimbuf *times));
__EXTERN int __utime __PROTO((const char *path, const struct utimbuf *times));

#endif  /* _U_TIME_H */
