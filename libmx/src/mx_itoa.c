#include "libmx.h"

char *mx_itoa(int number) {
     int res = 0;
     long num = number;
     int len = mx_calc_num(number);
     char* str = mx_strnew(len);

     if (num < 0) {
          str[0] = '-';
          num *= -1;
     }
     if (num == 0) {
          str[0] = 0 + '0';
          return str;
     }
     len--;
     for (; num > 0; len--) {
          res = num % 10;
          str[len] = res + '0';
          num /= 10;
     }
     return str;
}
