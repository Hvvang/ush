#include "ush.h"

static int is_link(char *str) { // clean mem
	struct stat st;

	lstat(str, &st);
	if (S_ISLNK(st.st_mode)){ //если линк
    	return 1;
    }
    return 0;
}

<<<<<<< HEAD
static void get_log(char *str) {
	char *lst = mx_strnew(200);
	char *s = NULL;

	lst = getcwd(s, 1000);

	mx_strdel(&s);
	mx_strdel(&str);
	mx_ush_loop();
=======
static void get_log() {
	char *str = mx_strnew(200);
	char *s = NULL;

	str = getcwd(s, 1000);
	str = mx_strjoin(str, "/../");
	chdir("..");
	printf("%s\n", getcwd(s, 1000));

	mx_strdel(&s);
	mx_strdel(&str);
>>>>>>> fc9844dab0ba4ff53020527d03755d6729e482e5
}

void mx_chage_dir_and_pwd(char *str) {
	char *s = NULL;

	if (is_link(getenv("PWD"))) {
<<<<<<< HEAD
		get_log(str);
=======
		get_log();
>>>>>>> fc9844dab0ba4ff53020527d03755d6729e482e5
	}
	else {
		setenv("OLDPWD", getenv("PWD"), 1);
	    chdir(str);
		setenv("PWD", getcwd(s, 1000), 1);
	}
	free(s);
}
