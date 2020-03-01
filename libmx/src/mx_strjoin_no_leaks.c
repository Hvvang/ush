#include "libmx.h"

char *mx_strjoin_no_leaks(char *s1, char *s2) {
	char* res = NULL;

	res = mx_strjoin(s1, s2);
	if (s1)
		mx_strdel(&s1);
	if (s2)
		mx_strdel(&s2);
	return res;
}
