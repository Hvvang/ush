#include "ush.h"

int mx_launch_process(char **args) {
	pid_t pid;
	pid_t wpid;
	int status = 0;

	pid = fork();

	if (pid == 0) {
		//Дочерний
		if (execvp(args[0], args) == -1) { //не удалось создать дочерный процес
			perror("ush: bad create child procces");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0) {
		perror("ush: bad forking");
	}
	else {
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}
