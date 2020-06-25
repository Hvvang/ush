#include "mx_shell.h"

static bool check_pwd(void) {
    char *real_path = realpath(getenv("PWD"), NULL);
    char temp[PATH_MAX];
    int res;

    getcwd(temp, PATH_MAX);
    if (getenv("PWD") && real_path)
        res = strcmp(real_path, temp);
    else
        res = 1;
    return res;
}

void mx_init_pwd(t_hash_table *hash_table) {
    if (getenv("PWD") == NULL || check_pwd()) {
        char path[PATH_MAX];
        char *pwd = mx_strjoin("PWD=", getcwd(path, PATH_MAX));
        char *oldpwd = mx_strjoin("OLDPWD=", getcwd(path, PATH_MAX));

        if (hash_table) {
            mx_push_to_export(pwd, hash_table);
            mx_push_to_export(oldpwd, hash_table);
        }
        else {
            setenv("PWD", path, 1);
            setenv("OLDPWD", path, 1);
        }
        mx_strdel(&pwd);
        mx_strdel(&oldpwd);
    }
}
