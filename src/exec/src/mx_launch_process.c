#include "../inc/mx_exec.h"

/*
*   Initialising child process for executing the
*   command in foreground that find binary files in
*   $PATH shell environment variable with changing
*   signals handling and stopping parent process
*   executing while child is active.
*/

/*
    TODO: change executing function to execve()
    and add finding path to binary file
*/
int mx_launch_process(t_command *command, t_processes **processes) {
	char **args = mx_str_join_arr(command->command, command->arguments);
	int status;
	pid_t pid;

	mx_parent_signal();
	if ((pid = fork()) < 0)
		perror("fork");
	else if (pid == 0) {
		extern char *const *environ;

		char *path = mx_get_path_to_bin(args[0]);
		mx_child_signals();
		if (setpgid(getpid(), getpid()) < 0)
			perror("setpgid");
		mx_set_term_assoc(getpid());
		if (execve(path, args, environ) == -1) {
			mx_strdel(&path);
			fprintf(stderr, "u$h: command  not found: %s\n", args[0]);
		}
		mx_strdel(&path);
		_exit(1);
	}
	else {
		if (waitpid(pid, &status, WUNTRACED) < 0) {
            mx_printstr(strerror(errno));
            mx_printstr("\n");
        }
		mx_set_term_assoc(getpid());
		if (WIFSTOPPED(status))
			mx_suspend_process(args, processes, pid);
		mx_del_strarr(&args);
	}
	return 1;
}
