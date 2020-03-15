#include "ush.h"
#define MX_PWD_DEFAULT 'L'
#define MX_CD_DEFAULT '0'

static char set_default(int builtin) {
    char flag;

    if (builtin == MX_PWD) {
        flag = MX_PWD_DEFAULT;
    }
    if (builtin == MX_CD) {
        flag = MX_CD_DEFAULT;
    }
    return flag;
}

char mx_check_flags(int builtin, int *index, char **args,  bool(*valid)(int *, char *, char *)) {
    char flag = set_default(builtin);
    int toggle = 1;

    for (int i = 0; toggle && args[i]; i++) {
        if (!(*valid)(&toggle, args[i], &flag)) {
            mx_builtin_usage(builtin, flag);
            flag = '\0';
            break;
        }
        *index = i;
        if (!mx_strcmp(args[i], "--"))
            *index = *index + 1;
    }
    return flag;
}
