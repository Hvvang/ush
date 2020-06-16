#include "libmx.h"

void mx_push_front(t_list **list, void *data) {
	t_list* head = NULL;

	if (!list || !data)
		return ;
    head = mx_create_node(data);
    if (!head)
    	return ;
    head->next = *list;
    *list = head;
}
