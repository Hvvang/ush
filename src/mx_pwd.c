#include "ush.h"

// static void pwd_error(char *str) {
// 	fprintf(stderr, "%s", "u$h: pwd: ");
// 	fprintf(stderr, "%s", str);
// 	fprintf(stderr, "%s", ": ");
// 	fprintf(stderr, "%s\n", "invalid option");
// 	fprintf(stderr, "%s\n", "pwd: usage: pwd [-LP]");
// 	return ;
// }

// static int this_flag(t_command *commands) {
// 	if (!commands->arguments[0])
// 		return 0;
// 	if (commands->arguments[0][0] == '-' && !commands->arguments[0][1])
// 		return 0;
// 	if (commands->arguments[0][0] != '-')
// 		return 0;
// 	return 1;
// }

int mx_pwd(t_command *commands) {
	char s[PATH_MAX + 1];
	char flag = mx_check_flags(MX_PWD, commands->arguments, mx_valid_pwd);

	if (!flag)
		commands->exit = 1;
	else {
		if (flag == 'P')
			printf("%s\n", getenv("PWD"));
		if (flag == 'L')
			printf("%s\n", getcwd(s, PATH_MAX + 1));
	}
	// if (!this_flag(commands))
	// 	printf("%s\n", getenv("PWD"));
	// else {
	// 	if (commands->fl[5] == 1)
	// 		printf("%s\n", getenv("PWD"));
	// 	else if (commands->fl[7] == 1)
	// 		printf("%s\n", getcwd(s, 1000));
	// 	else
	// 		pwd_error(commands->arguments[0]);
	// 	}
	return 0;
}
