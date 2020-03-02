#include "ush.h"

int mx_isNewLine(char *data) {
    if (!strcmp(data, "\n"))
        return NEWLINE;
    return DONT_UNDERSTAND;
}
