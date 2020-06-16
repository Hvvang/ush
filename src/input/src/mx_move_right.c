#include "mx_input.h"

void mx_move_right(char *str, int *pos) {
    int len = strlen(str);

    if ((*pos) < len) {
        printf("%c", str[*pos]);
        *pos = (*pos) + 1;
    }
    fflush(NULL);
}
