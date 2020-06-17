#include "ush.h"

void mx_del_struct(t_command **head) {
    t_command *tmp;

    while (*head) {
        tmp = *head;
        mx_strdel(&tmp->command);
        mx_del_strarr(&tmp->arguments);
        free(tmp);
    }
}
