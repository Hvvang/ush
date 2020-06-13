#include "../inc/mx_parser.h"

void mx_filter_substitution(char **arg, int *i) {
    char *temp = NULL;
    // char *res = NULL;
    // char substitution[BUFSIZ];

    if (MX_IS_BRACKET((*arg)[*i + 1])) {
        mx_del_char_in_str(*arg, *i);
        mx_del_char_in_str(*arg, *i);
        temp = mx_substr_to_symbol(&((*arg)[*i]), ")");
        mx_del_char_in_str(*arg, *i + strlen(temp));
    }
    else
        while (mx_get_substitutions(arg));

        // temp = mx_get_substitution(*arg, i);
    // printf("temp = %s\n", temp);
    // strcpy(substitution, temp);
    // mx_filter_input(&temp);
    // res = mx_subshell(temp);
    // mx_replace_var(arg, substitution, res, i - strlen(substitution));
    // mx_strdel(&res);
    // *i -= 1;
}
