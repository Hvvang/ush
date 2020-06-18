#include "mx_builtins.h"

void mx_set_env(char **env) {
    for (int i = 0; env[i]; i++) {
        int equal = mx_get_char_index(env[i], '=');
        char *key = strndup(env[i], equal);
        char *value = strdup(env[i] + equal + 1);;

        setenv(key, value, 1);
        mx_strdel(&key);
        mx_strdel(&value);
    }
}
