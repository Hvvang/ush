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

#define MX_W_INT(m) (*(int*) & (m))
#define MX_WSTOPSIG(m) (MX_W_INT(m) >> 8)
#define MX_WSTATUS(m) (MX_W_INT(m) & 0177)
#define MX_WIFSTOPPED(m) (MX_WSTATUS(m) == _WSTOPPED && MX_WSTOPSIG(m) != 0x13)
#define MX_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#define MX_WAIT_TO_INT(m) (*(int *) & (m))
#define MX_WEXITSTATUS(x) ((MX_WAIT_TO_INT(x) >> 8) & 0x000000ff)

// DEFAULT funcs
void mx_del_struct(t_command **head);
int mx_launch_process(t_command *command, t_hash_table *hash_table); // запуск дочернего процеса
bool mx_match(char *src, char *regex);
void mx_ush_loop (t_hash_table *hash_table); // базовый цикл
void pop_front(t_command **head);

// char *mx_subshell(char *substitution);

#endif
