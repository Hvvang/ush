#include "../inc/mx_parser.h"

static char *replace_chars_by_str(char *str, int itms, char *substr) {
    char *tmp = mx_strdup(substr);

    while (itms--)
        mx_del_char_in_str(str, 0);
    str = mx_strjoin_no_leaks(tmp, str);
    return str;
}

static char *filter_tilda(char *arg) {
    if (arg[0] == '~') {
        if (arg[1] == '/' || !arg[1])
            arg = replace_chars_by_str(arg, 1, getenv("HOME"));
        else if (arg[1] == '+' && (arg[2] == '/' || !arg[2]))
            arg = replace_chars_by_str(arg, 2, getenv("PWD"));
        else if (arg[1] == '-' && (arg[2] == '/' || !arg[2]))
            arg = replace_chars_by_str(arg, 2, getenv("OLDPWD"));
        else if (arg[1] != '+' && arg[1] != '-' && arg[1] != '/') {
            arg =replace_chars_by_str(arg, 1, USERFOLDER);
        }
    }
    return arg;
}

static void filter_quote(char *arg, int *i, int literal) {
    mx_del_char_in_str(arg, *i);
    mx_skip_literal(arg, i, literal);
    mx_del_char_in_str(arg, *i);
    *i -= 1;
}
// static char *get_parameter(char *arg, int *i) {
//     char *param = NULL;
//     int items = 0;
//     int nestLiteral = mx_get_literal(arg[*i + 1]);
//
//     for (int i = *i; arg[i]; i++) {
//         if (nextLiteral == QBRACKET) {
//             if (arg[i] == '}')
//                 break;
//             items++;
//         }
//         else if (nextLiteral == -1) {
//             if (arg[i]) == ' ')
//                 break;
//             items++;
//         }
//     }

//     param = mx_strndup(arg + *i + 1, index - *i);
//
//     printf("param")
// }

// static void filter_parameter(char *arg, int *i) {
//     int nextLiteral = mx_get_literal(arg[*i + 1]);
//     int index = *i;
//
//     if (nextLiteral == QBRACKET)
//         filter_quote(arg, &index, BRACKET);
//     nextLiteral = mx_get_literal(arg[*i + 1]);
//     if (nextLiteral == -1) {
//         int items = *i;
//
//             printf("COUNT");
//         printf("param = %s\n", param);
//         replace_chars_by_str(arg, index - *i + 1, getenv(param), *i);
//     }
// }

char *mx_filter_input(char *arg) {
    arg = filter_tilda(arg);
    for (int i = 0; arg[i]; i++) {
        int currLiteral = mx_get_literal(arg[i]);

        if (currLiteral == SLASH)
            mx_del_char_in_str(arg, i);
        else if (currLiteral == SQUOTE || currLiteral == DQUOTE)
            filter_quote(arg, &i, currLiteral);
        // else if (currLiteral == DOLLAR)
        //     filter_parameter(arg, &i);
    }
    return arg;
}
