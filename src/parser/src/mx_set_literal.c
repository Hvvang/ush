#include "mx_parser.h"

char mx_set_literal(const int literal) {
    if (literal == QUOTE)
        return '`';
    if (literal == SQUOTE)
        return '\'';
    if (literal == DQUOTE)
        return '\"';
    if (literal == BRACKET)
        return '(';
    if (literal == QBRACKET)
        return '{';
    if (literal == CBRACKET)
        return ')';
    if (literal == CQBRACKET)
        return '}';
    if (literal == SLASH)
        return '\\';
    if (literal == DOLLAR)
        return '$';
    return -1;
}
