#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
 	int i = 0;

    if (str == NULL || sub == NULL)
     	return -2;
    while (*str != '\0') {
        if (!mx_strncmp(str,sub, mx_strlen(sub)))
        	return i;
        else {
        	str++;
            i++;
        }
    }
     return -1;
}
