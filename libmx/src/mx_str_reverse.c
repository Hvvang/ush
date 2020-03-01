#include "libmx.h"

void mx_str_reverse(char *s) {
    int len = 0;
    int ind = 0;

    if (!s || !*s) return;
    len = mx_strlen(s);
    while (ind < len / 2){
        mx_swap_char(&s[ind], &s[len - ind - 1]);
        ind++;
    }
}
