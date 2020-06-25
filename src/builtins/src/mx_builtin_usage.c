#include "mx_builtins.h"

#define MX_INVALID_OPTION "%s: -%c: invalid option\n"
#define MX_BAD_OPTION "%s: bad option: -%c\n"
#define MX_INVALID_PARAM "%s: %c: invalid parameter name\n"

void mx_builtin_usage(int builtin, char *command, char error) {
    switch (builtin) {
        case MX_WHICH:
            fprintf(stderr, MX_BAD_OPTION, command, error);
            break;
        case MX_ENV:
            fprintf(stderr, "env: usage: env [-i] [-P utilpath] [-u name]\n");
            break;
        case MX_COLOR:
            fprintf(stderr, MX_INVALID_OPTION, command, error);
            break;
    }
}
