#include "mx_exec.h"

/*
*   While child process is executing all signals
*   from parrent process must be ignored.
*   SIG_IGN - default signal handler option.
*/
void mx_stop_signals(void) {
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
}
