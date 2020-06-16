#include "mx_input.h"

void mx_print_del(char *str, int *pos) {
    mx_del_char_in_str(str, *pos);
    int i = strlen(str);

    printf("%s ", &str[*pos]);
    while (i >= *pos) {
        i--;
        printf("\b");
    }
    fflush(NULL);
}
