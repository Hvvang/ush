#include "mx_shell.h"

static void create_vars(t_hash_table *hash_table) {
    extern char **environ;

    setenv("status", "0", 1);
    for (unsigned i = 0; environ[i]; i++)
        mx_push_to_export(environ[i], hash_table);
}

t_hash_table *mx_create_hash_table(void) {
	t_hash_table *hash_table = (t_hash_table*)malloc(sizeof(t_hash_table));

	hash_table->processes = (t_processes*)malloc(sizeof(t_processes));
	hash_table->processes = NULL;
	hash_table->export = (t_var_map*)malloc(sizeof(t_var_map));
	hash_table->export_size = 0;
	create_vars(hash_table);
	return hash_table;
}
