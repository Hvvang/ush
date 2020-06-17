#include "mx_input.h"

void mx_print_backspace(char *str, int *pos) {
    if (*pos > 0) {
        printf("\b");
        mx_del_char_in_str(str, *pos - 1);
        printf("%s ", str + (*pos) - 1);
        for (unsigned i = 0; i <= strlen(str + (*pos) - 1); i++)
            printf("\b");
        fflush(NULL);
        *pos = (*pos) - 1;
    }
}
