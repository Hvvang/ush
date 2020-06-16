#include "libmx.h"

char *mx_strnew(const int size) {
    char *result = (char *)malloc(sizeof(char) * size + 1);

    for (int i = 0; i <= size; i++) {
        result[i] = '\0';
    }
    return result;
}
