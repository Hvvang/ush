#include "ush.h"

static int check_flag(cmd_bl *cmd) {
	// доделать проверку на флаг ли это
	for (int i = 0; cmd->argv[i]; i++) {
		if (mx_strcmp(cmd->argv[0], "-L") == 0)
			return 1;
		else if (mx_strcmp(cmd->argv[0], "-P") == 0)
			return 2;
		else if (mx_strcmp(cmd->argv[0], "-PL") == 0)
			return 3;
		else if (mx_strcmp(cmd->argv[0], "-LP") == 0)
			return 4;
	}
	return 0;
}

static void pwd_error(char *str, cmd_bl *cmd, char *argv) {
	write(2, str, mx_strlen(str));
	if (argv != NULL) {
		write(2, argv, mx_strlen(argv));
	}
	write(2, "\n", 1);
	cmd->exit = 1;
	mx_ush_loop();
}

int mx_print_pwd(cmd_bl *cmd) {
	char s[1000];

	if (cmd->argv[0] == NULL) {
		printf("%s\n", getenv("PWD"));
	}
	else if (check_flag(cmd) == 0)
		pwd_error("pwd: too many arguments", cmd, NULL);
	else if (check_flag(cmd) == 1)
		printf("%s\n", getenv("PWD"));
	else if (check_flag(cmd) == 2) 
		printf("%s\n", getcwd(s, 1000));
	else if (check_flag(cmd) == 3)
		printf("%s\n", getenv("PWD"));
	else if (check_flag(cmd) == 4)
		printf("%s\n", getcwd(s, 1000));
	else if (check_flag(cmd) == 0)
		pwd_error("pwd: bad option:", cmd, cmd->argv[0]);
	return 0;
}
