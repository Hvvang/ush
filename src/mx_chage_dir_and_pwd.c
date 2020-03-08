#include "ush.h"

static int is_link(char *str) { // clean mem
	struct stat st;

	lstat(str, &st);
	if (S_ISLNK(st.st_mode)){ //если линк
    	return 1;
    }
    return 0;
}

static void get_log() {
	char *str = mx_strnew(200);
	char *s = NULL;

	str = getcwd(s, 1000);
	printf("%s\n", str);

	mx_strdel(&s);
	mx_strdel(&str);
}

void mx_chage_dir_and_pwd(char *str) {
	char *s = NULL;

	if (is_link(getenv("PWD"))) {
		get_log();
	}
	else {
		setenv("OLDPWD", getenv("PWD"), 1);
	    chdir(str);
		setenv("PWD", getcwd(s, 1000), 1);
	}
	free(s);
	mx_ush_loop();
}
