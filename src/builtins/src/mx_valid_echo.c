#include "mx_builtins.h"

bool mx_valid_echo(int *toggle, char *arg, char *flag, int *index) {
    if (arg[0] == '-') {
        for (int j = 1; arg[j]; j++) {
            if (arg[j] != 'n' && arg[j] != 'e' && arg[j] != 'E') {
                *toggle = 0;
                return true;
            }
        }
        *index = *index + 1;
        *flag = arg[strlen(arg) - 1];
    }
    else
        *toggle = 0;
    return true;
}
