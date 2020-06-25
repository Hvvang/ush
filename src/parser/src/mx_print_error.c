#include "mx_parser.h"

#define MX_TERMINATING_CHAR "%s: syntax error: missing terminating character\n"
#define MX_SUBST_CHAR "%s: syntax error: missing subsitution character\n"
#define MX_BRACE_CHAR "%s: syntax error: missing brace character\n"
#define MX_PARSE_ERROR "%s: parse error near `;;'\n"

void mx_print_error(int error) {
    char *res = mx_itoa(error);

    setenv("status", res, 1);
    mx_strdel(&res);
    switch (error) {
        case -1:
            fprintf(stderr, MX_TERMINATING_CHAR, MX_SHELL_NAME);
            break;
        case -2:
            fprintf(stderr, MX_TERMINATING_CHAR, MX_SHELL_NAME);
            break;
        case -3:
            fprintf(stderr, MX_SUBST_CHAR, MX_SHELL_NAME);
            break;
        case -4:
            fprintf(stderr, MX_BRACE_CHAR, MX_SHELL_NAME);
            break;
        case -5:
            fprintf(stderr, MX_PARSE_ERROR, MX_SHELL_NAME);
            break;
    }
}
