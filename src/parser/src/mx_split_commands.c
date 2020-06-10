#include "../inc/mx_parser.h"

static void get_args(char *line, int *i, int literal) {
    for (*i = *i + 1; line[*i]; (*i)++) {
        int ch = mx_get_literal(line[*i]);

        if (literal > DQUOTE && literal < SLASH)
            if (ch == literal + 2)
                return;
        if (ch == literal) {
            return;
        }
        else if (ch > -1) {
            if (ch == DOLLAR && mx_get_literal(line[*i + 1]) == -1) {
                continue;
            }
            get_args(line, i, ch);
        }
    }
}

t_list *mx_split_commands(char *commands, char delim) {
    t_list *list = NULL;
    int index = 0; // index of last literal exicting

    for (int i = 0; commands[i]; i++) {
        if (MX_IS_QUOTE(commands[i]) || MX_IS_SQUOTE(commands[i])
            || MX_IS_DQUOTE(commands[i]) || MX_IS_BRACKET(commands[i])
            || MX_IS_QBRACKET(commands[i]) || MX_IS_DOLLAR(commands[i])) {
            get_args(commands, &i, mx_get_literal(commands[i]));
        }
        if (commands[i] == delim) {
            char *test = mx_strndup(&commands[index], i - index);
            // printf("test is = %s\n", test);
            mx_push_back(&list, test);
            while (commands[i] == delim) {
                i++;
            }
            index = i;
            i--;
        }
        else if (!commands[i + 1])
            mx_push_back(&list, mx_strndup(&commands[index], i - index + 1));
    }
    return list;
}
