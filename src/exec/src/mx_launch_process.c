#include "mx_exec.h"

/*
*   Initialising child process for executing the
*   command in foreground that find binary files in
*   $PATH shell environment variable with changing
*   signals handling and stopping parent process
*   executing while child is active.
*/

static void parent_exec(char **args, t_processes **processes,
						pid_t pid) {
	int status;

	if (waitpid(pid, &status, WUNTRACED) < 0) {
		mx_printstr(strerror(errno));
		mx_printstr("\n");
	}
	if (status != 1)
		setenv("status", "127", 1);
	mx_set_term_assoc(getpid());
	if (WIFSTOPPED(status))
		mx_suspend_process(args, processes, pid);
	mx_del_strarr(&args);
}

int mx_launch_process(t_command *command, t_processes **processes,
					  char *path, char **env) {
	char **args = mx_str_join_arr(command->command, command->arguments);
	pid_t pid;

	mx_stop_signals();
	if ((pid = fork()) == 0) {
		mx_activate_signals();
	    if (setpgid(getpid(), getpid()) < 0)
	        perror("setpgid");
	    mx_set_term_assoc(getpid());
	    if (execve(path, args, env) == -1)
	        fprintf(stderr, "u$h: command not found: %s\n", args[0]);
	    _exit(1);
	}
	else
		parent_exec(args, processes, pid);
	return 1;
}
