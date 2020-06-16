#include "mx_builtins.h"

bool mx_valid_cd(int *toggle, char *arg, char *flag, int *index) {
    if (!strcmp(arg, "--")) {
        *toggle = 0;
    }
    else if (arg[0] == '-' && arg[1]) {
        for (int j = 1; arg[j]; j++) {
            *flag = arg[j];
            if (arg[j] != 's' && arg[j] != 'P') {
                *toggle = 0;
                return true;
            }
        }
        *index = *index + 1;
    }
    else
        *toggle = 0;
    return true;
}
