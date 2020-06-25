#include "mx_parser.h"

static void mx_dup2_fd(int *fd1, int *fd2) {
    if (fd1[0] != STDIN_FILENO) {
        if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO)
            perror("error dup2 stdin");
        close(fd1[0]);
    }
    if (fd2[1] != STDOUT_FILENO) {
        if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO)
            perror("error dup2 stdout");
        close(fd2[1]);
    }
}

static char *data_from_fd(int *fd) {
    size_t n_read = 0;
    size_t sum_read = 0;
    char buf[BUFSIZ];
    char *res = NULL;

    while ((n_read = read(fd[0], buf, BUFSIZ)) > 0)
        sum_read += n_read;
    res = strdup(buf);
    res[sum_read] = '\0';
    for (unsigned i = 0; res[i]; i++) {
        if (res[i] == '\n')
            res[i] = ' ';
    }
    return res;
}

static void write_to_fd(int *fd1, int *fd2, char *substitution) {
    int len = strlen(substitution) + 1;

    if (pipe(fd1) < 0 || pipe(fd2) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if (write(fd1[1], substitution, len) != len)
        perror("error write to pipe");
    close(fd1[1]);
}

char *mx_subshell(char *substitution, int *status) {
	char **args = mx_strsplit(substitution, ' ');
	int fd1[2];
	int fd2[2];
    pid_t pid;

    write_to_fd(fd1, fd2, substitution);
	if ((pid = fork()) == 0) {
		mx_dup2_fd(fd1, fd2);
		if (execvp(args[0], args) == -1)
            fprintf(stderr, "ush: command not found: %s\n", substitution);
		_exit(1);
	}
	else {
		waitpid(pid, status, WUNTRACED | WCONTINUED);
        if (*status != 1)
            setenv("status", "1", 1);
        mx_strdel(&substitution);
        mx_del_strarr(&args);
        close(fd1[0]);
        close(fd2[1]);
	}
	return data_from_fd(fd2);;
}
