#include "ush.h"

int mx_skip_literal(char *str, int *index, int literal) {
    int i = *index;

    for (*index = *index + 1; *index < (int)strlen(str); (*index)++) {
        if (literal < 3 && mx_get_literal(str[*index]) == literal)
            break;
        else if (literal == DOLLAR ) {
            int tmp = mx_get_literal(str[*index]);

            while ((tmp == BRACKET || tmp == QBRACKET)
                    && mx_get_literal(str[*index]) != tmp + 2)
                    (*index)++;
            break;
        }
        else if (literal == 3 && mx_get_literal(str[*index]) == CQBRACKET)
            break;
        else if (literal == SLASH && mx_get_literal(str[*index]) == SLASH
                 && mx_get_literal(str[*index]) == SLASH)
            break;
    }
    return (i != *index) ? mx_get_literal(str[*index]) : -1;
}
