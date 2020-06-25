#include "mx_shell.h"

static void print_prompt(void) {
	char **prompt = mx_get_prompt_mode();

	printf("%s", *prompt);
	fflush(stdout);
}

void mx_ush_loop (t_hash_table *hash_table) {
	int status = 0;

	while (status != 666) {
		char *stdin_line = mx_strnew(PATH_MAX);
		char *res = NULL;

		print_prompt();
		hash_table->savetty = mx_enable_canon();
		stdin_line = mx_ush_read_line(stdin_line, &status);
		if (status == 666)
			break;
		mx_disable_canon(hash_table->savetty);
		res = mx_strtrim(stdin_line);
		mx_strdel(&stdin_line);
		status = mx_handle_command(res, hash_table);
	}
	mx_clear_all(hash_table);
}
