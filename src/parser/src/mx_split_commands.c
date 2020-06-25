#include "mx_parser.h"

static bool check_closing(const char *line, int i, int literal) {
    if ((literal == SQUOTE || literal == DQUOTE) &&
        (MX_IS_SQUOTE(line[i]) ||
        (MX_IS_DQUOTE(line[i]) && !(MX_IS_SLASH(line[i - 1]))))) {
        return true;
    }
    else if (literal == QUOTE &&
            (MX_IS_QUOTE(line[i]) && !(MX_IS_SLASH(line[i - 1])))) {
            return true;
    }
    else if ((literal == BRACKET || literal == QBRACKET) &&
            (mx_get_literal(line[i]) == literal + 2))
            return true;
    return false;
}

static void skip_nesting(const char *line, int *i, int literal) {
    if (!(MX_IS_SLASH(line[*i - 1]))) {
        if (literal == DOLLAR) {
            (*i) += 1;
            if (!(MX_IS_BRACKET(line[*i])) && !(MX_IS_QBRACKET(line[*i])))
                return;
            literal = mx_get_literal(line[*i]);
        }
        for (*i = *i + 1; line[*i]; (*i)++) {
            if (check_closing(line, *i, literal))
                return;
            if (MX_NEST_COMMAND(line[*i])) {
                skip_nesting(line, i, mx_get_literal(line[*i]));
            }
        }
    }
}

t_list *mx_split_commands(char *line, char delim) {
    t_list *commands = NULL;
    int index = 0;

    for (int i = 0; line[i]; i++) {
        if (MX_NEST_COMMAND(line[i]))
            skip_nesting(line, &i, mx_get_literal(line[i]));
        if (line[i] == delim && !(MX_IS_SLASH(line[i - 1]))) {
            char *temp = strndup(&line[index], i - index);
            char *res = mx_strtrim(temp);

            if (strlen(res))
                mx_push_back(&commands, res);
            else
                mx_strdel(&res);
            mx_strdel(&temp);
            index = i + 1;
        }
    }
    return commands;
}
