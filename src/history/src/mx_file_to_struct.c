#include "mx_history.h"

t_history *mx_file_to_struct(void) {
    char *history_path = mx_join_path(getenv("HOME"), MX_HISTORY_FILE);
    FILE * fp = fopen(history_path, "r");
    char *line = mx_strnew(PATH_MAX);
    t_history *history = NULL;

    if (fp) {
        mx_strdel(&history_path);
        while ((fgets(line, PATH_MAX, fp)) != NULL) {
            history = mx_command_to_struct(history, line);
        }
        mx_strdel(&line);
        history = mx_command_to_struct(history, "\0");
        fclose(fp);
        return history;
    }
    else {
        perror(history_path);
        mx_strdel(&history_path);
        return NULL;
    }
}
