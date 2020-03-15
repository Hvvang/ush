#include "ush.h"

bool mx_valid_pwd(int *toggle, char *arg, char *flag) {
    if (!strcmp(arg, "--"))
        *toggle = 0;
    else if (!strcmp(arg, "-"))
        return true;
    else if (arg[0] == '-') {
        for (int j = 1; arg[j]; j++) {
            if (arg[j] != 'L' && arg[j] != 'P')
                return false;
        }
        *flag = arg[strlen(arg) - 1];
    }
    else
        *toggle = 0;
    return true;
}