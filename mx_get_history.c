#include "ush.h"

#define MX_IS_UP_ARROW(code)    !strcmp(code, "\033[A\0")

static t_list *create_copy(t_list *history) {
    t_list *temp = history;
    t_list *copy = NULL;

    while (temp) {
        mx_push_back(&copy, temp->data);
        temp = temp->next;
    }
    return copy;
}

static void clear_input(char *input, int *pos) {
    // printf("\npos = %d\n", *pos);
    int len = strlen(input);

    while (*pos > 0) {
        printf("\b");
        *pos = *pos - 1;
    }
    memset(input, ' ', len);
    printf("%s", input);
    *pos += len;
    memset(input, '\b', len);
    printf("%s", input);
    *pos -= len;
    // printf("pos = %d", *pos);
}

void mx_get_history(char *input, int *pos, t_list *history) {
    if (history) {
		// printf("history->data = %s", history->data);

        t_list *before = create_copy(history);
        t_list *after = NULL;
        char c[5];

        clear_input(input, pos);
        while (read(STDIN_FILENO, &c, 4) && MX_IS_UP_ARROW(c)) {
            // mx_push_front(&after, strdup(before->data));
            // mx_pop_front(&before);

            clear_input(input, pos);

            // int len = strlen(before->data);
            // char *car_pos = mx_strnew(len);
            //
            // printf("%s", before->data);
            // memset(car_pos, '\b', len);
            // *pos += len;
            // mx_strdel(&car_pos);
        }
        // input = strdup(before->data);
    }
}
