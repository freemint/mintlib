/*
 *  
 * MMedour - 2024/06/24 - getgrgid_r & getgrnam_r draft c implementation and validation
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <grp.h>
#include <errno.h>

int getgrnam_r(const char *name, struct group *grp, char *buf, size_t buflen, struct group **result)
{
    char **mem_ptr;
    struct group *g;
    size_t gr_size, len, mem_array_counter, mem_array_pos;

    if (grp == NULL || buf == NULL)
    {
        __set_errno(EINVAL);
        *result = NULL;
        return -1;
    }

    g = getgrnam(name);

    if (g == NULL)
    {
        *result = NULL;
        return -1;
    }

    /* Get the size needed to store getgrgid */
    gr_size = 0;
    gr_size += strlen(g->gr_name) + 1;
    gr_size += strlen(g->gr_passwd) + 1;

	mem_array_counter = 0;
    for (mem_ptr = g->gr_mem; *mem_ptr; mem_ptr++)
    {
        gr_size += strlen(*mem_ptr) + 1;
		mem_array_counter++;
    }
	gr_size += (mem_array_counter + 1) * (sizeof(char*));

    if (gr_size > buflen)
    {
        __set_errno(ERANGE);
        *result = NULL;
        return -1;
    }

    grp->gr_gid = g->gr_gid;

    gr_size = 0;
	grp->gr_mem = (char**)&buf[gr_size];
    gr_size += (mem_array_counter + 1) * (sizeof(char*));

    grp->gr_name = &buf[gr_size];
    len = strlen(g->gr_name) + 1;
    memcpy(&buf[gr_size], g->gr_name, len);
    gr_size += len;
    
    grp->gr_passwd = &buf[gr_size];
    len = strlen(g->gr_passwd) + 1;
    memcpy(&buf[gr_size], g->gr_passwd, len);
    gr_size += len;
    
	mem_array_pos = 0;
    for(mem_ptr = g->gr_mem;*mem_ptr;mem_ptr++)
    {
        len = strlen(*mem_ptr) + 1;
        memcpy(&buf[gr_size], *mem_ptr, len);
		grp->gr_mem[mem_array_pos] = &buf[gr_size];
		mem_array_pos++;
        gr_size += len;
    }
	grp->gr_mem[mem_array_pos] = NULL;

    *result = grp;
    return 0;
}
