#include "ush.h"

static char *dell_path(char *str) {
	int len = strlen(str) - 1;
	char *tmp = strdup(str);
	int count = 2;

	for (; len > 0 && count; len--) {
		if (tmp[len] == '/')
			count--;
	}
	free(str);
	str = strndup(tmp, len + 1);
	mx_strdel(&tmp);
	return str;
}

char *mx_path_to_canonical(char *str) { //нормализация пути
	char *buff = mx_strnew(strlen(str));
	int j = 0;

	for (int i = 0; str[i]; i++) {
		if (str[i] == '.' && str[i + 1] == '/')
			i += 1;
		else if (str[i] == '.' && str[i + 1] == '.') {
			buff = dell_path(buff);
			j = strlen(buff);
			i += 1;
		}
		else
			buff[j++] = str[i];
	}
	free(str);
	str = strdup(buff);
	mx_strdel(&buff);
	return str;
}
