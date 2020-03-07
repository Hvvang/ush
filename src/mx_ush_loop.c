#include "ush.h"


static int is_exit(char *line) {
	char **args = mx_strsplit(line, ' ');
	int sw = 0;

	if (mx_strncmp(args[0], "exit", 4) == 0)
		sw = 1;
	return sw;
}

static int is_builtin(char *line) {
	char *str[11] = {"exit","fg","unset","export","cd",
	                "pwd", "echo", "which", "env", NULL };
	char *ch_str =  malloc(sizeof(char) * 20);
	char *dest =  malloc(sizeof(char) * 20);
	int sw = 0;
	int i = 0;

	for (; line[i]; i++) {
		if (line[i] != '\n') {
			ch_str[i] = line[i];
			ch_str[i + 1] = '\0';
		}
	}
	for (i = 0; ch_str[i]; i++) {
		if (ch_str[i] == ' ')
			break;
		dest[i] = ch_str[i];
		dest[i + 1] = '\0';
	}
	for (int i = 0; str[i] != NULL; i++) {
		if (mx_strcmp(dest, str[i]) == 0) {
			sw = 1;
		}
	}
	mx_strdel(&ch_str);
	return sw;
}


void mx_ush_loop () {
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
											//чтение аргументов
			if (isatty(0)){
				if (commands) {
					t_command *temp = commands;

					while (temp) {
						if (is_builtin(temp->command));
							mx_builtin_func(temp);
						else 													// если функции надо искать
							printf("u$h: command  not found: %s", line);
						temp = temp->next;
					}
				}														// если запуск с ./ush
			}
		}
		else { 																	//  если запуск с echo "some text" | ./ush
			printf("asd\n");
			exit(0);
		}
		mx_strdel(&stdin_line);
	}
	mx_ush_loop();
}
