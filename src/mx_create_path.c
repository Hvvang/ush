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

char *mx_create_path(char *command, int d_type, char flag) {
    char *path = NULL;
    char buff[PATH_MAX + 1];
    char *tmp = NULL;

    if (flag == '0' || flag == 's') {
        if (!strcmp(command, ".."))
            path = dell_path(getenv("PWD"));
        else {
            if (command[0] == '/')
                tmp = strdup("\0");
            else
                tmp = mx_strjoin(getcwd(buff, PATH_MAX), "/");
            path = mx_strjoin(tmp, command);
        }
    }
    else if (flag == 'P') {
        if (!strcmp(command, ".."))
            path = dell_path(getcwd(buff, PATH_MAX));
        else {
            chdir(command);
            path = strdup(getcwd(buff, PATH_MAX));
        }
    }
    mx_strdel(&tmp);
    return path;
}
