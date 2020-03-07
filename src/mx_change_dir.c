#include "ush.h"

static int check_flag(t_command *command) {
	int size = 0;

	for (int i = 0; command->arguments[i]; i++) {
		size = strlen(command->arguments[i]);
		if ((command->arguments[i][0] == '-' && size > 1) && strcmp(command->arguments[0], "--"))
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

static void cd_error(char *str, char *file_name) {
	write(2, str, strlen(str));
	write(2, file_name ,strlen(file_name));
	write(2, "\n", 1);
	command->exit = 1;
	mx_ush_loop();
}

static int got_to_lvl_up (t_command *command) {
	if (strcmp(command->arguments[0], "..") == 0)
		return 1;
	if (strcmp(command->arguments[0], "../") == 0)
		return 1;
	return 0;
}

static void mx_dir_or_file(t_command *command) { //проверка аргументов
	if (is_dir(command->arguments[0]) == 0) // если не папка или не существует
    	cd_error(NO_F_OR_D, command->arguments[0]);
    else if (is_dir(command->arguments[0]) == 5) 	// елси не файл и не существует
    	cd_error(NO_D, command->arguments[0]);
    else if (is_dir(command->arguments[0]) == 10) // если линк
    	mx_chage_link_dir_pwd(command->arguments[0]);
    else if (got_to_lvl_up(command)) // перейти на уровень выше
    	mx_chage_dir_and_pwd("..");
    else if ((is_dir(command->arguments[0]) || is_dir(command->arguments[1])) && !command->arguments[2]) //если 2 аргумент
		cd_error(STR_NO_PWD, command->arguments[0]);
	else if (command->arguments[0] && command->arguments[1] && command->arguments[2]) { // если 3 аргумента
		write(2, MANY_ARGV, 22);
		write(2, "\n", 1);
		command->exit = 1;
		mx_ush_loop();
	}
	else //перейти по аргументу
    	mx_chage_dir_and_pwd(command->arguments[0]);
}

void mx_change_dir(t_command *command) {
	if ((!command->arguments[0] || !strcmp(command->arguments[0], "--")) ||
		 !strcmp(command->arguments[0], "~")) { //cd && cd -- && cd ~
		mx_chage_dir_and_pwd(getenv("HOME"));
	}
	else if (check_flag(command) == 1)
		printf("flag\n");
	else
		mx_dir_or_file(command);
}
