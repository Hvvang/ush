#include "libmx.h"

int mx_count_words(const char *str, char c) {
	int count = 0;
	int i = 0;

	if (str == NULL)
		return -1;
	while (str[i] != '\0') {
	    while (str[i] == c && str[i] != '\0')
	    	i++;
	    if (str[i] != c && str[i] != '\0')
	    	count++;
	    while (str[i] != c && str[i] != '\0')
	    	i++;   
	}
	return count;
}
