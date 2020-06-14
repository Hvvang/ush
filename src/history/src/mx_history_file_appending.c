#include "../inc/mx_history.h"


void mx_history_file_appending(const char *command) {
    char *history_path = mx_join_path(getenv("HOME"), MX_HISTORY_FILE);
    int fd = open(history_path, O_WRONLY | O_CREAT | O_APPEND, 0600);

    mx_strdel(&history_path);
    if (!fd)
        perror("file error");
    write(fd, command, strlen(command));
    write(fd, "\n", 1);
    close(fd);
}
