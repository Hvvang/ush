#include "mx_builtins.h"

int mx_is_ush_builtins(char *command) {
    if (!strcmp(command, "export"))
        return MX_EXPORT;
    else if (!strcmp(command, "unset"))
        return MX_UNSET;
    else if (!strcmp(command, "exit"))
        return MX_EXIT;
    else if (!strcmp(command, "env"))
        return MX_ENV;
    else if (!strcmp(command, "cd"))
        return MX_CD;
    else if (!strcmp(command, "fg"))
        return MX_FG;
    else if (!strcmp(command, "pwd"))
        return MX_PWD;
    else if (!strcmp(command, "echo"))
        return MX_ECHO;
    else if (!strcmp(command, "jobs"))
        return MX_JOBS;
    else if (!strcmp(command, "which"))
        return MX_WHICH;
    else if (!strcmp(command, "history"))
        return MX_HISTORY;
    else
        return -1;
}
