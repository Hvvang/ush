#include "ush.h"

static int is_link(char *str) { // clean mem
	struct stat st; // leak

	lstat(str, &st);
	if (S_ISLNK(st.st_mode)) //если линк
    	return 1;
    return 0;
}

static void get_log(char *str) {
	chdir(str);
	return ;
}

void mx_chage_dir_and_pwd(char *str) {
	char buff[PATH_MAX + 1]; // leak

	if (is_link(getenv("PWD"))) {
		get_log(str);
	}
	else {
		setenv("OLDPWD", getenv("PWD"), 1);
	    chdir(str);
		setenv("PWD", getcwd(buff, PATH_MAX + 1), 1);
	}
}
