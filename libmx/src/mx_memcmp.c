#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    char *s1_1 = (char *)s1;
    char *s2_2 = (char *)s2;

   while ((n--) && (*s1_1) && (*s2_2)) {
        if (*s1_1 != *s2_2)
            return *s1_1 - *s2_2;
        s1_1++;
        s2_2++;
    }
    return 0;
}
