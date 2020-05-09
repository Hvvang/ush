#include "../inc/mx_builtins.h"

static void export_unset_error(char *str, char *builtin, int er_case) {
	fprintf(stderr, "%s", builtin);
	fprintf(stderr, "%s", str);
	fprintf(stderr, "%s\n", "': not a valid identifier");
	if (!strcmp(builtin, "u$h: export: `") && er_case == 0){
		fprintf(stderr, "%s", "export: usage: export [-nf]");
		fprintf(stderr, "%s\n", " [name[=value] ...]");
	}
	if (!strcmp(builtin, "u$h: unset: `") && er_case == 0)
		fprintf(stderr, "%s\n", "unset: usage: unset [-f] [-v] [name ...]");
}

bool mx_error_export_unset(t_command *cmd, char *builtin) {
	int len = mx_str_arr_size(cmd->arguments);
	int sw = 0;

	if (cmd->arguments[0][0] == '-' && isalpha(cmd->arguments[0][1])) {
		export_unset_error(cmd->arguments[0], builtin, 0);
		return true;
	}
	if (!strcmp(cmd->arguments[0], "--") && !strcmp(cmd->arguments[1], "--")) {
		export_unset_error(cmd->arguments[0], builtin, 1);
		return true;
	}
	for (int i = len - 1; i != -1; i--) {
		if (!isalpha(cmd->arguments[i][0])) {
			export_unset_error(cmd->arguments[i], builtin, 1);
			sw = 1;
		}
	}
	if (sw == 1)
		return true;
	return false;
}
