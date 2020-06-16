#include "libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
	unsigned char* ptr = (unsigned char*) src;
	unsigned char* ptr2 = (unsigned char*) dst;
	
     for (size_t i = 0; i < n; i++) {
     	ptr2[i] = ptr[i];
     }
     return (void*)dst;
}
