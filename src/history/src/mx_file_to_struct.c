#include "../inc/mx_history.h"

t_history *mx_file_to_struct(void) {
    FILE * fp = fopen(MX_HISTORY_PATH, "r");
    char *line = NULL;
    size_t len = 0;
    t_history *history = NULL;

    while ((getline(&line, &len, fp)) != -1)
        history = mx_command_to_struct(history, line);
    return history;
}
