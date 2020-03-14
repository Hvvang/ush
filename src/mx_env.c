#include "ush.h"

static int is_break(char *str) { //если данные без = не пишем в env
	for (int i = 0; str[i]; i++)
		if (str[i] == '=')
			return 0;
	return 1;
}

static char *is_clear_cmd(char *str) { //если данные с ="" удаляем ""
	char *buff = (char*)malloc(sizeof(char) * strlen(str) + 1);

	for (int i = 0; str[i]; i++) {
		if (str[i] == '"' && (str[i] && str[i + 1] == '"')) {
			return buff;
		}
		buff[i] = str[i];
		buff[i + 1] = '\0';
	}
	return buff;
}

static void add_exp_in_env(t_env *env) {
	int len = mx_str_arr_size(env->exp);

	env->env = (char**)malloc(sizeof(char*) * len);
	for (int i = 0, j = 0; env->exp[i]; i++) {
		if (is_break(env->exp[i]) == 1)
			continue;
		else {
			env->env[j] = (char*)malloc(sizeof(char) * strlen(env->exp[i]));
			env->env[j] = is_clear_cmd(env->exp[i]);
			j++;
			env->env[j + 1] = NULL;
		}
	}
}

void mx_env(t_command *commands, t_env *env) {
	add_exp_in_env(env); //пишем в env данные из export

	commands->exit = 1;
	if (commands->fl[4] && !commands->arguments[1])
		return ;
	for (int i = 0; env->env[i]; i++) {
		printf("%s\n", env->env[i]);
	}
	return ;
}

