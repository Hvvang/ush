#include "ush.h"

void mx_builtin_func(t_command *commands, t_env *env) {
	// for (int i = 0; commands->arguments[i]; i++)
	// 	mx_check_flag(commands->arguments[i], commands);
	if (!strcmp(commands->command, "env"))
		mx_env(commands, env);
	else if (!strcmp(commands->command, "cd"))
		mx_cd(commands);
	else if (!strcmp(commands->command, "pwd"))
		mx_pwd(commands);
	else if (!strcmp(commands->command, "export"))
		mx_export(commands, env);
	else if (!strcmp(commands->command, "unset"))
		mx_unset(commands, env);
	else if (!strcmp(commands->command, "exit"))
		exit(0);
}