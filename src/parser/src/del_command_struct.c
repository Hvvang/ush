#include "mx_parser.h"

void del_command_struct(t_command **head) {
	if ((*head)->command)
	mx_strdel(&((*head)->command));
	if ((*head)->arguments)
	mx_del_strarr(&((*head)->arguments));
	free(*head);
	*head = NULL;
}
