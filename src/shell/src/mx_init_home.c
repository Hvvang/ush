#include "mx_shell.h"

void mx_init_home(t_hash_table *hash_table) {
    if (getenv("HOME") == NULL) {
        struct passwd *pw = getpwuid(getuid());
        char *home = mx_strjoin("HOME=", pw->pw_dir);

        if (hash_table)
            mx_push_to_export(home, hash_table);
        else
            setenv("HOME", pw->pw_dir, 1);
        mx_strdel(&home);
    }
}
