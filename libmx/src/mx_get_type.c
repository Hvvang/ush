#include "libmx.h"

int mx_get_type(const char *path) {
	DIR *dir = opendir(path);
	struct stat stat;

	errno = 0;
	lstat(path, &stat);
	if (dir)
		closedir(dir);
	if (S_ISLNK(stat.st_mode))
		return MX_LINK;
	else if (S_ISREG(stat.st_mode))
		return MX_FILE;
	else if (S_ISBLK(stat.st_mode))
		return MX_BLOCK;
	else if (S_ISDIR(stat.st_mode))
		return MX_DIR;
	else if (S_ISCHR(stat.st_mode))
		return MX_CHAR;
	else if (S_ISFIFO(stat.st_mode))
		return MX_FIFO;
	else
		return MX_EFAULT;
}
