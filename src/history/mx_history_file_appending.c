#include "mx_history.h"


void mx_history_file_appending(const char *command) {
    int fd = open(MX_HISTORY_PATH, O_WRONLY | O_CREAT | O_APPEND, 0600);

    write(fd, command, strlen(command));
    write(fd, "\n", 1);
    close(fd);
}
