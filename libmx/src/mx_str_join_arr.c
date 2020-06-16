#include "libmx.h"

char **mx_str_join_arr(char *str, char **arr) {
    unsigned size = mx_str_arr_size(arr);
    char **res = (char **)malloc(sizeof(char *) * (size + 1) + 1);

    res[0] = strdup(str);
    res[size + 1] = NULL;
    for (unsigned i = 0; i < size; i++) {
        res[i + 1] = strdup(arr[i]);
    }
    return res;
}
