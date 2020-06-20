#include "mx_builtins.h"

#define MX_GENERAL 0
#define MX_PROCESS_INDEX 1
#define MX_PROCESS_NAME 2
#define MX_NO_SUCH_JOB "fg: %s: no such job\n"
#define MX_JOB_NOT_FOUND "fg: job not found: %s\n"
#define MX_NO_JOBS "fg: no current job\n"

static char *get_param(char *arg, int *type) {
    if (!arg || !strcmp(arg, "--"))
        *type = MX_GENERAL;
    else {
        if (arg[0] == '%') {
            if (mx_match(&arg[1], "[0-9]"))
                *type = MX_PROCESS_INDEX;
            else
                *type = MX_PROCESS_NAME;
            return &arg[1];
        }
        else
            *type = MX_PROCESS_NAME;
    }
    return arg;
}

static t_processes *get_by_index(t_processes **prcs, char *arg, char *param) {
    if (atoi(param) > mx_get_processes_num(prcs)) {
        setenv("status", "127", 1);
        fprintf(stderr, MX_NO_SUCH_JOB, arg);
        return NULL;
    }
    else {
        t_processes *temp = *prcs;

        while (temp->index != atoi(param))
            temp = temp->next;
        return temp;
    }
}

static t_processes *get_by_name(t_processes **prcs, char *param) {
    t_processes *temp = *prcs;

    while (temp) {
        if (!strcmp(temp->command[0], param))
            return temp;
        for (int i = 0; temp->command[0][i] && param[i]; i++) {
            if (temp->command[0][i] != param[i])
                break;
            if (!param[i + 1])
                return temp;
        }
        temp = temp->next;
    }
    setenv("status", "127", 1);
    fprintf(stderr, MX_JOB_NOT_FOUND, param);
    return NULL;
}

static t_processes *get_pid(t_processes **prcs, char *arg,
                            char *param, int type) {
    if (type == MX_GENERAL) {
        if (!(*prcs)) {
            setenv("status", "1", 1);
            fprintf(stderr, MX_NO_JOBS);
        }
    }
    else if (type == MX_PROCESS_INDEX)
        return get_by_index(prcs, arg, param);
    else if (type == MX_PROCESS_NAME)
        return get_by_name(prcs, param);
    return *prcs;
}

void mx_fg(t_processes **processes, char **args) {
    t_processes *local = NULL;

    if (args[0]) {
        for (unsigned i = 0; args[i]; i++) {
            int type;
            char *param = get_param(args[i], &type);

            if ((local = get_pid(processes, args[i], param, type))) {
                tcsetpgrp(STDIN_FILENO, local->pid);
                mx_continue_process(processes, local, local->pid);
                tcsetpgrp(STDIN_FILENO, getpgrp());
            }
        }
    }
    else {
        if ((local = get_pid(processes, NULL, NULL, MX_GENERAL))) {
            tcsetpgrp(STDIN_FILENO, local->pid);
            mx_continue_process(processes, local, local->pid);
            tcsetpgrp(STDIN_FILENO, getpgrp());
        }
    }
}
