#include "mx_history.h"

void mx_print_history(void) {
    t_history *history = mx_file_to_struct();
    int index = 0;

    while (history->next) {
        history = history->next;
    }
    while (history->prev) {
        printf(" %d  %s\n", ++index, history->command);
        history = history->prev;
    }
    mx_clear_history_list(&history);
}
