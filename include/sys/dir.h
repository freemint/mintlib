/*
 * kludge city: fake out BSD'ish compatible dir routines with
 * our Posix comaptible portable dir stuff
 */

#ifndef _SYS_DIR_H
#define _SYS_DIR_H 1

#ifdef _SYS_DIRENT_H
#  error "<sys/dir.h>: You cannot use both <sys/dirent.h> and <sys/dir.h>.\n\
        <sys/dir.h> is provided for BSD compatibility\n"
#endif

/* note that the presence of _SYS_DIR_H causes dirent.h to
 * behave differently
 */
#include <sys/dirent.h>

#endif
