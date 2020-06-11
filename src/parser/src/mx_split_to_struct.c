#include "../inc/mx_parser.h"

static t_command *create_node(char *command, char **arguments) {
	t_command *node = NULL;
	int size = mx_str_arr_size(arguments);

	node = (t_command*)malloc(sizeof(t_command));
	if (node == NULL)
		return NULL;
    node->command = strdup(command);
	node->arguments = malloc(sizeof(char*) * size + 1);
	for (int i = 0; i < size; i++)
		node->arguments[i] = strdup(arguments[i]);
	node->arguments[size] = NULL;
    node->next = NULL;
    return node;
}

static void push_back(t_command **commands, char *command, char **arguments) {
    t_command *current = *commands;

    if (*commands == NULL) {
        *commands = create_node(command, arguments);
        return;
    }
    while (current->next) {
        current = current->next;
    }
    current->next = create_node(command, arguments);
}

t_command *mx_split_to_struct(char *stdin_line) {
    char **commands = mx_get_commands(stdin_line);
    t_command *commd_struct = NULL;

    if (commands) {
        for (int i = 0; commands[i]; i++) {
			char **arr = NULL;

			mx_filter_input(&commands[i]);
			arr = mx_strsplit(commands[i], MX_ARGS_DELIM);
            push_back(&commd_struct, arr[0], &arr[1]);
			mx_del_strarr(&arr);
        }
		mx_del_strarr(&commands);
    }
    return commd_struct;
}
