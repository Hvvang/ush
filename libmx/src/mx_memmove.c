#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
	char* d = (char*)dst;
	const char* s = (char*)src;
	char* tmp = NULL;

	tmp = mx_strnew(len);
    for (size_t j = 0; j < len; j++)
        tmp[j] = s[j];
	for (size_t i = 0; i < len; i++)
        d[i] = tmp[i];
	free(tmp);
	tmp = NULL;
	return (void*)dst;
}
