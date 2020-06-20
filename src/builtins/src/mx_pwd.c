#include "mx_builtins.h"

#define MX_FLAG 0
#define MX_BAD_OPTION -1
#define MX_MANY_ARGS -2
#define MX_PWD_DEFAULT 'L'

static int validation(char **args, char *flag) {
	int toggle = 1;

	for (unsigned i = 0; args[i]; i++) {
		if (!strcmp(args[i], "--") || !strcmp(args[i], "-")) {
			*flag = MX_PWD_DEFAULT;
			toggle = 0;
		}
	    else if (args[i][0] == '-') {
	        for (unsigned j = 1; args[i][j]; j++) {
	            *flag = args[i][j];
	            if (args[i][j] != 'L' && args[i][j] != 'P')
					return MX_BAD_OPTION;
	        }
	    }
		else
			return MX_MANY_ARGS;
		if ((!toggle && args[i + 1]))
			return MX_MANY_ARGS;
	}
	return MX_FLAG;
}

static char get_flag(t_command *command) {
	char flag = MX_PWD_DEFAULT;
	int error = validation(command->arguments, &flag);

	setenv("status", "0", 1);
	if (error) {
		if (error == MX_MANY_ARGS)
			fprintf(stderr, "pwd: too many arguments\n");
		else if (error == MX_BAD_OPTION)
			fprintf(stderr, "pwd: bad option: -%c\n", flag);
		setenv("status", "1", 1);
	}
	return flag;
}

void mx_pwd(t_command *command) {
	char str[PATH_MAX + 1];
	char flag = get_flag(command);

	if (!atoi(getenv("status"))) {
		if (flag == 'L')
			printf("%s\n", getenv("PWD"));
		if (flag == 'P')
			printf("%s\n", getcwd(str, PATH_MAX + 1));
	}
}
