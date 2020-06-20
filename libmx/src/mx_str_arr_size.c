#include "libmx.h"

int mx_str_arr_size(char **arr) {
    int i = 0;

    if (arr)
        while (arr[i])
            i++;
    return i;
}
