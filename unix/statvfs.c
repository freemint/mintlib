#include <sys/statvfs.h>
#include <sys/statfs.h>
#include <string.h>
#include <limits.h>

static void fixup(struct statvfs *out, const struct statfs *in)
{
	memset(out, 0, sizeof(struct statvfs));
	out->f_bsize = in->f_bsize;
	out->f_frsize = in->f_bsize;
	out->f_blocks = in->f_blocks;
	out->f_bfree = in->f_bfree;
	out->f_bavail = in->f_bavail;
	out->f_files = in->f_files;
	out->f_ffree = in->f_ffree;
	out->f_favail = in->f_ffree;
	out->f_fsid = in->f_fsid;
	out->f_flag = 0;
	out->f_namemax = PATH_MAX;
}

int statvfs(const char *path, struct statvfs *buf)
{
	struct statfs kbuf;
	if (statfs(path, &kbuf)<0) return -1;
	fixup(buf, &kbuf);
	return 0;
}
