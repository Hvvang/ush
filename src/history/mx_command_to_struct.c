#include "mx_history.h"

t_history *mx_command_to_struct(t_history *history, const char *command) {
    if (!history) {
        history = mx_create_history_node(command);
        return history;
    }
    t_history *new_item = mx_create_history_node(command);
    history->prev = new_item;
    history->prev->next = history;
    history = history->prev;
    return history;
}
