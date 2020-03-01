#include "libmx.h"

char *mx_strtrim(const char *str) { 
	int i = 0;
	int b = 0;
    int len = 0;
    int j = 0;
    char *des = NULL;

	if (str == NULL)
		return NULL;
	len = mx_strlen(str);
	j = len - 1;
	for (; i !=  len ; i++) {
		if (mx_isspace(str[b]))
			 b++;
		 if (mx_isspace(str[j]))
		 	j--;
	}
	des = mx_strnew(j - b);
	if (des == NULL)
		return "";
    return des = mx_strncpy(des, &str[b], j - b + 1);
}
