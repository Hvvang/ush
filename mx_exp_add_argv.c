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

static int mx_is_exp_dbl (char *str, char **arr) { //проверка на дубликаты по имени
	char *cmp = nrml_str(str);
	char *cmp_s = NULL;

	for (int i = 0; arr[i]; i++) {
		cmp_s = nrml_str(arr[i]);
		if (!strcmp(cmp_s, cmp))
			return i;
	}
	return -1;
}

static void add_in_exp(char *str, t_env *env) { //добавляем в export
	int len = mx_get_array_size(env->exp);

	env->exp[len] = (char *)malloc(sizeof(char) * strlen(str));
	env->exp[len] = str;
	env->exp[len + 1] = NULL;
}

void mx_exp_add_argv(t_command *cmd, t_env *env) {
	for (int i = 0; cmd->arguments[i]; ++i) {
		if (mx_is_exp_dbl(cmd->arguments[i], env->exp) > -1) { // если дубликат
			mx_exp_change_dublicate(cmd->arguments[i], env,
					 mx_is_exp_dbl(cmd->arguments[i], env->exp));
		} 
		else {
			add_in_exp(cmd->arguments[i], env);
		}
	}
}
