#include "mx_exec.h"

/*
*   Function returns number of suspended processes
*   that are keeping in t_processes processes
*   structure.
*/
int mx_get_processes_num(t_processes **process) {
    t_processes *temp = *process;
    int size = 0;

    while (temp) {
        temp = temp->next;
        size++;
    }
    return size;
}
