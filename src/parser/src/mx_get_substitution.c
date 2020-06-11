#include "../inc/mx_parser.h"

static int get_sub_lvl(char *arg, int *i) {
    int lvl = 0;
    unsigned index;

    for(index = *i; arg[index] == '\\' && arg[index + 1] == '`'; index += 2)
        lvl++;
    return lvl;
}

char *mx_get_substitution(char *arg, int *i) {
    bool toggle = true;
    int index;
    int lvl = get_sub_lvl(arg, i);

    for (index = (lvl) ? lvl * 2 : 1; index; index--)
        mx_del_char_in_str(arg, *i);
    for (index = *i; arg[index] && toggle; index++) {
        if (lvl == 0 && (arg[index - 1] != '\\' && arg[index] == '`'))
            break;
        if (MX_IS_SLASH(arg[index]) && MX_IS_QUOTE(arg[index + 1])) {
            if (lvl == get_sub_lvl(arg, &index)) {
                toggle = false;
                break;
            }
            index += 2;
        }
    }
    for (lvl = (lvl) ? lvl * 2 : 1; lvl; lvl--)
        mx_del_char_in_str(arg, index);
    return mx_strndup(arg + *i, index - *i);
}
