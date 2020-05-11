#include "libmx.h"

void mx_del_str_arr(char **arr) {
    for (unsigned i = 0; arr[i]; i++) {
        mx_strdel(&arr[i]);
    }
    free(arr);
    arr = NULL;
}
