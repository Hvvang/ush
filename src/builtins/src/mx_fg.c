#include "../inc/mx_builtins.h"

#define MX_GENERAL 0
#define MX_PROCESS_INDEX 1
#define MX_PROCESS_NAME 2
#define MX_FG "fg: "
#define MX_ERROR_EXISTING "no such job"
#define MX_NO_JOBS "no current job"

static char *get_param(char *arg, int *type) {
    if (!arg)
        *type = MX_GENERAL;
    else {
        if (arg[0] == '%') {
            for (unsigned i = 1; arg[i]; i++) {
                if (isdigit(arg[i]))
                    *type = MX_PROCESS_INDEX;
                else {
                    *type = MX_PROCESS_NAME;
                    break;
                }
            }
            return &arg[1];
        }
        else
            *type = MX_PROCESS_NAME;
    }
    return arg;
}

static t_processes *get_pid(t_processes *prcs, char *arg, int pids_num) {
    int type;
    char *param = get_param(arg, &type);

    if (type == MX_GENERAL) {
        if (!prcs)
            fprintf(stderr, "%s%s\n", MX_FG, MX_NO_JOBS);
        return prcs;
    }
    else if (type == MX_PROCESS_INDEX) {
        if (atoi(param) > pids_num)
            fprintf(stderr, "%s: %s: %s\n", MX_FG, arg, MX_ERROR_EXISTING);
        else {
            t_processes *temp = prcs;

            while (temp->index != atoi(param))
                temp = temp->next;
            return temp;
        }
    }
    else if (type == MX_PROCESS_NAME) {
        t_processes *temp = prcs;

        while (temp) {
            if (!strcmp(temp->command[0], param))
                return temp;
            temp = temp->next;
        }
        fprintf(stderr, "%s: %s: %s\n", MX_FG, arg, MX_ERROR_EXISTING);
    }
    return NULL;
}


void mx_fg(t_processes *processes, char **args, int *pids_num) {
    for (unsigned i = 0; ; i++) {
        t_processes *local = get_pid(processes, args[i], *pids_num);
        int status;

        if (local) {
            kill(local->pid, SIGCONT);
            if (waitpid(local->pid, &status, WUNTRACED) != -1) {
                if (!MX_WIFSTOPPED(status)) {
                    (*pids_num)--;
                    mx_clear_process(&processes, (void *)local);
                    return;
                }
                else if (MX_WIFSTOPPED(status)) {
                    printf("\n[%d]  + %d suspended  ", local->index, local->pid);
                    fflush(stdout);
                    mx_print_strarr(local->command, " ");
                    printf("\n");
                }
            }
        }
        if (!args[i + 1])
            break;
    }
}
