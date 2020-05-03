#include "mx_input.h"

void mx_input_moving(char *line, int *pos, bool *esc, char *c) {
    if (MX_IS_LEFT_ARROW(c)) {
        if (!(*esc))
            get_prev(pos);
        else
            get_home(pos, esc);
    }
    else if (MX_IS_RIGHT_ARROW(c)) {
        if (!(*esc))
            get_next(line, pos);
        else
            get_end(line, pos, esc);
    }
    else if (MX_IS_END(c)) {
        get_end(line, pos, esc);
    }
    else if (MX_IS_HOME(c)) {
        get_home(pos, esc);
    }
}
