#include "ush.h"

int mx_isPipe(char *data) {
    if (!strcmp(data, "|"))
        return PIPE;
    return DONT_UNDERSTAND;
}
