#include "ush.h"

void mx_export(t_command *cmd, t_env *env) {

	if(!cmd->arguments[0]) {
		// mx_bubble_sort(env->exp, mx_get_array_size(env->exp)); //вкл если надо
		for (int i = 0; env->exp[i]; ++i) {
			printf("%s", "declare -x ");
			printf("%s\n", env->exp[i]);
		}
	}
	else {
		mx_exp_add_argv(cmd, env);
	}
}
