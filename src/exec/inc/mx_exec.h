#ifndef MX_EXEC_H
#define MX_EXEC_H

#include "../../../inc/mx_posix.h"
#include "../../../libmx/inc/libmx.h"
#include "../../parser/inc/mx_parser.h"

#define MX_NOT_FOUND -1
#define MX_CHANGED_VAR 0
#define MX_NEW_VAR 1

#define MX_W_INT(m) (*(int*) & (m))
#define MX_WSTOPSIG(m) (MX_W_INT(m) >> 8)
#define MX_WSTATUS(m) (MX_W_INT(m) & 0177)
#define MX_WIFSTOPPED(m) (MX_WSTATUS(m) == _WSTOPPED && MX_WSTOPSIG(m) != 0x13)
#define MX_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#define MX_WAIT_TO_INT(m) (*(int *) & (m))
#define MX_WEXITSTATUS(x) ((MX_WAIT_TO_INT(x) >> 8) & 0x000000ff)

// export variable map (key[=[value]])
typedef struct s_var_map {
	char *key;
	char *value;
}			   t_var_map;

typedef struct s_processes {
	char **command;
	pid_t pid;
	struct s_processes *next;
}			   t_processes;

// shell hash_table for custom export and environment
typedef struct s_hash_table {
	char **env; // shell environment (can be changed);
	unsigned export_size; // number of export variables;
	int processes_num; // number of suspended processes on exec;
	struct s_processes *processes; // stoped processes structure;
	struct s_var_map *export; // export variables structure;
}			   t_hash_table;


void mx_builtin_func(t_command *commands, t_hash_table *hash_table);
int mx_is_ush_builtins(char *command);
void mx_hash_table_create(t_hash_table *hash_table);

void mx_create_vars(t_hash_table *hash_table);
void mx_del_hash_table(t_hash_table *hash_table);
void mx_push_process(t_processes **processes, char **command, pid_t pid);
void mx_clear_process(t_processes **prcs, void *kill);

#endif
