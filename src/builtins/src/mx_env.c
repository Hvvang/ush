#include "mx_builtins.h"

#define MX_IS_ENV(command) !strcmp(command, "env")

static void env_print(void) {
    extern char **environ;

    mx_print_strarr(environ, "\n");
    printf("\n");
}

static void swap_command(t_command *command, char *def, int index) {
    if (command->arguments[index] || def) {
        free(command->command);
        command->command = (def) ?
                            strdup(def) :
                            strdup(command->arguments[index]);
        for (int i = 0; command->arguments[i]; i++) {
            free(command->arguments[i]);
            if (command->arguments[i + index])
                command->arguments[i] = strdup(command->arguments[i + index]);
            else
                command->arguments[i] = NULL;
        }
    }
}

static void exec_from_env(t_command *command,
                          t_hash_table *hash_table,
                          int index) {
    extern char **environ;
    char *path = mx_join_path(command->arguments[index],
                              command->arguments[index + 1]);

    swap_command(command, "ls", index + 2);
    mx_launch_process(command, &hash_table->processes, path, environ);
    mx_strdel(&path);
}


void mx_env(t_command *command, t_hash_table *hash_table) {
    int index = 0;
	char flag = mx_check_flags(MX_ENV, &index, command, mx_valid_env);
    int status = 0;

    if (flag == 'P') {
        exec_from_env(command, hash_table, index);
        return;
    }
    else if (flag == 'u')
        swap_command(command, "unset", index);
    else
        swap_command(command, NULL, index + 1);
    if (!command->arguments[index] && MX_IS_ENV(command->command))
		env_print();
    else
        mx_exec_command(command, hash_table, &status);
}
