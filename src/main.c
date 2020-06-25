#include "ush.h"

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
		mx_clear_all(hash_table);
	}
	mx_ush_loop(hash_table);
}
