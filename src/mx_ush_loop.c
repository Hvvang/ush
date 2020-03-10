#include "ush.h"


// static int is_exit(char *line) {
// 	char **args = mx_strsplit(line, ' ');
// 	int sw = 0;
//
// 	if (mx_strncmp(args[0], "exit", 4) == 0)
// 		sw = 1;
// 	return sw;
// }

static int is_builtin(char *command) {
	char *built_ins[11] = {"exit","fg","unset","export","cd",
	                "pwd", "echo", "which", "env", NULL };

	for (int i = 0; built_ins[i]; i++) {
		if (!strcmp(command, built_ins[i]))
			return 1;
	}
	return 0;
}


void mx_ush_loop (t_list *history) {
	int status = 1;
	char *stdin_line = NULL;

	while (status) {

		printf(MX_SHELL_PROMPT);
		stdin_line = mx_ush_read_line(); //чтение аргументов

		// if (stdin_line[0] == '\x03') {
		// 	t_list *temp = history;
		// 	int i = 0;
		//
		// 	while (temp) {
		// 		printf("history[%d] = %s\n", i++, temp->data);
		//
		// 		temp = temp->next;
		// 	}
		// }

		if (stdin_line[0] != '\0') {
			t_command *commands = mx_split_to_struct(stdin_line);

			mx_push_back(&history, mx_strdup(stdin_line));
			// if (commands) {
			// 	t_command *temp = commands;
			//
			// 	while (temp) {
			// 		printf("command = %s\n", temp->command);
			// 		for (int i = 0; temp->arguments[i]; i++) {
			// 			printf("\targument[%i] = %s\n", i, temp->arguments[i]);
			// 		}
			// 		temp = temp->next;
			// 	}
			// }
											//чтение аргументов


			if (isatty(0)){
				if (commands) {
					t_command *temp = commands;

					while (temp) {
						if (is_builtin(temp->command))
							mx_builtin_func(temp);
						else 													// если функции надо искать
							fprintf(stderr, "u$h: command  not found: %s\n", temp->command);
						temp = temp->next;
					}
				}														// если запуск с ./ush
			}
		}
		// else { 																	//  если запуск с echo "some text" | ./ush
		// 	printf("asd\n");
		// 	exit(0);
		// }
		mx_strdel(&stdin_line);
		mx_ush_loop(history);
	}
}
