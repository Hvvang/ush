#ifndef MX_PARSER_H
#define MX_PARSER_H

#include "../../../inc/mx_posix.h"
#include "../../../libmx/inc/libmx.h"

#define MX_SHELL_NAME "ush"
#define MX_COMMAND_DELIM ';'
#define MX_ARGS_DELIM ' '

#ifdef __linux__
    #define MX_USERFOLDER "/home/"
#else
    #define MX_USERFOLDER "/Users/"
#endif

#define MX_IS_QUOTE(c) mx_get_literal(c) == QUOTE
#define MX_IS_SQUOTE(c) mx_get_literal(c) == SQUOTE
#define MX_IS_DQUOTE(c) mx_get_literal(c) == DQUOTE
#define MX_IS_BRACKET(c) mx_get_literal(c) == BRACKET
#define MX_IS_QBRACKET(c) mx_get_literal(c) == QBRACKET
#define MX_IS_CBRACKET(c) mx_get_literal(c) == CBRACKET
#define MX_IS_CQBRACKET(c) mx_get_literal(c) == CQBRACKET
#define MX_IS_SLASH(c) mx_get_literal(c) == SLASH
#define MX_IS_DOLLAR(c) mx_get_literal(c) == DOLLAR
#define MX_IS_REGULAR(c) mx_get_literal(c) == -1

#define MX_NEST_COMMAND(c) (!(MX_IS_REGULAR(c)) &&\
                            (MX_IS_QUOTE(c) || MX_IS_SQUOTE(c) ||\
                            MX_IS_DQUOTE(c) || MX_IS_DOLLAR(c)))

typedef enum e_literals { // Literal struct
	QUOTE, // `
	SQUOTE, // '
	DQUOTE, // "
	BRACKET, // (
	QBRACKET, // {
	CBRACKET, // )
	CQBRACKET, // }
	SLASH, // "\"
	DOLLAR, // $
}            t_literals;

typedef struct s_command {
	char *command;
	char **arguments;
}              t_command;

#include "../../shell/inc/mx_shell.h"
#include "../../exec/inc/mx_exec.h"
#include "../../builtins/inc/mx_builtins.h"

int mx_check_input(char *stdin_line);
void mx_replace_var(char **arg, char *before, char *after, int *i);
int mx_check_subs_lvls(char *str, int *index, int prev_lvl);
void mx_print_error(int error);
void mx_find_close_quote(char *str, int *i, char c);
char **mx_get_commands(char *stdin_line, char delim);
t_list *mx_split_commands(char *line, char delim);
int mx_get_literal(const char c);
char **mx_list_to_arr(t_list *list);
char mx_set_literal(const int literal);
int mx_skip_literal(char *str, int *index, int literal);
int mx_split_to_struct(char *stdin_line, t_hash_table *hash_table);
char *mx_replace_chars_by_str(char *str, int i, int itms, char *substr);
char *mx_substr_to_symbol(char *str, char *symbol);
void mx_filter_input(char **arg, int *status);
void mx_filter_tilda(char **arg, int *status);
void mx_filter_parameter(char **arg);
void mx_filter_substitution(char **arg, int *i, int *status);
int mx_get_substitution_by_quote(char **arg, int *status);
int mx_get_substitution_by_bracket(char **arg, int *status);
char *mx_subshell(char *substitution, int *status);
void mx_exec_command(t_command *command, t_hash_table *hash_table, int *status);
void del_command_struct(t_command **head);

#endif
