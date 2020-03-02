#include "ush.h"

int mx_isLess(char *data) {
    if (!strcmp(data, "<"))
        return LESS;
    return DONT_UNDERSTAND;
}
