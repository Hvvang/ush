#include "mx_builtins.h"

void mx_builtin_func(t_command *command, t_hash_table *hash_table) {
	// setenv("_", MX_USH_PATH, 1);

	// for (int i = 0; command->arguments[i]; i++)
	// 	mx_check_flag(command->arguments[i], command);
	if (!strcmp(command->command, "env")) {
        // mx_env(command, hash_table);
    }
	else if (!strcmp(command->command, "cd"))
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
    else if (!strcmp(command->command, "fg")) {
        // printf("--------- before fg ---------\n");
        // print_process(&hash_table->processes);
        mx_fg(&hash_table->processes, command->arguments);
        // printf("--------- after fg ---------\n");
        // print_process(&hash_table->processes);
    }
	else if (!strcmp(command->command, "exit")) {
		// del_struct(&command);
        // mx_del_hash_table(hash_table);
		// mx_del_strarr(&hash_table->hash_table);
		// mx_del_strarr(&hash_table->unset);

		exit(0);
	}
}
