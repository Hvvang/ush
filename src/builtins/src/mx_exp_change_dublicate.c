#include "../inc/mx_builtins.h"

static int not_variable(char *str) {
	for (int i = 0; str[i]; i++)
		if (str[i] == '=')
			return 0;
	return 1;
}

static char *is_variable(char *str) {
	int len = strlen(str);

	if (str[len - 1] == '=' && str[len] == '\0'){
		str = mx_strjoin(str, "\"\"");
		return str;
	}
	return str;
}

void mx_exp_change_dublicate(char *str, t_env *env, int index) {

	if (not_variable(str))
		return ;
	else {
		char *dst = mx_strdup(is_variable(str)); //leak

		env->exp[index] = (char*)malloc(sizeof(char) * strlen(dst));
		env->exp[index] = dst;
	}
}
