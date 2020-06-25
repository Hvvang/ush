#include "mx_parser.h"

void mx_replace_var(char **arg, char *before, char *after, int *i) {
    int size = strlen(*arg) - strlen(before) + strlen(after);

    for (int j = strlen(before); j; j--)
        mx_del_char_in_str(*arg, *i);
    *arg = realloc(*arg, sizeof(char) * size + 1);
    for (int j = 0; after[j]; j++)
        mx_insert_char_to_str(arg, after[j], (*i)++);
    (*arg)[size] = '\0';
}
