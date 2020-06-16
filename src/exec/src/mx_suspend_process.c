#include "mx_exec.h"

void print_suspended(char **args, pid_t pid, int suspended_index) {
    printf("\n[%d]  + %d suspended  ", suspended_index, pid);
    fflush(stdout);
    mx_print_strarr(args, " ");
    printf("\n");
}

void mx_suspend_process(char **args, t_processes **processes, pid_t pid) {
    mx_push_process(processes, args, pid);
    print_suspended(args, pid, (*processes)->index);
}
