#include "libmx.h"

char **mx_strsplit(const char *s, char c) {
    int size_arr = mx_count_words(s, c);
    int counter = 0;
    char **result = malloc(sizeof(char *) * (size_arr + 1));
    int index = 0;

    for (unsigned long i = 0; i < strlen(s); i++) {
        index = mx_get_char_index(s + i, c);
        index = (index == -1) ? strlen(s) : index;
        if (index) {
            result[counter] = strndup(s + i, index);
            i += mx_strlen(result[counter]) - 1;
            counter++;
        }
    }
    result[size_arr] = NULL;
    return result;
}
