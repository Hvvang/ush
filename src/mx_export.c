#include "ush.h"

static int is_dublicate(char **arr, char *str) {
	for (int i = 0; arr[i]; i++) {
		if (mx_strcmp(arr[i], str) == 0)
			return 1;
	}
	return 0;
}

void mx_export(t_command *commands) {

	if(!commands->arguments[0]) {
		printf("standart out\n" );
	}
	else {	
		int len = mx_get_array_size(commands->env);

		for (int i = 0; commands->arguments[i]; i++) {
			if (is_dublicate(commands->env, commands->arguments[i]))
				break;
			else {
				commands->env[len] = malloc(sizeof(char) * mx_strlen(commands->arguments[i]));
				commands->env[len] = commands->arguments[i];
				len++;
			}
			commands->env[len] = NULL;
		}
		
	}
	for (int i = 0; commands->env[i]; i++)
		printf("%s\n", commands->env[i]);
	// mx_env(commands);
}
