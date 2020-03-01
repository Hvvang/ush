#include "libmx.h"

char *mx_strcpy(char *dst, const char *src) {
    int i = 0;

    if (src == NULL)
		return NULL;
    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return dst;
}
