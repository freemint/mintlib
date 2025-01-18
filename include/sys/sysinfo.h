#ifndef _SYS_SYSINFO_H
#define _SYS_SYSINFO_H

/* Return number of configured processors.  */
extern int get_nprocs_conf (void);

/* Return number of available processors.  */
extern int get_nprocs (void);

/* Return number of physical pages of memory in the system.  */
extern long int get_phys_pages (void);

/* Return number of available physical pages of memory in the system.  */
extern long int get_avphys_pages (void);

/* Return maximum number of processes this real user ID can have.  */
extern long int get_child_max (void);

#endif /* sys/sysinfo.h */