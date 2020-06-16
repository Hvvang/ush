#include "libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    char *buf = mx_strnew(n);
    
    if(!buf)
    	return NULL;
    mx_strncpy(buf, s1, n);
    return buf;
}
