#include "ush.h"

// static void create_new_env(t_env *env) {
	
// }

void mx_env_create(t_env *env) {
	extern char **environ; //clear mem
	int arr_size = mx_get_array_size(environ);

	// if (arr_size == 0)
	// 	create_new_env(env);
	env->env_ch = (char **)malloc(sizeof(char*) * arr_size + 1); //env cache
	for (int i = 0; i < arr_size; i++) {
		env->env_ch[i] = (char*)malloc(sizeof(char) * strlen(environ[i]));
		env->env_ch[i] = environ[i];
	}
		env->env_ch[arr_size + 1] = NULL;		
}
