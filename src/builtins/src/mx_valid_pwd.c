#include "../inc/mx_builtins.h"

bool mx_valid_pwd(int *toggle, char *arg, char *flag, int *index) {
    if (!strcmp(arg, "--")) {
        *index = *index + 1;
        *toggle = 0;
    }
    else if (!strcmp(arg, "-"))
        return true;
    else if (arg[0] == '-') {
        for (int j = 1; arg[j]; j++) {
            *flag = arg[j];
            if (arg[j] != 'L' && arg[j] != 'P')
                return false;
        }
        *index = *index + 1;
    }
    else
        *toggle = 0;
    return true;
}
