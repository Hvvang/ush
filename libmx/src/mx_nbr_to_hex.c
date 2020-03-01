#include "libmx.h"

static char* math_hex(unsigned long nbr, int len);

char *mx_nbr_to_hex(unsigned long nbr) {
    unsigned long num = nbr;
    int len = 0;
    char *str = NULL;
    
    if (nbr == 0) {
        str = mx_strnew(2);
        *str = '0';
        return str;
    }
    while (num != 0) {
        num = num / 16;
        len++;
    }
    return math_hex(nbr, len);
}

static char* math_hex(unsigned long nbr, int len) {
    int ost = 0;
    char *str = NULL;

    str = mx_strnew(len);
    for (int i = 0; i < len; i++ ) {
        ost = nbr % 16;
        nbr = nbr / 16;
        if (ost >= 0 && ost <= 9)
            ost += 48;
        if (ost >= 10 && ost <= 15)
            ost += 87;
        str[i] = ost;
    }
    mx_str_reverse(str);
    return str;
}
