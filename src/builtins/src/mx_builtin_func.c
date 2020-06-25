#include "mx_builtins.h"

static void main_builtins(t_command *command,
	                 	  t_hash_table *hash_table,
					 	  int *status) {
	if (!strcmp(command->command, "cd"))
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
	else if (!strcmp(command->command, "jobs"))
		mx_print_processes(hash_table->processes);
    else if (!strcmp(command->command, "fg"))
        mx_fg(&hash_table->processes, command->arguments);
	else if (!strcmp(command->command, "exit")
			|| !strcmp(command->command, "bye"))
		mx_exit(command, status);
}

static void extended_builtins(t_command *command) {
	if (!strcmp(command->command, "history"))
		mx_print_history();
	if (!strcmp(command->command, "true"))
		mx_true();
	if (!strcmp(command->command, "false"))
		mx_false();
	if (!strcmp(command->command, "color"))
		mx_color(command);
}


void mx_builtin_func(t_command *command,
	                 t_hash_table *hash_table,
					 int *status) {
	bool pwd = true;
	bool home = true;

	if (!getenv("PWD"))
		pwd = false;
	if (!getenv("HOME"))
		home = false;
	mx_init_pwd(hash_table);
	mx_init_home(hash_table);
	main_builtins(command, hash_table, status);
	extended_builtins(command);
	if (!pwd)
		unsetenv("PWD");
	if (!home)
		unsetenv("HOME");
}
