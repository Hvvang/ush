#include "ush.h"

static int is_dir(t_command *commands) { // clean mem
	struct stat st;

	if (commands->fl[7] || commands->fl[5])
		lstat(mx_curl_normal(commands->arguments[1]), &st);
	else
		lstat(mx_curl_normal(commands->arguments[0]), &st);

	if (S_ISDIR(st.st_mode) && !S_ISREG(st.st_mode))  // папка
		return 1;
	else if (S_ISREG(st.st_mode)) // файл
		return 2;
	else if (S_ISLNK(st.st_mode)) //линк
		return 3;
    return 0;
}

static void is_link(t_command *commands, char *buff, char *dest) {
	if (commands->arguments[1][0] == '/') { // если переход от корня
		chdir(commands->arguments[1]);
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", getcwd(dest, PATH_MAX), 1);
	}
	else {
		chdir(commands->arguments[1]);
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", getcwd(buff, PATH_MAX), 1);
	}
}

static void go_link(t_command *commands) {
	char *buff = NULL;
	char dest[PATH_MAX + 1];

	if (commands->fl[5] || commands->fl[7]) // переход по линке с флагами
		is_link(commands, buff, dest);
	else {  
		if (commands->arguments[0][0] == '/') {  // переход по линке без флагов
			
			chdir(commands->arguments[0]);
			setenv("OLDPWD", getenv("PWD"), 1);
			setenv("PWD", commands->arguments[0], 1);
		}
		else {
			chdir(mx_curl_normal(commands->arguments[0]));
			buff = mx_strjoin(getenv("PWD"), "/");
			setenv("OLDPWD", getenv("PWD"), 1);
			setenv("PWD", mx_strjoin(buff,
			mx_curl_normal(commands->arguments[0])), 1);
		}
	}
}

void mx_dir_file_link(t_command *commands) {
	if (is_dir(commands) == 0) // если не папка, файл, линк
		mx_cd_error(commands, 1);
	if (is_dir(commands) == 1) //если папка
		mx_go_dir(commands);
	if (is_dir(commands) == 2) // если файл
		mx_cd_error(commands, 2);
	if (is_dir(commands) == 3) // если линк link/ - не работает, найти решение
		go_link(commands);
}
