#include "ush.h"

void mx_chage_link_dir_pwd(char *str) {
	char *s = NULL;
	char *d = malloc(sizeof(char) * 500);

	printf("cwd = %s\n", getcwd(s, 1000));
    printf("env = %s\n", getenv("PWD"));
    printf("old = %s\n", getenv("OLDPWD"));
    realpath(str, d);
    printf("%s\n", d);
    chdir(str);

    printf("---------------\n");

    printf("cwd = %s\n", getcwd(s, 1000));
    printf("env = %s\n", getenv("PWD"));
    printf("old = %s\n", getenv("OLDPWD"));
    realpath(str, d);
    printf("%s\n", d);
    
	mx_ush_loop();
}
