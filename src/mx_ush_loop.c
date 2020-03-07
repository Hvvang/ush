#include "ush.h"


static int is_exit(char *line) {
	char **args = mx_strsplit(line, ' ');
	int sw = 0;

	if (mx_strncmp(args[0], "exit", 4) == 0)
		sw = 1;
	return sw;
}

// static int is_builtin(char *line) {
// 	char **args = mx_strsplit(line, ' ');
// 	char *str[6] = {"cd", "pwd", "echo", "which", "env", NULL};
// 	char *str2[6] = {"cd\n", "pwd\n", "echo\n", "which\n", "env\n", NULL};
// 	int sw = 0;
//
// 	for (int i = 0; str[i]; i++) {
// 		if (args[1] == NULL) {
// 			if (mx_strcmp(args[0], str2[i]) == 0)
// 				sw = 1;
// 		}
// 		if (args[1] != NULL) {
// 			if (mx_strcmp(args[0], str[i]) == 0)
// 				sw = 1;
// 		}
// 	}
//
// 	return sw;
// }

void mx_ush_loop (void) {
	int status = 1;
	char *stdin_line = NULL;

	while (status) {

		printf(MX_SHELL_PROMPT);
		stdin_line = mx_ush_read_line(); //чтение аргументов

		if (stdin_line[0] != '\0') {
			t_command *commands = mx_split_to_struct(stdin_line);

			if (commands) {
				t_command *temp = commands;
				
				while (temp) {
					printf("command = %s\n", temp->command);
					for (int i = 0; temp->arguments[i]; i++) {
						printf("\targument[%i] = %s\n", i, temp->arguments[i]);
					}
					temp = temp->next;
				}
			}

			if (is_exit(stdin_line)) {
				mx_strdel(&stdin_line);
				exit(0);
			}
			mx_strdel(&stdin_line);
		}
		// printf("line = \"%s\"\n", line);


		// если запуск с ./ush
		// if (isatty(1))
		// 	// если функции относяться к builtin
		// 	if(is_builtin(line))
		// 		// запускаем на выполнение ф-и builtin
		// 		mx_builtin_func(line);
		// 	// если функции надо искать
		// 	else
		// 		printf("error\n");
		// 	//  если запуск с echo "some text" | ./ush
		// else
		// 	printf("ddds\n");


		// system("leaks -q ush");

		mx_ush_loop();
	}
}
