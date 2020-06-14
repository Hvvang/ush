#include "../inc/mx_builtins.h"

void mx_clear_process(t_processes **prcs, void *kill) {
    t_processes *temp = *prcs;
    t_processes *del = NULL;

    if (!temp->next) {
        mx_del_strarr(&temp->command);
        // free(temp);
        return;
    }
    while (temp->next) {
        printf("%p =? %p", (void *)temp, kill);
        if ((void *)temp->next == kill)
            break;
        temp = temp->next;
    }
    del = temp->next;
    temp->next = del->next;
    mx_del_strarr(&del->command);
    free(del->next);
    free(del);
}
