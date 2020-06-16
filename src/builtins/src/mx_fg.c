#include "../inc/mx_builtins.h"

#define MX_GENERAL 0
#define MX_PROCESS_INDEX 1
#define MX_PROCESS_NAME 2
#define MX_FG "fg: "
#define MX_NO_SUCH_JOB "no such job"
#define MX_JOB_NOT_FOUND "job not found: "
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

static t_processes *get_pid(t_processes **prcs, char *arg,
                            char *param, int type) {
    if (type == MX_GENERAL) {
        // if (*prcs) {
            // printf("excisted\n");
            // printf("pid = %d\n", (*prcs)->pid);
        // }
        if (!(*prcs))
            fprintf(stderr, "%s%s\n", MX_FG, MX_NO_JOBS);
        return *prcs;
    }
    else if (type == MX_PROCESS_INDEX) {
        if (atoi(param) > mx_get_processes_num(prcs))
            fprintf(stderr, "%s%s: %s\n", MX_FG, arg, MX_NO_SUCH_JOB);
        else {
            t_processes *temp = *prcs;

            while (temp->index != atoi(param))
                temp = temp->next;
            return temp;
        }
    }
    else if (type == MX_PROCESS_NAME) {
        t_processes *temp = *prcs;

        while (temp) {
            if (!strcmp(temp->command[0], param))
                return temp;
            temp = temp->next;
        }
        fprintf(stderr, "%s%s%s\n", MX_FG, MX_JOB_NOT_FOUND, param);
    }
    return NULL;
}


void print_process(t_processes **processes) {
    t_processes *temp = *processes;

    printf("address of first node is %p\n", (void *)(*processes));
    while (temp) {
        printf("command = ");
        fflush(stdout);
        mx_print_strarr(temp->command, " ");
        printf(",\tpid = %d, index = %d\n", temp->pid, temp->index);
        temp = temp->next;
    }
}

void mx_fg(t_processes **processes, char **args) {
    for (unsigned i = 0; ; i++) {
        int type;
        // printf("1\n");
        char *param = get_param(args[i], &type);
        // printf("2\n");
        // print_process(processes);

        t_processes *local = get_pid(processes, args[i], param, type);
        // printf("3\n");


        if (local) {
            // printf("local->pid = %d\n", local->pid);
            tcsetpgrp(STDIN_FILENO, local->pid);
            mx_continue_process(processes, local, local->pid);
            tcsetpgrp(STDIN_FILENO, getpgrp());
        }
        if (!args[i + 1])
            break;
    }
}
