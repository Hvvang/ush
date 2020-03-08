#include "ush.h"

<<<<<<< HEAD
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
=======
// static int get_env_position (char **environ) { // найти HOME= позицию в масиве env
// 	int pos = 0;

// 	for (int i = 0; environ[i]; i++)
// 		if (mx_strncmp("HOME=", environ[i], 5) == 0)
// 			pos = i;
// 	return pos;
// }

// static void add_environ(char **environ, cmd_bl *cmd) { //записать HOME системы в структуру
// 	int pos = get_env_position(environ);
// 	int size = mx_strlen(environ[pos]);
// 	int cn = 5;
// 	int stac = size - cn;

// 	cmd->home = (char*)malloc(sizeof(char) * size - 5); // clear mem

// 	for (int i = 0; i < stac; i++) {
// 		cmd->home[i] = environ[pos][cn];
// 		cn++;
// 	}
// }


void mx_builtin_func(t_command *commands) {
	extern char **environ;

	if (!strcmp(commands->command, "exit")){
		// printf("%i\n", cmd->exit);
		// exit(cmd->exit); //  + проверка на аргументы
		exit(0);
	}
	if (!strcmp(commands->command, "pwd"))
		mx_print_pwd(commands); // печать pwd
	if (!strcmp(commands->command, "cd")) {
		mx_change_dir(commands);
	}
>>>>>>> fc9844dab0ba4ff53020527d03755d6729e482e5
}
