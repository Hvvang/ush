#include "ush.h"

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
}
