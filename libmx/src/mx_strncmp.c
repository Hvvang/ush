#include "libmx.h"

int mx_strncmp(const char *s1, const char *s2, int n) {
    int res = 0;
    
    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            res = s1[i] - s2[i];
        }
    }
    return res;
}
