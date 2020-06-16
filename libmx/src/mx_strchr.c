#include "libmx.h"

char* mx_strchr(char* str, char c) {
	if (str == NULL)
		return NULL;
    for (int i = 0; str[i] != '\0'; i++) {
         if (str[i] == c)
         	 return &str[i];
	}
	return NULL;
}
