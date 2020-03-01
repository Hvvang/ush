#include "libmx.h"

char *mx_strdup(const char *str) {
	char *buf = NULL;

	if (str == NULL)
		return NULL;
	if (*str == '\0') {
		buf = (char*)malloc(sizeof(char) * 1);
		if (buf == NULL)
			return NULL;
	    buf[0] = '\0';
	    return buf;
	}
    int len = mx_strlen(str);
    buf = mx_strnew(len);
    if (buf == NULL)
		return NULL;
    mx_strcpy(buf, str);
    return buf;
}
