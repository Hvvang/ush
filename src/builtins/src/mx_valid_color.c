#include "mx_builtins.h"

bool mx_valid_color(int *toggle, char *arg, char *flag, int *index) {
    if (!strcmp(arg, "--")) {
        *toggle = 0;
    }
    else if (arg[0] == '-' && arg[1]) {
        for (int j = 1; arg[j]; j++) {
            *flag = arg[j];
            if (arg[j] != 'r' && arg[j] != 'l'
                && arg[j] != 'f' && arg[j] != 'b') {
                *toggle = 0;
                return false;
            }
        }
        *index = *index + 1;
    }
    else
        *toggle = 0;
    return true;
}
