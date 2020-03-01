#include "libmx.h"

int mx_sqrt(int x)
{
    int l = 0;
    int r = 0; 
    int c = 0;

    r = x;
    if (x < 0)
        return 0;
    if (x == 2147483647)
        return 0;
    while (l <= r) {
        c = ( l + r ) / 2;
        if(c * c == x)
            return c;
        if(c * c > x)
            r = c - 1;
        if(c * c < x)
          l = c + 1;
    }
    return 0;
}
