#include "ush.h"

static int is_dublicate(char **arr, char *str) {
	for (int i = 0; arr[i]; i++) {
		if (strcmp(arr[i], str) == 0)
			return 1;
	}
	return 0;
}

static char *normal(char *str) {
	int len = strlen(str);
	char *buff = malloc(sizeof(char) * len + 2); 
	int sw = 0;

	for (int i = 0; i < len; i++)
		if (str[i] == '=')
			sw = 1;
	if (sw == 0) {
		for (int i = 0; str[i]; i++)
			buff[i] = str[i];
		buff[len] = '=';
	}
	else
		return str;
	return buff;
}

void mx_export(t_command *commands, t_env *env) {

	if(!commands->arguments[0]) {
		
	}
	else {	
		int len = mx_get_array_size(env->env);

		for (int i = 0; commands->arguments[i]; i++) {
			if (is_dublicate(env->env, commands->arguments[i]))
				i++;
			else {
				env->env[len] = malloc(sizeof(char) * mx_strlen(commands->arguments[i]));
				env->env[len] = normal(commands->arguments[i]);
				len++;
			}
			env->env[len] = NULL;
		}
		
	}
}
