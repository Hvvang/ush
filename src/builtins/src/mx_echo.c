#include "../inc/mx_builtins.h"
#define _BSD_SOURCE

static void change_char_to_unprint(char *str, int i) {
    char c = str[i + 1];

    mx_del_char_in_str(str, i);
    if (c == '0')
        str[i] = '\0';
    else if (c == 'a')
        str[i] = '\a';
    else if (c == 'b')
        str[i] = '\b';
    else if (c == 't')
        str[i] = '\t';
    else if (c == 'n')
        str[i] = '\n';
    else if (c == 'v')
        str[i] = '\v';
    else if (c == 'f')
        str[i] = '\f';
    else if (c == 'r')
        str[i] = '\r';
}

static void get_echo_flags(int *flags, char **args, int index) {
    for (int i = 0; i < index; i++) {
        for (int j = 1; args[i][j]; j++) {
            if (args[i][j] == 'n')
                flags[0] = 1;
            else if (args[i][j] == 'e') {
                flags[1] = 1;
                flags[2] = 0;
            }
            else {
                flags[1] = 0;
                flags[2] = 1;
            }
        }
    }
}

void mx_echo(t_command *commands) {
    int index = 0;
    int flags[3] = {0, 0, 0};

    mx_check_flags(MX_ECHO, &index, commands, mx_valid_echo);
    get_echo_flags(flags, commands->arguments, index);
    if (flags[1]) {
        for (int i = 0; commands->arguments[index][i]; i++) {
            if (commands->arguments[index][i] == '\\')
                change_char_to_unprint(commands->arguments[index], i);
        }
    }
    mx_print_strarr(&commands->arguments[index], " ");
    if (!flags[0])
        printf("\n");
}
