#include "mx_parser.h"

static t_command *create_node(char *command, char **arguments) {
	t_command *node = NULL;
	int size = mx_str_arr_size(arguments);

	node = (t_command*)malloc(sizeof(t_command));
	if (node == NULL)
		return NULL;
    node->command = command;
	node->arguments = malloc(sizeof(char*) * size + 1);
	for (int i = 0; i < size; i++)
		node->arguments[i] = arguments[i];
	node->arguments[size] = NULL;
    return node;
}

void del_command_struct(t_command **head) {
	if ((*head)->command)
    	mx_strdel(&((*head)->command));
	if ((*head)->arguments)
    	mx_del_strarr(&((*head)->arguments));
    free(*head);
    *head = NULL;
}


void mx_exec_command(t_command *command, t_hash_table *hash_table, int *status) {
	if (command) {
		if (mx_is_ush_builtins(command->command) != -1)
			mx_builtin_func(command, hash_table, status);
		else {
			char *path = mx_get_path_to_bin(command->command);
			extern char **environ;

			mx_launch_process(command, &hash_table->processes, path, environ);
			mx_strdel(&path);
		}
	}
}

int mx_split_to_struct(char *stdin_line, t_hash_table *hash_table) {
    char **commands = mx_get_commands(stdin_line);
	int status = 0;

    if (commands) {
        for (int i = 0; commands[i] && status != 666; i++) {
			t_command *commd_struct = NULL;
			char **arr = NULL;

			mx_filter_input(&commands[i], &status);
			if (!status) {
				arr = mx_strsplit(commands[i], MX_ARGS_DELIM);
				commd_struct = create_node(arr[0], &arr[1]);
				mx_exec_command(commd_struct, hash_table, &status);
				if (commd_struct)
					del_command_struct(&commd_struct);
			}
        }
		mx_del_strarr(&commands);
    }
	return status;
}
