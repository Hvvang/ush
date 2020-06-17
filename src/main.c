#include "ush.h"

static struct termios *mx_get_tty(void) {
    static struct termios tty;

    return &tty;
}

static bool check_stdin(t_hash_table *hash_table) {
    char *buff = NULL;
    size_t linecap = 0;
    ssize_t linelen = 0;

    if (isatty(STDIN_FILENO))
        return false;
    buff = mx_strnew(ARG_MAX + 1);
    while ((linelen = getline(&buff, &linecap, stdin)) > 0) {
        buff[linelen] = '\0';
        if (buff[linelen - 1] == '\n')
            buff[linelen - 1] = '\0';
        mx_handle_command(buff, hash_table);
    }
    mx_strdel(&buff);
    return true;
}

int main(int argc, char **argv) {
	t_hash_table *hash_table = mx_init_env();

	if (argc > 1) {
		fprintf(stderr, "%s: illegal option -- %s\n", MX_SHELL_NAME, argv[1]);
		fprintf(stderr, "usage: %s ./ush\n", MX_SHELL_NAME);
		return 1;
	}
	if (check_stdin(hash_table)) {
		tcsetattr(STDIN_FILENO, TCSADRAIN, mx_get_tty());
		exit(1);
	}
	// t_hash_table *hash_table = create_hash_table();
	// exit(1);
	// signal(SIGINT, sigint_handler);
	// signal(SIGCONT, sigcont_handler);
	// signal(SIGQUIT, sigquit_handler);
	// signal(SIGTSTP, sigstp_handler);
	// mx_create_vars(hash_table);
	mx_ush_loop(hash_table);
	// system("leaks ush");
}
