#include "mx_parser.h"


char **mx_get_commands(char *stdin_line, char delim) {
    int error = mx_check_input(stdin_line);
    int size = strlen(stdin_line);

    if (stdin_line[size - 1] != delim) {
        stdin_line = realloc(stdin_line, size + 1);
        stdin_line[size] = '\0';
        mx_insert_char_to_str(&stdin_line, delim, size);
    }
    if (error != 1) {
        mx_strdel(&stdin_line);
        mx_print_error(error);
        return NULL;
    }
    else {
        t_list *list = mx_split_commands(stdin_line, delim);
        char **commands = mx_list_to_arr(list);

        mx_del_list(&list);
        mx_strdel(&stdin_line);
        return commands;
    }
}
