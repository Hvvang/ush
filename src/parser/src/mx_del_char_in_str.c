#include "mx_parser.h"


void mx_del_char_in_str(char *str, int pos) {
    int len = strlen(str);
    int i = pos;

    if (pos > len - 1 || pos < 0)
        return;
    for (; i <= len - 1; i++)
        str[i] = str[i + 1];
    // str = realloc(str, i + 1);
    str[i] = '\0';
}
