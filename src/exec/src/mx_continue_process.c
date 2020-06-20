#include "mx_exec.h"

void print_continue(char **args, pid_t pid, int continued_index) {
    printf("[%d]  + %d continued  ", continued_index, pid);
    fflush(stdout);
    mx_print_strarr(args, " ");
    printf("\n");
}

void mx_continue_process(t_processes **processes, t_processes *current, pid_t pid) {
    int status;

    if (kill(-current->pid, SIGCONT))
        return ;
    print_continue(current->command, pid, current->index);
    if (waitpid(current->pid, &status, WUNTRACED) != -1) {
        if (WIFSTOPPED(status)) {
            setenv("status", "146", 1);
            print_suspended(current->command, current->pid, current->index);
        }
        else if (!WIFSTOPPED(status)) {
            if (!WEXITSTATUS(status))
                setenv("status", "0", 1);
            else
                setenv("status", "1", 1);
            mx_clear_process(processes, (void *)current);
        }
    }
}
