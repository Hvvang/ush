#include "mx_exec.h"

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

char *mx_get_path_to_bin(char *programm_name) {
    char **all_paths = split_PATH(programm_name);
    char *true_path = NULL;

    if (mx_get_type(programm_name) < 2)
        true_path = strdup(programm_name);
    else {
        for (unsigned i = 0; all_paths[i]; i++) {
            if (mx_get_type(all_paths[i]) < 2) {
                true_path = strdup(all_paths[i]);
                break;
            }
        }

    }
    mx_del_strarr(&all_paths);
    return true_path;
}
