#include "mx_builtins.h"

#define MX_IS_ENV(command) !strcmp(command, "env")
#define MX_NO_SUCH_FILE "env: %s: No such file or directory\n"

// static void env_print(void) {
//     extern char **environ;
//
//     mx_print_strarr(environ, "\n");
//     printf("\n");
// }

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

// static void exec_from_env(t_command *command,
//                           t_hash_table *hash_table,
//                           int index) {
//     extern char **environ;
//     char *path = check_path(command->arguments[index + 1],
//                             command->arguments[index]);
//
//     if (path) {
//         swap_command(command, command->arguments[index + 1], index + 2);
//         mx_launch_process(command, &hash_table->processes, path, environ);
//         mx_strdel(&path);
//     }
//     else if (command->arguments[index + 1]) {
//         setenv("status", "1", 1);
//         fprintf(stderr, MX_NO_SUCH_FILE, command->arguments[index + 1]);
//     }
// }


void mx_env(t_command *command, t_hash_table *hash_table) {
    int index = 0;
	char flag = mx_check_flags(MX_ENV, &index, command, mx_valid_env);
    char *path = NULL;
    extern char **environ;

    if (flag == 'P') {
        index++;
        path = check_path(command->arguments[index],
                          command->arguments[index - 1]);
    }
    else
        path = mx_get_path_to_bin(command->arguments[index]);

    if (flag == '0') {
        mx_launch_process(command, &hash_table->processes, path, environ);
        return;
    }
    else {
        swap_command(command, NULL, index + 1);
    }
}
