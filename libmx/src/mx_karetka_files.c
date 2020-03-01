#include "uls.h"

void mx_karetka_files(char** str) {
	for (int i; *str[i] != '\0'; i++) {
		if (*str[i] == '\b' || str[i] == '\f' 
			|| *str[i] == '\n' 
			|| *str[i] == '\r' 
			|| *str[i] == '\t' 
			|| *str[i] == '\v')
			*str[i] == '?';
	}
}