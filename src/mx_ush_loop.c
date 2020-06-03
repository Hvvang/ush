#include "../inc/ush.h"

static int is_builtin(char *command) {
	char *built_ins[11] = {"exit","fg","unset","export","cd",
	                "pwd", "echo", "which", "env", NULL };

	for (int i = 0; built_ins[i]; i++) {
		if (!strcmp(command, built_ins[i]))
			return 1;
	}
	return 0;
}

void mx_ush_loop (t_env *env) {
	int status = 1;
	char *stdin_line = NULL;

	while (status) {
		printf(MX_SHELL_PROMPT);
		stdin_line = mx_ush_read_line(); //чтение аргументов
		if (stdin_line[0] != '\0') {
			t_command *commands = mx_split_to_struct(stdin_line);

			if (isatty(0)){
				while (commands) {
					commands->exit = 0;
					if (is_builtin(commands->command))
						mx_builtin_func(commands, env);
					else
						mx_launch_process(commands);
						// если функции надо искать
						// fprintf(stderr, "u$h: command  not found: %s\n", commands->command);
					pop_front(&commands);
				}
			}
		}
		mx_strdel(&stdin_line);
		// system("leaks ush");
		mx_ush_loop(env);
	}
}
