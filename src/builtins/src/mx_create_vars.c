#include "../inc/mx_builtins.h"

void mx_create_vars(t_hash_table *hash_table) {
    extern char **environ;

    setenv("status", "0", 1);
    for (unsigned i = 0; environ[i]; i++)
        mx_create_export(environ[i], hash_table);
}
