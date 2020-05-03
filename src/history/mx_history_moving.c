#include "mx_history.h"

char *mx_history_moving(t_history *history, char *keyCode) {
    if (history) {
        if (!strcmp(keyCode, MX_UP_ARROW)) {
            if (history->next)
                history = history->next;
            return history->command;
        }
        if (!strcmp(keyCode, MX_DOWN_ARROW) && history->prev) {
            history = history->prev;
            return history->command;
        }
    }
    return NULL;
}
