#include "libmx.h"

static int lenght_words(const char *str);
static char* copy_words(const char *str, char** res);
static int count_words(const char *str);

char *mx_del_extra_spaces(const char *str) {
    char *res = NULL;
    int count = 0;
    int len = 0;
    char *tmp = NULL;

    tmp = mx_strtrim(str);
    count = count_words(tmp);
    if (count == 0)
        return tmp;
    len = lenght_words(tmp);
    res = mx_strnew(len + count - 1);
    res = copy_words(tmp, &res);
    mx_strdel(&tmp);
    return res;
}

static int lenght_words(const char *str) {
    int i = 0;
    int len = 0;

    while (str[i] != '\0') {
    if (mx_isspace(str[i]) != 1)
        len++;
        i++;
    }
    return len;
}

static char* copy_words(const char *str, char** res) {
    int i = 0;
    int j = 0;

    while (str[i] != '\0') {
        if (mx_isspace(str[i]) != 1 && str[i] != '\0') {
            (*res)[j] = str[i];
            j++;
        }
        else if (str[i] != '\0' && mx_isspace(str[i])) {
            (*res)[j] = ' ';
            j++;
            while (mx_isspace(str[i+1]) == 1 && str[i] != '\0')
                i++;
        }
        i++;
    }
    return *res;
}

static int count_words(const char *str) {
    int count = 0;
    int i = 0;

    if (str == NULL)
        return -1;
    while (str[i] != '\0') {
        while (mx_isspace(str[i]) == 1 && str[i] != '\0')
            i++;
        if (mx_isspace(str[i]) != 1 && str[i] != '\0')
            count++;
        while (mx_isspace(str[i]) != 1 && str[i] != '\0')
            i++;   
    }
    return count;
}
