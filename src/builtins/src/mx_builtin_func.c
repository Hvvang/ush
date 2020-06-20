#include "mx_builtins.h"

void mx_builtin_func(t_command *command,
	                 t_hash_table *hash_table,
					 int *status) {
	if (!strcmp(command->command, "cd"))
		mx_cd(command);
    else if (!strcmp(command->command, "history"))
		mx_print_history();
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
	else if (!strcmp(command->command, "jobs"))
		mx_print_processes(hash_table->processes);
    else if (!strcmp(command->command, "fg"))
        mx_fg(&hash_table->processes, command->arguments);
	else if (!strcmp(command->command, "exit"))
		mx_exit(command, status);
}
