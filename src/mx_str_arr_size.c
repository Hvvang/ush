#include "ush.h"

int mx_str_arr_size(char **arr) {
    int i = 0;

    while (arr[i])
        i++;
    return i;
}
