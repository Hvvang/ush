#include "mx_shell.h"

void mx_init_pwd(t_hash_table *hash_table) {
    if (getenv("PWD") == NULL) {
        char path[PATH_MAX];
        char *pwd = mx_strjoin("PWD=", getcwd(path, PATH_MAX));
        char *oldpwd = mx_strjoin("OLDPWD=", getcwd(path, PATH_MAX));

        mx_push_to_export(pwd, hash_table);
        mx_push_to_export(oldpwd, hash_table);
        mx_strdel(&pwd);
        mx_strdel(&oldpwd);
    }
}
