#include "../inc/mx_input.h"

void mx_print_regular(char *str, char c, int *pos) {
    if (pos != 0 && str[*pos] != '\t' && c == '\t')
        return;
    mx_insert_char_to_str(str, c, *pos);

    printf("%s", str + (*pos));
    for (int i = 0; i < strlen(str + (*pos)); i++)
        printf("\b");
    printf("%c", c);
    fflush(stdout);
    *pos = (*pos) + 1;
}
