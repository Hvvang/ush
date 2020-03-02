#include "ush.h"

int mx_isWord(char *data) {
    if (!mx_isPipe(data) && !mx_isNewLine(data) && !mx_isGreat(data)
        && !mx_isLess(data) && !mx_isGreatGreat(data)
        && !mx_isGreatAmpersand(data) && !mx_isAmpersand(data)) {
            return WORD;
        }
    return DONT_UNDERSTAND;
}
