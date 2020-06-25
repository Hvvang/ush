#ifndef MX_BUILTINS_H
#define MX_BUILTINS_H

#include "../../../libmx/inc/libmx.h"
#include "../../parser/inc/mx_parser.h"
#include "../../history/inc/mx_history.h"

#define MX_NOT_FOUND -1
#define MX_CHANGED_VAR 0
#define MX_NEW_VAR 1

// custom built-ins enum structure
typedef enum e_builtins {
	MX_NOT_A_USH_BUILTIN = -1,
	MX_EXPORT = 0,
	MX_UNSET = 1,
	MX_EXIT = 2,
	MX_ENV = 3,
	MX_CD = 4,
	MX_FG = 5,
	MX_PWD = 6,
	MX_ECHO = 7,
	MX_JOBS = 8,
	MX_WHICH = 9,
	MX_HISTORY = 10,
	MX_TRUE = 11,
	MX_FALSE = 12,
	MX_COLOR = 13,
	MX_BYE = 14,
}            t_builtins;

void mx_builtin_func(t_command *commands, t_hash_table *hash_table, int *status);
void mx_builtin_usage(int builtin, char *command, char error);
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
void mx_env(t_command *command, t_hash_table *hash_table);
bool mx_valid_env(int *toggle, char *arg, char *flag, int *index);
char **mx_copy_env(void);
void mx_clear_env(void);
void mx_set_env(char **env);
void mx_exit(t_command *command, int *status);
void mx_true(void);
void mx_false(void);
void mx_color(t_command *command);
bool mx_valid_color(int *toggle, char *arg, char *flag, int *index);

#endif
