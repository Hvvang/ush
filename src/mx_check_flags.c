#include "ush.h"

static char set_default(int builtin) {
    char flag;

    if (builtin == MX_PWD) {
        flag = 'P';
    }
    if (builtin == MX_CD) {
        flag = '\0';
    }
    return flag;
}


char mx_check_flags(int builtin, char **args,  bool(*valid)(int *, char *, char *)) {
    char flag = set_default(builtin);
    int toggle = 1;

    for (int i = 0; toggle && args[i]; i++) {
        if (!(*valid)(&toggle, args[i], &flag)) {
            mx_builtin_usage(builtin, flag);
            flag = '\0';
            break;
        }
    }
    return flag;
}
