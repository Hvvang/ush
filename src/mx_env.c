#include "ush.h"

void mx_env(t_command *commands, t_env *env) {

	commands->exit = 1;
	for (int i = 0; env->env[i]; i++) {
		printf("%s\n", env->env[i]);
	}
	return ;
}

