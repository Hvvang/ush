#ifndef MX_BUILTINS_H
#define MX_BUILTINS_H

#include "../../../libmx/inc/libmx.h"
#include "../../parser/inc/mx_parser.h"
#include "../../shell/inc/mx_shell.h"
#include "../../history/inc/mx_history.h"
#include "../../exec/inc/mx_exec.h"

#define MX_NOT_FOUND -1
#define MX_CHANGED_VAR 0
#define MX_NEW_VAR 1

// // export variable map (key[=[value]])
// typedef struct s_var_map {
// 	char *key;
// 	char *value;
// }			   t_var_map;
//
// // shell hash_table for custom export and environment
// typedef struct s_hash_table {
// 	unsigned export_size; // number of export variables;
// 	t_processes *processes; // stoped processes structure;
// 	struct s_var_map *export; // export variables structure;
// }			   t_hash_table;

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

void mx_builtin_func(t_command *commands, t_hash_table *hash_table);
void mx_builtin_usage(int builtin, char error);
void mx_cd(t_command *commands);
char mx_check_flags(int builtin, int *index, t_command *command, bool(*valid)(int *, char *, char *, int *));
void mx_echo(t_command *command);
void mx_error_handle(int builtin, const char *command, int d_type);
void mx_export(t_command *command, t_hash_table *hash_table);
void mx_fg(t_processes **processes, char **args);
int mx_is_ush_builtins(char *command);
void mx_pwd(t_command *command);
void mx_unset(t_command *command, t_hash_table *hash_table);
bool mx_valid_cd(int *toggle, char *arg, char *flag, int *index);
bool mx_valid_echo(int *toggle, char *arg, char *flag, int *index);
bool mx_valid_which(int *toggle, char *arg, char *flag, int *index);
void mx_which(t_command *command);

#endif
