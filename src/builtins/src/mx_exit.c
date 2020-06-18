#include "mx_builtins.h"

void mx_exit(t_command *command, int *status) {
    int exit_value;
    char *exit_value_str = NULL;

    if (mx_str_arr_size(command->arguments) > 1)
        fprintf(stderr, "exit: too many arguments\n");
    if (command->arguments[0]) {
        exit_value = atoi(command->arguments[0]);
        exit_value_str = mx_itoa(exit_value);
        setenv("status", exit_value_str, 1);
        mx_strdel(&exit_value_str);
    }
    *status = 666;
}
