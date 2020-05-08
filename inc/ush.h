#ifndef USH_H
#define USH_H

#include "mx_posix.h"
#include "../libmx/inc/libmx.h"
#include "../src/builtins/inc/mx_builtins.h"
#include "../src/parser/inc/mx_parser.h"
#include "../src/input/inc/mx_input.h"

#define NO_F_OR_D "cd: no such file or directory: "
#define NO_D "cd: not a directory: "
#define STR_NO_PWD "No such file or directory:"
#define MANY_ARGV "cd: too many arguments"

#define FLAG "acEeiLnPsu"

#define MX_SHELL_PROMPT "u$h> "

// DEFAULT funcs
void mx_del_str_arr(char **arr);
void mx_del_struct(t_command **head);
int  mx_launch_process(char **argv); // запуск дочернего процеса
bool mx_match(char *src, char *regex);
void mx_ush_loop (t_env *env); // базовый цикл
void pop_front(t_command **head);

#endif
