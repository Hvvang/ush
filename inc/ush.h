#ifndef USH_H
#define USH_H

#include "mx_posix.h"
#include "../libmx/inc/libmx.h"
#include "../src/shell/inc/mx_shell.h"
#include "../src/parser/inc/mx_parser.h"
// #include "../src/exec/inc/mx_exec.h"
// #include "../src/builtins/inc/mx_builtins.h"
#include "../src/input/inc/mx_input.h"
// #include "../src/history/inc/mx_history.h"

void mx_del_struct(t_command **head);
void mx_ush_loop (t_hash_table *hash_table); // базовый цикл
void pop_front(t_command **head);
void mx_handle_command(char *stdin_line, t_hash_table *hash_table);

#endif
