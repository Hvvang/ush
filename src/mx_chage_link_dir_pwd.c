#include "ush.h"

void mx_chage_link_dir_pwd(char *str) {
    chdir(str);
    setenv("PWD", str, 1);
	mx_ush_loop();
}
