#include "ush.h"
// Переход по аргументам с флагами и без для папок

static char *dell_path(char *str) {
	int len = strlen(str);

	for (int i = len; i > 0; i--) {
		if (str[i] == '/')
			break;
		str[i] = '\0';
	}
	return str;
}

static void is_flag_p(t_command *cmd, char *dest, char *buff) {
	if (cmd->arguments[1][0] && cmd->arguments[1][1] ==
	'.' && !cmd->arguments[1][2]) {
		dest = getcwd(dest, PATH_MAX);
		setenv("OLDPWD", getenv("PWD"), 1);
		chdir(dell_path(dest));
		setenv("PWD", getcwd(dest, PATH_MAX), 1);	
	}
	else {
		chdir(cmd->arguments[1]);
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", getcwd(buff, PATH_MAX), 1);
	}
}

static void is_flag_s(t_command *cmd, char *dest, char *buff) {
	if (cmd->arguments[1][0] && cmd->arguments[1][1] ==
	'.' && !cmd->arguments[1][2]) {
		dest = getenv("PWD");
		setenv("OLDPWD", getenv("PWD"), 1);
		chdir(dell_path(dest));
		setenv("PWD", getcwd(dest, PATH_MAX), 1);	
	}
	else {
		chdir(cmd->arguments[1]);
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", getcwd(buff, PATH_MAX), 1);
	}
}

void mx_go_dir(t_command *cmd) {
	char buff[PATH_MAX + 1];
	char *dest = malloc(sizeof(char) * strlen(getenv("PWD")) + 1);
	
	if (cmd->fl[7])
		is_flag_p(cmd, dest, buff);
	else if (cmd->fl[8])
		is_flag_s(cmd, dest, buff);
	else {
		if (cmd->arguments[0][0] && cmd->arguments[0][1] ==
			'.' && !cmd->arguments[0][2]) {
			dest = getenv("PWD");
			setenv("OLDPWD", getenv("PWD"), 1);
			chdir(dell_path(dest));
			setenv("PWD", getcwd(dest, PATH_MAX), 1);	
		}
		else {
			chdir(cmd->arguments[0]);
			setenv("OLDPWD", getenv("PWD"), 1);
			setenv("PWD", getcwd(buff, PATH_MAX), 1);
		}
	}
}
