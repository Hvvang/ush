#include "mx_input.h"

void mx_clear_part_input(char *line, int len, int *pos, char *c) {
    if (c[0] == 127)
        mx_print_backspace(line, pos);
    else if (MX_IS_DEL(c)) {
        if (*pos < len)
            mx_print_del(line, pos);
        else
            printf("\a");
    }
    else if (MX_IS_BS(c)) {
        while (*pos > 0)
            mx_print_backspace(line, pos);
    }
    else if (MX_IS_VT(c)) {
        while (*pos < len) {
            mx_print_del(line, pos);
            len = strlen(line);
        }
    }
}
