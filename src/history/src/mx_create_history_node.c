#include "../inc/mx_history.h"

t_history *mx_create_history_node(const char *command) {
    t_history *history = (t_history*)malloc(sizeof(t_history));

    history->command = strdup(command);
    history->prev = NULL;
    history->next = NULL;
    return history;
}
