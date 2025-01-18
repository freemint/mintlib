
#include <unistd.h>
#include <bits/local_lim.h>
#include <mint/osbind.h>
#include <mint/sysvars.h>

#include <sys/sysinfo.h>

#ifndef FALSE
#define FALSE   0
#endif
#ifndef TRUE
#define TRUE    1
#endif
#ifndef UNLIMITED
#define UNLIMITED	(0x7fffffffL)
#endif

static int is_there_altram(void){
    if(Supexec(*ramtop) > 0x01000000L){
        return TRUE;
    }
    return FALSE;
}

static unsigned long int get_altram_value(void){
    if(is_there_altram()){
        return (int)((Supexec(*ramtop) - 0x01000000L));
    }
    return 0;
}

static unsigned long int get_stram_value(void){
    return Supexec(*phystop);
}

static unsigned long int get_available_altram(void){
    if(is_there_altram()){
        return Mxalloc(-1, 1);
    }
    return 0;
}

static unsigned long int get_available_stram(void){
    return Mxalloc(-1, 0);
}

__typeof__(get_nprocs_conf) __get_nprocs_conf;
int __get_nprocs_conf (void){
    return 1;
}
weak_alias (__get_nprocs_conf, get_nprocs_conf)

/* Return number of available processors.  */
__typeof__(get_nprocs) __get_nprocs;
int __get_nprocs (void){
    return 1;
}
weak_alias (__get_nprocs, get_nprocs)

/* Return number of physical pages of memory in the system.  */
__typeof__(get_phys_pages) __get_phys_pages;
long int __get_phys_pages (void){
    return ((get_stram_value() + get_altram_value()) / getpagesize());
}
weak_alias (__get_phys_pages, get_phys_pages)

/* Return number of available physical pages of memory in the system.  */
__typeof__(get_avphys_pages) __get_avphys_pages;
long int __get_avphys_pages (void){
    return (get_available_stram() + get_available_altram()) / getpagesize();
}
weak_alias (__get_avphys_pages, get_avphys_pages)

/* Return maximum number of processes this real user ID can have.  */
__typeof__(get_child_max) __get_child_max;
long int __get_child_max (void){
#ifdef CHILD_MAX
    return CHILD_MAX;
#else
    return UNLIMITED;
#endif
}
weak_alias (__get_child_max, get_child_max)