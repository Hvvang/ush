#include "libmx.h"

int mx_list_size(t_list *list) {
	int i = 0;
	t_list* tmp = list;
	
	//tmp = list;
	

	while (tmp != NULL) {
		i++;
		tmp = tmp->next;
	}
	return i;
}
