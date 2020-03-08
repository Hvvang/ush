#include "ush.h"

static void env_create(t_command *commands) {
	extern char **environ; //clear mem
	int arr_size = mx_get_array_size(environ);

	commands->env = (char **)malloc(sizeof(char*) * arr_size);
	for (int i = 0; i < arr_size; i++) {
		commands->env[i] = (char*)malloc(sizeof(char) * mx_strlen(environ[i]));
		commands->env[i] = environ[i];
	}
		commands->env[arr_size + 1] = NULL;		
}

void mx_builtin_func(t_command *commands) {
	env_create(commands); // заполнеиня из env;

	if (!strcmp(commands->command, "exit"))
		exit(0);
	if (!strcmp(commands->command, "pwd"))
		mx_print_pwd(commands);
	if (!strcmp(commands->command, "cd"))
		mx_change_dir(commands);
	if (!strcmp(commands->command, "env"))
		mx_env(commands);
	if (!strcmp(commands->command, "export"))
		mx_export(commands);
	if (!strcmp(commands->command, "unset"))
		mx_unset(commands);
}
