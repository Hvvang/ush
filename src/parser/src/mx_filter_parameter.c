#include "mx_parser.h"

static char *get_var(char *arg, int *i) {
    char *temp = NULL;

    if (MX_IS_QBRACKET(arg[*i])) {
        mx_del_char_in_str(arg, *i);
        temp = mx_substr_to_symbol(&arg[*i], "}");
    }
    else
        temp = mx_substr_to_symbol(&arg[*i], " `'\"(){}\\$");
    return temp;
}

void mx_filter_parameter(char **arg, int *i) {
    char *temp = NULL;
    char *res = NULL;

    mx_del_char_in_str(*arg, *i);
    temp = get_var(*arg, i);
    if (getenv(temp) || !strcmp(temp, "?")) {
        res = (!strcmp(temp, "?")) ? getenv("status") : getenv(temp);
        mx_replace_var(arg, temp, res, i);
    }
    else {
        for (unsigned j = strlen(temp); j; j--)
            mx_del_char_in_str(*arg, *i);
    }
    mx_strdel(&temp);
    *i -= - 1;
}
