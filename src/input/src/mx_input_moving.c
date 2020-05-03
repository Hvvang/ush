#include "../inc/mx_input.h"

void mx_input_moving(char *line, int *pos, bool *esc, char *c) {
    if (MX_IS_LEFT_ARROW(c)) {
        if (!(*esc))
            mx_move_left(pos);
        else
            mx_get_start(pos, esc);
    }
    else if (MX_IS_RIGHT_ARROW(c)) {
        if (!(*esc))
            mx_move_right(line, pos);
        else
            mx_get_end(line, pos, esc);
    }
    else if (MX_IS_END(c)) {
        mx_get_end(line, pos, esc);
    }
    else if (MX_IS_HOME(c)) {
        mx_get_start(pos, esc);
    }
}
