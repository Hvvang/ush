#include "mx_history.h"

static char *get_real_home(void) {
    struct passwd *pw = getpwuid(getuid());
    char *home = strdup(pw->pw_dir);

    return home;
}

t_history *mx_file_to_struct(void) {
    char *home = get_real_home();
    char *history_path = mx_join_path(home, MX_HISTORY_FILE);
    FILE * fp = fopen(history_path, "r");
    char *line = mx_strnew(PATH_MAX);
    t_history *history = NULL;

    mx_strdel(&home);
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
