#include "mx_parser.h"


char **mx_list_to_arr(t_list *list) {
    t_list *temp = list;
    char **commands = NULL;
    int list_size = mx_list_size(temp);

    if (list_size > 0) {
        commands = (char **)malloc(sizeof(char *) * list_size + 1);
        for (int i = 0; i < list_size; i++) {
            if (temp->data)
                commands[i] = strdup(temp->data);
            else
                commands[i] = NULL;
            temp = temp->next;
        }
        commands[list_size] = NULL;
    }
    return commands;
}
