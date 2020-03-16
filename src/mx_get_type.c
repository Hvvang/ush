#include "ush.h"

int mx_get_type(const char *path) {
	struct stat stat;

	lstat(path, &stat);
	// if (S_ISSOCK(stat.st_mode))
	// 	return MX_SOCKET;
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