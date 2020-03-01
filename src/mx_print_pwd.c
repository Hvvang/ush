#include "ush.h"

int mx_print_pwd(void) {
	char s[200];
	printf("%s\n", getcwd(s, 200));
	return 0;
}
