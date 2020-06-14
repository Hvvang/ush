#include "../inc/ush.h"

static void signal_for_child(void) {
    signal(SIGINT, SIG_DFL); // C-c
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL); // for move of terminals
    // signal(SIGTTOU, SIG_DFL);
}

static void mx_set_ctrl_term(pid_t pid) {
    // mx_printint(pid);
    // mx_printstr("\n");
    if (tcsetpgrp(0, pid) < 0) {
        mx_printstr(strerror(errno));
        mx_printstr(" tcsetpgrp\n");
    }
    if (tcsetpgrp(1, pid) < 0) {
        mx_printstr(strerror(errno));
        mx_printstr(" tcsetpgrp\n");
    }
}

static void signal_for_parent(void) {
    signal(SIGINT, SIG_IGN); // C-c
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN); // for move of terminals
    signal(SIGTTOU, SIG_IGN);
}

int mx_launch_process(t_command *command, t_hash_table *hash_table) {
	char **args = mx_str_join_arr(command->command, command->arguments);
	int status;
	pid_t pid;

	signal_for_parent();
	if ((pid = fork()) < 0) {
		perror("fork");
	}
	if (pid == 0) {
		signal_for_child();
		if (setpgid(getpid(), getpid()) < 0)
			perror("fork");
		mx_set_ctrl_term(getpid());
		if (execvp(args[0], args) == -1)
			fprintf(stderr, "u$h: command  not found: %s\n", command->command);
		_exit(1);
	}
	else {
		if (waitpid(pid, &status, WUNTRACED) < 0) {
            mx_printstr(strerror(errno));
            mx_printstr("\n");
        }
		mx_set_ctrl_term(getpid());
		if (WIFSTOPPED(status)) {
			hash_table->processes_num++;
			printf("\n[%d]  + %d suspended  ", hash_table->processes_num, pid);
			fflush(stdout);
			mx_print_strarr(args, " ");
			printf("\n");
			mx_push_process(&hash_table->processes, args, pid);
		}
	}
	return 1;
}
