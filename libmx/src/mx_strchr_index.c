#include "libmx.h"

int mx_strchr_index(char* str, char c) {
	if (str == NULL)
		return -2;
   	for (int i = 0; str[i] != '\0'; i++) {
         if (str[i] == c)
         	return i;
	}
	return -1;
}
