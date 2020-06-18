#include "mx_exec.h"

void mx_print_processes(t_processes *processes) {
    t_processes *temp = processes;

    if (temp) {
        printf("index  job\n");
        while (temp) {
            printf("  %d  ", temp->index);
            mx_print_strarr(temp->command, " ");
            printf("\n");
            temp = temp->next;
        }
    }
}
