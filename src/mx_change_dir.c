#include "ush.h"

static void change_dir(char *str) {
	char buff[PATH_MAX + 1];

	chdir(str);
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", getcwd(buff, PATH_MAX), 1);
}

static void return_old_pwd(void) {
	char buff[PATH_MAX + 1]; // добавить обработку флагов

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
	if (!commands->arguments[0]) {
		return 1;
	}
	if (!strcmp(commands->arguments[0], "--")) {

		return 1;
	}
	if (commands->arguments[0][0] == '~' && commands->arguments[0][1] != '\0')
		return 2;
	if (!strcmp(commands->arguments[0], "~") && commands->arguments[0][1] == '\0') {
		return 1;
	}
	return 0;
}
static void change_dir_home(char *str) {
	char buff[PATH_MAX + 1];
	int size = strlen(str);
	char *way = malloc(sizeof(char*) * size);
	char *dst = malloc(sizeof(char*) * strlen(getenv("HOME")) + size);

	for (int i = 0; i < size - 1; i++) {
		way[i] = str[i + 1];
		way[i + 1] = '\0';
	}
	dst = mx_strjoin(getenv("HOME"), way); // проверка на то существует ли путь????
	chdir(dst);
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", getcwd(buff, PATH_MAX), 1);
	mx_strdel(&way);
	mx_strdel(&dst);
}

void mx_change_dir(t_command *commands) {

	if (cd_home(commands) == 1) {
		change_dir(getenv("HOME"));
	}
	else if (cd_home(commands) == 2) {
		change_dir_home(commands->arguments[0]);
	} 
	else if (strcmp(commands->arguments[0], "-") == 0) //back to oldpwd
		return_old_pwd();
	else if ((commands->fl[8] || commands->fl[7]) && !commands->arguments[1])
		return ;
	else
		mx_dir_file_link(commands);
}
