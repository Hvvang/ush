#include "ush.h"

static int get_len_unset(char *str) {
	int len = 0;

	for (int i = 0; str[i]; i++)
		len++;
	return len;
}

static void dell_from_env(t_command *commands, t_env *env) {
	int env_size = mx_get_array_size(env->env);
	int unset_size = mx_get_array_size(commands->arguments);
	int len = 0;

	for (int i = 0; i < unset_size; i++) {
		for (int j = 0; j < env_size; j++) {
			len = get_len_unset(commands->arguments[i]);
			if (strncmp(env->env[j], commands->arguments[i], len) == 0)
				j++;
		}
	}
}

void mx_unset(t_command *commands, t_env *env) {
	dell_from_env(commands, env);
}
