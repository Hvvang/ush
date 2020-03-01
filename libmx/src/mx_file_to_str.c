#include "libmx.h"

static char* return_my_line(char **buff, char **res);

char *mx_file_to_str(const char *file) {
    int size = 0;
    char* res = NULL;
    char* buff = mx_strnew(1);
    int fd = open(file, O_RDONLY);

    if (read(fd, NULL, 0) == -1)
    {
        close(fd);
        mx_strdel(&buff);
        return NULL;
    }
    while ((size = read(fd, buff, 1) > 0)) {
        char* tmp = mx_strdup(res);
        mx_strdel(&res);
        res = mx_strjoin(tmp, buff);
        mx_strdel(&tmp);
     }
     close(fd);
     return return_my_line(&buff, &res);
}

static char* return_my_line(char **buff, char **res) {
    if (*res == NULL) {
        mx_strdel(buff);
        return NULL;
    }
    else {
        mx_strdel(buff);
        return *res;
    }
    return *res;
}
