#include "../inc/mx_parser.h"

char *mx_filter_tilda(char *arg) {
    for (int i = 0; arg[i]; i++) {
        if (!(MX_IS_REGULAR(arg[i])))
            mx_skip_literal(arg, &i, mx_get_literal(arg[i]));
        if (arg[i] == '~') {
            if (i > 0 && arg[i - 1] != ' ')
                continue;
            if (arg[i + 1] == '/' || !arg[i + 1])
                arg = mx_replace_chars_by_str(arg, i, 1, getenv("HOME"));
            else if (arg[i + 1] == '+' && (arg[i + 2] == '/' || !arg[2]))
                arg = mx_replace_chars_by_str(arg, i, 2, getenv("PWD"));
            else if (arg[i + 1] == '-' && (arg[i + 2] == '/' || !arg[2]))
                arg = mx_replace_chars_by_str(arg, i, 2, getenv("OLDPWD"));
            else if (arg[i + 1] != '+' && arg[i + 1] != '-' && arg[1] != '/') {
                arg = mx_replace_chars_by_str(arg, i, 1, MX_USERFOLDER);
            }
        }
    }
    return arg;
}
