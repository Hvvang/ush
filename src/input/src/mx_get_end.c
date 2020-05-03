#include "../inc/mx_input.h"

void mx_get_end(char *str, int *pos, bool *esc) {
    int len = strlen(str);

    while (*pos < len)
        mx_move_right(str, pos);
    *esc = false;
}
