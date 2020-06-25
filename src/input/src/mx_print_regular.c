#include "mx_input.h"

void mx_print_regular(char *str, char *c, int *pos) {
    int temp = *pos;
    char *str_temp = strdup(str);

    mx_clear_input(str_temp, &temp);
    mx_strdel(&str_temp);
    for (int i = strlen(c) - 1; c[i]; i--)
        mx_insert_char_to_str(&str, c[i], *pos);
    printf("%s", str);
    fflush(stdout);
    for (unsigned i = *pos + strlen(c); i < strlen(str); i++)
        printf("\b");
    fflush(stdout);
    *pos = (*pos) + strlen(c);
}
