#include "libmx.h"

int mx_calc_num(int number) {
    long num = 0;
    int len = 0;

    num = number;
    if(num == 0)
        return 1;
    num = number;
    if (num < 0) {
        num *= -1;
        len = 1;
    }
    for (; num > 0; len++) {
        num /= 10;
    }
    return len;
}
