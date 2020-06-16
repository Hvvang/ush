#ifndef MX_SHELL_H
#define MX_SHELL_H

#define MX_DEFAULT_PATH "PATH=/bin:/usr/bin:/usr/local/bin:/usr/sbin:/sbin"

#include "../../exec/inc/mx_exec.h"
// #include "../../builtins/inc/mx_builtins.h"

// export variable map (key[=[value]])
typedef struct s_var_map {
	char *key;
	char *value;
}			   t_var_map;

// shell hash_table for custom export and environment
typedef struct s_hash_table {
	unsigned export_size; // number of export variables;
	t_processes *processes; // stoped processes structure;
	struct s_var_map *export; // export variables structure;
}			   t_hash_table;

t_hash_table *mx_create_hash_table(void);
t_hash_table *mx_init_env();
int mx_push_to_export(char *command, t_hash_table *hash_table);
int mx_find_key_index(char *command, t_hash_table *hash_table, int equal);
void mx_del_hash_table(t_hash_table *hash_table);

#endif
