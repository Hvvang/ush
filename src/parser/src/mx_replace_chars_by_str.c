#include "mx_parser.h"

char *mx_replace_chars_by_str(char *str, int i, int itms, char *substr) {
    int new_len = mx_strlen(str) - itms + strlen(substr);
    char *res = mx_strnew(new_len);
    bool toggle = true;
    int j;

    while (itms--)
        mx_del_char_in_str(str, i);
    for (int index = 0; index < new_len; index++) {
        if (index < i)
            res[index] = str[index];
        else if (toggle) {
            for (j = 0; substr[j]; j++)
                res[index + j] = substr[j];
            toggle = false;
        }
        else
            res[index + j] = substr[index];
    }
    return res;
}
