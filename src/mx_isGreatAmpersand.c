#include "ush.h"

int mx_isGreatAmpersand(char *data) {
    if (!strcmp(data, ">&"))
        return GREATAMPERSAND;
    return DONT_UNDERSTAND;
}
