#include "ush.h"

static int check_flag(t_command *command) {
	// доделать проверку на флаг ли это
	for (int i = 0; command->arguments[i]; i++) {
		if (mx_strcmp(command->arguments[0], "-L") == 0)
			return 1;
		else if (mx_strcmp(command->arguments[0], "-P") == 0)
			return 2;
		else if (mx_strcmp(command->arguments[0], "-PL") == 0)
			return 3;
		else if (mx_strcmp(command->arguments[0], "-LP") == 0)
			return 4;
	}
	return 0;
}

static void pwd_error(char *str, char *argv) {
	write(2, str, mx_strlen(str));
	if (argv != NULL) {
		write(2, argv, mx_strlen(argv));
	}
	write(2, "\n", 1);
	command->exit = 1;
	mx_ush_loop();
}

int mx_print_pwd(t_command *command) {
	char s[1000];

	if (!command->arguments[0]) {
		printf("%s\n", getenv("PWD"));
	}
	else if (check_flag(command) == 0)
		pwd_error("pwd: too many arguments", NULL);
	else if (check_flag(command) == 1)
		printf("%s\n", getenv("PWD"));
	else if (check_flag(command) == 2)
		printf("%s\n", getcwd(s, 1000));
	else if (check_flag(command) == 3)
		printf("%s\n", getenv("PWD"));
	else if (check_flag(command) == 4)
		printf("%s\n", getcwd(s, 1000));
	else if (check_flag(command) == 0)
		pwd_error("pwd: bad option:", command->arguments[0]);
	return 0;
}
