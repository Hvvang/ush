#include "libmx.h"

static void swap_str(char **str1, char** str2);
static void check_str(int *last, int* first, char** arr, char* str3);
static void main_job(char **arr, int *first, int *last);

int mx_quicksort(char **arr, int left, int right) {
    int first = left;
    int last = right;
    char* middle = NULL;

    if (!arr)
        return -1;
    if (left < right) {
        middle = arr[(left + (right - left) / 2)];
        while (first <= last) {
        check_str(&last, &first, arr, middle);
        main_job(arr, &first, &last);
    }
}  
    if (left < last)
        mx_quicksort(arr, left, last);
    if (first < right)
        mx_quicksort(arr, first, right);
    return 0;
}

static void swap_str(char **str1, char** str2) {
    char *temp = *str1; 
    *str1 = *str2; 
    *str2 = temp; 
}

static void check_str(int *last, int* first, char** arr, char* str3) {
    while (mx_strcmp(arr[*first], str3) < 0)
        (*first)++;
    while (mx_strcmp(arr[*last], str3) > 0)
        (*last)--;
}

static void main_job(char **arr, int *first, int *last) {
    if (*first <= *last) {
        if ((*first != *last) &&
        (mx_strcmp(arr[*first], arr[*last]) > 0))
            swap_str(&arr[*first], &arr[*last]);
        (*first)++;
        (*last)--;
    }
}
