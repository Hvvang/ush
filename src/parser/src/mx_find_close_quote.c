#include "mx_parser.h"

void mx_find_close_quote(char *str, int *i, char c) {
    if (str[*i] == c) {
        (*i)++;
        while (str[*i]) {
            if (str[*i] == c) {
                break;
            }
            (*i)++;
        }
    }
}
