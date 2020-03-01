#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
	int i = 0;
	int j = 0;

	for (; s1[i] != '\0'; i++)
		;
	     for (; s2[j] != '\0'; j++) {
		     s1[i + j] = s2[j];
	     }
	s1[i + j] = '\0';
	return s1;
}
