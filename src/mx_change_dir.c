#include "ush.h"

static void change_dir(char *str) {
	char buff[PATH_MAX + 1];

	chdir(str);
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", getcwd(buff, PATH_MAX), 1);
}

static void return_old_pwd(void) {
	char buff[PATH_MAX + 1];

	if (!getenv("OLDPWD"))
		return ;
	else {
		setenv("PWD", getenv("OLDPWD"), 1);
		setenv("OLDPWD", getcwd(buff, PATH_MAX), 1);
		chdir(getenv("PWD"));
		printf("%s\n", getenv("PWD"));
	}
}

static int cd_home(t_command *commands) {
	if (!commands->arguments[0])
		return 1;
	if (!strcmp(commands->arguments[0], "--"))
		return 1;
	if (!strcmp(commands->arguments[0], "~"))
		return 1;
	return 0;
}

void mx_change_dir(t_command *commands) {

	if (cd_home(commands)) // go Home
		change_dir(getenv("HOME"));
	else if (strcmp(commands->arguments[0], "-") == 0) //back to oldpwd
		return_old_pwd();
	else if ((commands->fl[5] || commands->fl[7]) && !commands->arguments[1])
		return ;
	else
		mx_dir_file_link(commands);
}
