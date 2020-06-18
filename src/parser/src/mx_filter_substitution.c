#include "mx_parser.h"

void mx_filter_substitution(char **arg, int *i, int *status) {
    if (MX_IS_BRACKET((*arg)[*i + 1]))
        while (mx_get_substitution_by_bracket(arg, status));
    else
        while (mx_get_substitution_by_quote(arg, status));
    *i -= 1;
}
