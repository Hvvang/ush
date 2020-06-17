#include "mx_exec.h"

/*
*   While child process is executing all signals
*   must be handled.
*   SIG_DFL - default signal handler option.
*/
void mx_activate_signals(void) {
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    // signal(SIGTTOU, SIG_DFL);
}
