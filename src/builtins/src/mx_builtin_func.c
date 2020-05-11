#include "../inc/mx_builtins.h"

void mx_builtin_func(t_command *command, t_env *env) {
	// for (int i = 0; command->arguments[i]; i++)
	// 	mx_check_flag(command->arguments[i], command);
	if (!strcmp(command->command, "env"))
		mx_env(command, env);
	else if (!strcmp(command->command, "cd"))
		mx_cd(command);
	else if (!strcmp(command->command, "pwd"))
		mx_pwd(command);
	else if (!strcmp(command->command, "echo"))
		mx_echo(command);
	else if (!strcmp(command->command, "export"))
		mx_export(command, env);
	else if (!strcmp(command->command, "unset"))
		mx_unset(command, env);
	else if (!strcmp(command->command, "which"))
		mx_which(command);
	else if (!strcmp(command->command, "exit")) {
		// mx_del_struct(&command);
		// mx_del_strarr(&env->env);
		// mx_del_strarr(&env->export);
		// mx_del_strarr(&env->unset);

		exit(0);
	}
}
