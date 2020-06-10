#include "../inc/mx_parser.h"

static void filter_squote(char *arg, int *i);
static char *filter_dquote(char *arg, int *i);
static char *filter_parameter(char *arg, int *i);
static char *filter_substitution(char *arg, int *i);

static void filter_squote(char *arg, int *i) {
    mx_del_char_in_str(arg, *i);
    mx_skip_literal(arg, i, SQUOTE);
    mx_del_char_in_str(arg, *i);
    *i -= 1;
}

static char *filter_dquote(char *arg, int *i) {
    mx_del_char_in_str(arg, *i);
    for (; arg[*i]; (*i)++) {
        if (MX_IS_DQUOTE(arg[*i]))
            break;
        else if (MX_IS_SLASH(arg[*i]) && !(MX_IS_REGULAR(arg[*i])))
            mx_del_char_in_str(arg, *i);
        else if (MX_IS_QUOTE(arg[*i]))
            arg = filter_substitution(arg, i);
        else if (MX_IS_DOLLAR(arg[*i])) {
            if (MX_IS_BRACKET(arg[*i + 1]))
                arg = filter_substitution(arg, i);
            else
                arg = filter_parameter(arg, i);
        }
    }
    mx_del_char_in_str(arg, *i);
    *i -= 1;
    return arg;
}

static char *filter_parameter(char *arg, int *i) {
    char *temp = NULL;
    char *res = NULL;

    mx_del_char_in_str(arg, *i);
    if (MX_IS_QBRACKET(arg[*i])) {
        mx_del_char_in_str(arg, *i);
        temp = mx_substr_to_symbol(&arg[*i], "}");
        mx_del_char_in_str(arg, *i + strlen(temp));
    }
    else
        temp = mx_substr_to_symbol(&arg[*i], " `'\"(){}\\$");
    if (getenv(temp) || !strcmp(temp, "?")) {
        res = (!strcmp(temp, "?")) ? getenv("status") : getenv(temp);
        arg = mx_replace_substr(arg, temp, res);
        *i = *i + strlen(res) - 1;
    }
    else {
        for (unsigned j = strlen(temp); j; j--)
            mx_del_char_in_str(arg, *i);
        *i = *i - 1;
    }
    mx_strdel(&temp);
    return arg;
}

static char *filter_substitution(char *arg, int *i) {
    char *temp = NULL;
    char *res = NULL;
    char *substitution = NULL;

    if (MX_IS_BRACKET(arg[*i + 1])) {
        mx_del_char_in_str(arg, *i);
        mx_del_char_in_str(arg, *i);
        temp = mx_substr_to_symbol(&arg[*i], ")");
        mx_del_char_in_str(arg, *i + strlen(temp));
    }
    else
        temp = mx_get_substitution(arg, i);
    substitution = strdup(temp);
    res = mx_filter_input(temp);
    free(temp);
    temp = mx_subshell(res);
    arg = mx_replace_substr(arg, substitution, temp);
    *i = *i + strlen(temp) - 1;
    mx_strdel(&substitution);
    mx_strdel(&res);
    mx_strdel(&temp);
    return arg;
}

char *mx_filter_input(char *arg) {
    char *res = strdup(arg);

    res = mx_filter_tilda(res);
    for (int i = 0; res[i]; i++) {
        if (MX_IS_SLASH(res[i]) && !(MX_IS_QUOTE(res[i + 1])))
            mx_del_char_in_str(res, i);
        else if (MX_IS_SQUOTE(res[i]))
            filter_squote(res, &i);
        else if (MX_IS_DQUOTE(res[i]))
            res = filter_dquote(res, &i);
        else if (MX_IS_QUOTE(res[i])
                 || ( MX_IS_SLASH(res[i]) && MX_IS_QUOTE(res[i + 1])))
            res = filter_substitution(res, &i);
        else if (MX_IS_DOLLAR(res[i])) {
            if (MX_IS_BRACKET(res[i + 1])) {
                res = filter_substitution(res, &i);
            }
            else {
                res = filter_parameter(res, &i);
            }
        }
    }
    return res;
}
