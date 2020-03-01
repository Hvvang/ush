#include "ush.h"

// static void get_cmd_str(t_cmd *cmd) {
// 	char *str[] = {"cd", "pwd", "exit", "echo", "which", "env", NULL};
	
// 	cmd->cmd_str = malloc(sizeof(char **) * 6);
// 	for (int i = 0; str[i]; i++) {
// 		cmd->cmd_str[i] = malloc(sizeof(char) * mx_strlen(str[i]));
// 		cmd->cmd_str[i] = str[i];
// 	}
// }

// static void print_cmd(t_line *g_line, t_cmd *cmd) {
// 	int sw = -1;

// 	for (int i = 0; cmd->cmd_str[i]; i++)
// 		if (mx_strcmp(g_line->args[0], cmd->cmd_str[i]) == 0) 
// 			sw = i;
// 	if (sw == 0)
// 		mx_change_dir(g_line);
// 	else if (sw == 1)
// 		mx_print_pwd();
// 	else if (sw == 2)
// 		printf("%s\n", "exit$");
// 	else if (sw == 3)
// 		printf("%s\n", "echo$");
// 	else if (sw == 4)
// 		printf("%s\n", "which$");
// 	else if (sw == 5)
// 		printf("%s\n", "env$");
// }

// void mx_check_flag(t_line *g_line) {
// 	t_cmd  *cmd = malloc(sizeof(t_cmd));

// 	get_cmd_str(cmd);
// 	// get_cmd_func(cmd);
// 	print_cmd(g_line, cmd);
// }
