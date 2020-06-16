#include "libmx.h"

void *mx_memset(void *b, int c, size_t len) {  
	unsigned char* ptr = (unsigned char*)b;
    size_t i = 0;

    for (; i < len; i++) {
	    ptr[i] = c;
	}
	return (void*)b;
}
