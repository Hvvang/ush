#include "ush.h"

t_list *mx_split_commands(char *commands, char delim) {
    t_list *list = NULL;
    int index = 0; // index of last literal exicting

    for (int i = 0; commands[i]; i++) {
        if (mx_get_literal(commands[i]) > - 1)
            mx_skip_literal(commands, &i, mx_get_literal(commands[i]));
        if (commands[i] == delim) {
            mx_push_back(&list, strndup(&commands[index], i - index));
            while (commands[i] == delim) {
                i++;
            }
            index = i;
            i--;
        }
        else if (!commands[i + 1])
            mx_push_back(&list, strndup(&commands[index], i - index + 1));
    }
    return list;
}
