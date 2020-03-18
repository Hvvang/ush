#include "ush.h"

void pop_front(t_command **head) {
	t_command *prev = NULL;

	if (!head || !(*head))
		return ;
    else {
        mx_strdel(&((*head)->command));
        mx_del_strarr(&((*head)->arguments));
        if ((*head)->next == NULL) {
            free(*head);
            *head = NULL;
            return ;
        }
        prev = (*head)->next;
        free(*head);
        *head = prev;
    }
}
