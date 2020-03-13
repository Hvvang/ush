#include "ush.h"

static char *nrml_str (char *str) { //пишем все до =
	char *buff = (char*)malloc(sizeof(char)* strlen(str));

	for (int i = 0; str[i]; i++) {
		if (str[i] == '=')
			break;
		buff[i] = str[i];
		buff[i + 1] = '\0';
	}
	return buff;
}

static void dell_from_env(t_command *commands, t_env *env) {
	int size = 0;
	int sw = 0;
	char **buff = malloc(sizeof(char*) * mx_get_array_size(env->exp));

	for (int i = 0, j = 0; env->exp[i]; i++) { 
		sw = 0;
		for (int k = 0; commands->arguments[k]; k++) {
			size = strlen(commands->arguments[k]);
			if (strcmp(nrml_str(env->exp[i]), nrml_str(commands->arguments[k])) == 0) {
				sw = 1;
				break;
			}
		}
		if (sw == 0) {
			buff[j] = mx_strnew(strlen(env->exp[i]));
			buff[j] = env->exp[i];
			buff[j + 1] = NULL;
			j++;
		}
	}
	env->exp = buff;
}

void mx_unset(t_command *commands, t_env *env) {
	
	if (commands->arguments[0]) {
		for (int i = 0; commands->arguments[i]; i++) {
			if (commands->arguments[i][0] == '=') {
				fprintf(stderr, "%s", "u$h: unset: `");
				fprintf(stderr, "%s", commands->arguments[i]);
				fprintf(stderr, "%s\n", "': not a valid identifier");
				return ;
			}
		}
		dell_from_env(commands, env);
	}
	return ;
}
