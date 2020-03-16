#include "ush.h"

bool mx_valid_cd(int *toggle, char *arg, char *flag) {
    if (!strcmp(arg, "--") || !strcmp(arg, "-"))
        *toggle = 0;
    else if (arg[0] == '-') {
        for (int j = 1; arg[j]; j++) {
            if (arg[j] != 's' && arg[j] != 'P') {
                *flag = arg[j];
                return false;
            }
        }
        *flag = arg[strlen(arg) - 1];
    }
    else
        *toggle = 0;
    return true;
}
