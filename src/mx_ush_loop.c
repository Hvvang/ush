#include "ush.h"


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
	char *line = NULL;

	while (status) {
		printf("u$h> ");
		line = mx_ush_read_line(); 												//чтение аргументов
		if (isatty(0)){ 														// если запуск с ./ush
			if(is_builtin(line)) 												// если функции относяться к builtin
				mx_builtin_func(line); 											// запускаем на выполнение ф-и builtin 
			else {																// если функции надо искать
				printf("u$h: command  not found: %s", line);
				mx_ush_loop();
			}
		}
		else { 																	//  если запуск с echo "some text" | ./ush
			printf("asd\n"); 
			exit(0);
		}
		mx_strdel(&line);
		// system("leaks -q ush");
		mx_ush_loop();
	}
}



