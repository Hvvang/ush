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

void mx_export(t_command *cmd, t_env *env) {
	if (mx_valid_export_unset(cmd)) {
		mx_bubble_sort(env->exp, mx_get_array_size(env->exp)); //вкл если надо
		for (int i = 0; env->exp[i]; i++) {
			printf("%s", "declare -x ");
			print_export(env->exp[i]);
		}
	}
	else if (mx_error_export_unset(cmd, "u$h: export: `")) // если есть ошибки export no_alpha: 123 234 -- -- 
		return ;
	else
		mx_exp_add_argv(cmd, env);
	return ;
}
