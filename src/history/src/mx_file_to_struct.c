#include "../inc/mx_history.h"

t_history *mx_file_to_struct(void) {
    FILE * fp = fopen(MX_HISTORY_PATH, "r");

    char *line = mx_strnew(PATH_MAX);
    t_history *history = NULL;

    if (fp) {
        while ((fgets(line, PATH_MAX, fp)) != NULL) {
            history = mx_command_to_struct(history, line);
        }
        fclose(fp);
        return history;
    }
    else {
        perror(MX_HISTORY_PATH);
        return NULL;
    }
}
