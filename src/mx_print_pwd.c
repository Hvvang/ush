#include "ush.h"

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
	char s[1000];
	int arr[2] = {0, 0};

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
	return 0;
}
