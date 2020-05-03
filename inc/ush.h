#ifndef USH_H
#define USH_H

#include "mx_posix.h"

#define NO_F_OR_D "cd: no such file or directory: "
#define NO_D "cd: not a directory: "
#define STR_NO_PWD "No such file or directory:"
#define MANY_ARGV "cd: too many arguments"

#define FLAG "acEeiLnPsu"

typedef struct builtin_arr { // структура отформатированого масива для билтов
	char **arr;
} bl_arr;

typedef struct environ {
	char **env;
	char **exp;
	char **unset;
} t_env;

#define MX_SHELL_NAME "ush"
#define MX_SHELL_PROMPT "u$h> "
#define MX_COMMAND_DELIM ';'
#define MX_ARGS_DELIM ' '

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


// DEFAULT funcs
int mx_get_type(const char *path);
void pop_front(t_command **head);
void mx_del_str_arr(char **arr);
void mx_del_struct(t_command **head);
void mx_enable_canon(void);
bool mx_match(char *src, char *regex);
void mx_del_char_in_str(char *str, int pos);
void mx_insert_char_to_str(char *str, char c, int pos);

// PARSER funcs
char mx_set_literal(const int literal);
int mx_get_literal(const char c);
int mx_str_arr_size(char **arr);
char **mx_get_commands(const char *stdin_line);
int mx_check_input(char *stdin_line, int *index);
int mx_skip_literal(char *str, int *index, int literal);
t_command *mx_split_to_struct(char *stdin_line);
char **mx_list_to_arr(t_list *list);
t_list *mx_split_commands(char *commands, char delim);
int mx_check_subs_lvls(char *str, int *index);
char *mx_filter_input(char *arg);


// BUILTINS funcs
void mx_builtin_usage(int builtin, char error);
void mx_error_handle(int builtin, const char *command, int d_type);
void  mx_pwd(t_command *command); //выводит текущее местополжение
void mx_cd(t_command *command); // запуск команды cd
char mx_check_flags(int builtin, int *index, t_command *commands, bool(*valid)(int *, char *, char *, int *));
bool mx_valid_pwd(int *toggle, char *arg, char *flag, int *index);
bool mx_valid_cd(int *toggle, char *arg, char *flag, int *index);
bool mx_valid_echo(int *toggle, char *arg, char *flag, int *index);
bool mx_valid_export_unset(t_command *cmd); // валидация export and unset
bool mx_error_export_unset(t_command *cmd, char *builtin); //error for unset and export
void mx_echo(t_command *commands);



void mx_ush_loop (t_env *env, t_list *history); // базовый цикл
char *mx_ush_read_line(t_list *history); // парсинг вводимых данных
int  mx_launch_process(char **argv); // запуск дочернего процеса
int  mx_get_array_size(char **arr); // получить размер масива
void mx_builtin_func(t_command *commands, t_env *env); //главная ф-я билтинтов

void mx_get_history(char *input, int *pos, t_list *histry);

void mx_env(t_command *commands, t_env *env); //запуск команды env
void mx_export(t_command *commands, t_env *env); // обработка export
void mx_unset(t_command *commands, t_env *env); //обработка unset
void mx_env_create(t_env *env); // функция создание среды переменных
int mx_check_flag(char *str, t_command *commands); //проверка приходящих флагов
void mx_dir_file_link(t_command *commands); // проверка и выполнения на папку,линк,файл
void mx_cd_error(t_command *commands, int error_code); //ошибки ф-и cd
void mx_go_dir(t_command *cmd); // переход по папка с флагами и без
void mx_exp_change_dublicate(char *str, t_env *env, int index); // изменить дубликаты в export
void mx_exp_add_argv(t_command *cmd, t_env *env); //добавить данные в export

#endif
