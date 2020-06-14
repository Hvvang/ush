#ifndef MX_BUILTINS_H
#define MX_BUILTINS_H

#include "../../../inc/mx_posix.h"
#include "../../../libmx/inc/libmx.h"
#include "../../parser/inc/mx_parser.h"
#include "../../history/inc/mx_history.h"

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
	int index;
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

// custom built-ins enum structure
typedef enum e_builtins {
	MX_EXPORT,
	MX_UNSET,
	MX_EXIT,
	MX_ENV,
	MX_CD,
	MX_FG,
	MX_PWD,
	MX_ECHO,
	MX_WHICH,
	MX_HISTORY,
	MX_NOT_A_USH_BUILTIN
}            t_builtins;

char *mx_join_path(const char *left, const char *right);
void mx_builtin_func(t_command *commands, t_hash_table *hash_table);
int mx_is_ush_builtins(char *command);
void mx_builtin_usage(int builtin, char error);
void mx_cd(t_command *commands);
char mx_check_flags(int builtin, int *index, t_command *command, bool(*valid)(int *, char *, char *, int *));
void mx_echo(t_command *command);
void mx_hash_table_create(t_hash_table *hash_table);
void mx_env(t_command *commands, t_hash_table *hash_table);
void mx_error_handle(int builtin, const char *command, int d_type);
void mx_exp_add_argv(t_command *cmd, t_hash_table *hash_table);
void mx_pwd(t_command *command);
bool mx_valid_cd(int *toggle, char *arg, char *flag, int *index);
bool mx_valid_echo(int *toggle, char *arg, char *flag, int *index);
void mx_exp_change_dublicate(char *str, t_hash_table *hash_table, int index);
void mx_unset(t_command *command, t_hash_table *hash_table);
void mx_export(t_command *command, t_hash_table *hash_table);
bool mx_valid_which(int *toggle, char *arg, char *flag, int *index);
void mx_which(t_command *command);

void mx_fg(t_processes *processes, char **args, int *pids_num);
void mx_create_vars(t_hash_table *hash_table);
int mx_create_export(char *command, t_hash_table *hash_table);
void mx_del_hash_table(t_hash_table *hash_table);
void mx_push_process(t_processes **processes, char **command, pid_t pid);
void mx_clear_process(t_processes **prcs, void *kill);

#endif
