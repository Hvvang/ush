#include "libmx.h"

void mx_del_strarr(char ***arr) {
   int i = 0;

   while (arr[i]) {
       mx_strdel(arr[i]);
       i++;
   }
   free(*arr);
   *arr = NULL;
}
