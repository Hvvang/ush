#include "mx_builtins.h"

int mx_is_ush_builtins(char *command) {
    if (!strcmp(command, "export"))
        return MX_EXPORT;
    if (!strcmp(command, "unset"))
        return MX_UNSET;
    if (!strcmp(command, "exit"))
        return MX_EXIT;
    if (!strcmp(command, "env"))
        return MX_ENV;
    if (!strcmp(command, "cd"))
        return MX_CD;
    if (!strcmp(command, "fg"))
        return MX_FG;
    if (!strcmp(command, "pwd"))
        return MX_PWD;
    if (!strcmp(command, "echo"))
        return MX_ECHO;
    if (!strcmp(command, "which"))
        return MX_WHICH;
    if (!strcmp(command, "history"))
        return MX_HISTORY;
    else
        return MX_NOT_A_USH_BUILTIN;
}
