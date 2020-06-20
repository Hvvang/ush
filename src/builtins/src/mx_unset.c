#include "mx_builtins.h"

#define MX_NOT_ENOUGH_ARGS "unset: not enough arguments\n"
#define MX_INVALID_NAME "unset: %s: invalid parameter name\n"
#define MX_NO_OPTIONS 1
#define MX_SUCCESS 0
#define MX_NOT_A_PARAM -1

static int validation(char **arg, bool *toggle) {
	if ((!strcmp(*arg, "-") || !strcmp(*arg, "--")) && *toggle) {
		*toggle = !(*toggle);
		if (!*(++arg)) {
			setenv("status", "1", 1);
			fprintf(stderr, MX_NOT_ENOUGH_ARGS);
		}
		return MX_NOT_A_PARAM;
	}
	for (unsigned i = 0; (*arg)[i]; i++) {
		if (!isalpha((*arg)[i]) && (i > 0 && !isdigit((*arg)[i]))) {
			setenv("status", "1", 1);
			fprintf(stderr, MX_INVALID_NAME, (*arg));
			return MX_NOT_A_PARAM;
		}
		if (!(*arg)[i + 1])
			return MX_SUCCESS;
	}
	return MX_NO_OPTIONS;
}

static void del_arg(char *arg, t_hash_table *hash_table) {
	for (unsigned i = 0; i < hash_table->export_size; i++) {
		if (strstr(hash_table->export[i].key, arg)) {
			free(hash_table->export[i].key);
			free(hash_table->export[i].value);
			for (; i < hash_table->export_size - 1; i++) {
				char *key = hash_table->export[i + 1].key;
				char *value = hash_table->export[i + 1].value;

				hash_table->export[i].key = strdup(key);
				hash_table->export[i].value = strdup(value);
				free(hash_table->export[i + 1].key);
				free(hash_table->export[i + 1].value);
			}
			hash_table->export_size--;
		}
	}
}

void mx_unset(t_command *command, t_hash_table *hash_table) {
	bool toggle = true;

	setenv("status", "0", 1);
	if (command->arguments[0]) {
		for (unsigned i = 0; command->arguments[i]; i++) {
			if (validation(&command->arguments[i], &toggle) == MX_SUCCESS) {
				del_arg(command->arguments[i], hash_table);
				unsetenv(command->arguments[i]);
			}
		}
	}
	else {
		setenv("status", "1", 1);
		fprintf(stderr, MX_NOT_ENOUGH_ARGS);
	}
}
