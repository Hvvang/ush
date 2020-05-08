#include "../inc/ush.h"

void mx_del_struct(t_command **head) {
    t_command *tmp;

    while (*head) {
        tmp = *head;
        *head = (*head)->next;
        mx_strdel(&tmp->command);
        mx_del_strarr(&tmp->arguments);
        free(tmp);
    }
}
