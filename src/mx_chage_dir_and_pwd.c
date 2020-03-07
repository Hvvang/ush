#include "ush.h"

static int is_link(char *str) { // clean mem
	struct stat st;

	lstat(str, &st);
	if (S_ISLNK(st.st_mode)){ //если линк
    	return 1;
    }
    return 0;
}

static void get_log(void) {
	// char *pwd = getenv("PWD");
	// char *dest = (char*)malloc(sizeof(char) * 100);
	// int size = mx_strlen(pwd);
	// int count = 0;

	// for (int i = 0; size > 0; size--) {
	// 	if (pwd[size] != '/')
	// }
	// mx_strdel(&dest);
}

void mx_chage_dir_and_pwd(char *str) {
	char *s = NULL;

	if (is_link(getenv("PWD"))) {
		get_log();
		setenv("OLDPWD", getenv("PWD"), 1);
	    chdir(str);
		setenv("PWD", getcwd(s, 1000), 1);
	}
	else {
		setenv("OLDPWD", getenv("PWD"), 1);
	    chdir(str);
		setenv("PWD", getcwd(s, 1000), 1);
	}
	free(s);
	mx_ush_loop();
}
