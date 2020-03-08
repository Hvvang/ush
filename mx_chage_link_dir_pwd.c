#include "ush.h"

void mx_chage_link_dir_pwd(char *str) {
    // char *s = NULL;
    chdir(str);
    setenv("PWD", str, 1);
    // mx_strdel(&s);
    mx_ush_loop();
}
