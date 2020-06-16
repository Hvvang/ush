#include "mx_shell.h"

void mx_del_hash_table(t_hash_table *hash_table) {
    for (unsigned i = 0; i < hash_table->export_size; i++) {
        mx_strdel(&hash_table->export[i].key);
        mx_strdel(&hash_table->export[i].value);
    }
    free(hash_table);
    hash_table = NULL;
}
