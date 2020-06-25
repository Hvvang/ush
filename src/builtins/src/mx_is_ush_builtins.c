#include "mx_builtins.h"

static int extended_builtins(char *command) {
    if (!strcmp(command, "history"))
        return MX_HISTORY;
    else if (!strcmp(command, "true"))
        return MX_TRUE;
    else if (!strcmp(command, "false"))
        return MX_FALSE;
    else if (!strcmp(command, "color"))
        return MX_COLOR;
    else if (!strcmp(command, "bye"))
        return MX_BYE;
    return -1;
}

static int main_builtins(char *command) {
    if (!strcmp(command, "export"))
        return MX_EXPORT;
    else if (!strcmp(command, "unset"))
        return MX_UNSET;
    else if (!strcmp(command, "exit"))
        return MX_EXIT;
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
    return extended_builtins(command);
}


int mx_is_ush_builtins(char *commands) {
    return main_builtins(commands);
}
