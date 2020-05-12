#include "../inc/mx_builtins.h"

static void get_export_env(t_env *env) {
	// if (!env->export) {
		extern char **environ;
		int arr_size = mx_str_arr_size(environ);

		env->export = (char **)malloc(sizeof(char*) * arr_size + 1);
		for (int i = 0; i < arr_size; i++) {
			char **params = mx_strsplit(environ[i], '=');

			env->export[i] = mx_strdup(environ[i]);
			if (params[2]) {
				int index = strchr(env->export[i], '=') - env->export[i] + 1;

				mx_insert_char_to_str(env->export[i], '\'', index);
				mx_insert_char_to_str(env->export[i], '\'', strlen(env->export[i]));
			}
			mx_del_strarr(&params);
		}
		env->export[arr_size] = NULL;
	// }
}

void mx_env_create(t_env *env) {
	get_export_env(env);

}
