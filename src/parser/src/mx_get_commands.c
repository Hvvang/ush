#include "mx_parser.h"

char **mx_get_commands(const char *stdin_line) {
    char *temp = mx_strdup(stdin_line);
    int result = 0;
    int error = mx_check_input(temp, &result);

    if (error != 1) {
        mx_strdel(&temp);
        mx_print_error(error);
        return NULL;
    }
    else {
        t_list *list = mx_split_commands(temp, MX_COMMAND_DELIM);
        char **commands = mx_list_to_arr(list);

        mx_del_list(&list);
        mx_strdel(&temp);
        return commands;
    }
}
