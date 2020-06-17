#include "mx_shell.h"

void mx_init_path(t_hash_table *hash_table) {
    if (getenv("PATH") == NULL)
        mx_push_to_export(MX_DEFAULT_PATH, hash_table);
}
