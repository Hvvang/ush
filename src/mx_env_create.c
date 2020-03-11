#include "ush.h"

void mx_env_create(t_env *env) {
	extern char **environ; //clear mem
	int arr_size = mx_get_array_size(environ);

	env->env = (char **)malloc(sizeof(char*) * arr_size + 1);
	for (int i = 0; i < arr_size; i++) {
		env->env[i] = (char*)malloc(sizeof(char) * strlen(environ[i]));
		env->env[i] = environ[i];
	}
	env->env[arr_size + 1] = NULL;
	env->exp = env->env; // копия env для масива export
}
