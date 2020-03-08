#include "ush.h"

char *mx_ush_read_line(void) {
    size_t bufsize = 1;
    char *tmp = NULL;
    char *stdin_line = NULL;

    getline(&tmp, &bufsize, stdin);
    stdin_line = mx_strtrim(tmp);
    return stdin_line;
}
