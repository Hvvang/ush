#include "libmx.h"

void mx_insert_char_to_str(char **str, char c, int pos) {
    int len = strlen((*str));
    int i = len - 1;

    if ((*str) == NULL)
        return;
    (*str)[len + 1] = '\0';
    for (; i >= pos; i--)
        (*str)[i + 1] = (*str)[i];
    (*str)[pos] = c;
}
