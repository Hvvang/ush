#include "mx_exec.h"

/*
*   The function tcsetpgrp() makes the process group with
*   process group ID pgrp the foreground process group on
*   the terminal associated to fd, which must be the
*   controlling terminal of the calling process, and still
*   be associated with its session.
*/
void mx_set_term_assoc(pid_t pid) {
    tcsetpgrp(STDIN_FILENO, pid);
    tcsetpgrp(STDOUT_FILENO, pid);
    // if (tcsetpgrp(STDIN_FILENO, pid) < 0) {
    //     mx_printstr(strerror(errno));
    //     mx_printstr(" tcsetpgrp\n");
    // }
    // if (tcsetpgrp(STDOUT_FILENO, pid) < 0) {
    //     mx_printstr(strerror(errno));
    //     mx_printstr(" tcsetpgrp\n");
    // }
}
