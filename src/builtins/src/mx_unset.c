#include "../inc/mx_builtins.h"

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
	char **buff = malloc(sizeof(char*) * mx_str_arr_size(env->export));

	for (int i = 0, j = 0; env->export[i]; i++) { 
		sw = 0;
		for (int k = 0; commands->arguments[k]; k++) {
			size = strlen(commands->arguments[k]);
			if (strcmp(nrml_str(env->export[i]), nrml_str(commands->arguments[k])) == 0) {
				sw = 1;
				break;
			}
		}
		if (sw == 0) {
			buff[j] = mx_strnew(strlen(env->export[i]));
			buff[j] = env->export[i];
			buff[j + 1] = NULL;
			j++;
		}
	}
	env->export = buff;
}

void mx_unset(t_command *cmd, t_env *env) {
	if (mx_valid_export_unset(cmd))
		return ;
	else if (mx_error_export_unset(cmd, "u$h: unset: `")) // если есть ошибки export no_alpha: 123 234 -- -- 
		return ;
	else
		dell_from_env(cmd, env);
	return ;
}
