#include "libmx.h"

void mx_pop_front(t_list **head) {
	t_list *prev = NULL;

	if (!head || !(*head))
		return ;
	if ((*head)->next == NULL) {
		free(*head);
		*head = NULL;
		return ;
	}
    prev = (*head)->next;
    (*head)->data = NULL;
    free(*head); 
    *head = prev;
}
