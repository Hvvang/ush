#include "../inc/mx_parser.h"

static void filter_squote(char *arg, int *i);
static void filter_dquote(char **arg, int *i);

static void filter_squote(char *arg, int *i) {
    mx_del_char_in_str(arg, *i);
    mx_skip_literal(arg, i, SQUOTE);
    mx_del_char_in_str(arg, *i);
    *i -= 1;
}

static void filter_dquote(char **arg, int *i) {
    mx_del_char_in_str(*arg, *i);
    for (; (*arg)[*i]; (*i)++) {
        if (MX_IS_DQUOTE((*arg)[*i])) {
            mx_del_char_in_str(*arg, *i);
            break;
        }
        else if (MX_IS_SLASH((*arg)[*i]) && !(MX_IS_REGULAR((*arg)[*i])))
            mx_del_char_in_str(*arg, *i);
        else if (MX_IS_QUOTE((*arg)[*i]))
            mx_filter_substitution(arg, i);
        else if (MX_IS_DOLLAR((*arg)[*i])) {
            if (MX_IS_BRACKET((*arg)[*i + 1]))
                mx_filter_substitution(arg, i);
            else
                mx_filter_parameter(arg, i);
        }
    }
    *i -= 1;
}

void mx_filter_input(char **arg) {
    mx_filter_tilda(arg);
    for (int i = 0; (*arg)[i]; i++) {
        if (MX_IS_SLASH((*arg)[i]) && !(MX_IS_QUOTE((*arg)[i + 1])))
            mx_del_char_in_str(*arg, i);
        else if (MX_IS_SQUOTE((*arg)[i]))
            filter_squote(*arg, &i);
        else if (MX_IS_DQUOTE((*arg)[i]))
            filter_dquote(arg, &i);
        else if (MX_IS_QUOTE((*arg)[i])
                 || ( MX_IS_SLASH((*arg)[i]) && MX_IS_QUOTE((*arg)[i + 1])))
            mx_filter_substitution(arg, &i);
        else if (MX_IS_DOLLAR((*arg)[i])) {
            if (MX_IS_BRACKET((*arg)[i + 1]))
                mx_filter_substitution(arg, &i);
            else
                mx_filter_parameter(arg, &i);
        }
    }
}
