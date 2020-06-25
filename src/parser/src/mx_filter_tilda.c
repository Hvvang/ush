#include "mx_parser.h"

#define MX_NO_USER "%s: no such user or named directory: %s\n"
#define MX_ERROR 1
#define MX_SUCCESS 0

static void filter_to_pwd(char **arg, int i) {
    if ((*arg)[i + 1] == '+')
        mx_replace_var(arg, "~+", getenv("PWD"), &i);
    else if ((*arg)[i + 1] == '-')
        mx_replace_var(arg, "~-", getenv("OLDPWD"), &i);
}

static int check_user(char *arg) {
    char *str = mx_substr_to_symbol(arg, " ");
    char *user = mx_join_path(MX_USERFOLDER, str);

    if (mx_get_type(user) == MX_EFAULT) {
        fprintf(stderr, MX_NO_USER, MX_SHELL_NAME, str);
        setenv("status", "1", 1);
        return MX_ERROR;
    }
    mx_strdel(&str);
    mx_strdel(&user);
    return MX_SUCCESS;
}

void mx_filter_tilda(char **arg, int *status) {
    mx_init_pwd(NULL);
	mx_init_home(NULL);
    for (int i = 0; (*arg)[i]; i++) {
        if (!(MX_IS_REGULAR((*arg)[i])))
            mx_skip_literal(*arg, &i, mx_get_literal((*arg)[i]));
        if ((*arg)[i] == '~') {
            if (i > 0 && (*arg)[i - 1] != ' ')
                continue;
            if ((*arg)[i + 1] == '/' || (*arg)[i + 1] == ' '
                || !(*arg)[i + 1])
                mx_replace_var(arg, "~", getenv("HOME"), &i);
            else if ((*arg)[i + 2] == '/' || (*arg)[i + 2] == ' '
                    || !(*arg)[i + 2])
                filter_to_pwd(arg, i);
            else if ((*arg)[i + 1] != '+' && (*arg)[i + 1] != '-'
                     && (*arg)[i + 1] != '/')
                if ((*status = check_user(&(*arg)[i + 1])) == MX_SUCCESS)
                    mx_replace_var(arg, "~", MX_USERFOLDER, &i);
        }
    }
}
