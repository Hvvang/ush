#include "ush.h"

static void get_ref_of_dir_up(char *str, int *index) {
	int len = strlen(str) - 1;
	int count = 2;

	for (; len > 0 && count; len--) {
		if (str[len] == '/')
			count--;
		str[len] = '\0';
	}
	*index = len + 1;
}

static char *path_to_canonical(char *str) {
	char *buff = mx_strnew(strlen(str));
	int index = 0;

	for (int i = 0; str[i]; i++) {
		if ((str[i] == '.' || str[i] == '/') && str[i + 1] == '/')
			i += 1;
		else if (str[i] == '.' && str[i + 1] == '.'
				 && (str[i + 2] == '/' || !str[i + 2])) {
			get_ref_of_dir_up(buff, &index);
			i += 1;
		}
		else
			buff[index++] = str[i];
	}
	if (buff[index - 1] == '/')
		buff[index - 1] = '\0';
	free(str);
	str = strdup(buff);
	mx_strdel(&buff);
	return str;
}

static char *create_path(const char *command, char flag) {
	char *path = NULL;
    char buff[PATH_MAX + 1];

    if (flag == '0' || flag == 's') {
		char *tmp = NULL;

        if (command[0] == '/')
            tmp = strdup("\0");
        else
            tmp = mx_strjoin(getenv("PWD"), "/");
        path = mx_strjoin(tmp, command);
		mx_strdel(&tmp);
    }
    else if (flag == 'P') {
		chdir(command);
		path = strdup(getcwd(buff, PATH_MAX));
    }
	path = path_to_canonical(path);
    return path;
}

static void change_dir_and_env(t_command *commands, int index, char flag) {
	char *path = strdup(commands->arguments[index]);
	int d_type;

	path = create_path(path, flag);
	d_type = mx_get_type(path);
	if (commands->arguments[index + 1]) {
		mx_error_handle(MX_CD, path, MX_ANY);
		commands->exit = 1;
	}
	else if (d_type == MX_FILE || d_type == MX_EFAULT
		|| (d_type == MX_LINK && flag == 's')) {
		mx_error_handle(MX_CD, commands->arguments[index], d_type);
		commands->exit = 1;
	}
	else {
		chdir(path);
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", path, 1);
	}
	mx_strdel(&path);
}

void mx_cd(t_command *commands) {
	int index = 0;
	char flag = mx_check_flags(MX_CD, &index, commands, mx_valid_cd);
	char *path = NULL;

	if (!commands->exit) {
		if (!commands->arguments[index]) {
			commands->arguments[index] = strdup(getenv("HOME"));
		}
		else if (!strcmp(commands->arguments[index], "-")) {
			free(commands->arguments[index]);
			commands->arguments[index] = strdup(getenv("OLDPWD"));
			mx_cd(commands);
			if (!commands->exit)
				printf("%s\n", getenv("PWD"));
			return;
		}
		change_dir_and_env(commands, index, flag);
	}
}
