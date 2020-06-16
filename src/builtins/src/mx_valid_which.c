#include "mx_builtins.h"

bool mx_valid_which(int *toggle, char *arg, char *flag, int *index) {
    if (!strcmp(arg, "--") || !strcmp(arg, "-")) {
        *index = *index + 1;
        *toggle = 0;
    }
    else if (arg[0] == '-' && arg[1]) {
        for (int j = 1; arg[j]; j++) {
            *flag = arg[j];
            if (arg[j] != 's' && arg[j] != 'a')
                return false;
        }
        *index = *index + 1;
    }
    else
        *toggle = 0;
    return true;
}
