#include "mx_input.h"

void mx_move_left(int *pos) {
    if ((*pos) > 0) {
        printf("\b");
        *pos = (*pos) - 1;
    }
    fflush(NULL);
}
