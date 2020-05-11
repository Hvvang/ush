#include "libmx.h"

void mx_strdel(char **str) {
	if (*str != NULL) {

		// printf("[mx_strdel] str = %s address = %p\n", *str, (void *)(*str));
    	free(*str);
    	*str = NULL;
		// printf("2\n");
   	}
}
