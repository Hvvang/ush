#include "libmx.h"

char *mx_join_path(const char *left, const char *right) {
	char *tmp = mx_strjoin(left, "/");
	char *path = mx_strjoin(tmp, right);

	mx_strdel(&tmp);
    return path;
}
