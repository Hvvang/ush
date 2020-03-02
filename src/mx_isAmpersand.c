#include "ush.h"

int mx_isAmpersand(char *data) {
    if (!strcmp(data, "&"))
        return AMPERSAND;
    return DONT_UNDERSTAND;
}
