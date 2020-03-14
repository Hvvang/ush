#include "ush.h"

static char set_default(int builtin) {
    char flag = '\0';

    if (builtin == MX_PWD) {
        flag = 'P';
    }
    return flag;
}


char mx_check_flags(int builtin, char **args,  bool(*valid)(int *, char *, char *)) {
    char flag = set_default(builtin);
    int toggle = 1;

    for (int i = 0; args[i]; i++) {
        if (!(*valid)(&toggle, args[i], &flag)) {
            flag = '\0';
            break;
        }
    }
    return flag;
}
