#include "mx_builtins.h"

#define MX_SHELL_BUILTIN ": shell built-in command"


static char **get_true_path(char *programm_name) {
    char **all_paths = get_paths(programm_name);

    if (mx_is_ush_builtins(programm_name) != -1 ||
        mx_get_type(programm_name) < 2) {
        int size = mx_str_arr_size(all_paths) + 2;

        all_paths = realloc(all_paths, sizeof(all_paths) + sizeof(char*) + 1);
        for (int i = size - 2; i > 0; i--){
            all_paths[i] = strdup(all_paths[i - 1]);
            free(all_paths[i - 1]);
        }
        all_paths[0] = (mx_get_type(programm_name) < 2) ?
                        strdup(programm_name) :
                        mx_strjoin(programm_name, MX_SHELL_BUILTIN);
        all_paths[size - 1] = NULL;
    }
    return all_paths;
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

    if (!command->arguments[index])
        setenv("status", "1", 1);
    else if (!atoi(getenv("status"))) {
        while (command->arguments[index]) {
            print_paths(command, index, flag);
            index++;
        }
    }
}
