#include "libmx.h"

void *mx_realloc(void *ptr, size_t size) {
	void* p = NULL;
	size_t old_size;

	if (size == 0 && ptr) {
		free(ptr);
		return NULL;
	}
	if (!ptr && size)
		return (void *)mx_strnew(size);
	old_size = mx_strlen((char*)ptr);
	if (size < old_size)
		p = mx_strnew(old_size);
    else
    	p = mx_strnew(size);
    if (p == NULL)
    	return NULL;
    mx_memcpy(p, ptr, size);
    free(ptr);
    return (void*)p;
}
