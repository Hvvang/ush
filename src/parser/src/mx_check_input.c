#include "mx_parser.h"

static int check_dollar(char *str, int *i, int len, int sub_lvl);
static int check_subquote(char *line, int *i, int len, int sub_lvl);
static int check_dquote(char *line, int *i, int len, int sub_lvl);

static int check_dollar(char *str, int *i, int len, int sub_lvl) {
    if (MX_IS_BRACKET(str[*i + 1]) || MX_IS_QBRACKET(str[*i + 1])) {
        for (*i = *i + 2; *i < len; (*i)++) {
            int error = 1;

            if ((MX_IS_CBRACKET(str[*i + 1]) || MX_IS_CQBRACKET(str[*i + 1]))
                && !(MX_IS_SLASH(str[*i - 1])))
                return 1;
            else if (MX_IS_QUOTE(str[*i]) && !(MX_IS_SLASH(str[*i - 1])))
                error = check_subquote(str, i, len, sub_lvl);
            else if (MX_IS_SQUOTE(str[*i]) && !(MX_IS_SLASH(str[*i - 1])))
                error = mx_skip_literal(str, i, SQUOTE);
            else if (MX_IS_DOLLAR(str[*i]) && !(MX_IS_SLASH(str[*i - 1])))
                error = check_dollar(str, i, len, sub_lvl);
            else if (MX_IS_DQUOTE(str[*i]) && !(MX_IS_SLASH(str[*i - 1])))
                error = check_dquote(str, i, len, sub_lvl);
            if (error != 1)
                return error;
        }
        return -4;
    }
    else
        return 1;
}

static int check_subquote(char *line, int *i, int len, int sub_lvl) {
    for (*i = *i + 1; *i < len; (*i)++) {
        int error = 1;

        if (MX_IS_QUOTE(line[*i])) {
            int lvl = mx_check_subs_lvls(line, i, sub_lvl);

            if ((sub_lvl) == lvl)
                return 1;
            else if ((sub_lvl) > lvl)
                return -3;
            else
                error = check_subquote(line, i, len, lvl);
        }
        else if (MX_IS_SQUOTE(line[*i]) && !(MX_IS_SLASH(line[*i - 1])))
            error = mx_skip_literal(line, i, SQUOTE);
        else if (MX_IS_DQUOTE(line[*i]) && !(MX_IS_SLASH(line[*i - 1])))
            error = check_dquote(line, i, len, sub_lvl);
        else if (MX_IS_DOLLAR(line[*i]))
            error = check_dollar(line, i, len, sub_lvl);
        if (error != 1)
            return error;
    }
    return -3;
}

static int check_dquote(char *line, int *i, int len, int sub_lvl) {
    for (*i = *i + 1; *i < len; (*i)++) {
        int error = 1;

        if (MX_IS_QUOTE(line[*i]))
            error = check_subquote(line, i, len, sub_lvl);
        else if (MX_IS_DOLLAR(line[*i]) && !(MX_IS_SLASH(line[*i - 1])))
            error = check_dollar(line, i, len, sub_lvl);
        else if (MX_IS_DQUOTE(line[*i]) && !(MX_IS_SLASH(line[*i - 1])))
            return 1;
        if (error != 1)
            return error;
    }
    return -2;
}


// Func that check input lineing on quote closing
int mx_check_input(char *line) {
    int len = strlen(line);
    int error = 1;

    for (int i = 0; i < len && error == 1; i++) {
        if (!(MX_IS_SLASH(line[i - 1])) && line[i] == ';'
            && line[i + 1] == ';')
            return -5;
        else if (MX_IS_SLASH(line[i]) && !line[i + 1])
            error = -1;
        else if (MX_IS_QUOTE(line[i]) && !(MX_IS_SLASH(line[i - 1])))
            error = check_subquote(line, &i, len, 0);
        else if (MX_IS_SQUOTE(line[i]) && !(MX_IS_SLASH(line[i - 1])))
            error = mx_skip_literal(line, &i, SQUOTE);
        else if (MX_IS_DQUOTE(line[i]) && !(MX_IS_SLASH(line[i - 1])))
            error = check_dquote(line, &i, len, 0);
        else if (!(MX_IS_SLASH(line[i - 1])) && MX_IS_DOLLAR(line[i]))
            error = check_dollar(line, &i, len, 0);
    }
    return error;
}
