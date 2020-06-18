#include "mx_exec.h"

/*
*   Clearing node of t_processes process structure
*   that have finished or terminated by input
*   signal.
*/

void mx_clear_process(t_processes **prcs, void *kill) {
    t_processes *temp = *prcs;
    t_processes *head = *prcs;

    if ((void *)temp == kill) {
        temp = (*prcs)->next;
        mx_del_strarr(&(*prcs)->command);
        free(*prcs);
        *prcs = temp;
    }
    else {
        while (temp->next) {
            temp->index -= 1;
            if ((void *)temp->next == kill)
                break;
            temp = temp->next;
        }
        *prcs = temp->next;
        temp->next = (*prcs)->next;
        mx_del_strarr(&(*prcs)->command);
        free(*prcs);
        *prcs = head;
    }
}
