#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
     size_t i = n;
     unsigned char* str = (unsigned char*)s;

     while (i > 0) {
          if (str[i] != c)
               i--;
          else 
               return &str[i];
     }
     return NULL;

}
