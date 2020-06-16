#include "mx_parser.h"

static void get_args(char *line, int *i, int literal) {
    for (*i = *i + 1; line[*i]; (*i)++) {
        int ch = mx_get_literal(line[*i]);

        if (literal == QUOTE && ch == QUOTE) {
            if (!(MX_IS_SLASH(line[*i - 1])))
                return;
            *i += 1;
        }
        else if ((literal == SQUOTE || literal == DQUOTE)
             && !(MX_IS_SLASH(line[*i - 1]))) {
            mx_skip_literal(line, i, literal);
            return;
        }
        else if ((literal == BRACKET || literal == QBRACKET)
                  && ch == literal + 2)
            return;
        else if (!(MX_IS_SLASH(line[*i - 1])) && ch == DOLLAR
                 && (MX_IS_BRACKET(line[*i + 1])
                 || MX_IS_QBRACKET(line[*i + 1])))
            get_args(line, i, mx_get_literal(line[*i + 1]));
    }
}

t_list *mx_split_commands(char *commands, char delim) {
    t_list *list = NULL;
    int index = 0; // index of last literal exicting

    for (int i = 0; commands[i]; i++) {
        if (!(MX_IS_REGULAR(commands[i])) && mx_get_literal(commands[i]) < 3) {
            if (MX_IS_DOLLAR(commands[i]) && !(MX_IS_BRACKET(commands[i + 1])
                || MX_IS_QBRACKET(commands[i + 1])))
                continue;
            get_args(commands, &i, mx_get_literal(commands[i + 1]));
        }
        if (commands[i] == delim) {
            mx_push_back(&list, mx_strndup(&commands[index], i - index));
            while (commands[i] == delim)
                i++;
            index = i;
            i--;
        }
        else if (!commands[i + 1])
            mx_push_back(&list, mx_strndup(&commands[index], i - index + 1));
    }
    return list;
}
