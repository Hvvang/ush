#include "ush.h"

int mx_isGreat(char *data) {
    if (!strcmp(data, ">"))
        return GREAT;
    return DONT_UNDERSTAND;
}
