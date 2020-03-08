#include "ush.h"

static int check_dollar(char *str, int *index, int len);
static int check_subquote(char *str, int *index, int len);
static int check_dquote(char *str, int *index, int len);

static int check_dollar(char *str, int *index, int len) {
    int literal_close = mx_get_literal(str[*index + 1]);

    if (literal_close == BRACKET || literal_close == QBRACKET) {
        for (*index = *index + 2; *index < len; (*index)++) {
            int currLiteral = mx_get_literal(str[*index]);
            int prevLiteral = mx_get_literal(str[*index - 1]);
            int error = 0;

            if (currLiteral == literal_close + 2 && prevLiteral != SLASH)
                return 1;
            else if (currLiteral == QUOTE && prevLiteral != SLASH)
                error = check_subquote(str, index, len);
            else if (currLiteral == SQUOTE && prevLiteral != SLASH)
                error = mx_skip_literal(str, index, SQUOTE);
            else if (currLiteral == DOLLAR && prevLiteral != SLASH)
                error = check_dollar(str, index, len);
            else if (currLiteral == DQUOTE && prevLiteral != SLASH)
                error = check_dquote(str, index, len);
            if (error == -1)
                return -1;
        }
    }
    else
        return 0;
    return -1;
}

static int check_subquote(char *str, int *index, int len) {
    for (*index = *index + 1; *index < len; (*index)++) {
        int currLiteral = mx_get_literal(str[*index]);
        int prevLiteral = mx_get_literal(str[*index - 1]);
        int error = 0;

        if (currLiteral == QUOTE && prevLiteral != SLASH)
            return 1;
        else if (currLiteral > -1 && prevLiteral == SLASH)
            error = mx_skip_literal(str, index, SQUOTE);
        else if (currLiteral == DQUOTE && prevLiteral != SLASH)
            error = check_dquote(str, index, len);
        else if (currLiteral == DOLLAR && prevLiteral != SLASH)
            error = check_dollar(str, index, len);
        if (error == -1)
            return -1;
    }
    return -1;
}

static int check_dquote(char *str, int *index, int len) {
    for (*index = *index + 1; *index < len; (*index)++) {
        int currLiteral = mx_get_literal(str[*index]);
        int prevLiteral = mx_get_literal(str[*index - 1]);
        int error = 0;

        if (currLiteral == QUOTE && prevLiteral != SLASH)
            error = check_subquote(str, index, len);
        else if (currLiteral == DOLLAR && prevLiteral != SLASH)
            error = check_dollar(str, index, len);
        else if (currLiteral == DQUOTE && prevLiteral != SLASH)
            return 1;
        if (error == -1)
            return -1;
    }
    return -1;
}

int mx_check_input(char *stdin_line, int *index) {
    int len = strlen(stdin_line);
    int error = 0;

    for (int i = *index; i < len; i++) {
        int currLiteral = mx_get_literal(stdin_line[i]);
        int prevLiteral = mx_get_literal(stdin_line[i - 1]);

        if (currLiteral == QUOTE && !(i > 0 && prevLiteral == SLASH))
            error = check_subquote(stdin_line, &i, len);
        else if (currLiteral == SQUOTE && !(i > 0 && prevLiteral == SLASH))
            error = mx_skip_literal(stdin_line, &i, SQUOTE);
        else if (currLiteral == DQUOTE && !(i > 0 && prevLiteral == SLASH))
            error = check_dquote(stdin_line, &i, len);
        else if (currLiteral == DOLLAR && !(i > 0 && prevLiteral == SLASH))
            error = check_dollar(stdin_line, &i, len);
        if (error == -1)
            break;
    }
    return error;
}
