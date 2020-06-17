#include "ush.h"

static void print_prompt(void) {
	printf(MX_SHELL_PROMPT);
	fflush (NULL);
}

void mx_ush_loop (t_hash_table *hash_table) {
	while (true) {
		char *stdin_line = mx_strnew(PATH_MAX);
		char *res = NULL;

		print_prompt();
		hash_table->savetty = mx_enable_canon();
		stdin_line = mx_ush_read_line(stdin_line);
		mx_disable_canon(hash_table->savetty);
		res = mx_strtrim(stdin_line);
		mx_strdel(&stdin_line);
		mx_handle_command(res, hash_table);
		mx_ush_loop(hash_table);
	}
}
