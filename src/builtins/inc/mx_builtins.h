#ifndef MX_BUILTINS_H
#define MX_BUILTINS_H

#include "../../../inc/mx_posix.h"
#include "../../../libmx/inc/libmx.h"
#include "../../parser/inc/mx_parser.h"

typedef struct environ {
	char **env;
	char **exp;
	char **unset;
} t_env;


typedef enum e_builtins { // builtins struct
	MX_ENV,
	MX_CD,
	MX_PWD,
	MX_WHICH,
	MX_ECHO,
	MX_EXPORT,
	MX_UNSET,
	MX_EXIT
}            t_builtins;

void mx_builtin_func(t_command *commands, t_env *env);
void mx_builtin_usage(int builtin, char error);
void mx_cd(t_command *commands);
char mx_check_flags(int builtin, int *index, t_command *commands,  bool(*valid)(int *, char *, char *, int *));
void mx_echo(t_command *commands);
void mx_env_create(t_env *env);
void mx_env(t_command *commands, t_env *env);
bool mx_error_export_unset(t_command *cmd, char *builtin);
void mx_error_handle(int builtin, const char *command, int d_type);
void mx_exp_add_argv(t_command *cmd, t_env *env);
void mx_pwd(t_command *commands);
bool mx_valid_cd(int *toggle, char *arg, char *flag, int *index);
bool mx_valid_echo(int *toggle, char *arg, char *flag, int *index);
bool mx_valid_export_unset(t_command *cmd);
bool mx_valid_pwd(int *toggle, char *arg, char *flag, int *index);
void mx_exp_change_dublicate(char *str, t_env *env, int index);
void mx_unset(t_command *cmd, t_env *env);
void mx_export(t_command *cmd, t_env *env);

#endif
