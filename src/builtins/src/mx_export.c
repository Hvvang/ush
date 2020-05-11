#include "../inc/mx_builtins.h"
#define MX_NO_OPTIONS 1
#define MX_SUCCESS 0
#define MX_ERROR -1
#define MX_NOT_AN_IDENTIFIER "export: not an identifier:"

static int validation(char **args) {
	if (args[0]) {
		if (!isalpha(args[0][0])) {
			fprintf(stderr, "%s %s\n", MX_NOT_AN_IDENTIFIER, args[0]);
			return MX_ERROR;
		}
		return MX_SUCCESS;
	}
	return MX_NO_OPTIONS;
}

static char *append_arg(char **args) {
	char *new_arg = NULL;
	char *temp = mx_strjoin(args[0], "=");

	if (args[1])
		new_arg = mx_strjoin(temp, args[1]);
	else
		new_arg = mx_strjoin(temp, "''");
	mx_strdel(&temp);
	return new_arg;
}

static void paste_arg(char **args, t_env *env) {
	unsigned i = 0;

	for (; env->export[i]; i++) {
		if (env->export[i][0] == args[0][0]) {
			char **parameter = mx_strsplit(env->export[i], '=');

			if (!strcmp(parameter[0], args[0])) {
				free(env->export[i]);
				env->export[i] = append_arg(args);
				mx_del_strarr(&parameter);
				return ;
			}
			mx_del_strarr(&parameter);
		}
	}
	env->export[i] = malloc(sizeof(char *) + 1);
	env->export[i++] = append_arg(args);
	env->export[i] = NULL;
	mx_quicksort(env->export, 0, i - 1);
}

void mx_export(t_command *command, t_env *env) {
	if (!command->arguments[0]) {
		mx_print_strarr(env->export, "\n");
		printf("\n");
	}
	for (unsigned i = 0; command->arguments[i]; i++) {
		char **args = mx_strsplit(command->arguments[i], '=');

		if (validation(args) != MX_ERROR) {
			paste_arg(args, env);
		}
		if (args)
			mx_del_strarr(&args);
	}
}
