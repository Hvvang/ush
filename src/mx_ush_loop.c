#include "ush.h"


static int is_exit(char *line) {
	char **args = mx_strsplit(line, ' ');
	int sw = 0;

	if (mx_strncmp(args[0], "exit", 4) == 0)
		sw = 1;
	return sw;
}

static int is_builtin(char *line) {
	char **args = mx_strsplit(line, ' ');
	char *str[6] = {"cd", "pwd", "echo", "which", "env", NULL};
	char *str2[6] = {"cd\n", "pwd\n", "echo\n", "which\n", "env\n", NULL};
	int sw = 0;

	for (int i = 0; str[i]; i++) {
		if (args[1] == NULL) {
			if (mx_strcmp(args[0], str2[i]) == 0)
				sw = 1;
		}
		if (args[1] != NULL) {
			if (mx_strcmp(args[0], str[i]) == 0)
				sw = 1;
		}
	}
		
	return sw;
}

void mx_ush_loop (void) {
	int status = 1;
	char *line = NULL;

	while (status) {

		printf("u$h> ");
		line = mx_ush_read_line(); //чтение аргументов

		if (is_exit(line)) {
			free(line);
			exit(0);
		}
		// если запуск с ./ush
		if (isatty(1)) 
			// если функции относяться к builtin
			if(is_builtin(line))
				// запускаем на выполнение ф-и builtin
				mx_builtin_func(line); 
			// если функции надо искать
			else 
				printf("error\n");
			//  если запуск с echo "some text" | ./ush
		else 
			printf("ddds\n");

		
		// system("leaks -q ush");
		
		mx_strdel(&line);
		mx_ush_loop();
	}
}



