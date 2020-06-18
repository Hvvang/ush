#include "mx_history.h"

char *mx_history_moving(t_history **history, char *keyCode) {
    if (*history) {
        if (MX_IS_UP_ARROW(keyCode) || MX_IS_DLE(keyCode)) {
            if ((*history)->next)
                *history = (*history)->next;
            else
                printf("\a");
            return ((*history)->command);
        }
        else if (MX_IS_DOWN_ARROW(keyCode)) {
            if ((*history)->prev)
                (*history) = (*history)->prev;
            return (*history)->command;
        }
    }
    return NULL;
}
