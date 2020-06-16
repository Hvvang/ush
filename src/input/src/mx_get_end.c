#include "mx_input.h"

void mx_get_end(char *str, int *pos) {
    int len = strlen(str);

    while (*pos < len)
        mx_move_right(str, pos);
}
