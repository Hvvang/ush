#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
     size_t i = 0;
     unsigned char* str = (unsigned char*)s;

     while (i < n)
     {
          if (str[i] != c)
               i++;
          else 
               return &str[i];
     }
     return NULL;
}
