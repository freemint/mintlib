/* File to describe user definable devices. */

#ifndef _DEVICE_H
#define _DEVICE_H

#ifndef _COMPILER_H
#include <compiler.h>
#endif

#ifdef __TURBOC__
# include <sys\types.h>
#else
# include <sys/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef long (*devfunc_t)();

struct _device {
	char	*dosnm,		/* name under DOS (e.g. "CON:") 	*/
		*unxnm;		/* name under UNIX (e.g. "console") 	*/
	dev_t 	dev;		/* device number   (e.g. 0xffff)	*/
	devfunc_t 	open, close, read, write, ioctl;
	struct _device	*next;
};

/*
 * Pseudo-device interface stuff. New devices can be hooked into the chain
 * that's rooted at __devices. All unx2dos and low level i/o functions use this
 * chain in determining whether files are devices or disk files, as does stat().
 * The major device number of user-supplied devices must *NOT* be 0 or 0xff,
 * both of which are reserved.
 */

#define mkdev(major,minor)  ((dev_t)((((major) << 8) & 0xff00)|((minor) & 0x00ff)))

/* major/minor defined in <types.h> */

extern struct _device *__devices;

__EXTERN void _install_device __PROTO((struct _device *d));
__EXTERN struct _device *_dev_fd __PROTO((int fd));
__EXTERN struct _device *_dev_dosname __PROTO((const char *dosnm));
__EXTERN struct _device *_dev_unxname __PROTO((const char *unm));

#ifdef __cplusplus
}
#endif

#endif /* _DEVICE_H */
