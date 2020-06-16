#include "libmx.h"

int mx_bubble_sort(char **arr, int size) {
    char *text;
    int swap = 0;
    int i;
    int j;

    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if (mx_strcmp(arr[i], arr[j]) > 0) {
                text = arr[i];
                arr[i] = arr[j];
                arr[j] = text;
                swap = swap + 1;
            }
        }
    }
    return swap;
}
