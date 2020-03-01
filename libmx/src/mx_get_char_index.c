#include "libmx.h"

int mx_get_char_index(const char *str, char c) {
	int ind = 0;

	if (!str)
		return -2;
	while (str[ind] != '\0') {
		if (str[ind] == c)
			return ind;
	    else 
	    	ind++;
	}
	if (str[ind] == '\0')
        return -1;
    return ind;
}
