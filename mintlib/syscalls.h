/* This file is generated, DO NOT EDIT!!! All changes will get
   overwritten.
   Edit ./syscalls.list in the MiNTLib distribution instead.  */

__EXTERN long __write __PROTO ((int, void*, long));
__EXTERN int __fstat __PROTO ((int, void*));
__EXTERN long __times __PROTO ((void*));
__EXTERN int __pause __PROTO ((void));
__EXTERN int __rename __PROTO ((void*, void*));
__EXTERN int __truncate __PROTO ((void*, long));
__EXTERN int __waitpid __PROTO ((int, void*, int));
__EXTERN int __wait __PROTO ((void*));
__EXTERN int __wait3 __PROTO ((void*, int, void*));
__EXTERN int __wait4 __PROTO ((int, void*, int, void*));
__EXTERN void* __readdir __PROTO ((void*));
__EXTERN int __fsync __PROTO ((int));
__EXTERN int __lstat __PROTO ((void*, void*));
__EXTERN int __dup2 __PROTO ((int, int));
__EXTERN int __getppid __PROTO ((void));
__EXTERN int __close __PROTO ((int));
__EXTERN int __setgid __PROTO ((int));
__EXTERN int __statfs __PROTO ((void*, void*));
__EXTERN int __sigaction __PROTO ((int, void*, void*));
__EXTERN int __sigblock __PROTO ((long));
__EXTERN void* __signal __PROTO ((int, void*));
__EXTERN void __sigpause __PROTO ((void));
__EXTERN int __sigpending __PROTO ((void*));
__EXTERN void __sigreturn __PROTO ((void));
__EXTERN int __sigsetmask __PROTO ((long));
__EXTERN int __fork __PROTO ((void));
__EXTERN int __symlink __PROTO ((void*, void*));
__EXTERN int __readlink __PROTO ((void*, void*, int));
__EXTERN int __ioctl __PROTO ((int, int, void*));
__EXTERN int __stty __PROTO ((int, void*));
__EXTERN int __gtty __PROTO ((int, void*));
__EXTERN int __ftruncate __PROTO ((int, long));
__EXTERN int __creat __PROTO ((void*, short));
__EXTERN int __fcntl_v __PROTO ((int, int, va_list));
__EXTERN int __setsid __PROTO ((void));
__EXTERN int __setuid __PROTO ((int));
__EXTERN int __umask __PROTO ((int));
__EXTERN int __kill __PROTO ((int, int));
__EXTERN int __killpg __PROTO ((int, int));
__EXTERN int __gettimeofday __PROTO ((void*, void*));
__EXTERN int __settimeofday __PROTO ((void*, void*));
__EXTERN int __getitimer __PROTO ((int, void*));
__EXTERN int __setitimer __PROTO ((int, void*, void*));
__EXTERN int __getpriority __PROTO ((int, int));
__EXTERN int __setpriority __PROTO ((int, int, int));
__EXTERN int __nice __PROTO ((int));
__EXTERN int __link __PROTO ((void*, void*));
__EXTERN long __lseek __PROTO ((int, long, int));
__EXTERN int __execve __PROTO ((void*, void*, void*));
__EXTERN int __getgid __PROTO ((void));
__EXTERN int __rmdir __PROTO ((void*));
__EXTERN int __getegid __PROTO ((void));
__EXTERN int __getuid __PROTO ((void));
__EXTERN int __pipe __PROTO ((void*));
__EXTERN int __getpid __PROTO ((void));
__EXTERN int __dup __PROTO ((int));
__EXTERN int __setregid __PROTO ((int, int));
__EXTERN int __alarm __PROTO ((int));
__EXTERN int __geteuid __PROTO ((void));
__EXTERN int __setreuid __PROTO ((int, int));
__EXTERN int __chdir __PROTO ((void*));
__EXTERN int __access __PROTO ((void*, int));
__EXTERN int __getgroups __PROTO ((int, short));
__EXTERN int __chown __PROTO ((void*, short, short));
__EXTERN int __select __PROTO ((int, void*, void*, void*));
__EXTERN int __getrusage __PROTO ((int, void*));
__EXTERN int __initgroups __PROTO ((void*, short));
__EXTERN int __setgroups __PROTO ((long, void*));
__EXTERN int __getrlimit __PROTO ((int, void*));
__EXTERN int __setrlimit __PROTO ((int, void*));
__EXTERN long __read __PROTO ((int, void*, long));
__EXTERN int __open_v __PROTO ((void*, int, va_list));
__EXTERN int __flock __PROTO ((int, int));
__EXTERN int __utime __PROTO ((void*, void*));
__EXTERN int __mkdir __PROTO ((void*, int));
__EXTERN int __stat __PROTO ((void*, void*));
__EXTERN int __sync __PROTO ((void));
__EXTERN int __chmod __PROTO ((void*, short));
__EXTERN int __unlink __PROTO ((void*));

