#include "libmx.h"

static char* mreplace(char **res, int i, const char *sub, const char *replace);

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    int i = 0;
    int count = 0;
    char *res = NULL;

    if (str == NULL)
        return NULL;
    if (str[0] == '\0')
        return (char*)str;
    count = mx_count_substr(str, sub);
    res = mx_strdup(str);
    if (str == NULL || sub == NULL || replace == NULL) 
        return NULL;
    while (count > 0) {
        i = mx_get_substr_index(res, sub);
        res = mreplace(&res, i, sub, replace);
        count--;
    }
    return res;
}

static char* mreplace(char **res, int i, const char *sub,
    const char *replace) {
    char *str = NULL;
    char *tmp = *res;
    char *before = mx_strndup(*res, i);
    char *after = mx_strdup((const char*)&tmp[i + mx_strlen(sub)]);

    mx_strdel(res);
    tmp = mx_strjoin(before, replace);
    str = mx_strjoin(tmp, after);
    mx_strdel(&tmp);
    mx_strdel(&before);
    mx_strdel(&after);
    return str;
}
