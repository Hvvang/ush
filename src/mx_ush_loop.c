#include "ush.h"


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

		// 	if (commands) {
		// 		t_command *temp = commands;

		// 		while (temp) {
		// 			printf("command = %s\n", temp->command);
		// 			for (int i = 0; temp->arguments[i]; i++) {
		// 				printf("\targument[%i] = %s\n", i, temp->arguments[i]);
		// 			}
		// 			temp = temp->next;
		// 		}
		// 	}
											//чтение аргументов
			if (isatty(0)){
				if (commands) {
					t_command *temp = commands;

					while (temp) {
						if (is_builtin(temp->command)) {
							mx_builtin_func(temp, env);
						}
						else 													// если функции надо искать
							fprintf(stderr, "u$h: command  not found: %s\n", temp->command);
						temp = temp->next;
					}
				}
			}
		}
		// else { 																
		// 	printf("asd\n");
		// 	exit(0);
		// }
		mx_strdel(&stdin_line);
		mx_ush_loop(env);
	}
}
