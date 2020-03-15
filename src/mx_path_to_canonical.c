#include "ush.h"

static char *dell_path(char *str) {
	int len = strlen(str);
	char *tmp = strdup(str);

	for (; len > 0; len--) {
		if (tmp[len] == '/')
			break;
	}
	str = strndup(tmp, len);
	mx_strdel(&tmp);
	return str;
}

char *mx_path_to_canonical(char *str) { //нормализация пути
	char *buff = mx_strnew(strlen(str));
	int j = 0;

	for (int i = 0; str[i]; i++) {
		if (str[i] == '.' && str[i + 1] == '/')
			i += 1;
		else if (str[i] == '.' && str[i + 1] == '.' && str[i + 2] == '/') {
			dell_path(buff);
			i += 2;
		}
		else
			buff[j++] = str[i];
	}
	free(str);
	str = strdup(buff);
	mx_strdel(&buff);
	return str;
}
