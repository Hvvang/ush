#include "mx_shell.h"

void clear_processes(t_hash_table *hash_table) {
    t_processes *temp = hash_table->processes;

    while (temp) {
        kill(temp->pid, SIGKILL);
        mx_clear_process(&temp, (void *)temp);
    }
}

void clear_export(t_hash_table *hash_table) {
    t_var_map *temp = hash_table->export;

    for (unsigned i = 0; i < hash_table->export_size; i++) {
        mx_strdel(&(temp[i].key));
        if (temp[i].value)
            mx_strdel(&(temp[i].value));
    }
}

void mx_clear_all(t_hash_table *hash_table) {
    int exit_code = atoi(getenv("status"));

    exit_code = exit_code % 256;
    if (hash_table->processes)
        clear_processes(hash_table);
    if (hash_table->export)
        clear_export(hash_table);
    if (hash_table->export)
        free(hash_table->export);
    exit(exit_code);
}
