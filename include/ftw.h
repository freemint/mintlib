/*
**  <FTW.H>
**  Header values for the third parameter to the user-supplied function
**  for ftw().
**
*/

#ifndef _FTW_H
#define _FTW_H
	
#ifdef __cplusplus
extern "C" {
#endif

#define FTW_F		0	/* A normal file			*/
#define FTW_D		1	/* A directory				*/
#define FTW_DNR		2	/* Something opendir(3) failed on	*/
#define FTW_NS		3	/* Something stat(2) failed on		*/


__EXTERN int ftw
    __PROTO((char *path, int (*fn)(const char *, struct stat *, int), int param));

#ifdef __cplusplus
}
#endif

#endif /* _FTW_H */
