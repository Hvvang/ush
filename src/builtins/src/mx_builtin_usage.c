#include "mx_builtins.h"

#define MX_INVALID_OPTION "u$h: %s: -%c: invalid option\n"


void mx_builtin_usage(int builtin, char *command, char error) {
    fprintf(stderr, MX_INVALID_OPTION, command, error);
    switch (builtin) {
        case MX_PWD:
            fprintf(stderr, "pwd: usage: pwd [-LP]\n");
            break;
        case MX_EXPORT:
            fprintf(stderr, "export: usage: export [name[=value] ...]\n");
            break;
        case MX_UNSET:
            fprintf(stderr, "unset: usage: export [name ...]\n");
            break;
        case MX_WHICH:
            fprintf(stderr, "which: usage: which [-as] [pragramname ...]\n");
            break;
        case MX_ENV:
            fprintf(stderr, "env: usage: env [-i] [-P utilpath] [-u name]\n");
            break;
    }
}
