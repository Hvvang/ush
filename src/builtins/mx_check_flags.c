#include "ush.h"
#define MX_PWD_DEFAULT 'L'
#define MX_CD_DEFAULT '0'
#define MX_ECHO_DEFAULT '0'

static char set_default(int builtin) {
    char flag;

    if (builtin == MX_PWD) {
        flag = MX_PWD_DEFAULT;
    }
    if (builtin == MX_CD) {
        flag = MX_CD_DEFAULT;
    }
    if (builtin == MX_ECHO) {
        flag = MX_ECHO_DEFAULT;
    }
    return flag;
}

char mx_check_flags(int builtin, int *index, t_command *commands,  bool(*valid)(int *, char *, char *, int *)) {
    char **args = commands->arguments;
    char flag = set_default(builtin);
    int toggle = 1;

    for (int i = 0; toggle && args[i]; i++) {
        if (!(*valid)(&toggle, args[i], &flag, index)) {
            mx_builtin_usage(builtin, flag);
            flag = '\0';
            commands->exit = 1;
            break;
        }
        // *index = i;
        // if (!mx_strcmp(args[i], "--"))
        //     *index = *index + 1;
    }
    // printf("index = %d\n", *index);
    // exit(1);
    return flag;
}
