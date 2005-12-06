/*
**  <FTW.H>
**  Header values for the third parameter to the user-supplied function
**  for ftw().
**
*/

#ifndef _FTW_H
#define _FTW_H

#ifndef _FEATURES_H
# include <features.h>
#endif

__BEGIN_DECLS

#define FTW_F		0	/* A normal file			*/
#define FTW_D		1	/* A directory				*/
#define FTW_DNR		2	/* Something opendir(3) failed on	*/
#define FTW_NS		3	/* Something stat(2) failed on		*/

extern int ftw (char *path, int (*fn)(const char *, struct stat *, int), int param);

__END_DECLS

#endif /* _FTW_H */
