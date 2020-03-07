#include "ush.h"

// потом удалить
static char *what_it_cmd(char *line) {
	char *str[10] = {"exit","fg","unset","export","cd",
	                "pwd","echo","which","env",NULL};
	char *ch_str = (char*)malloc(sizeof(char) * 20);
	char *dest =  malloc(sizeof(char) * 20);

	int i = 0;
	for (; line[i]; i++) {
		if (line[i] != '\n') {
			ch_str[i] = line[i];
			ch_str[i + 1] = '\0';
		}
	}
	for (i = 0; ch_str[i]; i++) {
		if (ch_str[i] == ' ')
			break;
		dest[i] = ch_str[i];
		dest[i + 1] = '\0';
	}
	for (int i = 0; str[i] != NULL; i++) {
		if (mx_strcmp(dest, str[i]) == 0) {
			return str[i];
		}
	}
	return "error";
}

static void add_to_struct(cmd_bl *cmd, char *line) {
	cmd->cmd = what_it_cmd(line);
	char *str = malloc(sizeof(char) * mx_strlen(line) - mx_strlen(cmd->cmd)); // clear mem
	int size = mx_strlen(cmd->cmd);
	int j = 0;

	for(int i = size; line[i]; i++) {
		if (line[i] == '\n')
			break;
		str[j] = line[i];
		j++;
	}
	
	cmd->argv = mx_strsplit(str, ' '); //clear mem
}

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


void mx_builtin_func(char *line) {
	cmd_bl *cmd = (cmd_bl*)malloc(sizeof(cmd_bl));
	extern char **environ;

	add_to_struct(cmd, line);
	if (mx_strcmp(cmd->cmd, "error") == 0) {
		printf("aasdasdasd\n");
		exit(cmd->exit); //  если левак
	}
	if (mx_strcmp(cmd->cmd, "exit") == 0){
		printf("%i\n", cmd->exit);
		exit(cmd->exit); //  + проверка на аргументы
	}
	if (mx_strcmp(cmd->cmd, "pwd") == 0)
		mx_print_pwd(cmd); // печать pwd
	if (mx_strcmp(cmd->cmd, "cd") == 0) {
		mx_change_dir(cmd); 
	}
}
