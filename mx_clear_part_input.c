#include "mx_input.h"

void mx_clear_part_input(char *line, int *pos, char *c) {
    if (c[0] == 127)
        print_backspace(line, pos);
    else if (MX_IS_DEL(c)) {
        if (pos < len)
            print_del(line, pos);
        else
            printf("\a");
    }
    else if (MX_IS_BS(c)) {
        while (pos > 0)
            print_backspace(line, pos);
    }
    else if (MX_IS_VT(c)) {
        int len = strlen(line);

        while (pos < len) {
            print_del(line, pos);
            len = strlen(line);
        }
    }
}
