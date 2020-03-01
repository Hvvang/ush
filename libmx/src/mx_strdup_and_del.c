#include "libmx.h"

char *mx_strdup_and_del(char **str) {
	char *s = mx_strdup(*str);

	mx_strdel(str);
	return s;
}
