#include "mx_parser.h"

void mx_filter_tilda(char **arg) {
    for (int i = 0; (*arg)[i]; i++) {
        if (!(MX_IS_REGULAR((*arg)[i])))
            mx_skip_literal(*arg, &i, mx_get_literal((*arg)[i]));
        if ((*arg)[i] == '~') {
            if (i > 0 && (*arg)[i - 1] != ' ')
                continue;
            if ((*arg)[i + 1] == '/' || !(*arg)[i + 1])
                mx_replace_var(arg, "~/", getenv("HOME"), &i);
            else if ((*arg)[i + 1] == '+' && ((*arg)[i + 2] == '/' || !(*arg)[i + 2]))
                mx_replace_var(arg, "~+/", getenv("PWD"), &i);
            else if ((*arg)[i + 1] == '-' && ((*arg)[i + 2] == '/' || !(*arg)[i + 2]))
                mx_replace_var(arg, "~-/", getenv("OLDPWD"), &i);
            else if ((*arg)[i + 1] != '+' && (*arg)[i + 1] != '-' && (*arg)[i + 1] != '/') {
                mx_replace_var(arg, "~", MX_USERFOLDER, &i);
            }
        }
    }
}
