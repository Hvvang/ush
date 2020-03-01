#include "libmx.h"

static void print_int(int n);

void mx_printint(int n) {
    if (n == -2147483648) {
        mx_printchar('-');
        mx_printint(214748364);
        mx_printchar('8');
    }
    else
        print_int(n);
}

static void print_int(int n) {
    if (n < 0) {
        mx_printchar('-');
        n *= -1;
        mx_printint(n);
    }
    else if (n > 9) {
        int r = n % 10;
        n /= 10;
        mx_printint(n);
        mx_printchar(r + '0');
    } 
    else
        mx_printchar(n + '0');
    }
