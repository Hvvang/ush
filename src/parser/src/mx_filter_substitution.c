#include "../inc/mx_parser.h"

void mx_filter_substitution(char **arg, int *i) {
    if (MX_IS_BRACKET((*arg)[*i + 1]))
        while (mx_get_substitution_by_bracket(arg));
    else
        while (mx_get_substitution_by_quote(arg));
    *i -= 1;
}
