#include "../inc/mx_builtins.h"
#define MX_PWD_DEFAULT 'L'
#define MX_CD_DEFAULT '0'
#define MX_ECHO_DEFAULT '0'
#define MX_WHICH_DEFAULT '0'

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
    if (builtin == MX_WHICH) {
        flag = MX_WHICH_DEFAULT;
    }
    return flag;
}

char mx_check_flags(int builtin, int *index, t_command *command,
                    bool(*valid)(int *, char *, char *, int *)) {
    char **args = command->arguments;
    char flag = set_default(builtin);
    int toggle = 1;

    for (int i = 0; toggle && args[i]; i++) {
        if (!(*valid)(&toggle, args[i], &flag, index)) {
            mx_builtin_usage(builtin, flag);
            flag = '\0';
            command->exit = 1;
            break;
        }
    }
    return flag;
}
