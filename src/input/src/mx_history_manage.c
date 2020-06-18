#include "mx_input.h"

void mx_history_manage(char *line, int *pos, int *len, char *key) {
    t_history *history = mx_file_to_struct();

    while (MX_IS_UP_ARROW(key) || MX_IS_DOWN_ARROW(key) || MX_IS_DLE(key)) {
        mx_clear_input(line, pos);
        strcpy(line, mx_history_moving(&history, key));
        if (line) {
            printf("%s", line);
            fflush(stdout);
            *pos = strlen(line);
            *len = strlen(line);
        }
        memset(key, '\0', PATH_MAX);
        read(STDIN_FILENO, key, 4);
    }
    mx_clear_history_list(&history);
}
