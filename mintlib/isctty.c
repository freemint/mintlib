/* _isctty():  determine if a file descriptor refers to this process's
   controlling tty.
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <support.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <mint/mintbind.h>
#include "lib.h"

int
_isctty(int fd)
{
  struct xattr st, tt;

  if (!(isatty(fd)) || !(isatty(-1)))
    return 0;
  if (fd == -1)
    return 1;
  if (__mint >= 9 && !Fcntl (fd, &st, FSTAT) && !Fcntl (-1, &tt, FSTAT)) {
    return (st.st_dev == tt.st_dev && st.st_ino == tt.st_ino);
  }
  /* We know that __mint < 9 (the Fcntl's above don't have the chance
     to fail), use the same algorithm that ttyname() uses in this
     case: it returns "/dev/aux" if fd == -2 */
  return fd != -2;
}
