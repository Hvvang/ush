#include "ush.h"

<<<<<<< HEAD
static void pwd_error(char *str) {
	fprintf(stderr, "%s", "u$h: pwd: ");
	fprintf(stderr, "%s", str);
	fprintf(stderr, "%s", ": ");
	fprintf(stderr, "%s\n", "invalid option");
	fprintf(stderr, "%s\n", "pwd: usage: pwd [-LP]");
	mx_ush_loop();
}

static int check_flag(char *str, t_command *commands) {
	int sw = 0;
	int len = mx_strlen(str);

	for (int i = len; str[i] != '-'; i--) {
		if (str[i] == 'L') {
			commands->fl[0] = 1;
			commands->fl[1] = 0;
			sw = 1;
		}
		if (str[i] == 'P') {
			commands->fl[0] = 0;
			commands->fl[1] = 1;
			sw = 1;
		}
	}
	return sw;
}

int mx_print_pwd(t_command *commands) {
=======
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

static void pwd_error(char *str, char *argv, t_command *command) {
	write(2, str, mx_strlen(str));
	if (argv != NULL) {
		write(2, argv, mx_strlen(argv));
	}
	write(2, "\n", 1);
	command->exit = 1;
	mx_ush_loop();
}

int mx_print_pwd(t_command *command) {
>>>>>>> fc9844dab0ba4ff53020527d03755d6729e482e5
	char s[1000];
	int arr[2] = {0, 0};

<<<<<<< HEAD
	commands->fl = arr;
	if (!commands->arguments[0] || commands->arguments[0][0] != '-')
		printf("%s\n", getenv("PWD"));
	else
		for (int i = 0; commands->arguments[i] ; i++) {
			if (check_flag(commands->arguments[i], commands) == 0)
				pwd_error(commands->arguments[i]);
			else {
				if (commands->fl[0] == 1)
					printf("%s\n", getenv("PWD"));
				if (commands->fl[1] == 1)
					printf("%s\n", getcwd(s, 1000));
			}
		}	
=======
	if (!command->arguments[0]) {
		printf("%s\n", getenv("PWD"));
	}
	else if (check_flag(command) == 0)
		pwd_error("pwd: too many arguments", NULL, command);
	else if (check_flag(command) == 1)
		printf("%s\n", getenv("PWD"));
	else if (check_flag(command) == 2)
		printf("%s\n", getcwd(s, 1000));
	else if (check_flag(command) == 3)
		printf("%s\n", getenv("PWD"));
	else if (check_flag(command) == 4)
		printf("%s\n", getcwd(s, 1000));
	else if (check_flag(command) == 0)
		pwd_error("pwd: bad option:", command->arguments[0], command);
>>>>>>> fc9844dab0ba4ff53020527d03755d6729e482e5
	return 0;
}
