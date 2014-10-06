/*
Public domain termios tc[get|set]attr() for the MiNT library
10 October 1993 entropy@terminator.rs.itd.umich.edu -- first attempt
*/

#include <errno.h>
#include <termios.h>
#include <unistd.h>

#include <sys/param.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <mint/mintbind.h>

#include "lib.h"

#define VTIME_MS	100  /* count in .1 seconds */

int
tcgetattr(int fd, struct termios *stp)
{
  struct sgttyb sg;
  struct tchars t;
  struct ltchars lt;
  short flags;
  unsigned short vmin[2];
  long state, r;

  r = Fcntl((short) fd, (long) &sg, TIOCGETP);
  if (r < 0) {
    __set_errno ((int) -r);
    return -1;
  }
  r = Fcntl((short) fd, (long) &t, TIOCGETC);
  if (r < 0) {
    __set_errno ((int) -r);
    return -1;
  }
  r = Fcntl((short) fd, (long) &lt, TIOCGLTC);
  if (r < 0) {
    __set_errno ((int) -r);
    return -1;
  }
  r = ioctl (fd, TIOCGETD, &stp->c_line);
  if (r < 0) {
    __set_errno ((int) -r);
    return -1;
  }
  r = Fcntl((short) fd, (long) &flags, TIOCGFLAGS);
  if (r < 0) {
    flags = 0;
  }
  r = Fcntl((short) fd, (long) &state, TIOCGSTATE);
  if (r < 0) {
    state = 0;
  }
  stp->c_iflag = (tcflag_t) (((flags & _TF_BRKINT) ? BRKINT : 0)
			| ((sg.sg_flags & CRMOD) ? ICRNL : 0)
			| ((sg.sg_flags & (EVENP | ODDP)) ? INPCK :
			 ((sg.sg_flags & RAW) ? 0 : IGNPAR)) /*keep stty happy*/
			| ((sg.sg_flags & TANDEM) ? (IXON | IXOFF) : 0)
			| ((sg.sg_flags & RAW) ? 0 : IXON));
  stp->c_oflag = (tcflag_t) (sg.sg_flags & CRMOD) ? (OPOST | ONLCR) : 0;
  stp->c_cflag = (tcflag_t) (CREAD
			| ((flags & _TF_CAR) ? 0 : CLOCAL)
			| ((state & _TS_HPCL) ? HUPCL : 0)
			| (((flags & _TF_STOPBITS) == _TF_2STOP) ? CSTOPB : 0)
			| (flags & _TF_CHARBITS)
			| ((sg.sg_flags & RTSCTS) ? CRTSCTS : 0)
			| ((sg.sg_flags & EVENP) ? PARENB : 0)
			| ((sg.sg_flags & ODDP) ? (PARENB | PARODD) : 0));
  stp->c_lflag = (tcflag_t) ((sg.sg_flags & (TOSTOP | NOFLSH | ECHOCTL))
			| ((sg.sg_flags & ECHO) ? (ECHO | ECHOE | ECHOK) : 0)
			| ((sg.sg_flags & RAW)
				? 0 
				: ISIG | (sg.sg_flags & CBREAK ? 0 : ICANON)));
  stp->_c_ispeed = (speed_t) sg.sg_ispeed;
  stp->_c_ospeed = (speed_t) sg.sg_ospeed;
  stp->c_cc[VEOF]	= (cc_t) t.t_eofc;
  stp->c_cc[VEOL]	= (cc_t) t.t_brkc;
  stp->c_cc[VERASE]	= (cc_t) sg.sg_erase;
  stp->c_cc[VINTR]	= (cc_t) t.t_intrc;
  stp->c_cc[VKILL]	= (cc_t) sg.sg_kill;
  stp->c_cc[VQUIT]	= (cc_t) t.t_quitc;
  stp->c_cc[VSUSP]	= (cc_t) lt.t_suspc;
  stp->c_cc[VSTART]	= (cc_t) t.t_startc;
  stp->c_cc[VSTOP]	= (cc_t) t.t_stopc;
  r = Fcntl((short) fd, (long) &vmin, TIOCGVMIN);
  if (r < 0) {
    stp->c_cc[VMIN]	= (cc_t) 1;
    stp->c_cc[VTIME]	= (cc_t) 0;
  } else {
    if (vmin[1]) {
      stp->c_cc[VMIN]	= (cc_t) 0;
      stp->c_cc[VTIME]	= (cc_t) (vmin[1] >= 0xff*VTIME_MS) ? 0xff : vmin[1]/VTIME_MS;
    } else {
      stp->c_cc[VMIN]	= (cc_t) (vmin[0] >= 0xff) ? 0xff : vmin[0];
      stp->c_cc[VTIME]	= (cc_t) 0;
    }
  }
  stp->c_cc[VLNEXT]	= (cc_t) lt.t_lnextc;
  stp->c_cc[VWERASE]	= (cc_t) lt.t_werasc;
  stp->c_cc[VDSUSP]	= (cc_t) lt.t_dsuspc;
  stp->c_cc[VREPRINT]	= (cc_t) lt.t_rprntc;
  stp->c_cc[VFLUSHO]	= (cc_t) lt.t_flushc;
  return 0;
}
