#include "../inc/mx_builtins.h"

#define MX_NO_OPTIONS 1
#define MX_SUCCESS 0
#define MX_NOT_A_PARAM -1
#define MX_NOT_AN_IDENTIFIER "export: not an identifier:"

static int validation(char *command, bool *toggle) {
	if (command) {
		if ((!strcmp(command, "-") || !strcmp(command, "--")) && *toggle) {
			*toggle = !(*toggle);
			return MX_NOT_A_PARAM;
		}
		for (unsigned i = 0; command[i]; i++) {
			if (!isalpha(command[i]) || (i > 0 && !isdigit(command[i]))) {
				if (command[i] == '=')
					return MX_SUCCESS;
				fprintf(stderr, "%s %s\n", MX_NOT_AN_IDENTIFIER, command);
				return MX_NOT_A_PARAM;
			}
			return MX_SUCCESS;
		}
	}
	return MX_NO_OPTIONS;
}

static void sort_export(t_hash_table *hash_table, t_export *copy_export) {
	for (unsigned i = 0; i < hash_table->export_size; i++) {
		copy_export[i].key = mx_strdup(hash_table->export[i].key);
		if (hash_table->export[i].value)
			copy_export[i].value = strdup(hash_table->export[i].value);
		else
			copy_export[i].value = NULL;
	}
	for (unsigned i = 0; i < hash_table->export_size; i++) {
		for (unsigned j = 0; j < hash_table->export_size - i - 1; j++) {
			if (strcmp(copy_export[j].key, copy_export[j + 1].key) > 0) {
				char *temp_key = copy_export[j].key;
				char *temp_value = copy_export[j].value;

				copy_export[j].key = copy_export[j + 1].key;
				copy_export[j].value = copy_export[j + 1].value;
				copy_export[j + 1].key = temp_key;
				copy_export[j + 1].value = temp_value;
			}
		}
	}
}

static void export_print(t_hash_table *hash_table) {
	t_export copy_export[hash_table->export_size];

	sort_export(hash_table, &copy_export[0]);
	for (unsigned i = 0; i < hash_table->export_size; i++) {
		printf("%s=", copy_export[i].key);
		if (!copy_export[i].value || copy_export[i].value[0] == '\0')
			printf("\'\'");
		else if (mx_get_char_index(copy_export[i].value, '=') > 0
				 || mx_get_char_index(copy_export[i].value, ';') > 0)
			printf("\'%s\'", copy_export[i].value);
		else
			printf("%s", copy_export[i].value);
		printf("\n");
		mx_strdel(&copy_export[i].key);
		mx_strdel(&copy_export[i].value);
	}
}

void mx_export(t_command *command, t_hash_table *hash_table) {
	bool toggle = true;

	if (!command->arguments[0])
		export_print(hash_table);
	for (unsigned i = 0; command->arguments[i]; i++) {
		int valid_key = validation(command->arguments[i], &toggle);

		if (valid_key != MX_NOT_A_PARAM) {
			if (valid_key == MX_NO_OPTIONS)
				export_print(hash_table);
			else if (mx_create_variable(command->arguments[i], hash_table)) {
				if (hash_table->export[hash_table->export_size].value)
					setenv(hash_table->export[hash_table->export_size].key,
						   hash_table->export[hash_table->export_size].value,
						   1);
			}
		}
	}
}
