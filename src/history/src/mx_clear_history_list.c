#include "mx_history.h"

void mx_clear_history_list(t_history **history) {
    while ((*history)->prev)
        *history = (*history)->prev;
    while ((*history)->next) {
        *history = (*history)->next;
        mx_strdel(&((*history)->prev->command));
    }
    if (*history) {
        mx_strdel(&((*history)->command));
        if ((*history)->prev)
            free((*history)->prev);
        if ((*history)->next)
            free((*history)->next);
    }
}
