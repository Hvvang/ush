#ifndef MX_PARSER_H
#define MX_PARSER_H

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

#include "../../../inc/mx_posix.h"
#include "../../../libmx/inc/libmx.h"
#include <string.h>

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
	int exit;
	struct s_command *next;
}              t_command;

int mx_get_substitution_by_quote(char **arg);
int mx_get_substitution_by_bracket(char **arg);
int mx_check_input(char *stdin_line, int *index);
void mx_replace_var(char **arg, char *before, char *after, int *i);
int mx_check_subs_lvls(char *str, int *index, int prev_lvl);
int mx_print_error(int error);
void mx_filter_input(char **arg);
void mx_find_close_quote(char *str, int *i, char c);
char **mx_get_commands(const char *stdin_line);
int mx_get_literal(const char c);
char **mx_list_to_arr(t_list *list);
char mx_set_literal(const int literal);
int mx_skip_literal(char *str, int *index, int literal);
t_list *mx_split_commands(char *commands, char delim);
t_command *mx_split_to_struct(char *stdin_line);
char *mx_replace_chars_by_str(char *str, int i, int itms, char *substr);
char *mx_substr_to_symbol(char *str, char *symbol);
void mx_filter_tilda(char **arg);
void mx_filter_parameter(char **arg, int *i);
void mx_filter_substitution(char **arg, int *i);
char *mx_subshell(char *substitution);


#endif
