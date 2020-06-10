#include "../inc/mx_builtins.h"

void del_struct(t_command **head) {
    t_command *tmp;

    while (*head) {
        tmp = *head;
        *head = (*head)->next;
        mx_strdel(&tmp->command);
        mx_del_strarr(&tmp->arguments);
        free(tmp);
    }
}


void mx_builtin_func(t_command *command, t_hash_table *hash_table) {
	// for (int i = 0; command->arguments[i]; i++)
	// 	mx_check_flag(command->arguments[i], command);
	if (!strcmp(command->command, "env"))
		mx_env(command, hash_table);
	else if (!strcmp(command->command, "cd"))
		mx_cd(command);
	else if (!strcmp(command->command, "pwd"))
		mx_pwd(command);
	else if (!strcmp(command->command, "echo"))
		mx_echo(command);
	else if (!strcmp(command->command, "export"))
		mx_export(command, hash_table);
	else if (!strcmp(command->command, "unset"))
		mx_unset(command, hash_table);
	else if (!strcmp(command->command, "which"))
		mx_which(command);
    else if (!strcmp(command->command, "fg"))
        mx_fg(hash_table);
	else if (!strcmp(command->command, "exit")) {
		// del_struct(&command);
        // mx_del_hash_table(hash_table);
		// mx_del_strarr(&hash_table->hash_table);
		// mx_del_strarr(&hash_table->unset);

		exit(0);
	}
}
