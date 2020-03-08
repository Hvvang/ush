#include "ush.h"

static int check_command_on_exist(char **commands) {
    for (int i = 0; commands[i]; i++) {
        if (!strcmp(commands[i], "")) {
            fprintf(stderr,
                    "%s: syntax error near unexpected token `;;'\n",
                    MX_SHELL_NAME);
            return -1;
        }
        if (!strcmp(commands[i], " ")) {
            fprintf(stderr,
                    "%s: syntax error near unexpected token `;'\n",
                    MX_SHELL_NAME);
            return -1;
        }
    }
    return 0;
}

char **mx_get_commands(const char *stdin_line) {
    char *temp = mx_strdup(stdin_line);
    int result = 0;

    if (mx_check_input(temp, &result) == -1) {
        printf("ERROR\n");
        return NULL;
    }
    else {
        t_list *list = mx_split_commands(temp, MX_COMMAND_DELIM);
        char **commands = mx_list_to_arr(list);

        mx_del_list(&list);
        if (check_command_on_exist(commands)) {
            mx_del_strarr(&commands);
            return NULL;
        }
        return commands;
    }
}
