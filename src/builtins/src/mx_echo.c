#include "mx_builtins.h"

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


/*  Echo flags
*   -n - flag[0];
*   -e - flag[1]; default flag
*   -E - flag[2];
*/
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

void mx_echo(t_command *command) {
    int index = 0;
    int flags[3] = {0, 1, 0};

    mx_check_flags(MX_ECHO, &index, command, mx_valid_echo);
    get_echo_flags(flags, command->arguments, index);
    if (flags[1]) {
        for (unsigned i = index; command->arguments[i]; i++) {
            for (unsigned j = 0; command->arguments[i][j]; j++) {
                if (command->arguments[i][j] == '\\')
                    change_char_to_unprint(command->arguments[i], j);
            }
        }
    }
    mx_print_strarr(&command->arguments[index], " ");
    if (!flags[0])
        printf("\n");
}
