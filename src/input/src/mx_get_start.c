#include "../inc/mx_input.h"

void mx_get_start(int *pos, bool *esc) {
    while (*pos > 0)
        mx_move_left(pos);
    *esc = false;
}
