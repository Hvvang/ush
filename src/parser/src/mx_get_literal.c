#include "mx_parser.h"

int mx_get_literal(const char c) {
    if (c == '`')
        return QUOTE;
    if (c == '\'')
        return SQUOTE;
    if (c == '\"')
        return DQUOTE;
    if (c == '(')
        return BRACKET;
    if (c == '{')
        return QBRACKET;
    if (c == ')')
        return CBRACKET;
    if (c == '}')
        return CQBRACKET;
    if (c == '\\')
        return SLASH;
    if (c == '$')
        return DOLLAR;
    return -1;
}
