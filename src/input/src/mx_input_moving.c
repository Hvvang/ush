#include "mx_input.h"

void mx_input_moving(char *line, int *pos, char *c) {
    if (MX_IS_LEFT_ARROW(c))
        mx_move_left(pos);
    else if (MX_IS_RIGHT_ARROW(c))
        mx_move_right(line, pos);
    else if (MX_IS_END(c))
        mx_get_end(line, pos);
    else if (MX_IS_HOME(c))
        mx_get_start(pos);
}
