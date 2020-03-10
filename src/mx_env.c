#include "ush.h"


static void create_env(t_env *env) {
	int arr_size = mx_get_array_size(env->env_ch);

	env->env = (char **)malloc(sizeof(char*) * arr_size + 1); //env cache
	for (int i = 0; i < arr_size; i++) {
		env->env[i] = (char*)malloc(sizeof(char) * strlen(env->env_ch[i]));
		env->env[i] = env->env_ch[i];
	}
		env->env[arr_size + 1] = NULL;
}

void mx_env(t_command *commands, t_env *env) {

	commands->exit = 1;
	if (commands->fl[4] && !commands->arguments[1])
		return ;
	create_env(env);
	for (int i = 0; env->env[i]; i++) {
		printf("%s\n", env->env[i]);
	}
	return ;
}

