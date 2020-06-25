#include "mx_parser.h"

int mx_check_subs_lvls(char *str, int *index, int prev_lvl) {
    int lvl = 0;
    int pos = *index;

    for(; str[*index - 1] == '\\' && str[*index] == '`'; *index += 2) {
        if (lvl < prev_lvl + 1)
            lvl++;
        else {
            if (str[*index - 1] == '\\' && str[*index] == '`')
                mx_insert_char_to_str(&str, ' ', *index + 1);
            break;
        }
    }
    if (pos != *index)
        *index = *index - 2;
    return lvl;
}
