#include "mx_shell.h"

void mx_increment_shlvl(t_hash_table *hash_table) {
    int new_lvl = 1;
    int index = mx_find_key_index("SHLVL", hash_table, 0);
    char *curr_lvl = (index >= 0) ?
                     hash_table->export[index].value :
                     NULL;
    char shlvl[NAME_MAX];
    char *arg[2] = {NULL, NULL};

    if (curr_lvl != NULL)
        new_lvl += atoi(curr_lvl);
    sprintf(shlvl, "SHLVL=%d", new_lvl);
    mx_push_to_export(shlvl, hash_table);
    mx_strdel(&arg[0]);
}
