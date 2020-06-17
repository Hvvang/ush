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
    mx_strdel(&((*head)->command));
    mx_del_strarr(&((*head)->arguments));
    free(*head);
    *head = NULL;
}

void mx_split_to_struct(char *stdin_line, t_hash_table *hash_table) {
    char **commands = mx_get_commands(stdin_line);

    if (commands) {
        for (int i = 0; commands[i]; i++) {
			t_command *commd_struct = NULL;
			char **arr = NULL;

			mx_filter_input(&commands[i]);
			arr = mx_strsplit(commands[i], MX_ARGS_DELIM);
			commd_struct = create_node(arr[0], &arr[1]);
			if (commd_struct) {
				// printf("exec\n");
	            if (mx_is_ush_builtins(commd_struct->command) != MX_NOT_A_USH_BUILTIN) {
					// printf("builtin\n");
					// printf("command = %s\t", commd_struct->command);
					// mx_print_strarr(commd_struct->arguments, " ");
					// printf("\n");
					mx_builtin_func(commd_struct, hash_table);
				}
	            else {
					// printf("external prog\n");
					mx_launch_process(commd_struct, &hash_table->processes);
				}
				del_command_struct(&commd_struct);
	        }
        }
		mx_del_strarr(&commands);
    }
}
