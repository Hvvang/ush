#include "mx_parser.h"

static void get_nested(char **arg, int i, int j, int *status) {
    char *sub = strndup(&((*arg)[i + 2]), j - (i + 2));
    char *res = NULL;
    int size;

    while (j + 1 != i) {
        mx_del_char_in_str(*arg, i);
        j--;
    }
    mx_filter_input(&sub, status);
    if (*status)
        return;
    res = mx_subshell(sub, status);
    size = strlen(*arg) + strlen(res) + 1;
    *arg = realloc(*arg, size);
    (*arg)[size - 1] = '\0';
    for (int k = 0; res[k]; k++)
        mx_insert_char_to_str(arg, res[k], i++);
    mx_strdel(&res);
}

int mx_get_substitution_by_bracket(char **arg, int *status) {
    int i;
    int j;

    for (i = 0; (*arg)[i]; i++) {
        if (MX_IS_DOLLAR((*arg)[i]) && MX_IS_BRACKET((*arg)[i + 1])) {
            for (j = i + 2; (*arg)[j]; j++) {
                if (MX_IS_DOLLAR((*arg)[j]) && MX_IS_BRACKET((*arg)[j + 1])) {
                    break;
                }
                else if (!(MX_IS_SLASH((*arg)[j - 1]))
                         && MX_IS_CBRACKET((*arg)[j])) {
                    get_nested(arg, i, j, status);
                    return 1;
                }
            }
        }
    }
    return 0;
}
