#include "mx_shell.h"

static void increment_shlvl(t_hash_table *hash_table) {
    int new_lvl = 1;
    int index = mx_find_key_index("SHLVL", hash_table, 0);
    char *curr_lvl = hash_table->export[index].value;
    char shlvl[NAME_MAX];
    char *arg[2] = {NULL, NULL};

    if (curr_lvl != NULL)
        new_lvl += atoi(curr_lvl);
    sprintf(shlvl, "SHLVL=%d", new_lvl);
    mx_push_to_export(shlvl, hash_table);
    mx_strdel(&arg[0]);
}

t_hash_table *mx_init_env(void) {
    t_hash_table *hash_table = mx_create_hash_table();

    increment_shlvl(hash_table);
    if (getenv("HOME") == NULL) {
        struct passwd *pw = getpwuid(getuid());
        char *home = mx_strjoin("HOME=", pw->pw_dir);

        mx_push_to_export(home, hash_table);
        mx_strdel(&home);
    }
    if (getenv("PATH") == NULL)
        mx_push_to_export(MX_DEFAULT_PATH, hash_table);
    return hash_table;
}
