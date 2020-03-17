#include "ush.h"

void mx_builtin_usage(int builtin, char error) {
    switch (builtin) {
        case MX_PWD:
            fprintf(stderr, "u$h: pwd: -%c: invalid option\n", error);
            fprintf(stderr, "pwd: usage: pwd [-LP]\n");
            break;
        case MX_CD:
            fprintf(stderr, "u$h: cd: -%c: invalid option\n", error);
            fprintf(stderr, "cd: usage: cd [-sP] [{-}|dir]\n");
            break;
        case MX_EXPORT:
            fprintf(stderr, "u$h: export: -%c: invalid option\n", error);
            fprintf(stderr, "export: usage: export [name[=value] ...]\n");
            break;
        case MX_UNSET:
            fprintf(stderr, "u$h: unset: -%c: invalid option\n", error);
            fprintf(stderr, "unset: usage: export [name ...]\n");
            break;
        case MX_WHICH:
            fprintf(stderr, "u$h: which: -%c: invalid option\n", error);
            fprintf(stderr, "which: usage: which [-as] [pragramname ...]\n");
            break;
    }
}
