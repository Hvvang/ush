#ifndef MX_SHELL_H
#define MX_SHELL_H

#define MX_DEFAULT_PATH "PATH=/bin:/usr/bin:/usr/local/bin:/usr/sbin:/sbin"

#include "../../../inc/mx_posix.h"
#include "../../../libmx/inc/libmx.h"

// export variable map (key[=[value]])
typedef struct s_var_map {
	char *key;
	char *value;
}			   t_var_map;

typedef struct s_processes {
	char **command;
	pid_t pid;
	int index;
	struct s_processes *next;
}			   t_processes;

// shell hash_table for custom export and environment
typedef struct s_hash_table {
	struct termios savetty; // terminos settings;
	unsigned export_size; // number of export variables;
	t_processes *processes; // stoped processes structure;
	struct s_var_map *export; // export variables structure;
}			   t_hash_table;
#include "../..//exec/inc/mx_exec.h"

t_hash_table *mx_create_hash_table(void);
void mx_del_hash_table(t_hash_table *hash_table);
void mx_increment_shlvl(t_hash_table *hash_table);
t_hash_table *mx_init_env();
void mx_init_home(t_hash_table *hash_table);
void mx_init_path(t_hash_table *hash_table);
void mx_init_pwd(t_hash_table *hash_table);
int mx_push_to_export(char *command, t_hash_table *hash_table);
int mx_find_key_index(char *command, t_hash_table *hash_table, int equal);
void mx_clear_all(t_hash_table *hash_table);
void mx_ush_loop (t_hash_table *hash_table);
int mx_handle_command(char *stdin_line, t_hash_table *hash_table);

#endif
