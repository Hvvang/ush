#include "mx_builtins.h"

void mx_clear_env(void) {
    extern char **environ;

    if (environ) {
        for (int i = 0; environ[i]; i++) {
            int equal = mx_get_char_index(environ[i], '=');
            char *key = strndup(environ[i], equal);

            // printf("key = %s\n", key);
            unsetenv(key);
            mx_strdel(&key);
        }
    }
}
