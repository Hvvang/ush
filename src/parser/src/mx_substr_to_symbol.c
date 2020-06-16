#include "mx_parser.h"

char *mx_substr_to_symbol(char *str, char *symbol) {
    bool toggle = true;
    unsigned i;

    for (i = 0; str[i] && toggle; i++) {
        for (unsigned item = 0; symbol[item]; item++)
            if (str[i] == symbol[item]) {
                toggle = false;
                break;
            }
        if (!str[i + 1] && toggle) {
            i += 2;
            break;
        }
    }
    return strndup(str, i - 1);
}
