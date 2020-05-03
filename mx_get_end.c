#include "mx_input.h"

void mx_get_end(char *str, int *pos, bool *esc) {
    int len = strlen(str);

    while (*pos < len)
        get_next(str, pos);
    *esc = false;
}
