#ifndef MX_HISTORY_H
#define MX_HISTORY_H

#include "../../input/inc/mx_input.h"

#define MX_HISTORY_FILE ".ush_history"

typedef struct s_history {
    char *command;
    struct s_history *prev;
    struct s_history *next;
}              t_history;

void mx_history_file_appending(const char *command);
t_history *mx_create_history_node(const char *command);
t_history *mx_command_to_struct(t_history *history, const char *command);
t_history *mx_file_to_struct(void);
t_history *mx_update_history_struct(t_history *history);
char *mx_history_moving(t_history **history, char *keyCode);
void mx_clear_history_list(t_history **history);
void mx_print_history(void);

#endif
