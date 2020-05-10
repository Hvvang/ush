#include "../inc/mx_builtins.h"

#define MX_SHELL_BUILTIN ": shell built-in command"

char **get_progs_paths(char *programm_name) {
    char *env_path = getenv("PATH");

    if (env_path) {
        char **paths = mx_strsplit(env_path, ':');
        char *programm_path = mx_strjoin("/", programm_name);

        for (unsigned i = 0; paths[i]; i++) {
            paths[i] = mx_strjoin(paths[i], programm_path);
        }
        return paths;
    }
    return NULL;
}

char **get_true_path(char *programm_name) {
    char **all_paths = get_progs_paths(programm_name);
    char **true_path = (char **)malloc(sizeof(char *));
    int index = 0;

    if (mx_is_ush_builtins(programm_name) != MX_NOT_A_USH_BUILTIN) {
        true_path[index] = malloc(sizeof(char *) + 1);
        true_path[index++] = mx_strjoin(programm_name, MX_SHELL_BUILTIN);
    }
    for (unsigned i = 0; all_paths[i]; i++) {
        if (mx_get_type(all_paths[i]) < 2) {
            true_path[index] = malloc(sizeof(char *) + 1);
            true_path[index++] = mx_strdup(all_paths[i]);
        }
    }
    true_path[index] = NULL;
    mx_del_strarr(&all_paths);
    return true_path;
}

static void print_paths(t_command *command, int index, char flag) {
    char **paths = get_true_path(command->arguments[index]);

    if (paths[0]) {
        printf("%s\n", paths[0]);
        if (flag == 'a')
            for (unsigned i = 1; paths[i]; i++)
                printf("%s\n", paths[i]);
        mx_del_strarr(&paths);
    }
    else {
        fprintf(stderr, "%s not found\n", command->arguments[index]);
        command->exit = 1;
    }
}

void mx_which(t_command *command) {
    int index = 0;
    char flag = mx_check_flags(MX_WHICH, &index, command, mx_valid_which);

    if (!command->exit) {
        if (flag != 's') {
            while (command->arguments[index]) {
                print_paths(command, index, flag);
                index++;
            }
        }
    }
}
