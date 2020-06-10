#include "../inc/ush.h"

int mx_launch_process(t_command *command, t_hash_table *hash_table) {
	char **args = mx_str_join_arr(command->command, command->arguments);
	int status;
	pid_t pid = fork();

	hash_table->pids[hash_table->pids_num++] = pid;
	if (pid == 0) {
		if (execvp(args[0], args) == -1)
			fprintf(stderr, "u$h: command  not found: %s\n", command->command);
		_exit(1);
	}
	else
		waitpid(pid, &status, WUNTRACED);
	return 1;
}
