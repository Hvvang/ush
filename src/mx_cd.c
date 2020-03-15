#include "ush.h"

static int get_type(const char *path) {
	char *tmp_path = NULL;
	struct stat stat;

	lstat(path, &stat);
	if (S_ISDIR(stat.st_mode))
		return MX_DIR;
	else if (S_ISREG(stat.st_mode))
		return MX_FILE;
	else if (S_ISLNK(stat.st_mode))
		return MX_LINK;
	else
		return MX_EFAULT;
}

static void handle_error(const char *command, int d_type) {
	fprintf(stderr, "u$h: cd: %s: ", command);
	if (d_type == MX_FILE || d_type == MX_LINK)
		fprintf(stderr, "Not a directory\n");
	if (d_type == MX_EFAULT)
		fprintf(stderr, "No such file or directory\n");
}

static char *create_path(const char *command, char flag) {
	char *path = NULL;
	char buff[PATH_MAX + 1];
	int d_type = get_type(command);

	if (d_type == MX_FILE || d_type == MX_EFAULT
		|| (d_type == MX_LINK && flag == 's'))
		handle_error(command, d_type);
	else {
		path = mx_create_path((char*)command, d_type, flag);
		path = mx_path_to_canonical(path);
	}
	return path;
}

void mx_cd(t_command *commands) {
	int index = 0;
	char flag = mx_check_flags(MX_CD, &index, commands->arguments, mx_valid_cd);
	char *path = NULL;

	if (!flag) {
		commands->exit = 1;
		return;
	}
	else if (commands->arguments[index]) {
		if (commands->arguments[index + 1]) {
			fprintf(stderr, "u$h: cd: too many arguments\n");
			commands->exit = 1;
			return;
		}
		else if (!strcmp(commands->arguments[index], "-")) {
			free(commands->arguments[index]);
			commands->arguments[index] = strdup(getenv("OLDPWD"));
			mx_cd(commands);
			if (!commands->exit)
				printf("%s\n", getenv("PWD"));
			return;
		}
	}
	else
		commands->arguments[index] = strdup(getenv("HOME"));
	path = create_path(commands->arguments[index], flag);

	if (!path)
		commands->exit = 1;
	else {
		chdir(path);
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", path, 1);
		mx_strdel(&path);
	}
}
