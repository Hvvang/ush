#include "ush.h"

static void print_export(char *str) {
	int sw = 0;

	for (int i = 0; str[i]; i++)
		if (str[i] == '=')
			sw = 1;
	if (sw == 0)
		printf("%s\n", str);
	else { 
		for (int i = 0; str[i]; i++) {
			if (str[i] != '=')
				printf("%c", str[i]);
			else
				printf("%s", "=\"");
		}
		printf("%c", '\"');
		printf("\n");
	}
}

static bool mx_valid_export_unset(t_command *cmd) {
	if (!cmd->arguments[0])
		return true;
	if (!strcmp(cmd->arguments[0], "--") && !cmd->arguments[1])
		return true;
	return false;
}

static void mx_print_error(char *str) {
	fprintf(stderr, "%s", "u$h: export: `");
	fprintf(stderr, "%s", str);
	fprintf(stderr, "%s\n", "': not a valid identifier");
	fprintf(stderr, "%s", "export: usage: export [-nf]");
	fprintf(stderr, "%s\n", " [name[=value] ...] or export -p");
}

static bool mx_error_export_unset(t_command *cmd) {
	int len = mx_get_array_size(cmd->arguments);
	int sw = 0;
	
	for (int i = len - 1; i != -1; i--) {
		if (!isalpha(cmd->arguments[i][0])) {
			mx_print_error(cmd->arguments[i]);
			sw = 1;
		}
	}
	if (sw == 1)
		return true;
	return false;
}

void mx_export(t_command *cmd, t_env *env) {
	if (mx_valid_export_unset(cmd)) {
		// mx_bubble_sort(env->exp, mx_get_array_size(env->exp)); //вкл если надо
		for (int i = 0; env->exp[i]; i++) {
			printf("%s", "declare -x ");
			print_export(env->exp[i]);
		}
	}
	else if (mx_error_export_unset(cmd)) // если есть ошибки export no_alpha: 123 234 -- -- 
		return ;
	else
		mx_exp_add_argv(cmd, env);
	return ;
}