static long _sys_ipi __PROTO ((int opcode, va_list args));
static long _sys_iiip __PROTO ((int opcode, va_list args));
static long _sys_v __PROTO ((int opcode, va_list args));
static long _sys_iipi __PROTO ((int opcode, va_list args));
static long _sys_i __PROTO ((int opcode, va_list args));
static long _sys_iip __PROTO ((int opcode, va_list args));
static long _sys_ii __PROTO ((int opcode, va_list args));
static long _sys_ipiv __PROTO ((int opcode, va_list args));
static long _sys_lili __PROTO ((int opcode, va_list args));
static long _sys_pp __PROTO ((int opcode, va_list args));
static long _sys_ilp __PROTO ((int opcode, va_list args));
static long _sys_iis __PROTO ((int opcode, va_list args));
static long _sys_ippp __PROTO ((int opcode, va_list args));
static long _sys_ipl __PROTO ((int opcode, va_list args));
static long _sys_iippp __PROTO ((int opcode, va_list args));
static long _sys_il __PROTO ((int opcode, va_list args));
static long _sys_iiii __PROTO ((int opcode, va_list args));
static long _sys_iiiv __PROTO ((int opcode, va_list args));
static long _sys_iii __PROTO ((int opcode, va_list args));
static long _sys_iipp __PROTO ((int opcode, va_list args));
static long _sys_ipp __PROTO ((int opcode, va_list args));
static long _sys_ip __PROTO ((int opcode, va_list args));
static long _sys_ipss __PROTO ((int opcode, va_list args));
static long _sys_iil __PROTO ((int opcode, va_list args));
static long _sys_ippi __PROTO ((int opcode, va_list args));
static long _sys_pip __PROTO ((int opcode, va_list args));
static long _sys_ipip __PROTO ((int opcode, va_list args));
static long _sys_lipl __PROTO ((int opcode, va_list args));
static long _sys_ips __PROTO ((int opcode, va_list args));
static long _sys_iipip __PROTO ((int opcode, va_list args));
static long _sys_lp __PROTO ((int opcode, va_list args));

static struct _dispatch funcs[] = 
{
  { __write, _sys_lipl },
  { __fstat, _sys_iip },
  { __times, _sys_lp },
  { __pause, _sys_i },
  { __rename, _sys_ipp },
  { __truncate, _sys_ipl },
  { __waitpid, _sys_iipi },
  { __wait, _sys_ip },
  { __wait3, _sys_ipip },
  { __wait4, _sys_iipip },
  { __readdir, _sys_pp },
  { __fsync, _sys_ii },
  { __lstat, _sys_ipp },
  { __dup2, _sys_iii },
  { __getppid, _sys_i },
  { __close, _sys_ii },
  { __setgid, _sys_ii },
  { __statfs, _sys_ipp },
  { __sigaction, _sys_iipp },
  { __sigblock, _sys_il },
  { __signal, _sys_pip },
  { __sigpause, _sys_v },
  { __sigpending, _sys_ip },
  { __sigreturn, _sys_v },
  { __sigsetmask, _sys_il },
  { __fork, _sys_i },
  { __symlink, _sys_ipp },
  { __readlink, _sys_ippi },
  { __ioctl, _sys_iiip },
  { __stty, _sys_iip },
  { __gtty, _sys_iip },
  { __ftruncate, _sys_iil },
  { __creat, _sys_ips },
  { __fcntl_v, _sys_iiiv },
  { __setsid, _sys_i },
  { __setuid, _sys_ii },
  { __umask, _sys_ii },
  { __kill, _sys_iii },
  { __killpg, _sys_iii },
  { __gettimeofday, _sys_ipp },
  { __settimeofday, _sys_ipp },
  { __getitimer, _sys_iip },
  { __setitimer, _sys_iipp },
  { __getpriority, _sys_iii },
  { __setpriority, _sys_iiii },
  { __nice, _sys_ii },
  { __link, _sys_ipp },
  { __lseek, _sys_lili },
  { __execve, _sys_ippp },
  { __getgid, _sys_i },
  { __rmdir, _sys_ip },
  { __getegid, _sys_i },
  { __getuid, _sys_i },
  { __pipe, _sys_ip },
  { __getpid, _sys_i },
  { __dup, _sys_ii },
  { __setregid, _sys_iii },
  { __alarm, _sys_ii },
  { __geteuid, _sys_i },
  { __setreuid, _sys_iii },
  { __chdir, _sys_ip },
  { __access, _sys_ipi },
  { __getgroups, _sys_iis },
  { __chown, _sys_ipss },
  { __select, _sys_iippp },
  { __getrusage, _sys_iip },
  { __initgroups, _sys_ips },
  { __setgroups, _sys_ilp },
  { __getrlimit, _sys_iip },
  { __setrlimit, _sys_iip },
  { __read, _sys_lipl },
  { __open_v, _sys_ipiv },
  { __flock, _sys_iii },
  { __utime, _sys_ipp },
  { __mkdir, _sys_ipi },
  { __stat, _sys_ipp },
  { __sync, _sys_i },
  { __chmod, _sys_ips },
  { __unlink, _sys_ip },
};

