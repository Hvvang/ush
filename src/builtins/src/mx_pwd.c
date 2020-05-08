#include "../inc/mx_builtins.h"

void mx_pwd(t_command *commands) {
	char s[PATH_MAX + 1];
	int index = 0;
	char flag = mx_check_flags(MX_PWD, &index, commands, mx_valid_pwd);

	if (!commands->exit) {
		if (flag == 'L')
			printf("%s\n", getenv("PWD"));
		if (flag == 'P')
			printf("%s\n", getcwd(s, PATH_MAX + 1));
	}
}
