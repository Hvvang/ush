#include "libmx.h"

double mx_pow(double n, unsigned int pow) {
    double sum = 1;

    if (pow == 0)
        return sum;
    while (pow > 0) {
        sum = sum * n;
        pow--;
    }
    return sum;
}
