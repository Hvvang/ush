#include "libmx.h"

static bool is_space(char c){
    if (c == 32) 
        return 1;
    if (c == '\t')
        return 1;
    if (c == '\n')
        return 1;
    if (c == '\v')
        return 1;
    if (c == '\f')
        return 1;
    if (c == '\r')
        return 1;
    return 0;
}

static bool is_digit(char c) {
    if (c < 48 || c > 57)
        return false;
    return true;
}

int mx_atoi(const char *str) {
    int i = 0;
    int flag = 1;
    int res = 0;
    
    if (str[0] == '-') {
        flag = -1;
        i++;
    }
    while (is_space(str[i]))
        i++;
    while (str[i] && is_digit(str[i])) {
        res = res * 10 + str[i] - 48;
        i++;
    }
    return res * flag;
}
