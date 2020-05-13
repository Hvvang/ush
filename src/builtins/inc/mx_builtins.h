#ifndef MX_BUILTINS_H
#define MX_BUILTINS_H

#include "../../../inc/mx_posix.h"
#include "../../../libmx/inc/libmx.h"
#include "../../parser/inc/mx_parser.h"

#define MX_NOT_FOUND -1
#define MX_CHANGED_VAR 0
#define MX_NEW_VAR 1

typedef struct s_export {
	char *key;
	char *value;
}			   t_export;


typedef struct s_hash_table {
	char **env;
	char **unset;
	unsigned export_size;
	struct s_export *export;
}			   t_hash_table;

typedef enum e_builtins { // builtins struct
	MX_EXPORT,
	MX_UNSET,
	MX_EXIT,
	MX_ENV,
	MX_CD,
	MX_FG,
	MX_PWD,
	MX_ECHO,
	MX_WHICH,
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
bool mx_error_export_unset(t_command *cmd, char *builtin);
void mx_error_handle(int builtin, const char *command, int d_type);
void mx_exp_add_argv(t_command *cmd, t_hash_table *hash_table);
void mx_pwd(t_command *command);
bool mx_valid_cd(int *toggle, char *arg, char *flag, int *index);
bool mx_valid_echo(int *toggle, char *arg, char *flag, int *index);
bool mx_valid_export_unset(t_command *cmd);
void mx_exp_change_dublicate(char *str, t_hash_table *hash_table, int index);
void mx_unset(t_command *command, t_hash_table *hash_table);
void mx_export(t_command *command, t_hash_table *hash_table);
bool mx_valid_which(int *toggle, char *arg, char *flag, int *index);
void mx_which(t_command *command);


void mx_create_export(t_hash_table *hash_table);
int mx_create_variable(char *command, t_hash_table *hash_table);
void mx_del_hash_table(t_hash_table *hash_table);

#endif
