#include "mx_input.h"

void mx_get_start(int *pos) {
    while (*pos > 0)
        mx_move_left(pos);
}
