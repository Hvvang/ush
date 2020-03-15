#include "ush.h"

void mx_builtin_usage(int builtin, char error) {
    switch (builtin) {
        case MX_PWD:
            fprintf(stderr, "u$h: pwd: -%c: invalid option\n", error);
            fprintf(stderr, "pwd: usage: pwd [-LP]\n");
            break;
        case MX_CD:
            fprintf(stderr, "u$h: cd: -%c: invalid option\n", error);
            fprintf(stderr, "cd: usage: cd [-s|[-P] [{-}|dir]\n");
            break;
    }
}
