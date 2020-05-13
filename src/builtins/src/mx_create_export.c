#include "../inc/mx_builtins.h"

void mx_create_export(t_hash_table *hash_table) {
    extern char **environ;

    for (unsigned i = 0; environ[i]; i++)
        mx_create_variable(environ[i], hash_table);
}
