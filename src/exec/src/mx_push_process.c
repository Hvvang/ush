#include "mx_exec.h"

/*
*   Creating new process node and adding
*	it to t_processes process structure.
*/

static t_processes *create_node(char **command, pid_t pid) {
	t_processes *node = (t_processes *)malloc(sizeof(t_processes));
	int size = mx_str_arr_size(command);

	if (node == NULL)
		return NULL;
	node->command = (char **)malloc(sizeof(char *) * size + 1);
	for (int i = 0; command[i]; i++) {
		node->command[i] = strdup(command[i]);
	}
	node->command[size] = NULL;
	node->pid = pid;
    node->next = NULL;
    return node;
}

void mx_push_process(t_processes **processes, char **command, pid_t pid) {
    t_processes* head = NULL;

	if (!processes || !command || !pid) {
		return ;
	}
	if (*processes == NULL) {
        *processes = create_node(command, pid);
		(*processes)->index = 1;
		return;
    }
    head = create_node(command, pid);
    if (!head)
    	return;
    head->next = *processes;
	head->index = head->next->index + 1;
    *processes = head;
}
