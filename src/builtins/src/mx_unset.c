#include "../inc/mx_builtins.h"

#define MX_INVALID_NAME "invalid parameter name"
#define MX_NO_OPTIONS 1
#define MX_SUCCESS 0
#define MX_NOT_A_PARAM -1

static int validation(char *arg, bool *toggle) {
	if ((!strcmp(arg, "-") || !strcmp(arg, "--")) && *toggle) {
		*toggle = !(*toggle);
		return MX_NOT_A_PARAM;
	}
	for (unsigned i = 0; arg[i]; i++) {
		if (!isalpha(arg[i]) || (i > 0 && !isdigit(arg[i]))) {
			fprintf(stderr, "unset: %s: %s\n", arg, MX_INVALID_NAME);
			return MX_NOT_A_PARAM;
		}
		return MX_SUCCESS;
	}
	return MX_NO_OPTIONS;
}

static void del_arg(char *arg, t_env *env) {
	for (unsigned i = 0; env->export[i]; i++) {
		if (strstr(env->export[i], arg)) {
			char **parameter = mx_strsplit(env->export[i], '=');

			if (!strcmp(parameter[0], arg)) {
				for ( ; env->export[i]; i++) {
					mx_strdel(&(env->export[i]));
					if (env->export[i + 1])
						env->export[i] = mx_strdup(env->export[i + 1]);
					else
						env->export[i] = NULL;
				}
				mx_del_strarr(&parameter);
				return ;
			}
			mx_del_strarr(&parameter);
		}
	}
}

void mx_unset(t_command *command, t_env *env) {
	bool toggle = true;

	for (unsigned i = 0; command->arguments[i]; i++) {
		if (validation(command->arguments[i], &toggle) == MX_SUCCESS) {
			del_arg(command->arguments[i], env);
		}
	}
}