#define MAX_SYS_OPCODE 78

static
long _sys_ipi (int opcode, va_list args)
{
  void* a1 = va_arg (args, void*);
  int a2 = va_arg (args, int);
  return (long) ((func) funcs[opcode].call) (a1, a2);
}

static
long _sys_iiip (int opcode, va_list args)
{
  int a1 = va_arg (args, int);
  int a2 = va_arg (args, int);
  void* a3 = va_arg (args, void*);
  return (long) ((func) funcs[opcode].call) (a1, a2, a3);
}

static
long _sys_v (int opcode, va_list args)
{
  ((func) funcs[opcode].call) ();
  return (long) 0;}

static
long _sys_iipi (int opcode, va_list args)
{
  int a1 = va_arg (args, int);
  void* a2 = va_arg (args, void*);
  int a3 = va_arg (args, int);
  return (long) ((func) funcs[opcode].call) (a1, a2, a3);
}

static
long _sys_i (int opcode, va_list args)
{
  return (long) ((func) funcs[opcode].call) ();
}

static
long _sys_iip (int opcode, va_list args)
{
  int a1 = va_arg (args, int);
  void* a2 = va_arg (args, void*);
  return (long) ((func) funcs[opcode].call) (a1, a2);
}

static
long _sys_ii (int opcode, va_list args)
{
  int a1 = va_arg (args, int);
  return (long) ((func) funcs[opcode].call) (a1);
}

static
long _sys_ipiv (int opcode, va_list args)
{
  void* a1 = va_arg (args, void*);
  int a2 = va_arg (args, int);
  int a3 = va_arg (args, int);
  return (long) ((func) funcs[opcode].call) (a1, a2, a3, args);
}

static
long _sys_lili (int opcode, va_list args)
{
  int a1 = va_arg (args, int);
  long a2 = va_arg (args, long);
  int a3 = va_arg (args, int);
  return (long) ((func) funcs[opcode].call) (a1, a2, a3);
}

static
long _sys_pp (int opcode, va_list args)
{
  void* a1 = va_arg (args, void*);
  return (long) ((func) funcs[opcode].call) (a1);
}

static
long _sys_ilp (int opcode, va_list args)
{
  long a1 = va_arg (args, long);
  void* a2 = va_arg (args, void*);
  return (long) ((func) funcs[opcode].call) (a1, a2);
}

static
long _sys_iis (int opcode, va_list args)
{
  int a1 = va_arg (args, int);
  short a2 = va_arg (args, short);
  return (long) ((func) funcs[opcode].call) (a1, a2);
}

static
long _sys_ippp (int opcode, va_list args)
{
  void* a1 = va_arg (args, void*);
  void* a2 = va_arg (args, void*);
  void* a3 = va_arg (args, void*);
  return (long) ((func) funcs[opcode].call) (a1, a2, a3);
}

