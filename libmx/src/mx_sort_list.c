#include "libmx.h"

static void swap(t_list *a, t_list *b);

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *a, void *b)) {
    t_list *i;
    t_list *j;

    for (i = lst; i != NULL; i = i->next) {
          for (j = i; j->next != NULL; j = j->next) {
            if (cmp (i->data, j->next->data) > 0)
              swap (i, j->next);
      }
    }
   return lst;
}
static void swap(t_list *a, t_list *b) {
    void *temp = a->data;
    
    a->data = b->data;
    b->data = temp;
}
