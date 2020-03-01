#include "libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
	unsigned char* d = (unsigned char*)dst;
	unsigned char* s = (unsigned char*)src;
	size_t i = 0;

	while (i < n) {
 		d[i] = s[i];
 		if (s[i] == (unsigned char)c)
 			return (d + (++i));
 		i++;
 	}
 	return NULL;
}
