#include "mx_parser.h"

static int get_sub_lvl(char *arg, const int *i) {
    int lvl = 0;
    unsigned index;

    if (*i == 0 && arg[*i] == '`')
        lvl = 1;
    else if (*i > 0 && arg[*i] == '`' && arg[*i - 1] != '\\') {
        lvl = 1;
    }
    for(index = *i; arg[index] == '\\' && arg[index + 1] == '`'; index += 2)
        lvl += 2; // increment +2 to avoid error on skiping literal
    return lvl;
}

static void get_nested(char **arg, int i, int j, int lvl_prev, int *status) {
    char *sub = strndup(&((*arg)[i + lvl_prev]),
                        j - (i + lvl_prev));
    char *res = NULL;
    int size;

    while (j + lvl_prev != i) {
        mx_del_char_in_str(*arg, i);
        j--;
    }
    mx_filter_input(&sub, status);
    if (*status)
        return;
    res = mx_subshell(sub, status);
    size = strlen(*arg) + strlen(res) + 1;
    *arg = realloc(*arg, size);
    for (int k = 0; res[k]; k++)
        mx_insert_char_to_str(arg, res[k], i++);
    mx_strdel(&res);
}

int mx_get_substitution_by_quote(char **arg, int *status) {
    int i;
    int j;

    for (i = 0; (*arg)[i]; i++) {
        int lvl_prev = get_sub_lvl((*arg), &i);

        if (lvl_prev) {
            for (j = i + lvl_prev; (*arg)[j]; j++) {
                if (lvl_prev <= get_sub_lvl(*arg, &j))
                    break;
            }
            if (lvl_prev == get_sub_lvl(*arg, &j)) {
                get_nested(arg, i, j, lvl_prev, status);
                return 1;
            }
        }
    }
    return 0;
}
