#include "mx_exec.h"

#define MX_IS_EXEC(mode) (mode & S_IXUSR)

char *check_path(char *programm_name, char *path) {
    DIR *dir = opendir(path);
    struct stat stat;
    struct dirent *dirent;
    char *full_filename = NULL;

    if (dir) {
         while ((dirent = readdir(dir)) != NULL) {
             if (!strcmp(dirent->d_name, programm_name)) {
                 full_filename = mx_join_path(path, programm_name);
                 lstat(full_filename, &stat);
                 if (MX_IS_EXEC(stat.st_mode)) {
                     return full_filename;
                 }
                 free(full_filename);
             }
        }
        closedir(dir);
    }
    return full_filename;
}

char **get_paths(char *programm_name) {
    if (getenv("PATH")) {
        char **all_paths = mx_strsplit(getenv("PATH"), ':');
        int index = 0;

        if (all_paths) {
            for (int i = 0; all_paths[i]; i++) {
                char *temp = check_path(programm_name, all_paths[i]);

                free(all_paths[i]);
                if (temp) {
                    all_paths[index++] = mx_strdup(temp);
                    mx_strdel(&temp);
                }
            }
            all_paths = realloc(all_paths, sizeof(all_paths) + 1);
            all_paths[index] = NULL;
        }
        return all_paths;
    }
    return NULL;
}


char *mx_get_path_to_bin(char *programm_name) {
    char *true_path = NULL;

    if (mx_get_type(programm_name) < 2)
        true_path = strdup(programm_name);
    else {
        char **all_paths = get_paths(programm_name);

        if (all_paths) {
            for (unsigned i = 0; all_paths[i]; i++) {
                if (mx_get_type(all_paths[i]) < 2) {
                    true_path = strdup(all_paths[i]);
                    break;
                }
            }
            mx_del_strarr(&all_paths);
        }
    }
    return true_path;
}
