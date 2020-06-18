#include "mx_builtins.h"

char **mx_copy_env(void) {
    extern char **environ;
    int size = mx_str_arr_size(environ);
    char **env = (char **)malloc(sizeof(char *) * size + 1);

    for (int i = 0; environ[i]; i++) {
        env[i] = strdup(environ[i]);
    }
    env[size] = NULL;
    return env;
}
