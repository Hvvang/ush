#include "mx_history.h"

static char *get_real_home(void) {
    struct passwd *pw = getpwuid(getuid());
    char *home = strdup(pw->pw_dir);

    return home;
}

void mx_history_file_appending(const char *command) {
    char *home = get_real_home();
    char *history_path = mx_join_path(home, MX_HISTORY_FILE);
    int fd = open(history_path, O_WRONLY | O_CREAT | O_APPEND, 0600);
    FILE * fp = NULL;

    mx_strdel(&home);
    if (!fd)
        perror("file error");
    else {
        char line[PATH_MAX];

        fp = fopen(history_path, "r");
        while ((fgets(line, PATH_MAX, fp)) != NULL) ;
        fclose(fp);
        line[strlen(line) - 1] = '\0';
        if (strcmp(line, command)) {
            write(fd, command, strlen(command));
            write(fd, "\n", 1);
        }
        close(fd);
    }
    mx_strdel(&history_path);
}
