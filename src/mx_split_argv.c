#include "ush.h"

char **mx_split_argv(char *line) {
	int bufsize = 1024;
	char **args = malloc(bufsize * sizeof(char*));

	if (!args) {
		perror("ush: bad memory");
		exit(EXIT_FAILURE);
	}

	args = mx_strsplit(line, ' ');
	return args;
}
