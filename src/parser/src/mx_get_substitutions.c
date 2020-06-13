#include "../inc/mx_parser.h"

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

int mx_get_substitutions(char **arg) {
    char *sub = NULL;
    int index_i;
    int index_j;

    for (index_i = 0; (*arg)[index_i]; index_i++) {
        int lvl_prev = get_sub_lvl((*arg), &index_i);

        if (lvl_prev) {
            for (index_j = index_i + lvl_prev; (*arg)[index_j]; index_j++) {
                if (lvl_prev <= get_sub_lvl(*arg, &index_j))
                    break;
            }
            if (lvl_prev == get_sub_lvl(*arg, &index_j)) {
                sub = strndup(&((*arg)[index_i + lvl_prev]),
                index_j - (index_i + lvl_prev));
                while (index_j + lvl_prev != index_i) {
                    mx_del_char_in_str(*arg, index_i);
                    index_j--;
                }
                mx_filter_input(&sub);
                char *res = mx_subshell(sub);

                for (int k = 0; res[k]; k++)
                    mx_insert_char_to_str(*arg, res[k], index_i++);
                mx_strdel(&res);
                return 1;
            }
        }
    }
    return 0;
}
