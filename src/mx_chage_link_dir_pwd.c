#include "ush.h"

void mx_chage_link_dir_pwd(char *str) {
<<<<<<< HEAD
    // char *s = NULL;
    chdir(str);
    setenv("PWD", str, 1);
    // mx_strdel(&s);
    mx_ush_loop();
=======
    chdir(str);
    setenv("PWD", str, 1);
	mx_ush_loop();
>>>>>>> fc9844dab0ba4ff53020527d03755d6729e482e5
}
