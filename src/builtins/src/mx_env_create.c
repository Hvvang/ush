#include "../inc/mx_builtins.h"

void mx_env_create(t_env *env) {
	extern char **environ; //clear mem
	int arr_size = mx_str_arr_size(environ);

	env->export = (char **)malloc(sizeof(char*) * arr_size + 1);
	for (int i = 0; i < arr_size; i++) {
		env->export[i] = mx_strdup(environ[i]);
	}
	env->export[arr_size + 1] = NULL;
	mx_quicksort(env->export, 0, arr_size - 1);
}
