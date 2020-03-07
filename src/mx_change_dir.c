#include "ush.h"

static int check_flag(cmd_bl *cmd) {
	int size = 0;

	for (int i = 0; cmd->argv[i]; i++) {
		size = mx_strlen(cmd->argv[i]);
		if ((cmd->argv[i][0] == '-' && size > 1) && mx_strcmp(cmd->argv[0], "--") != 0)
			return 1;
	}
	return 0;
}

static int is_dir(char *str) { // clean mem
	struct stat st;

	lstat(str, &st);
	if (S_ISLNK(st.st_mode)) //если линк
		return 10;
	if (!S_ISDIR(st.st_mode) && !S_ISREG(st.st_mode))  // если не папка или не существует
		return 0;
	if (S_ISREG(st.st_mode)) // если не файл или несуществует
		return 5;
    return 1;
}

static void cd_error(char *str, char *file_name, cmd_bl *cmd) {
	write(2, str, mx_strlen(str));
	write(2, file_name ,mx_strlen(file_name));
	write(2, "\n", 1);
	cmd->exit = 1;
	mx_ush_loop();
}

static int got_to_lvl_up (cmd_bl *cmd) {
	if (mx_strcmp(cmd->argv[0], "..") == 0)
		return 1;
	if (mx_strcmp(cmd->argv[0], "../") == 0)
		return 1;
	return 0;
}

static void mx_dir_or_file(cmd_bl *cmd) { //проверка аргументов
	if (is_dir(cmd->argv[0]) == 0) // если не папка или не существует													
    	cd_error(NO_F_OR_D, cmd->argv[0], cmd);
    else if (is_dir(cmd->argv[0]) == 5) 	// елси не файл и не существует									
    	cd_error(NO_D, cmd->argv[0], cmd);
    else if (is_dir(cmd->argv[0]) == 10) // если линк
    	mx_chage_link_dir_pwd(cmd->argv[0]);
    else if (got_to_lvl_up(cmd)) // перейти на уровень выше
    	mx_chage_dir_and_pwd("..");
    else if ((is_dir(cmd->argv[0]) || is_dir(cmd->argv[1])) && !cmd->argv[2]) //если 2 аргумент
		cd_error(STR_NO_PWD, cmd->argv[0], cmd);
	else if (cmd->argv[0] && cmd->argv[1] && cmd->argv[2]) { // если 3 аргумента
		write(2, MANY_ARGV, 22);
		write(2, "\n", 1);
		cmd->exit = 1;
		mx_ush_loop();
	}
	else //перейти по аргументу
    	mx_chage_dir_and_pwd(cmd->argv[0]);
}

void mx_change_dir(cmd_bl *cmd) {
	if ((!cmd->argv[0] || mx_strcmp(cmd->argv[0], "--") == 0) ||
	mx_strcmp(cmd->argv[0], "~") == 0) { //cd && cd -- && cd ~
		mx_chage_dir_and_pwd(getenv("HOME"));
	}
	else if (check_flag(cmd) == 1)
		printf("flag\n");																					
	else
		mx_dir_or_file(cmd);																				
} 

