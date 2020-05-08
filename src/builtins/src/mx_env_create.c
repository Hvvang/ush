#include "../inc/mx_builtins.h"

void mx_env_create(t_env *env) {
	extern char **environ; //clear mem
	int arr_size = mx_str_arr_size(environ);

	env->exp = (char **)malloc(sizeof(char*) * arr_size + 1);
	for (int i = 0; i < arr_size; i++) {
		env->exp[i] = (char*)malloc(sizeof(char) * strlen(environ[i]));
		env->exp[i] = environ[i];
	}
	env->exp[arr_size + 1] = NULL;
}
