#include "ush.h"

static int get_lvl(char *str, int *index) {
    int lvl = 0;

    while (str[*index] == '\\' && str[*index + 1] == '`') {
        *index = *index + 2;
        lvl++;
    }
    return lvl;
}

int mx_check_subs_lvls(char *str, int *index) {
    int lvl = get_lvl(str, index);

    for (; *index < (int)strlen(str); (*index)++) {
        int current_lvl = get_lvl(str, index);

        if (current_lvl) {
            if (current_lvl < lvl) {
                return -1;
            }
            if (current_lvl > lvl) {
                *index = *index - (current_lvl * 2);
                mx_check_subs_lvls(str, index);
            }
            if (current_lvl == lvl)
                return 0;
        }

    }
    return 0;
}
