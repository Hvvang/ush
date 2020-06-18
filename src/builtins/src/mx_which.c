#include "mx_builtins.h"

#define MX_SHELL_BUILTIN ": shell built-in command"

static char **split_PATH(char *programm_name) {
    char *hash_table_path = getenv("PATH");

    if (hash_table_path) {
        char **paths = mx_strsplit(hash_table_path, ':');

        for (unsigned i = 0; paths[i]; i++) {
            char *temp = strdup(paths[i]);

            free(paths[i]);
            paths[i] = mx_join_path(temp, programm_name);
            mx_strdel(&temp);
        }
        return paths;
    }
    return NULL;
}

static char **get_true_path(char *programm_name) {
    char **all_paths = split_PATH(programm_name);
    int size = mx_str_arr_size(all_paths) + 1;
    char **true_path = (char **)malloc(sizeof(char *) * size + 1);
    int index = 0;

    if (mx_is_ush_builtins(programm_name) != -1 ||
        mx_get_type(programm_name) < 2) {
        true_path[index++] = (mx_get_type(programm_name) < 2) ?
                            mx_strdup(programm_name) :
                            mx_strjoin(programm_name, MX_SHELL_BUILTIN);
    }
    for (unsigned i = 0; all_paths[i]; i++) {
        if (mx_get_type(all_paths[i]) < 2)
            true_path[index++] = mx_strdup(all_paths[i]);
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
        setenv("status", "1", 1);
    }
}

void mx_which(t_command *command) {
    int index = 0;
    char flag = mx_check_flags(MX_WHICH, &index, command, mx_valid_which);

    if (!atoi(getenv("status"))) {
        if (flag != 's') {
            while (command->arguments[index]) {
                print_paths(command, index, flag);
                index++;
            }
        }
    }
}
