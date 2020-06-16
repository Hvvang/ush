#include "mx_input.h"

void mx_clear_input(char *input, int *pos) {
    int len = strlen(input);

    while (*pos > 0) {
        printf("\b");
        *pos = *pos - 1;
    }
    memset(input, ' ', len);
    printf("%s", input);
    memset(input, '\b', len);
    printf("%s", input);
    memset(input, '\0', len);
    fflush(NULL);
}
