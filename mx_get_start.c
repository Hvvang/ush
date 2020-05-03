#include "mx_input.h"

void mx_get_start(int *pos, bool *esc) {
    while (*pos > 0)
        get_prev(pos);
    *esc = false;
}
