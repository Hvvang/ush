#include "../inc/mx_builtins.h"
#define _BSD_SOURCE

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
		if (str[i] == '.' && str[i + 1] == '.'
			&& (str[i + 2] == '/' || !str[i + 2])) {
			get_ref_of_dir_up(buff, &index);
			i += 1;
		}
		else if (!(str[i] == '.' || (str[i] == '/' && buff[index - 1] == '/')))
			buff[index++] = str[i];
	}
	if (buff[index - 1] == '/' && strcmp(buff, "/"))
		buff[index - 1] = '\0';
	free(str);
	str = mx_strdup(buff);
	mx_strdel(&buff);
	return str;
}

static char *create_path(const char *command, char flag) {
	char *path = NULL;
    char buff[PATH_MAX + 1];

    if (flag == '0' || flag == 's') {
        if (command[0] != '/')
			path = mx_join_path(getenv("PWD"), command);
		else
			path = mx_strdup(command);
    }
    else {
		chdir(command);
		path = mx_strdup(getcwd(buff, PATH_MAX));
    }
	path = path_to_canonical(path);
    return path;
}

static void change_dir_and_env(t_command *command, int index, char flag) {
	char *path = path_to_canonical(command->arguments[index]);
	int d_type = mx_get_type(path);

	command->exit = 1;
	if (command->arguments[index + 1])
		mx_error_handle(MX_CD, path, MX_ANY);
	else if (d_type == MX_LINK && flag == 's')
		mx_error_handle(MX_CD, command->arguments[index], d_type);
	else if (errno)
		mx_error_handle(MX_CD, command->arguments[index], MX_EFAULT);
	else {
		command->exit = 0;
		path = create_path(path, flag);
		if (flag != 'P')
			chdir(path);
		if (strcmp(getenv("PWD"), path))
			setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", path, 1);
		mx_strdel(&path);
	}
}

void mx_cd(t_command *command) {
	int index = 0;
	char flag = mx_check_flags(MX_CD, &index, command, mx_valid_cd);

	if (!command->exit) {
		if (!command->arguments[index]) {
			command->arguments[index] = malloc(sizeof(char *) + 1);
			command->arguments[index] = mx_strdup(getenv("HOME"));
			command->arguments[index + 1] = NULL;
		}
		else if (!strcmp(command->arguments[index], "-")) {
			free(command->arguments[index]);
			command->arguments[index] = mx_strdup(getenv("OLDPWD"));
			mx_cd(command);
			if (!command->exit)
				printf("%s\n", getenv("PWD"));
			return;
		}
		change_dir_and_env(command, index, flag);
	}
}
