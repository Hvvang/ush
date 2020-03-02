#include "ush.h"

int mx_isGreatGreat(char *data) {
    if (!strcmp(data, ">>"))
        return GREATGREAT;
    return DONT_UNDERSTAND;
}
