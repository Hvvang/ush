#include "ush.h"

char *mx_ush_read_line(void) {
  char *line = NULL;
  size_t bufsize = 1;

  getline(&line, &bufsize, stdin);	
  return line;
}
