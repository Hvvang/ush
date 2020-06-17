#include "mx_input.h"

void mx_clear_screen(char *line, int pos) {
    unsigned long i = pos;

    system("clear");
    printf(MX_SHELL_PROMPT);
    fflush(stdout);
    printf("%s", line);
    while (i < strlen(line)) {
        printf("\b");
        i++;
    }
}
