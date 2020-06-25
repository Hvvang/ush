#include "mx_shell.h"

t_hash_table *mx_init_env(void) {
    t_hash_table *hash_table = mx_create_hash_table();
    char **prompt = mx_get_prompt_mode();

    *prompt = strdup(MX_SHELL_PROMPT);
    mx_increment_shlvl(hash_table);
    mx_init_home(hash_table);
    mx_init_path(hash_table);
    mx_init_pwd(hash_table);
    mx_activate_signals();
    return hash_table;
}
