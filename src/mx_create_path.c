#include "ush.h"

char *mx_create_path(char *command, char flag) {
    char *path = NULL;
    char buff[PATH_MAX + 1];

    if (flag == '0' || flag == 's') {
		char *tmp = NULL;

        if (command[0] == '/')
            tmp = strdup("\0");
        else
            tmp = mx_strjoin(getenv("PWD"), "/");
        path = mx_strjoin(tmp, command);
		mx_strdel(&tmp);
    }
    else if (flag == 'P') {
		chdir(command);
		path = strdup(getcwd(buff, PATH_MAX));
    }
    return path;
}
