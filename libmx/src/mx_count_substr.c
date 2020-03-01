#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    char *tmp = (char *)str;
    int count = 0;
    int i = 0;

    if (str == NULL || sub == NULL)
        return -1;
    if (sub[0] == '\0' && str[0] == '\0')
        return 1;
    if (sub[0] == '\0' || str[0] == '\0')
        return 0;
    while (mx_get_substr_index(tmp, sub) >= 0) {
        i = mx_get_substr_index(tmp, sub);
        tmp += mx_strlen(sub) + i;
        count++;
    }
    return count;
}
