
#ifndef _UTIME_H
#define _UTIME_H

#ifndef _FEATURES_H
# include <features.h>
#endif

#define __need_time_t
#include <time.h>

__BEGIN_DECLS

struct utimbuf {			/* type for utime() call */
	time_t	actime;
	time_t	modtime;
};
struct utimbuf64 {			/* type for __utime64() call */
	__time64_t	actime;
	__time64_t	modtime;
};

#ifndef __USE_TIME_BITS64
extern int utime(const char *path, const struct utimbuf *times) __THROW __nonnull ((1));
#else
extern int __REDIRECT_NTH (utime, (const char *__file,
                                   const struct utimbuf *__file_times),
                           __utime64);
#endif

__END_DECLS

#endif  /* _UTIME_H */
