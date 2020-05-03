#ifndef MX_PARSER_H
#define MX_PARSER_H

#define MX_SHELL_NAME "ush"
#define MX_COMMAND_DELIM ';'
#define MX_ARGS_DELIM ' '

#ifdef __linux__
    #define USERFOLDER "/home/"
#else
    #define USERFOLDER "/USERS/"
#endif

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
	DOLLAR // $
}            t_literals;


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

typedef enum e_types { // Types stuct
	// MX_SOCKET,
	MX_LINK,
	MX_FILE,
	MX_BLOCK,
	MX_DIR,
	MX_CHAR,
	MX_FIFO,
	MX_ANY,
	MX_EFAULT
}            t_types;


typedef struct s_command {
	char *command;
	char **arguments;
	int fl[10];
	int exit;
	struct s_command *next;
}              t_command;

int mx_check_input(char *stdin_line, int *index);
int mx_check_subs_lvls(char *str, int *index);
int mx_error_handle(int error);
char *mx_filter_input(char *arg);
void mx_find_close_quote(char *str, int *i, char c);
char **mx_get_commands(const char *stdin_line);
int mx_get_literal(const char c);
char **mx_list_to_arr(t_list *list);
char mx_set_literal(const int literal);
t_list *mx_split_commands(char *commands, char delim);
t_command *mx_split_to_struct(char *stdin_line);

#endif