static
long _sys_ipl (int opcode, va_list args)
{
  void* a1 = va_arg (args, void*);
  long a2 = va_arg (args, long);
  return (long) ((func) funcs[opcode].call) (a1, a2);
}

static
long _sys_iippp (int opcode, va_list args)
{
  int a1 = va_arg (args, int);
  void* a2 = va_arg (args, void*);
  void* a3 = va_arg (args, void*);
  void* a4 = va_arg (args, void*);
  return (long) ((func) funcs[opcode].call) (a1, a2, a3, a4);
}

static
long _sys_il (int opcode, va_list args)
{
  long a1 = va_arg (args, long);
  return (long) ((func) funcs[opcode].call) (a1);
}

static
long _sys_iiii (int opcode, va_list args)
{
  int a1 = va_arg (args, int);
  int a2 = va_arg (args, int);
  int a3 = va_arg (args, int);
  return (long) ((func) funcs[opcode].call) (a1, a2, a3);
}

static
long _sys_iiiv (int opcode, va_list args)
{
  int a1 = va_arg (args, int);
  int a2 = va_arg (args, int);
  int a3 = va_arg (args, int);
  return (long) ((func) funcs[opcode].call) (a1, a2, a3, args);
}

static
long _sys_iii (int opcode, va_list args)
{
  int a1 = va_arg (args, int);
  int a2 = va_arg (args, int);
  return (long) ((func) funcs[opcode].call) (a1, a2);
}

static
long _sys_iipp (int opcode, va_list args)
{
  int a1 = va_arg (args, int);
  void* a2 = va_arg (args, void*);
  void* a3 = va_arg (args, void*);
  return (long) ((func) funcs[opcode].call) (a1, a2, a3);
}

static
long _sys_ipp (int opcode, va_list args)
{
  void* a1 = va_arg (args, void*);
  void* a2 = va_arg (args, void*);
  return (long) ((func) funcs[opcode].call) (a1, a2);
}

static
long _sys_ip (int opcode, va_list args)
{
  void* a1 = va_arg (args, void*);
  return (long) ((func) funcs[opcode].call) (a1);
}

static
long _sys_ipss (int opcode, va_list args)
{
  void* a1 = va_arg (args, void*);
  short a2 = va_arg (args, short);
  short a3 = va_arg (args, short);
  return (long) ((func) funcs[opcode].call) (a1, a2, a3);
}

static
long _sys_iil (int opcode, va_list args)
{
  int a1 = va_arg (args, int);
  long a2 = va_arg (args, long);
  return (long) ((func) funcs[opcode].call) (a1, a2);
}

static
long _sys_ippi (int opcode, va_list args)
{
  void* a1 = va_arg (args, void*);
  void* a2 = va_arg (args, void*);
  int a3 = va_arg (args, int);
  return (long) ((func) funcs[opcode].call) (a1, a2, a3);
}

static
long _sys_pip (int opcode, va_list args)
{
  int a1 = va_arg (args, int);
  void* a2 = va_arg (args, void*);
  return (long) ((func) funcs[opcode].call) (a1, a2);
}

static
long _sys_ipip (int opcode, va_list args)
{
  void* a1 = va_arg (args, void*);
  int a2 = va_arg (args, int);
  void* a3 = va_arg (args, void*);
  return (long) ((func) funcs[opcode].call) (a1, a2, a3);
}

static
long _sys_lipl (int opcode, va_list args)
{
  int a1 = va_arg (args, int);
  void* a2 = va_arg (args, void*);
  long a3 = va_arg (args, long);
  return (long) ((func) funcs[opcode].call) (a1, a2, a3);
}

static
long _sys_ips (int opcode, va_list args)
{
  void* a1 = va_arg (args, void*);
  short a2 = va_arg (args, short);
  return (long) ((func) funcs[opcode].call) (a1, a2);
}

static
long _sys_iipip (int opcode, va_list args)
{
  int a1 = va_arg (args, int);
  void* a2 = va_arg (args, void*);
  int a3 = va_arg (args, int);
  void* a4 = va_arg (args, void*);
  return (long) ((func) funcs[opcode].call) (a1, a2, a3, a4);
}

static
long _sys_lp (int opcode, va_list args)
{
  void* a1 = va_arg (args, void*);
  return (long) ((func) funcs[opcode].call) (a1);
}

