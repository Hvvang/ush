#include "../inc/mx_history.h"

char *mx_history_moving(t_history *history, char *keyCode) {
    if (history) {
        if (!MX_IS_UP_ARROW(keyCode)) {
            if (history->next)
                history = history->next;
            return history->command;
        }
        else if (!MX_IS_DOWN_ARROW(keyCode) && history->prev) {
            history = history->prev;
            return history->command;
        }
    }
    return NULL;
}
