#include "libmx.h"

void mx_pop_back(t_list **head) {
    t_list* prev = NULL;

    if (!head || !(*head))
        return ;
    if (!(*head)->next) {
        (*head)->data = NULL;
        free(*head);
        *head = NULL;
        return ;
    }
    prev = *head;
    while (prev->next->next)
        prev = prev->next;
    prev->next->data = NULL;
    free(prev->next);
    prev->next = NULL;
}
